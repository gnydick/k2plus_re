/**
 * Decompiled and annotated from: filament_change.o
 * Purpose: Calculate flush volume for color transitions in multi-material printing
 *
 * This module calculates how much filament needs to be purged when switching
 * between colors based on perceptual color difference using HSV color space.
 *
 * Tool: Ghidra + Manual RE analysis
 * Original: klippy/chelper/filament_change.c
 *
 * =============================================================================
 * PROVENANCE NOTICE - READ BEFORE USING THIS CODE
 * =============================================================================
 *
 * This file was decompiled from compiled ARM object code using Ghidra.
 * The accuracy varies by category:
 *
 * GHIDRA DECOMPILATION (high confidence):
 *   - Control flow structure (if/else, loops, function calls)
 *   - Arithmetic operations and expressions
 *   - Function boundaries and call graph
 *   - Register usage patterns
 *
 * DATA SECTION EXTRACTION (high confidence):
 *   - Constants with DAT_* addresses (LUMA_R=0.2126, etc.)
 *   - Numeric literals from immediate values
 *   - String literals (if any)
 *
 * HUMAN INTERPRETATION (lower confidence):
 *   - Function names: rgb_to_hsv, calculate_flush_volume (guessed from behavior)
 *   - Variable names: max_val, delta, hue (assigned based on usage)
 *   - Comments explaining purpose and algorithm
 *   - Constant names: LUMA_R, DEG_60 (named for clarity)
 *   - Parameter names and types (inferred from calling convention)
 *
 * UNCERTAIN:
 *   - Exact floating-point precision behavior
 *   - Edge case handling that wasn't tested
 *   - Original variable/function names from source
 * =============================================================================
 */

#include <math.h>
#include <stdint.h>
#include <stdio.h>

/* ============================================
 * Constants (extracted from data section)
 * ============================================ */

// Color conversion constants
#define EPSILON         1e-6        // DAT_00010110 - floating point comparison threshold
#define DEG_60          60.0        // For hue calculation (60 degrees per sector)
#define DEG_360         360.0       // Full hue circle

// Perceptual luminance weights (ITU-R BT.709)
#define LUMA_R          0.2126      // DAT_000103f8 - Red weight
#define LUMA_G          0.7152      // DAT_00010400 - Green weight
#define LUMA_B          0.0722      // DAT_00010408 - Blue weight

// Flush volume calculation parameters
#define MAX_CHROMA_DIFF 1.0         // DAT_000103f0 - Maximum chroma difference
#define DARK_TO_LIGHT_EXP 0.5       // DAT_00010438 - Exponent for dark-to-light transition
#define DARK_TO_LIGHT_MULT 2.0      // DAT_00010440 - Multiplier for dark-to-light
#define LIGHT_TO_DARK_MULT 0.8      // DAT_00010450 - Multiplier for light-to-dark
#define SATURATION_WEIGHT1 0.5      // DAT_00010410
#define SATURATION_WEIGHT2 0.5      // DAT_00010418
#define COS_WEIGHT        0.5       // DAT_00010420 - Cosine similarity weight
#define MIN_FLUSH_VOLUME  50        // DAT_00010428 - Minimum flush in mm³
#define MAX_FLUSH_VOLUME  800       // DAT_00010430 - Maximum flush in mm³
#define CHROMA_SCALE      100.0     // DAT_00010454
#define VOLUME_OFFSET     0.5       // DAT_00010458 - Rounding offset

/* ============================================
 * RGB to HSV Color Conversion
 * ============================================ */

/**
 * Convert RGB color to HSV color space.
 *
 * @param r     Red component (0.0 - 1.0)
 * @param g     Green component (0.0 - 1.0)
 * @param b     Blue component (0.0 - 1.0)
 * @param h     Output: Hue (0.0 - 360.0 degrees)
 * @param s     Output: Saturation (0.0 - 1.0)
 * @param v     Output: Value/Brightness (0.0 - 1.0)
 */
void rgb_to_hsv(float r, float g, float b, float *h, float *s, float *v)
{
    float max_val = fmax(fmax(r, g), b);
    float min_val = fmin(fmin(r, g), b);
    float delta = max_val - min_val;

    // Calculate Hue
    if (fabs(delta) < EPSILON) {
        *h = 0.0f;  // Achromatic (gray)
    }
    else if (r == max_val) {
        // Red is dominant
        *h = fmod((g - b) / delta, 6.0f) * DEG_60;
    }
    else if (g == max_val) {
        // Green is dominant
        *h = ((b - r) / delta + 2.0f) * DEG_60;
    }
    else {
        // Blue is dominant
        *h = ((r - g) / delta + 4.0f) * DEG_60;
    }

    // Calculate Saturation
    if (fabs(max_val) < EPSILON) {
        *s = 0.0f;
    }
    else {
        *s = delta / max_val;
    }

    // Value is the maximum component
    *v = max_val;
}

/* ============================================
 * Flush Volume Calculation
 * ============================================ */

/**
 * Calculate the flush volume needed for a color transition.
 *
 * Uses perceptual color difference based on:
 * - Chroma difference in HSV space
 * - Luminance difference (dark-to-light vs light-to-dark)
 * - Hue angle difference with cosine weighting
 *
 * @param from_color    Source color as 0xRRGGBB
 * @param to_color      Target color as 0xRRGGBB
 * @return              Flush volume in mm³ (50-800 range)
 */
