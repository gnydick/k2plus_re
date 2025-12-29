/*
 * Decompiled from: box_wrapper.cpython-39.so
 * Function count: 698
 * Tool: Ghidra + Claude Code RE analysis
 *
 * =============================================================================
 * PROVENANCE NOTICE - RAW GHIDRA OUTPUT
 * =============================================================================
 *
 * This file contains RAW GHIDRA DECOMPILER OUTPUT with minimal cleanup.
 * It was decompiled from a compiled Cython extension (.cpython-39.so).
 *
 * WARNING: This is NOT production-quality code. It is provided for reference
 * only to understand the binary structure.
 *
 * WHAT THIS FILE CONTAINS:
 *   - Raw Ghidra decompilation of all 698 functions
 *   - Function addresses (e.g., 0x1b124)
 *   - PLT stubs for external Python/C library calls
 *   - FUN_* placeholder names for internal functions
 *   - PTR_* references to global data
 *
 * WHAT IS MISSING:
 *   - Meaningful function names (only FUN_XXXXXX)
 *   - Variable names (only local_*, param_*, etc.)
 *   - Type information beyond basic primitives
 *   - Comments explaining logic
 *   - Structure definitions
 *
 * HOW TO USE THIS FILE:
 *   - Cross-reference with strings extracted via `strings` command
 *   - Match FUN_* addresses to known Cython patterns
 *   - Use Python module introspection alongside this decompilation
 *   - Refer to the reconstructed Python file for high-level understanding
 *
 * For the cleaned-up Python reconstruction, see:
 *   reconstructed/box_wrapper.py
 * =============================================================================
 */

/* ============================================
 * Function: _DT_INIT
 * Address:  0x1b124
 * ============================================ */

void _DT_INIT(void)

{
  FUN_00035764();
  return;
}




/* ============================================
 * Function: PyUnicode_FromFormat
 * Address:  0x1b144
 * ============================================ */

void PyUnicode_FromFormat(void)

{
  (*(code *)PTR_PyUnicode_FromFormat_001b3d24)();
  return;
}




/* ============================================
 * Function: PyObject_SetItem
 * Address:  0x1b150
 * ============================================ */

void PyObject_SetItem(void)

{
  (*(code *)PTR_PyObject_SetItem_001b3d28)();
  return;
}




/* ============================================
 * Function: PyList_New
 * Address:  0x1b15c
 * ============================================ */

void PyList_New(void)

{
  (*(code *)PTR_PyList_New_001b3d2c)();
  return;
}




/* ============================================
 * Function: _PyUnicode_Ready
 * Address:  0x1b168
 * ============================================ */

void _PyUnicode_Ready(void)

{
  (*(code *)PTR__PyUnicode_Ready_001b3d30)();
  return;
}




/* ============================================
 * Function: raise
 * Address:  0x1b174
 * ============================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int raise(int __sig)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_raise_001b3d34)(__sig);
  return iVar1;
}




/* ============================================
 * Function: PyDict_SetItemString
 * Address:  0x1b180
 * ============================================ */

void PyDict_SetItemString(void)

{
  (*(code *)PTR_PyDict_SetItemString_001b3d38)();
  return;
}




/* ============================================
 * Function: PyDict_Size
 * Address:  0x1b18c
 * ============================================ */

void PyDict_Size(void)

{
  (*(code *)PTR_PyDict_Size_001b3d3c)();
  return;
}




/* ============================================
 * Function: PyException_SetTraceback
 * Address:  0x1b198
 * ============================================ */

void PyException_SetTraceback(void)

{
  (*(code *)PTR_PyException_SetTraceback_001b3d40)();
  return;
}




/* ============================================
 * Function: __cxa_finalize
 * Address:  0x1b1a4
 * ============================================ */

void __cxa_finalize(void)

{
  (*(code *)PTR___cxa_finalize_001b3d44)();
  return;
}




/* ============================================
 * Function: _PyFloat_FormatAdvancedWriter
 * Address:  0x1b1b0
 * ============================================ */

void _PyFloat_FormatAdvancedWriter(void)

{
  (*(code *)PTR__PyFloat_FormatAdvancedWriter_001b3d48)();
  return;
}




/* ============================================
 * Function: PyObject_Format
 * Address:  0x1b1bc
 * ============================================ */

void PyObject_Format(void)

{
  (*(code *)PTR_PyObject_Format_001b3d4c)();
  return;
}




