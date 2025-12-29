# Ghidra script to export decompiled C code
# @category Export
# @author Claude Code

from ghidra.app.decompiler import DecompInterface
from ghidra.util.task import ConsoleTaskMonitor
import os

def run():
    program_name = currentProgram.getName()
    base_name = program_name.replace(".cpython-39.so", "").replace(".so", "").replace(".o", "")
    output_dir = "/home/gnydick/IdeaProjects/k2plus/decompiled/"
    output_file = output_dir + base_name + "_decompiled.c"

    decomp = DecompInterface()
    decomp.openProgram(currentProgram)
    monitor = ConsoleTaskMonitor()

    func_manager = currentProgram.getFunctionManager()
    func_count = func_manager.getFunctionCount()

    with open(output_file, 'w') as f:
        f.write("/*\n")
        f.write(" * Decompiled from: %s\n" % program_name)
        f.write(" * Function count: %d\n" % func_count)
        f.write(" * Tool: Ghidra + Claude Code RE analysis\n")
        f.write(" */\n\n")

        processed = 0
        for func in func_manager.getFunctions(True):
            if monitor.isCancelled():
                break

            results = decomp.decompileFunction(func, 60, monitor)
            if results and results.decompileCompleted():
                decomp_func = results.getDecompiledFunction()
                if decomp_func:
                    f.write("/* ============================================\n")
                    f.write(" * Function: %s\n" % func.getName())
                    f.write(" * Address:  0x%x\n" % func.getEntryPoint().getOffset())
                    f.write(" * ============================================ */\n")
                    f.write(decomp_func.getC())
                    f.write("\n\n")

            processed += 1
            if processed % 100 == 0:
                print("Processed %d / %d functions" % (processed, func_count))

    print("Exported: %s (%d functions)" % (output_file, func_count))

run()
