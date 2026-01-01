// Ghidra script to export decompiled C code
// @category Export
// @author Claude Code

import ghidra.app.script.GhidraScript;
import ghidra.app.decompiler.DecompInterface;
import ghidra.app.decompiler.DecompileResults;
import ghidra.program.model.listing.Function;
import ghidra.program.model.listing.FunctionIterator;
import ghidra.util.task.ConsoleTaskMonitor;

import java.io.FileWriter;
import java.io.PrintWriter;

public class ExportDecompiled extends GhidraScript {
    @Override
    public void run() throws Exception {
        String programName = currentProgram.getName();
        String baseName = programName.replace(".cpython-39.so", "").replace(".so", "").replace(".o", "");
        String outputDir = "/home/gnydick/IdeaProjects/k2plus/decompiled/";
        String outputFile = outputDir + baseName + "_decompiled.c";

        DecompInterface decomp = new DecompInterface();
        decomp.openProgram(currentProgram);

        FunctionIterator funcIter = currentProgram.getFunctionManager().getFunctions(true);
        int funcCount = currentProgram.getFunctionManager().getFunctionCount();

        PrintWriter writer = new PrintWriter(new FileWriter(outputFile));
        writer.println("/*");
        writer.println(" * Decompiled from: " + programName);
        writer.println(" * Function count: " + funcCount);
        writer.println(" * Tool: Ghidra + Claude Code RE analysis");
        writer.println(" */\n");

        int processed = 0;
        while (funcIter.hasNext() && !monitor.isCancelled()) {
            Function func = funcIter.next();
            DecompileResults results = decomp.decompileFunction(func, 60, monitor);
            if (results != null && results.decompileCompleted()) {
                if (results.getDecompiledFunction() != null) {
                    writer.println("/* ============================================");
                    writer.println(" * Function: " + func.getName());
                    writer.printf(" * Address:  0x%x\n", func.getEntryPoint().getOffset());
                    writer.println(" * ============================================ */");
                    writer.println(results.getDecompiledFunction().getC());
                    writer.println("\n");
                }
            }
            processed++;
            if (processed % 100 == 0) {
                println("Processed " + processed + " / " + funcCount + " functions");
            }
        }
        writer.close();
        decomp.dispose();
        println("Exported: " + outputFile + " (" + funcCount + " functions)");
    }
}