/* ============================================
 * Function: PyNumber_Lshift
 * Address:  0x1b1c8
 * ============================================ */

void PyNumber_Lshift(void)

{
  (*(code *)PTR_PyNumber_Lshift_001b3d50)();
  return;
}




/* ============================================
 * Function: PyObject_ClearWeakRefs
 * Address:  0x1b1d4
 * ============================================ */

void PyObject_ClearWeakRefs(void)

{
  (*(code *)PTR_PyObject_ClearWeakRefs_001b3d54)();
  return;
}




/* ============================================
 * Function: _PyThreadState_UncheckedGet
 * Address:  0x1b1e0
 * ============================================ */

void _PyThreadState_UncheckedGet(void)

{
  (*(code *)PTR__PyThreadState_UncheckedGet_001b3d58)();
  return;
}




/* ============================================
 * Function: Py_EnterRecursiveCall
 * Address:  0x1b1f8
 * ============================================ */

void Py_EnterRecursiveCall(void)

{
  (*(code *)PTR_Py_EnterRecursiveCall_001b3d60)();
  return;
}




/* ============================================
 * Function: PyFrame_New
 * Address:  0x1b204
 * ============================================ */

void PyFrame_New(void)

{
  (*(code *)PTR_PyFrame_New_001b3d64)();
  return;
}




/* ============================================
 * Function: PyNumber_InPlaceAdd
 * Address:  0x1b210
 * ============================================ */

void PyNumber_InPlaceAdd(void)

{
  (*(code *)PTR_PyNumber_InPlaceAdd_001b3d68)();
  return;
}




/* ============================================
 * Function: PyNumber_Add
 * Address:  0x1b21c
 * ============================================ */

void PyNumber_Add(void)

{
  (*(code *)PTR_PyNumber_Add_001b3d6c)();
  return;
}




/* ============================================
 * Function: PyObject_GetAttrString
 * Address:  0x1b228
 * ============================================ */

void PyObject_GetAttrString(void)

{
  (*(code *)PTR_PyObject_GetAttrString_001b3d70)();
  return;
}




/* ============================================
 * Function: PyUnicode_Join
 * Address:  0x1b234
 * ============================================ */

void PyUnicode_Join(void)

{
  (*(code *)PTR_PyUnicode_Join_001b3d74)();
  return;
}




/* ============================================
 * Function: PyDict_Contains
 * Address:  0x1b240
 * ============================================ */

void PyDict_Contains(void)

{
  (*(code *)PTR_PyDict_Contains_001b3d78)();
  return;
}




/* ============================================
 * Function: PyImport_AddModule
 * Address:  0x1b24c
 * ============================================ */

void PyImport_AddModule(void)

{
  (*(code *)PTR_PyImport_AddModule_001b3d7c)();
  return;
}




/* ============================================
 * Function: PyBytes_FromStringAndSize
 * Address:  0x1b258
 * ============================================ */

void PyBytes_FromStringAndSize(void)

{
  (*(code *)PTR_PyBytes_FromStringAndSize_001b3d80)();
  return;
}




/* ============================================
 * Function: memcpy
 * Address:  0x1b264
 * ============================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memcpy(void *__dest,void *__src,size_t __n)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_memcpy_001b3d84)(__dest);
  return pvVar1;
}




/* ============================================
 * Function: PyObject_SetAttrString
 * Address:  0x1b270
 * ============================================ */

void PyObject_SetAttrString(void)

{
  (*(code *)PTR_PyObject_SetAttrString_001b3d88)();
  return;
}




/* ============================================
 * Function: PyErr_WarnEx
 * Address:  0x1b27c
 * ============================================ */

void PyErr_WarnEx(void)

{
  (*(code *)PTR_PyErr_WarnEx_001b3d8c)();
  return;
}




/* ============================================
 * Function: PyModule_NewObject
 * Address:  0x1b294
 * ============================================ */

void PyModule_NewObject(void)

{
  (*(code *)PTR_PyModule_NewObject_001b3d94)();
  return;
}




/* ============================================
 * Function: PyErr_SetObject
 * Address:  0x1b2ac
 * ============================================ */

void PyErr_SetObject(void)

{
  (*(code *)PTR_PyErr_SetObject_001b3d9c)();
  return;
}




/* ============================================
 * Function: PyErr_NormalizeException
 * Address:  0x1b2c4
 * ============================================ */

void PyErr_NormalizeException(void)

