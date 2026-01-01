#!/usr/bin/env python3
"""
Compare introspected module signatures against reconstructed Python files.

Usage:
    python3 compare_signatures.py module_dump.json reconstructed/

This compares the actual method signatures from the live printer
against what we have in the reconstructed Python files.
"""

import sys
import os
import json
import ast
import argparse
from pathlib import Path


class ReconstructedAnalyzer(ast.NodeVisitor):
    """AST visitor to extract class and method info from reconstructed files."""

    def __init__(self):
        self.classes = {}
        self.functions = {}
        self.current_class = None

    def visit_ClassDef(self, node):
        class_info = {
            'name': node.name,
            'bases': [self._get_name(b) for b in node.bases],
            'methods': {},
            'line': node.lineno,
        }

        self.current_class = class_info
        self.generic_visit(node)
        self.current_class = None

        self.classes[node.name] = class_info

    def visit_FunctionDef(self, node):
        func_info = {
            'name': node.name,
            'params': self._extract_params(node.args),
            'line': node.lineno,
            'decorators': [self._get_name(d) for d in node.decorator_list],
        }

        if self.current_class:
            self.current_class['methods'][node.name] = func_info
        else:
            self.functions[node.name] = func_info

    def _extract_params(self, args):
        params = []

        # Regular args
        defaults_offset = len(args.args) - len(args.defaults)
        for i, arg in enumerate(args.args):
            param = {'name': arg.arg}
            default_idx = i - defaults_offset
            if default_idx >= 0:
                param['has_default'] = True
                try:
                    param['default'] = ast.literal_eval(args.defaults[default_idx])
                except:
                    param['default'] = ast.dump(args.defaults[default_idx])
            params.append(param)

        # *args
        if args.vararg:
            params.append({'name': args.vararg.arg, 'var_positional': True})

        # **kwargs
        if args.kwarg:
            params.append({'name': args.kwarg.arg, 'var_keyword': True})

        return params

    def _get_name(self, node):
        if isinstance(node, ast.Name):
            return node.id
        elif isinstance(node, ast.Attribute):
            return f"{self._get_name(node.value)}.{node.attr}"
        elif isinstance(node, ast.Call):
            return self._get_name(node.func)
        return ast.dump(node)


def analyze_reconstructed_file(filepath):
    """Parse a reconstructed Python file and extract structure."""
    with open(filepath, 'r') as f:
        source = f.read()

    try:
        tree = ast.parse(source)
        analyzer = ReconstructedAnalyzer()
        analyzer.visit(tree)
        return {
            'classes': analyzer.classes,
            'functions': analyzer.functions,
            'error': None,
        }
    except SyntaxError as e:
        return {'error': str(e)}


def compare_params(live_params, recon_params):
    """Compare parameter lists."""
    issues = []

    # Build lookup by name
    live_names = {p['name']: p for p in live_params}
    recon_names = {p['name']: p for p in recon_params}

    # Check for missing/extra params
    live_set = set(live_names.keys())
    recon_set = set(recon_names.keys())

    missing = live_set - recon_set
    extra = recon_set - live_set

    if missing:
        issues.append(f"Missing params: {missing}")
    if extra:
        issues.append(f"Extra params: {extra}")

    # Check defaults for common params
    for name in live_set & recon_set:
        live_p = live_names[name]
        recon_p = recon_names[name]

        if 'default' in live_p and 'default' not in recon_p:
            issues.append(f"Param '{name}' missing default (should be {live_p['default']})")
        elif 'default' in live_p and 'default' in recon_p:
            if str(live_p['default']) != str(recon_p['default']):
                issues.append(f"Param '{name}' default mismatch: live={live_p['default']} vs recon={recon_p['default']}")

    return issues


