#!/usr/bin/env python3
"""
Merge accurate signatures from stubs into reconstructed files.

Usage:
    python3 merge_signatures.py re/decompiled/ re/reconstructed/ re/merged/

This script:
1. Reads the stub file (accurate signatures)
2. Reads the reconstructed file (inferred implementations)
3. Creates a merged file with correct signatures and implementations
4. Generates a mapping of parameter name changes for manual review

Project structure:
    k2plus/
    ├── re/
    │   ├── decompiled/      <- Stub files with accurate signatures
    │   ├── reconstructed/   <- Files with inferred implementations
    │   └── tools/           <- This script
    └── ...
"""

import ast
import sys
import re
from pathlib import Path


class SignatureExtractor(ast.NodeVisitor):
    """Extract method signatures from AST."""

    def __init__(self):
        self.classes = {}
        self.current_class = None

    def visit_ClassDef(self, node):
        self.current_class = node.name
        self.classes[node.name] = {'methods': {}, 'node': node}
        self.generic_visit(node)
        self.current_class = None

    def visit_FunctionDef(self, node):
        if self.current_class:
            params = []
            args = node.args

            # Get defaults offset
            num_defaults = len(args.defaults)
            num_args = len(args.args)
            defaults_start = num_args - num_defaults

            for i, arg in enumerate(args.args):
                param_info = {'name': arg.arg}
                if i >= defaults_start:
                    default_node = args.defaults[i - defaults_start]
                    try:
                        param_info['default'] = ast.literal_eval(default_node)
                    except:
                        param_info['default'] = ast.unparse(default_node)
                params.append(param_info)

            # *args
            if args.vararg:
                params.append({'name': args.vararg.arg, 'vararg': True})

            # **kwargs
            if args.kwarg:
                params.append({'name': args.kwarg.arg, 'kwarg': True})

            self.classes[self.current_class]['methods'][node.name] = {
                'params': params,
                'node': node,
                'lineno': node.lineno,
                'end_lineno': node.end_lineno,
            }


def extract_signatures(source_code):
    """Extract all class/method signatures from source code."""
    tree = ast.parse(source_code)
    extractor = SignatureExtractor()
    extractor.visit(tree)
    return extractor.classes


def format_param(param):
    """Format a parameter for output."""
    if param.get('vararg'):
        return f"*{param['name']}"
    if param.get('kwarg'):
        return f"**{param['name']}"

    name = param['name']
    if 'default' in param:
        default = param['default']
        if default is None:
            return f"{name}=None"
        elif isinstance(default, str):
            return f"{name}={repr(default)}"
        else:
            return f"{name}={default}"
    return name


def generate_param_mapping(stub_params, recon_params):
    """Generate mapping from reconstructed param names to stub param names."""
    mapping = {}

    # Skip 'self'
    stub_filtered = [p for p in stub_params if p['name'] != 'self' and not p.get('vararg') and not p.get('kwarg')]
    recon_filtered = [p for p in recon_params if p['name'] != 'self' and not p.get('vararg') and not p.get('kwarg')]

    # Simple positional mapping
    for i, (stub_p, recon_p) in enumerate(zip(stub_filtered, recon_filtered)):
        if stub_p['name'] != recon_p['name']:
            mapping[recon_p['name']] = stub_p['name']

    return mapping


def merge_files(stub_path, recon_path, output_path):
    """Merge stub signatures with reconstructed implementations."""

    with open(stub_path) as f:
        stub_source = f.read()

    with open(recon_path) as f:
        recon_source = f.read()

    stub_classes = extract_signatures(stub_source)
    recon_classes = extract_signatures(recon_source)

    # Track all param mappings for report
    all_mappings = {}

    # Start with reconstructed source and update signatures
    lines = recon_source.split('\n')

    # Process each class
    for class_name, stub_info in stub_classes.items():
        if class_name not in recon_classes:
            print(f"  Class {class_name} not in reconstructed file, skipping")
            continue

        recon_info = recon_classes[class_name]

        for method_name, stub_method in stub_info['methods'].items():
            if method_name not in recon_info['methods']:
                continue

            recon_method = recon_info['methods'][method_name]

            # Generate param mapping
            mapping = generate_param_mapping(stub_method['params'], recon_method['params'])
            if mapping:
                all_mappings[f"{class_name}.{method_name}"] = mapping

            # Build new signature
            new_params = ", ".join(format_param(p) for p in stub_method['params'])
            new_sig = f"def {method_name}({new_params}):"

            # Find and replace the old signature line
            old_lineno = recon_method['lineno'] - 1  # 0-indexed
            old_line = lines[old_lineno]

            # Preserve indentation
            indent = len(old_line) - len(old_line.lstrip())
            indent_str = old_line[:indent]

            # Replace the def line (may span multiple lines)
            lines[old_lineno] = indent_str + new_sig

    merged_source = '\n'.join(lines)

    # Add header comment about the merge
    header = '''# ===========================================================================
# MERGED FILE: Accurate signatures from live introspection + inferred implementations
#
# SIGNATURE SOURCE: Live printer introspection (ACCURATE)
# IMPLEMENTATION: Reverse engineered (INFERRED - may have errors)
#
# Parameter names in implementations may still use old names.
# See PARAM_MAPPING comments for required renames.
# ===========================================================================

'''

    # Write output
    with open(output_path, 'w') as f:
        f.write(header)
        f.write(merged_source)

    return all_mappings


def main():
    if len(sys.argv) < 4:
        print("Usage: merge_signatures.py stub_dir recon_dir output_dir")
        sys.exit(1)

    stub_dir = Path(sys.argv[1])
    recon_dir = Path(sys.argv[2])
    output_dir = Path(sys.argv[3])
    output_dir.mkdir(parents=True, exist_ok=True)

    # Find matching files
    stub_files = list(stub_dir.glob('*.py'))

    all_mappings = {}

    for stub_path in stub_files:
        module_name = stub_path.stem
        recon_path = recon_dir / f"{module_name}.py"

        if not recon_path.exists():
            print(f"No reconstructed file for {module_name}, copying stub")
            output_path = output_dir / f"{module_name}.py"
            with open(stub_path) as f:
                content = f.read()
            with open(output_path, 'w') as f:
                f.write(content)
            continue

        print(f"Merging {module_name}...")
        output_path = output_dir / f"{module_name}.py"

        try:
            mappings = merge_files(stub_path, recon_path, output_path)
            if mappings:
                all_mappings[module_name] = mappings
        except Exception as e:
            print(f"  Error: {e}")
            continue

    # Write mapping report
    if all_mappings:
        report_path = output_dir / "PARAM_MAPPINGS.md"
        with open(report_path, 'w') as f:
            f.write("# Parameter Name Mappings\n\n")
            f.write("These parameters need to be renamed in the implementation code:\n\n")

            for module, methods in all_mappings.items():
                f.write(f"## {module}\n\n")
                for method, mapping in methods.items():
                    f.write(f"### {method}\n")
                    for old, new in mapping.items():
                        f.write(f"- `{old}` -> `{new}`\n")
                    f.write("\n")

        print(f"\nParameter mapping report: {report_path}")


if __name__ == '__main__':
    main()