{
  (*(code *)PTR_PyErr_NormalizeException_001b3da4)();
  return;
}




/* ============================================
 * Function: _PyObject_CallFunction_SizeT
 * Address:  0x1b2d0
 * ============================================ */

void _PyObject_CallFunction_SizeT(void)

{
  (*(code *)PTR__PyObject_CallFunction_SizeT_001b3da8)();
  return;
}




/* ============================================
 * Function: PyIter_Next
 * Address:  0x1b2dc
 * ============================================ */

void PyIter_Next(void)

{
  (*(code *)PTR_PyIter_Next_001b3dac)();
  return;
}




/* ============================================
 * Function: PyNumber_Multiply
 * Address:  0x1b2e8
 * ============================================ */

void PyNumber_Multiply(void)

{
  (*(code *)PTR_PyNumber_Multiply_001b3db0)();
  return;
}




/* ============================================
 * Function: memcmp
 * Address:  0x1b2f4
 * ============================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

int memcmp(void *__s1,void *__s2,size_t __n)

{
  int iVar1;
  
  iVar1 = (*(code *)PTR_memcmp_001b3db4)(__s1);
  return iVar1;
}




/* ============================================
 * Function: _PyUnicodeWriter_Dealloc
 * Address:  0x1b300
 * ============================================ */

void _PyUnicodeWriter_Dealloc(void)

{
  (*(code *)PTR__PyUnicodeWriter_Dealloc_001b3db8)();
  return;
}




/* ============================================
 * Function: PyObject_RichCompare
 * Address:  0x1b30c
 * ============================================ */

void PyObject_RichCompare(void)

{
  (*(code *)PTR_PyObject_RichCompare_001b3dbc)();
  return;
}




/* ============================================
 * Function: PyCode_New
 * Address:  0x1b318
 * ============================================ */

void PyCode_New(void)

{
  (*(code *)PTR_PyCode_New_001b3dc0)();
  return;
}




/* ============================================
 * Function: _PyGen_Send
 * Address:  0x1b324
 * ============================================ */

void _PyGen_Send(void)

{
  (*(code *)PTR__PyGen_Send_001b3dc4)();
  return;
}




/* ============================================
 * Function: PyImport_GetModuleDict
 * Address:  0x1b330
 * ============================================ */

void PyImport_GetModuleDict(void)

{
  (*(code *)PTR_PyImport_GetModuleDict_001b3dc8)();
  return;
}




/* ============================================
 * Function: PyObject_GC_Track
 * Address:  0x1b33c
 * ============================================ */

void PyObject_GC_Track(void)

{
  (*(code *)PTR_PyObject_GC_Track_001b3dcc)();
  return;
}




/* ============================================
 * Function: PyNumber_Long
 * Address:  0x1b348
 * ============================================ */

void PyNumber_Long(void)

{
  (*(code *)PTR_PyNumber_Long_001b3dd0)();
  return;
}




/* ============================================
 * Function: PyErr_GivenExceptionMatches
 * Address:  0x1b354
 * ============================================ */

void PyErr_GivenExceptionMatches(void)

{
  (*(code *)PTR_PyErr_GivenExceptionMatches_001b3dd4)();
  return;
}




/* ============================================
 * Function: PyErr_SetString
 * Address:  0x1b360
 * ============================================ */

void PyErr_SetString(void)

{
  (*(code *)PTR_PyErr_SetString_001b3dd8)();
  return;
}




/* ============================================
 * Function: PyObject_DelItem
 * Address:  0x1b36c
 * ============================================ */

void PyObject_DelItem(void)

{
  (*(code *)PTR_PyObject_DelItem_001b3ddc)();
  return;
}




/* ============================================
 * Function: PyMethod_New
 * Address:  0x1b378
 * ============================================ */

void PyMethod_New(void)

{
  (*(code *)PTR_PyMethod_New_001b3de0)();
  return;
}




/* ============================================
 * Function: _PyObject_GC_New
 * Address:  0x1b384
 * ============================================ */

void _PyObject_GC_New(void)

{
  (*(code *)PTR__PyObject_GC_New_001b3de4)();
  return;
}




/* ============================================
 * Function: PyObject_GetItem
 * Address:  0x1b390
 * ============================================ */

void PyObject_GetItem(void)

{
  (*(code *)PTR_PyObject_GetItem_001b3de8)();
  return;
}




/* ============================================
 * Function: PyObject_Malloc
 * Address:  0x1b39c
 * ============================================ */