def compare_module(live_module, recon_data, module_name):
    """Compare a live module against reconstructed data."""
    results = {
        'module': module_name,
        'missing_classes': [],
        'extra_classes': [],
        'missing_methods': {},
        'extra_methods': {},
        'signature_mismatches': {},
    }

    if live_module.get('error'):
        results['live_error'] = live_module['error']
        return results

    if recon_data.get('error'):
        results['recon_error'] = recon_data['error']
        return results

    live_classes = set(live_module.get('classes', {}).keys())
    recon_classes = set(recon_data.get('classes', {}).keys())

    results['missing_classes'] = list(live_classes - recon_classes)
    results['extra_classes'] = list(recon_classes - live_classes)

    # Compare each class
    for class_name in live_classes & recon_classes:
        live_cls = live_module['classes'][class_name]
        recon_cls = recon_data['classes'][class_name]

        live_methods = set(live_cls.get('methods', {}).keys())
        recon_methods = set(recon_cls.get('methods', {}).keys())

        missing = live_methods - recon_methods
        extra = recon_methods - live_methods

        if missing:
            results['missing_methods'][class_name] = list(missing)
        if extra:
            results['extra_methods'][class_name] = list(extra)

        # Compare signatures for common methods
        for method_name in live_methods & recon_methods:
            live_method = live_cls['methods'][method_name]
            recon_method = recon_cls['methods'][method_name]

            live_sig = live_method.get('signature', {})
            if 'params' in live_sig:
                issues = compare_params(live_sig['params'], recon_method.get('params', []))
                if issues:
                    key = f"{class_name}.{method_name}"
                    results['signature_mismatches'][key] = issues

    return results


def main():
    parser = argparse.ArgumentParser(description='Compare introspected vs reconstructed')
    parser.add_argument('introspection_json', help='JSON from introspect_modules.py')
    parser.add_argument('reconstructed_dir', help='Directory with reconstructed .py files')
    parser.add_argument('--verbose', '-v', action='store_true', help='Show all comparisons')
    args = parser.parse_args()

    # Load introspection data
    with open(args.introspection_json) as f:
        live_data = json.load(f)

    recon_dir = Path(args.reconstructed_dir)

    print("=" * 70)
    print("SIGNATURE COMPARISON REPORT")
    print("=" * 70)
    print(f"Python version on printer: {live_data.get('python_version', 'unknown')}")
    print()

    total_issues = 0

    for module_name, live_module in live_data.get('modules', {}).items():
        # Find corresponding reconstructed file
        recon_file = recon_dir / f"{module_name}.py"

        if not recon_file.exists():
            print(f"\n[{module_name}] MISSING - No reconstructed file found")
            total_issues += 1
            continue

        recon_data = analyze_reconstructed_file(recon_file)
        results = compare_module(live_module, recon_data, module_name)

        # Report results
        issues_found = False
        output = []

        if results.get('live_error'):
            output.append(f"  Live module error: {results['live_error']}")
            issues_found = True

        if results.get('recon_error'):
            output.append(f"  Reconstructed file error: {results['recon_error']}")
            issues_found = True

        if results['missing_classes']:
            output.append(f"  Missing classes: {results['missing_classes']}")
            issues_found = True

        if results['extra_classes']:
            output.append(f"  Extra classes (not in live): {results['extra_classes']}")
            issues_found = True

        for cls, methods in results['missing_methods'].items():
            output.append(f"  {cls}: Missing methods: {methods}")
            issues_found = True

        for cls, methods in results['extra_methods'].items():
            output.append(f"  {cls}: Extra methods (not in live): {methods}")
            issues_found = True

        for method, issues in results['signature_mismatches'].items():
            for issue in issues:
                output.append(f"  {method}: {issue}")
            issues_found = True

        if issues_found:
            print(f"\n[{module_name}] ISSUES FOUND:")
            for line in output:
                print(line)
            total_issues += len(output)
        elif args.verbose:
            print(f"\n[{module_name}] OK")

    print()
    print("=" * 70)
    if total_issues == 0:
        print("All signatures match!")
    else:
        print(f"Found {total_issues} issues to investigate")
    print("=" * 70)


if __name__ == '__main__':
    main()