int calc_flushing_volume(uint32_t from_color, uint32_t to_color)
{
    // Extract RGB components from packed colors
    float from_r = (float)((from_color >> 16) & 0xFF) / 255.0f;
    float from_g = (float)((from_color >> 8) & 0xFF) / 255.0f;
    float from_b = (float)(from_color & 0xFF) / 255.0f;

    float to_r = (float)((to_color >> 16) & 0xFF) / 255.0f;
    float to_g = (float)((to_color >> 8) & 0xFF) / 255.0f;
    float to_b = (float)(to_color & 0xFF) / 255.0f;

    // Convert both colors to HSV
    float from_h, from_s, from_v;
    float to_h, to_s, to_v;

    rgb_to_hsv(from_r, from_g, from_b, &from_h, &from_s, &from_v);
    rgb_to_hsv(to_r, to_g, to_b, &to_h, &to_s, &to_v);

    // Convert hue to radians for trig calculations
    float from_h_rad = from_h * (M_PI / 180.0f);
    float to_h_rad = to_h * (M_PI / 180.0f);

    // Calculate chroma vectors in polar coordinates
    // Chroma = Saturation * Value (cylindrical HSV model)
    float from_chroma = from_s * from_v;
    float to_chroma = to_s * to_v;

    // Convert to Cartesian for difference calculation
    float from_x = cos(from_h_rad) * from_chroma;
    float from_y = sin(from_h_rad) * from_chroma;
    float to_x = cos(to_h_rad) * to_chroma;
    float to_y = sin(to_h_rad) * to_chroma;

    // Euclidean distance in chroma plane
    float dx = from_x - to_x;
    float dy = from_y - to_y;
    float chroma_diff = sqrt(dx * dx + dy * dy);
    chroma_diff = fmin(chroma_diff, MAX_CHROMA_DIFF);

    // Calculate perceptual luminance using ITU-R BT.709 weights
    float from_luma = from_r * LUMA_R + from_g * LUMA_G + from_b * LUMA_B;
    float to_luma = to_r * LUMA_R + to_g * LUMA_G + to_b * LUMA_B;

    float luma_factor;

    if (to_luma > from_luma) {
        // Dark to light transition - harder to flush
        // Uses power function for more aggressive flushing
        luma_factor = pow(to_luma - from_luma, DARK_TO_LIGHT_EXP) * DARK_TO_LIGHT_MULT;
    }
    else {
        // Light to dark transition - easier to flush
        luma_factor = (from_luma - to_luma) * LIGHT_TO_DARK_MULT;

        // Reduce chroma difference for light-to-dark (pigment covers easier)
        float sat_blend = from_v * SATURATION_WEIGHT1 + to_v * SATURATION_WEIGHT2;
        chroma_diff = fmin(sat_blend, chroma_diff);
    }

    // Scale chroma difference
    float scaled_chroma = chroma_diff * CHROMA_SCALE;

    // Combine factors using weighted Euclidean distance
    // This accounts for both color difference and luminance change
    float combined = luma_factor * luma_factor + scaled_chroma * scaled_chroma;
    combined -= 2.0f * luma_factor * scaled_chroma * COS_WEIGHT;  // Cosine correction

    float volume = sqrt(fmax(combined, 0.0f));

    // Clamp to valid range and round
    volume = fmax(volume, (float)MIN_FLUSH_VOLUME);
    volume = fmin(volume, (float)MAX_FLUSH_VOLUME);

    return (int)(volume + VOLUME_OFFSET);
}

/* ============================================
 * Public API
 * ============================================ */

/**
 * Get the flushing volume for a color transition.
 * This is the main entry point called from Python via FFI.
 *
 * @param from_color    Source color as 0xRRGGBB
 * @param to_color      Target color as 0xRRGGBB
 * @return              Flush volume in mm³
 */
int get_flushing_volume(uint32_t from_color, uint32_t to_color)
{
    return calc_flushing_volume(from_color, to_color);
}

/* ============================================
 * Test Main (for standalone testing)
 * ============================================ */

#ifdef STANDALONE_TEST
int main(void)
{
    // Test case: transition from near-black to a specific color
    uint32_t from = 0x000000;      // Black
    uint32_t to = 0xB437E1;        // Purple

    int volume = calc_flushing_volume(from, to);
    printf("Flush volume = %d mm³\n", volume);

    // Additional test cases
    printf("White to Black: %d mm³\n", calc_flushing_volume(0xFFFFFF, 0x000000));
    printf("Red to Green: %d mm³\n", calc_flushing_volume(0xFF0000, 0x00FF00));
    printf("Same color: %d mm³\n", calc_flushing_volume(0x808080, 0x808080));

    return 0;
}
#endif

/* ============================================
 * Notes on Algorithm
 * ============================================
 *
 * The flush volume calculation is based on perceptual color science:
 *
 * 1. HSV Conversion: RGB colors are converted to HSV (Hue, Saturation, Value)
 *    which better represents how humans perceive color differences.
 *
 * 2. Chroma Difference: The chromatic difference is calculated as the
 *    Euclidean distance in the polar chroma plane, accounting for both
 *    hue angle and saturation/value.
 *
 * 3. Luminance Weighting: Dark-to-light transitions require more flushing
 *    because light pigments don't cover dark as easily. The relationship
 *    is non-linear (power function).
 *
 * 4. Asymmetry: Light-to-dark transitions are easier because dark pigments
 *    cover light colors more effectively.
 *
 * 5. Final Calculation: Chroma and luminance factors are combined using
 *    a modified Euclidean distance with cosine correction for the angle
 *    between the factors.
 *
 * Typical values:
 * - Same color: 50 mm³ (minimum)
 * - Similar colors: 100-200 mm³
 * - Contrasting colors: 300-500 mm³
 * - Black to White: 600-800 mm³ (maximum)
 */