void PyObject_Malloc(void)

{
  (*(code *)PTR_PyObject_Malloc_001b3dec)();
  return;
}




/* ============================================
 * Function: PyInterpreterState_GetID
 * Address:  0x1b3a8
 * ============================================ */

void PyInterpreterState_GetID(void)

{
  (*(code *)PTR_PyInterpreterState_GetID_001b3df0)();
  return;
}




/* ============================================
 * Function: PyEval_EvalFrameEx
 * Address:  0x1b3b4
 * ============================================ */

void PyEval_EvalFrameEx(void)

{
  (*(code *)PTR_PyEval_EvalFrameEx_001b3df4)();
  return;
}




/* ============================================
 * Function: PySequence_Contains
 * Address:  0x1b3c0
 * ============================================ */

void PySequence_Contains(void)

{
  (*(code *)PTR_PySequence_Contains_001b3df8)();
  return;
}




/* ============================================
 * Function: PyTuple_GetItem
 * Address:  0x1b3cc
 * ============================================ */

void PyTuple_GetItem(void)

{
  (*(code *)PTR_PyTuple_GetItem_001b3dfc)();
  return;
}




/* ============================================
 * Function: PyMem_Realloc
 * Address:  0x1b3d8
 * ============================================ */

void PyMem_Realloc(void)

{
  (*(code *)PTR_PyMem_Realloc_001b3e00)();
  return;
}




/* ============================================
 * Function: PyErr_SetNone
 * Address:  0x1b3e4
 * ============================================ */

void PyErr_SetNone(void)

{
  (*(code *)PTR_PyErr_SetNone_001b3e04)();
  return;
}




/* ============================================
 * Function: PyErr_ExceptionMatches
 * Address:  0x1b3f0
 * ============================================ */

void PyErr_ExceptionMatches(void)

{
  (*(code *)PTR_PyErr_ExceptionMatches_001b3e08)();
  return;
}




/* ============================================
 * Function: PyOS_snprintf
 * Address:  0x1b3fc
 * ============================================ */

void PyOS_snprintf(void)

{
  (*(code *)PTR_PyOS_snprintf_001b3e0c)();
  return;
}




/* ============================================
 * Function: PyTraceBack_Here
 * Address:  0x1b408
 * ============================================ */

void PyTraceBack_Here(void)

{
  (*(code *)PTR_PyTraceBack_Here_001b3e10)();
  return;
}




/* ============================================
 * Function: _PyUnicodeWriter_Init
 * Address:  0x1b414
 * ============================================ */

void _PyUnicodeWriter_Init(void)

{
  (*(code *)PTR__PyUnicodeWriter_Init_001b3e14)();
  return;
}




/* ============================================
 * Function: PyObject_CallFinalizerFromDealloc
 * Address:  0x1b420
 * ============================================ */

void PyObject_CallFinalizerFromDealloc(void)

{
  (*(code *)PTR_PyObject_CallFinalizerFromDealloc_001b3e18)();
  return;
}




/* ============================================
 * Function: PyObject_Not
 * Address:  0x1b42c
 * ============================================ */

void PyObject_Not(void)

{
  (*(code *)PTR_PyObject_Not_001b3e1c)();
  return;
}




/* ============================================
 * Function: PyObject_Free
 * Address:  0x1b438
 * ============================================ */

void PyObject_Free(void)

{
  (*(code *)PTR_PyObject_Free_001b3e20)();
  return;
}




/* ============================================
 * Function: PyLong_FromSsize_t
 * Address:  0x1b444
 * ============================================ */

void PyLong_FromSsize_t(void)

{
  (*(code *)PTR_PyLong_FromSsize_t_001b3e24)();
  return;
}




/* ============================================
 * Function: PyFloat_FromDouble
 * Address:  0x1b450
 * ============================================ */

void PyFloat_FromDouble(void)

{
  (*(code *)PTR_PyFloat_FromDouble_001b3e28)();
  return;
}




/* ============================================
 * Function: PyType_Ready
 * Address:  0x1b45c
 * ============================================ */

void PyType_Ready(void)

{
  (*(code *)PTR_PyType_Ready_001b3e2c)();
  return;
}




/* ============================================
 * Function: PyLong_FromLong
 * Address:  0x1b468
 * ============================================ */

void PyLong_FromLong(void)

{
  (*(code *)PTR_PyLong_FromLong_001b3e30)();
  return;
}




/* ============================================
 * Function: PyLong_AsSsize_t
 * Address:  0x1b474
 * ============================================ */

void PyLong_AsSsize_t(void)

{
  (*(code *)PTR_PyLong_AsSsize_t_001b3e34)();
  return;
}




/* ============================================
 * Function: PyErr_Clear
 * Address:  0x1b480
 * ============================================ */

void PyErr_Clear(void)

{
  (*(code *)PTR_PyErr_Clear_001b3e38)();
  return;
}




/* ============================================
 * Function: _PyUnicode_FastCopyCharacters
 * Address:  0x1b498
 * ============================================ */

void _PyUnicode_FastCopyCharacters(void)

{
  (*(code *)PTR__PyUnicode_FastCopyCharacters_001b3e40)();
  return;
}




/* ============================================
 * Function: PyNumber_And
 * Address:  0x1b4a4
 * ============================================ */

void PyNumber_And(void)

{
  (*(code *)PTR_PyNumber_And_001b3e44)();
  return;
}




/* ============================================
 * Function: PyTuple_New
 * Address:  0x1b4bc
 * ============================================ */

void PyTuple_New(void)

{
  (*(code *)PTR_PyTuple_New_001b3e4c)();
  return;
}




/* ============================================
 * Function: PyThreadState_Get
 * Address:  0x1b4c8
 * ============================================ */

void PyThreadState_Get(void)

{
  (*(code *)PTR_PyThreadState_Get_001b3e50)();
  return;
}




/* ============================================
 * Function: PyNumber_Remainder
 * Address:  0x1b4d4
 * ============================================ */

void PyNumber_Remainder(void)

{
  (*(code *)PTR_PyNumber_Remainder_001b3e54)();
  return;
}




/* ============================================
 * Function: _PyDict_SetItem_KnownHash
 * Address:  0x1b4e0
 * ============================================ */

void _PyDict_SetItem_KnownHash(void)

{
  (*(code *)PTR__PyDict_SetItem_KnownHash_001b3e58)();
  return;
}




/* ============================================
 * Function: PyArg_UnpackTuple
 * Address:  0x1b4ec
 * ============================================ */

void PyArg_UnpackTuple(void)

{
  (*(code *)PTR_PyArg_UnpackTuple_001b3e5c)();
  return;
}




/* ============================================
 * Function: PyObject_SetAttr
 * Address:  0x1b4f8
 * ============================================ */

void PyObject_SetAttr(void)

{
  (*(code *)PTR_PyObject_SetAttr_001b3e60)();
  return;
}




/* ============================================
 * Function: PyErr_Occurred
 * Address:  0x1b504
 * ============================================ */

void PyErr_Occurred(void)

{
  (*(code *)PTR_PyErr_Occurred_001b3e64)();
  return;
}




/* ============================================
 * Function: PyImport_ImportModule
 * Address:  0x1b510
 * ============================================ */

void PyImport_ImportModule(void)

{
  (*(code *)PTR_PyImport_ImportModule_001b3e68)();
  return;
}




/* ============================================
 * Function: _PyDict_GetItem_KnownHash
 * Address:  0x1b51c
 * ============================================ */

void _PyDict_GetItem_KnownHash(void)

{
  (*(code *)PTR__PyDict_GetItem_KnownHash_001b3e6c)();
  return;
}




/* ============================================
 * Function: PyObject_CallObject
 * Address:  0x1b528
 * ============================================ */

void PyObject_CallObject(void)

{
  (*(code *)PTR_PyObject_CallObject_001b3e70)();
  return;
}




/* ============================================
 * Function: Py_LeaveRecursiveCall
 * Address:  0x1b534
 * ============================================ */

void Py_LeaveRecursiveCall(void)

{
  (*(code *)PTR_Py_LeaveRecursiveCall_001b3e74)();
  return;
}




/* ============================================
 * Function: PyNumber_InPlaceOr
 * Address:  0x1b540
 * ============================================ */

void PyNumber_InPlaceOr(void)

{
  (*(code *)PTR_PyNumber_InPlaceOr_001b3e78)();
  return;
}




/* ============================================
 * Function: PyTuple_GetSlice
 * Address:  0x1b54c
 * ============================================ */

void PyTuple_GetSlice(void)

{
  (*(code *)PTR_PyTuple_GetSlice_001b3e7c)();
  return;
}




/* ============================================
 * Function: PyRun_StringFlags
 * Address:  0x1b558
 * ============================================ */

void PyRun_StringFlags(void)

{
  (*(code *)PTR_PyRun_StringFlags_001b3e80)();
  return;
}




/* ============================================
 * Function: PyObject_CallFunctionObjArgs
 * Address:  0x1b564
 * ============================================ */

void PyObject_CallFunctionObjArgs(void)

{
  (*(code *)PTR_PyObject_CallFunctionObjArgs_001b3e84)();
  return;
}




/* ============================================
 * Function: PyDict_GetItemString
 * Address:  0x1b570
 * ============================================ */

void PyDict_GetItemString(void)

{
  (*(code *)PTR_PyDict_GetItemString_001b3e88)();
  return;
}




/* ============================================
 * Function: PyEval_EvalCodeEx
 * Address:  0x1b57c
 * ============================================ */

void PyEval_EvalCodeEx(void)

{
  (*(code *)PTR_PyEval_EvalCodeEx_001b3e8c)();
  return;
}




/* ============================================
 * Function: PyObject_Size
 * Address:  0x1b588
 * ============================================ */

void PyObject_Size(void)

{
  (*(code *)PTR_PyObject_Size_001b3e90)();
  return;
}




/* ============================================
 * Function: _PyLong_FormatAdvancedWriter
 * Address:  0x1b594
 * ============================================ */

void _PyLong_FormatAdvancedWriter(void)

{
  (*(code *)PTR__PyLong_FormatAdvancedWriter_001b3e94)();
  return;
}




/* ============================================
 * Function: _PyType_Lookup
 * Address:  0x1b5ac
 * ============================================ */

void _PyType_Lookup(void)

{
  (*(code *)PTR__PyType_Lookup_001b3e9c)();
  return;
}




/* ============================================
 * Function: PyImport_ImportModuleLevelObject
 * Address:  0x1b5b8
 * ============================================ */

void PyImport_ImportModuleLevelObject(void)

{
  (*(code *)PTR_PyImport_ImportModuleLevelObject_001b3ea0)();
  return;
}




/* ============================================
 * Function: PyObject_Hash
 * Address:  0x1b5c4
 * ============================================ */

void PyObject_Hash(void)

{
  (*(code *)PTR_PyObject_Hash_001b3ea4)();
  return;
}




/* ============================================
 * Function: PyUnicode_Compare
 * Address:  0x1b5d0
 * ============================================ */

void PyUnicode_Compare(void)

{
  (*(code *)PTR_PyUnicode_Compare_001b3ea8)();
  return;
}




/* ============================================
 * Function: _Py_NewReference
 * Address:  0x1b5dc
 * ============================================ */

void _Py_NewReference(void)

{
  (*(code *)PTR__Py_NewReference_001b3eac)();
  return;
}




/* ============================================
 * Function: PyLong_AsDouble
 * Address:  0x1b5e8
 * ============================================ */

void PyLong_AsDouble(void)

{
  (*(code *)PTR_PyLong_AsDouble_001b3eb0)();
  return;
}




/* ============================================
 * Function: PyDict_New
 * Address:  0x1b5f4
 * ============================================ */

void PyDict_New(void)

{
  (*(code *)PTR_PyDict_New_001b3eb4)();
  return;
}




/* ============================================
 * Function: PyDict_Next
 * Address:  0x1b600
 * ============================================ */

void PyDict_Next(void)

{
  (*(code *)PTR_PyDict_Next_001b3eb8)();
  return;
}




/* ============================================
 * Function: _PyObject_GetDictPtr
 * Address:  0x1b60c
 * ============================================ */

void _PyObject_GetDictPtr(void)

{
  (*(code *)PTR__PyObject_GetDictPtr_001b3ebc)();
  return;
}




/* ============================================
 * Function: PyUnicode_FromString
 * Address:  0x1b618
 * ============================================ */

void PyUnicode_FromString(void)

{
  (*(code *)PTR_PyUnicode_FromString_001b3ec0)();
  return;
}




/* ============================================
 * Function: PyType_GetFlags
 * Address:  0x1b624
 * ============================================ */

void PyType_GetFlags(void)

{
  (*(code *)PTR_PyType_GetFlags_001b3ec4)();
  return;
}




/* ============================================
 * Function: PyObject_GetIter
 * Address:  0x1b630
 * ============================================ */

void PyObject_GetIter(void)

{
  (*(code *)PTR_PyObject_GetIter_001b3ec8)();
  return;
}




/* ============================================
 * Function: PyUnicode_InternFromString
 * Address:  0x1b63c
 * ============================================ */

void PyUnicode_InternFromString(void)

{
  (*(code *)PTR_PyUnicode_InternFromString_001b3ecc)();
  return;
}




/* ============================================
 * Function: PyDict_SetItem
 * Address:  0x1b648
 * ============================================ */

void PyDict_SetItem(void)

{
  (*(code *)PTR_PyDict_SetItem_001b3ed0)();
  return;
}




/* ============================================
 * Function: PyObject_IsSubclass
 * Address:  0x1b654
 * ============================================ */

void PyObject_IsSubclass(void)

{
  (*(code *)PTR_PyObject_IsSubclass_001b3ed4)();
  return;
}




/* ============================================
 * Function: PySequence_List
 * Address:  0x1b660
 * ============================================ */

void PySequence_List(void)

{
  (*(code *)PTR_PySequence_List_001b3ed8)();
  return;
}




/* ============================================
 * Function: PyObject_Call
 * Address:  0x1b66c
 * ============================================ */

void PyObject_Call(void)

{
  (*(code *)PTR_PyObject_Call_001b3edc)();
  return;
}




/* ============================================
 * Function: PyType_IsSubtype
 * Address:  0x1b678
 * ============================================ */

void PyType_IsSubtype(void)

{
  (*(code *)PTR_PyType_IsSubtype_001b3ee0)();
  return;
}




/* ============================================
 * Function: PyUnicode_Decode
 * Address:  0x1b684
 * ============================================ */

void PyUnicode_Decode(void)

{
  (*(code *)PTR_PyUnicode_Decode_001b3ee4)();
  return;
}




/* ============================================
 * Function: PyErr_Format
 * Address:  0x1b690
 * ============================================ */

void PyErr_Format(void)

{
  (*(code *)PTR_PyErr_Format_001b3ee8)();
  return;
}




/* ============================================
 * Function: PySlice_New
 * Address:  0x1b69c
 * ============================================ */

void PySlice_New(void)

{
  (*(code *)PTR_PySlice_New_001b3eec)();
  return;
}




/* ============================================
 * Function: PyUnicode_FromStringAndSize
 * Address:  0x1b6a8
 * ============================================ */

void PyUnicode_FromStringAndSize(void)

{
  (*(code *)PTR_PyUnicode_FromStringAndSize_001b3ef0)();
  return;
}




/* ============================================
 * Function: PyModule_GetDict
 * Address:  0x1b6b4
 * ============================================ */

void PyModule_GetDict(void)

{
  (*(code *)PTR_PyModule_GetDict_001b3ef4)();
  return;
}




/* ============================================
 * Function: PyUnicode_Concat
 * Address:  0x1b6cc
 * ============================================ */

void PyUnicode_Concat(void)

{
  (*(code *)PTR_PyUnicode_Concat_001b3efc)();
  return;
}




/* ============================================
 * Function: PyNumber_Index
 * Address:  0x1b6d8
 * ============================================ */

void PyNumber_Index(void)

{
  (*(code *)PTR_PyNumber_Index_001b3f00)();
  return;
}




/* ============================================
 * Function: _PyUnicodeWriter_Finish
 * Address:  0x1b6f0
 * ============================================ */

void _PyUnicodeWriter_Finish(void)

{
  (*(code *)PTR__PyUnicodeWriter_Finish_001b3f08)();
  return;
}




/* ============================================
 * Function: _PyDict_NewPresized
 * Address:  0x1b6fc
 * ============================================ */

void _PyDict_NewPresized(void)

{
  (*(code *)PTR__PyDict_NewPresized_001b3f0c)();
  return;
}




/* ============================================
 * Function: PyUnicode_Format
 * Address:  0x1b708
 * ============================================ */

void PyUnicode_Format(void)

{
  (*(code *)PTR_PyUnicode_Format_001b3f10)();
  return;
}




/* ============================================
 * Function: PyMem_Malloc
 * Address:  0x1b714
 * ============================================ */

void PyMem_Malloc(void)

{
  (*(code *)PTR_PyMem_Malloc_001b3f14)();
  return;
}




/* ============================================
 * Function: PyNumber_Subtract
 * Address:  0x1b720
 * ============================================ */

void PyNumber_Subtract(void)

{
  (*(code *)PTR_PyNumber_Subtract_001b3f18)();
  return;
}




/* ============================================
 * Function: PyUnicode_New
 * Address:  0x1b72c
 * ============================================ */

void PyUnicode_New(void)

{
  (*(code *)PTR_PyUnicode_New_001b3f1c)();
  return;
}




/* ============================================
 * Function: PyTuple_Pack
 * Address:  0x1b738
 * ============================================ */

void PyTuple_Pack(void)

{
  (*(code *)PTR_PyTuple_Pack_001b3f20)();
  return;
}




/* ============================================
 * Function: Py_GetVersion
 * Address:  0x1b744
 * ============================================ */

void Py_GetVersion(void)

{
  (*(code *)PTR_Py_GetVersion_001b3f24)();
  return;
}




/* ============================================
 * Function: PyNumber_InPlaceSubtract
 * Address:  0x1b750
 * ============================================ */

void PyNumber_InPlaceSubtract(void)

{
  (*(code *)PTR_PyNumber_InPlaceSubtract_001b3f28)();
  return;
}




/* ============================================
 * Function: PyNumber_TrueDivide
 * Address:  0x1b75c
 * ============================================ */

void PyNumber_TrueDivide(void)

{
  (*(code *)PTR_PyNumber_TrueDivide_001b3f2c)();
  return;
}




/* ============================================
 * Function: PyObject_GC_UnTrack
 * Address:  0x1b768
 * ============================================ */

void PyObject_GC_UnTrack(void)

{
  (*(code *)PTR_PyObject_GC_UnTrack_001b3f30)();
  return;
}




/* ============================================
 * Function: PyErr_WriteUnraisable
 * Address:  0x1b774
 * ============================================ */

void PyErr_WriteUnraisable(void)

{
  (*(code *)PTR_PyErr_WriteUnraisable_001b3f34)();
  return;
}




/* ============================================
 * Function: PyDict_GetItemWithError
 * Address:  0x1b780
 * ============================================ */

void PyDict_GetItemWithError(void)

{
  (*(code *)PTR_PyDict_GetItemWithError_001b3f38)();
  return;
}




/* ============================================
 * Function: PyFloat_FromString
 * Address:  0x1b78c
 * ============================================ */

void PyFloat_FromString(void)

{
  (*(code *)PTR_PyFloat_FromString_001b3f3c)();
  return;
}




/* ============================================
 * Function: entry
 * Address:  0x1b798
 * ============================================ */

int processEntry entry(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = DAT_0001b828;
  iVar1 = FUN_0003667c(*(undefined4 *)(DAT_0001b828 + 0x1b7ac));
  *(int *)(iVar2 + 0x1b7b0) = iVar1;
  if (iVar1 != 0) {
    iVar1 = FUN_0003667c(*(undefined4 *)(iVar2 + 0x1b7b4));
    *(int *)(iVar2 + 0x1b7b8) = iVar1;
    if (iVar1 != 0) {
      iVar1 = FUN_0003667c(*(undefined4 *)(iVar2 + 0x1b7bc));
      *(int *)(iVar2 + 0x1b7c0) = iVar1;
      if (iVar1 != 0) {
        iVar1 = FUN_0003667c(*(undefined4 *)(iVar2 + 0x1b7c4));
        *(int *)(iVar2 + 0x1b7c8) = iVar1;
        if (iVar1 != 0) {
          iVar1 = FUN_0003667c(*(undefined4 *)(iVar2 + 0x1b7cc));
          *(int *)(iVar2 + 0x1b7d0) = iVar1;
          if (iVar1 != 0) {
            iVar2 = FUN_0003667c(*(undefined4 *)(iVar2 + 0x1b7d4));
            return -(uint)(iVar2 == 0);
          }
        }
      }
    }
  }
  return -1;
}




/* ============================================
 * Function: FUN_0001b82c
 * Address:  0x1b82c
 * ============================================ */

int FUN_0001b82c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = DAT_0001b884;
  iVar2 = FUN_00036664();
  if ((iVar2 == 0) &&
     (iVar3 = PyErr_ExceptionMatches(**(undefined4 **)(iVar1 + 0x1b848 + DAT_0001b888)), iVar3 != 0)
     ) {
    PyErr_Format(**(undefined4 **)(iVar1 + 0x1b848 + DAT_0001b88c),DAT_0001b890 + 0x1b878,param_2);
  }
  return iVar2;
}




/* ============================================
 * Function: FUN_0001b894
 * Address:  0x1b894
 * ============================================ */
