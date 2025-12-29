/*
 * Decompiled from: serial_485_wrapper.cpython-39.so
 * Function count: 503
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
 *   - Raw Ghidra decompilation of all 503 functions
 *   - Function addresses (e.g., 0x13620)
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
 *   reconstructed/serial_485_wrapper.py (if available)
 * =============================================================================
 */

/* ============================================
 * Function: _DT_INIT
 * Address:  0x13620
 * ============================================ */

void _DT_INIT(void)

{
  FUN_000173c0();
  return;
}




/* ============================================
 * Function: PyUnicode_FromFormat
 * Address:  0x13640
 * ============================================ */

void PyUnicode_FromFormat(void)

{
  (*(code *)PTR_PyUnicode_FromFormat_00040da0)();
  return;
}




/* ============================================
 * Function: PyObject_SetItem
 * Address:  0x1364c
 * ============================================ */

void PyObject_SetItem(void)

{
  (*(code *)PTR_PyObject_SetItem_00040da4)();
  return;
}




/* ============================================
 * Function: PyList_New
 * Address:  0x13658
 * ============================================ */

void PyList_New(void)

{
  (*(code *)PTR_PyList_New_00040da8)();
  return;
}




/* ============================================
 * Function: PyDict_SetItemString
 * Address:  0x13664
 * ============================================ */

void PyDict_SetItemString(void)

{
  (*(code *)PTR_PyDict_SetItemString_00040dac)();
  return;
}




/* ============================================
 * Function: PyDict_Size
 * Address:  0x13670
 * ============================================ */

void PyDict_Size(void)

{
  (*(code *)PTR_PyDict_Size_00040db0)();
  return;
}




/* ============================================
 * Function: PyException_SetTraceback
 * Address:  0x1367c
 * ============================================ */

void PyException_SetTraceback(void)

{
  (*(code *)PTR_PyException_SetTraceback_00040db4)();
  return;
}




/* ============================================
 * Function: __cxa_finalize
 * Address:  0x13688
 * ============================================ */

void __cxa_finalize(void)

{
  (*(code *)PTR___cxa_finalize_00040db8)();
  return;
}




/* ============================================
 * Function: PyObject_ClearWeakRefs
 * Address:  0x13694
 * ============================================ */

void PyObject_ClearWeakRefs(void)

{
  (*(code *)PTR_PyObject_ClearWeakRefs_00040dbc)();
  return;
}




/* ============================================
 * Function: _PyThreadState_UncheckedGet
 * Address:  0x136a0
 * ============================================ */

void _PyThreadState_UncheckedGet(void)

{
  (*(code *)PTR__PyThreadState_UncheckedGet_00040dc0)();
  return;
}




/* ============================================
 * Function: Py_EnterRecursiveCall
 * Address:  0x136b8
 * ============================================ */

void Py_EnterRecursiveCall(void)

{
  (*(code *)PTR_Py_EnterRecursiveCall_00040dc8)();
  return;
}




/* ============================================
 * Function: PyFrame_New
 * Address:  0x136c4
 * ============================================ */

void PyFrame_New(void)

{
  (*(code *)PTR_PyFrame_New_00040dcc)();
  return;
}




/* ============================================
 * Function: memmove
 * Address:  0x136d0
 * ============================================ */

/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memmove(void *__dest,void *__src,size_t __n)

{
  void *pvVar1;
  
  pvVar1 = (void *)(*(code *)PTR_memmove_00040dd0)(__dest);
  return pvVar1;
}




/* ============================================
 * Function: PyNumber_Add
 * Address:  0x136dc
 * ============================================ */

void PyNumber_Add(void)

{
  (*(code *)PTR_PyNumber_Add_00040dd4)();
  return;
}




/* ============================================
 * Function: PyObject_GetAttrString
 * Address:  0x136e8
 * ============================================ */

void PyObject_GetAttrString(void)

{
  (*(code *)PTR_PyObject_GetAttrString_00040dd8)();
  return;
}




/* ============================================
 * Function: PyUnicode_Join
 * Address:  0x136f4
 * ============================================ */

void PyUnicode_Join(void)

{
  (*(code *)PTR_PyUnicode_Join_00040ddc)();
  return;
}




/* ============================================
 * Function: PyImport_AddModule
 * Address:  0x13700
 * ============================================ */

void PyImport_AddModule(void)

{
  (*(code *)PTR_PyImport_AddModule_00040de0)();
  return;
}




/* ============================================
 * Function: PyBytes_FromStringAndSize
 * Address:  0x1370c
 * ============================================ */

void PyBytes_FromStringAndSize(void)

{
  (*(code *)PTR_PyBytes_FromStringAndSize_00040de4)();
  return;
}




/* ============================================
 * Function: PyObject_SetAttrString
 * Address:  0x13718
 * ============================================ */

void PyObject_SetAttrString(void)

{
  (*(code *)PTR_PyObject_SetAttrString_00040de8)();
  return;
}




/* ============================================
 * Function: PyErr_WarnEx
 * Address:  0x13724
 * ============================================ */

void PyErr_WarnEx(void)

{
  (*(code *)PTR_PyErr_WarnEx_00040dec)();
  return;
}




/* ============================================
 * Function: PyModule_NewObject
 * Address:  0x1373c
 * ============================================ */

void PyModule_NewObject(void)

{
  (*(code *)PTR_PyModule_NewObject_00040df4)();
  return;
}




/* ============================================
 * Function: PyErr_SetObject
 * Address:  0x13748
 * ============================================ */

void PyErr_SetObject(void)

{
  (*(code *)PTR_PyErr_SetObject_00040df8)();
  return;
}




/* ============================================
 * Function: PyErr_NormalizeException
 * Address:  0x13760
 * ============================================ */

void PyErr_NormalizeException(void)

{
  (*(code *)PTR_PyErr_NormalizeException_00040e00)();
  return;
}




/* ============================================
 * Function: _PyObject_CallFunction_SizeT
 * Address:  0x1376c
 * ============================================ */

void _PyObject_CallFunction_SizeT(void)

{
  (*(code *)PTR__PyObject_CallFunction_SizeT_00040e04)();
  return;
}




/* ============================================
 * Function: PyObject_RichCompare
 * Address:  0x13778
 * ============================================ */

void PyObject_RichCompare(void)

{
  (*(code *)PTR_PyObject_RichCompare_00040e08)();
  return;
}




/* ============================================
 * Function: PyCode_New
 * Address:  0x13784
 * ============================================ */

void PyCode_New(void)

{
  (*(code *)PTR_PyCode_New_00040e0c)();
  return;
}




/* ============================================
 * Function: _PyGen_Send
 * Address:  0x13790
 * ============================================ */

void _PyGen_Send(void)

{
  (*(code *)PTR__PyGen_Send_00040e10)();
  return;
}




/* ============================================
 * Function: PyImport_GetModuleDict
 * Address:  0x1379c
 * ============================================ */

void PyImport_GetModuleDict(void)

{
  (*(code *)PTR_PyImport_GetModuleDict_00040e14)();
  return;
}




/* ============================================
 * Function: PyObject_GC_Track
 * Address:  0x137a8
 * ============================================ */

void PyObject_GC_Track(void)

{
  (*(code *)PTR_PyObject_GC_Track_00040e18)();
  return;
}




/* ============================================
 * Function: PyErr_GivenExceptionMatches
 * Address:  0x137b4
 * ============================================ */

void PyErr_GivenExceptionMatches(void)

{
  (*(code *)PTR_PyErr_GivenExceptionMatches_00040e1c)();
  return;
}




/* ============================================
 * Function: PyErr_SetString
 * Address:  0x137c0
 * ============================================ */

void PyErr_SetString(void)

{
  (*(code *)PTR_PyErr_SetString_00040e20)();
  return;
}




/* ============================================
 * Function: PyObject_DelItem
 * Address:  0x137cc
 * ============================================ */

void PyObject_DelItem(void)

{
  (*(code *)PTR_PyObject_DelItem_00040e24)();
  return;
}




/* ============================================
 * Function: PyMethod_New
 * Address:  0x137d8
 * ============================================ */

void PyMethod_New(void)

{
  (*(code *)PTR_PyMethod_New_00040e28)();
  return;
}




/* ============================================
 * Function: _PyObject_GC_New
 * Address:  0x137e4
 * ============================================ */

void _PyObject_GC_New(void)

{
  (*(code *)PTR__PyObject_GC_New_00040e2c)();
  return;
}




/* ============================================
 * Function: PyObject_GetItem
 * Address:  0x137f0
 * ============================================ */

void PyObject_GetItem(void)

{
  (*(code *)PTR_PyObject_GetItem_00040e30)();
  return;
}




/* ============================================
 * Function: PyInterpreterState_GetID
 * Address:  0x137fc
 * ============================================ */

void PyInterpreterState_GetID(void)

{
  (*(code *)PTR_PyInterpreterState_GetID_00040e34)();
  return;
}




/* ============================================
 * Function: PyEval_EvalFrameEx
 * Address:  0x13808
 * ============================================ */

void PyEval_EvalFrameEx(void)

{
  (*(code *)PTR_PyEval_EvalFrameEx_00040e38)();
  return;
}




/* ============================================
 * Function: PySequence_Contains
 * Address:  0x13814
 * ============================================ */

void PySequence_Contains(void)

{
  (*(code *)PTR_PySequence_Contains_00040e3c)();
  return;
}




/* ============================================
 * Function: PyTuple_GetItem
 * Address:  0x13820
 * ============================================ */

void PyTuple_GetItem(void)

{
  (*(code *)PTR_PyTuple_GetItem_00040e40)();
  return;
}




/* ============================================
 * Function: PyMem_Realloc
 * Address:  0x1382c
 * ============================================ */

void PyMem_Realloc(void)

{
  (*(code *)PTR_PyMem_Realloc_00040e44)();
  return;
}




/* ============================================
 * Function: PyErr_SetNone
 * Address:  0x13838
 * ============================================ */

void PyErr_SetNone(void)

{
  (*(code *)PTR_PyErr_SetNone_00040e48)();
  return;
}




/* ============================================
 * Function: PyErr_ExceptionMatches
 * Address:  0x13844
 * ============================================ */

void PyErr_ExceptionMatches(void)

{
  (*(code *)PTR_PyErr_ExceptionMatches_00040e4c)();
  return;
}




/* ============================================
 * Function: PyOS_snprintf
 * Address:  0x13850
 * ============================================ */

void PyOS_snprintf(void)

{
  (*(code *)PTR_PyOS_snprintf_00040e50)();
  return;
}




/* ============================================
 * Function: PyTraceBack_Here
 * Address:  0x1385c
 * ============================================ */

void PyTraceBack_Here(void)

{
  (*(code *)PTR_PyTraceBack_Here_00040e54)();
  return;
}




/* ============================================
 * Function: PyObject_CallFinalizerFromDealloc
 * Address:  0x13868
 * ============================================ */

void PyObject_CallFinalizerFromDealloc(void)

{
  (*(code *)PTR_PyObject_CallFinalizerFromDealloc_00040e58)();
  return;
}




/* ============================================
 * Function: PyObject_Not
 * Address:  0x13874
 * ============================================ */

void PyObject_Not(void)

{
  (*(code *)PTR_PyObject_Not_00040e5c)();
  return;
}




/* ============================================
 * Function: PyObject_Free
 * Address:  0x13880
 * ============================================ */

void PyObject_Free(void)

{
  (*(code *)PTR_PyObject_Free_00040e60)();
  return;
}




/* ============================================
 * Function: PyLong_FromSsize_t
 * Address:  0x1388c
 * ============================================ */

void PyLong_FromSsize_t(void)

{
  (*(code *)PTR_PyLong_FromSsize_t_00040e64)();
  return;
}




/* ============================================
 * Function: PyFloat_FromDouble
 * Address:  0x13898
 * ============================================ */

void PyFloat_FromDouble(void)

{
  (*(code *)PTR_PyFloat_FromDouble_00040e68)();
  return;
}




/* ============================================
 * Function: PyType_Ready
 * Address:  0x138a4
 * ============================================ */

void PyType_Ready(void)

{
  (*(code *)PTR_PyType_Ready_00040e6c)();
  return;
}




/* ============================================
 * Function: PyLong_FromLong
 * Address:  0x138b0
 * ============================================ */

void PyLong_FromLong(void)

{
  (*(code *)PTR_PyLong_FromLong_00040e70)();
  return;
}




/* ============================================
 * Function: PyLong_AsSsize_t
 * Address:  0x138bc
 * ============================================ */

void PyLong_AsSsize_t(void)

{
  (*(code *)PTR_PyLong_AsSsize_t_00040e74)();
  return;
}




/* ============================================
 * Function: PyErr_Clear
 * Address:  0x138c8
 * ============================================ */

void PyErr_Clear(void)

{
  (*(code *)PTR_PyErr_Clear_00040e78)();
  return;
}




/* ============================================
 * Function: PyList_Append
 * Address:  0x138d4
 * ============================================ */

void PyList_Append(void)

{
  (*(code *)PTR_PyList_Append_00040e7c)();
  return;
}




/* ============================================
 * Function: PyTuple_New
 * Address:  0x138ec
 * ============================================ */

void PyTuple_New(void)

{
  (*(code *)PTR_PyTuple_New_00040e84)();
  return;
}




/* ============================================
 * Function: PyThreadState_Get
 * Address:  0x138f8
 * ============================================ */

void PyThreadState_Get(void)

{
  (*(code *)PTR_PyThreadState_Get_00040e88)();
  return;
}




/* ============================================
 * Function: PyNumber_Remainder
 * Address:  0x13904
 * ============================================ */

void PyNumber_Remainder(void)

{
  (*(code *)PTR_PyNumber_Remainder_00040e8c)();
  return;
}




/* ============================================
 * Function: _PyDict_SetItem_KnownHash
 * Address:  0x13910
 * ============================================ */

void _PyDict_SetItem_KnownHash(void)

{
  (*(code *)PTR__PyDict_SetItem_KnownHash_00040e90)();
  return;
}




/* ============================================
 * Function: PyArg_UnpackTuple
 * Address:  0x1391c
 * ============================================ */

void PyArg_UnpackTuple(void)

{
  (*(code *)PTR_PyArg_UnpackTuple_00040e94)();
  return;
}




/* ============================================
 * Function: PyObject_SetAttr
 * Address:  0x13928
 * ============================================ */

void PyObject_SetAttr(void)

{
  (*(code *)PTR_PyObject_SetAttr_00040e98)();
  return;
}




/* ============================================
 * Function: PyErr_Occurred
 * Address:  0x13934
 * ============================================ */

void PyErr_Occurred(void)

{
  (*(code *)PTR_PyErr_Occurred_00040e9c)();
  return;
}




/* ============================================
 * Function: PyImport_ImportModule
 * Address:  0x13940
 * ============================================ */

void PyImport_ImportModule(void)

{
  (*(code *)PTR_PyImport_ImportModule_00040ea0)();
  return;
}




/* ============================================
 * Function: _PyDict_GetItem_KnownHash
 * Address:  0x1394c
 * ============================================ */

void _PyDict_GetItem_KnownHash(void)

{
  (*(code *)PTR__PyDict_GetItem_KnownHash_00040ea4)();
  return;
}




/* ============================================
 * Function: PyObject_CallObject
 * Address:  0x13958
 * ============================================ */

void PyObject_CallObject(void)

{
  (*(code *)PTR_PyObject_CallObject_00040ea8)();
  return;
}




/* ============================================
 * Function: Py_LeaveRecursiveCall
 * Address:  0x13964
 * ============================================ */

void Py_LeaveRecursiveCall(void)

{
  (*(code *)PTR_Py_LeaveRecursiveCall_00040eac)();
  return;
}




/* ============================================
 * Function: PyTuple_GetSlice
 * Address:  0x13970
 * ============================================ */

void PyTuple_GetSlice(void)

{
  (*(code *)PTR_PyTuple_GetSlice_00040eb0)();
  return;
}




/* ============================================
 * Function: PyRun_StringFlags
 * Address:  0x1397c
 * ============================================ */

void PyRun_StringFlags(void)

{
  (*(code *)PTR_PyRun_StringFlags_00040eb4)();
  return;
}




/* ============================================
 * Function: PyObject_CallFunctionObjArgs
 * Address:  0x13988
 * ============================================ */

void PyObject_CallFunctionObjArgs(void)

{
  (*(code *)PTR_PyObject_CallFunctionObjArgs_00040eb8)();
  return;
}




/* ============================================
 * Function: PyDict_GetItemString
 * Address:  0x13994
 * ============================================ */

void PyDict_GetItemString(void)

{
  (*(code *)PTR_PyDict_GetItemString_00040ebc)();
  return;
}




/* ============================================
 * Function: PyEval_EvalCodeEx
 * Address:  0x139a0
 * ============================================ */

void PyEval_EvalCodeEx(void)

{
  (*(code *)PTR_PyEval_EvalCodeEx_00040ec0)();
  return;
}




/* ============================================
 * Function: PyObject_Size
 * Address:  0x139ac
 * ============================================ */

void PyObject_Size(void)

{
  (*(code *)PTR_PyObject_Size_00040ec4)();
  return;
}




/* ============================================
 * Function: _PyType_Lookup
 * Address:  0x139c4
 * ============================================ */

void _PyType_Lookup(void)

{
  (*(code *)PTR__PyType_Lookup_00040ecc)();
  return;
}




/* ============================================
 * Function: PyImport_ImportModuleLevelObject
 * Address:  0x139d0
 * ============================================ */

void PyImport_ImportModuleLevelObject(void)

{
  (*(code *)PTR_PyImport_ImportModuleLevelObject_00040ed0)();
  return;
}




/* ============================================
 * Function: PyObject_Hash
 * Address:  0x139dc
 * ============================================ */

void PyObject_Hash(void)

{
  (*(code *)PTR_PyObject_Hash_00040ed4)();
  return;
}




/* ============================================
 * Function: PyUnicode_Compare
 * Address:  0x139e8
 * ============================================ */

void PyUnicode_Compare(void)

{
  (*(code *)PTR_PyUnicode_Compare_00040ed8)();
  return;
}




/* ============================================
 * Function: _Py_NewReference
 * Address:  0x139f4
 * ============================================ */

void _Py_NewReference(void)

{
  (*(code *)PTR__Py_NewReference_00040edc)();
  return;
}




/* ============================================
 * Function: PyLong_AsDouble
 * Address:  0x13a00
 * ============================================ */

void PyLong_AsDouble(void)

{
  (*(code *)PTR_PyLong_AsDouble_00040ee0)();
  return;
}




/* ============================================
 * Function: PyDict_New
 * Address:  0x13a0c
 * ============================================ */

void PyDict_New(void)

{
  (*(code *)PTR_PyDict_New_00040ee4)();
  return;
}




/* ============================================
 * Function: PyDict_Next
 * Address:  0x13a18
 * ============================================ */

void PyDict_Next(void)

{
  (*(code *)PTR_PyDict_Next_00040ee8)();
  return;
}




/* ============================================
 * Function: _PyObject_GetDictPtr
 * Address:  0x13a24
 * ============================================ */

void _PyObject_GetDictPtr(void)

{
  (*(code *)PTR__PyObject_GetDictPtr_00040eec)();
  return;
}




/* ============================================
 * Function: PyUnicode_FromString
 * Address:  0x13a30
 * ============================================ */

void PyUnicode_FromString(void)

{
  (*(code *)PTR_PyUnicode_FromString_00040ef0)();
  return;
}




/* ============================================
 * Function: PyType_GetFlags
 * Address:  0x13a3c
 * ============================================ */

void PyType_GetFlags(void)

{
  (*(code *)PTR_PyType_GetFlags_00040ef4)();
  return;
}




/* ============================================
 * Function: PyObject_GetIter
 * Address:  0x13a48
 * ============================================ */

void PyObject_GetIter(void)

{
  (*(code *)PTR_PyObject_GetIter_00040ef8)();
  return;
}




/* ============================================
 * Function: PyUnicode_InternFromString
 * Address:  0x13a54
 * ============================================ */

void PyUnicode_InternFromString(void)

{
  (*(code *)PTR_PyUnicode_InternFromString_00040efc)();
  return;
}




/* ============================================
 * Function: PyDict_SetItem
 * Address:  0x13a60
 * ============================================ */

void PyDict_SetItem(void)

{
  (*(code *)PTR_PyDict_SetItem_00040f00)();
  return;
}




/* ============================================
 * Function: PySequence_Tuple
 * Address:  0x13a6c
 * ============================================ */

void PySequence_Tuple(void)

{
  (*(code *)PTR_PySequence_Tuple_00040f04)();
  return;
}




/* ============================================
 * Function: PyObject_IsSubclass
 * Address:  0x13a78
 * ============================================ */

void PyObject_IsSubclass(void)

{
  (*(code *)PTR_PyObject_IsSubclass_00040f08)();
  return;
}




/* ============================================
 * Function: PySequence_List
 * Address:  0x13a84
 * ============================================ */

void PySequence_List(void)

{
  (*(code *)PTR_PySequence_List_00040f0c)();
  return;
}




/* ============================================
 * Function: PyObject_Call
 * Address:  0x13a90
 * ============================================ */

void PyObject_Call(void)

{
  (*(code *)PTR_PyObject_Call_00040f10)();
  return;
}




/* ============================================
 * Function: PyType_IsSubtype
 * Address:  0x13a9c
 * ============================================ */

void PyType_IsSubtype(void)

{
  (*(code *)PTR_PyType_IsSubtype_00040f14)();
  return;
}




/* ============================================
 * Function: PyUnicode_Decode
 * Address:  0x13aa8
 * ============================================ */

void PyUnicode_Decode(void)

{
  (*(code *)PTR_PyUnicode_Decode_00040f18)();
  return;
}




/* ============================================
 * Function: PyErr_Format
 * Address:  0x13ab4
 * ============================================ */

void PyErr_Format(void)

{
  (*(code *)PTR_PyErr_Format_00040f1c)();
  return;
}




/* ============================================
 * Function: PySlice_New
 * Address:  0x13ac0
 * ============================================ */

void PySlice_New(void)

{
  (*(code *)PTR_PySlice_New_00040f20)();
  return;
}




/* ============================================
 * Function: PyUnicode_FromStringAndSize
 * Address:  0x13acc
 * ============================================ */

void PyUnicode_FromStringAndSize(void)

{
  (*(code *)PTR_PyUnicode_FromStringAndSize_00040f24)();
  return;
}




/* ============================================
 * Function: PyModule_GetDict
 * Address:  0x13ad8
 * ============================================ */

void PyModule_GetDict(void)

{
  (*(code *)PTR_PyModule_GetDict_00040f28)();
  return;
}




/* ============================================
 * Function: PyLong_FromLongLong
 * Address:  0x13ae4
 * ============================================ */

void PyLong_FromLongLong(void)

{
  (*(code *)PTR_PyLong_FromLongLong_00040f2c)();
  return;
}




/* ============================================
 * Function: PyNumber_Index
 * Address:  0x13af0
 * ============================================ */

void PyNumber_Index(void)

{
  (*(code *)PTR_PyNumber_Index_00040f30)();
  return;
}




/* ============================================
 * Function: PyUnicode_Format
 * Address:  0x13b08
 * ============================================ */

void PyUnicode_Format(void)

{
  (*(code *)PTR_PyUnicode_Format_00040f38)();
  return;
}




/* ============================================
 * Function: PyMem_Malloc
 * Address:  0x13b14
 * ============================================ */

void PyMem_Malloc(void)

{
  (*(code *)PTR_PyMem_Malloc_00040f3c)();
  return;
}




/* ============================================
 * Function: PyTuple_Pack
 * Address:  0x13b20
 * ============================================ */

void PyTuple_Pack(void)

{
  (*(code *)PTR_PyTuple_Pack_00040f40)();
  return;
}




/* ============================================
 * Function: Py_GetVersion
 * Address:  0x13b2c
 * ============================================ */

void Py_GetVersion(void)

{
  (*(code *)PTR_Py_GetVersion_00040f44)();
  return;
}




/* ============================================
 * Function: PyObject_GC_UnTrack
 * Address:  0x13b38
 * ============================================ */

void PyObject_GC_UnTrack(void)

{
  (*(code *)PTR_PyObject_GC_UnTrack_00040f48)();
  return;
}




/* ============================================
 * Function: PyErr_WriteUnraisable
 * Address:  0x13b44
 * ============================================ */

void PyErr_WriteUnraisable(void)

{
  (*(code *)PTR_PyErr_WriteUnraisable_00040f4c)();
  return;
}




/* ============================================
 * Function: PyDict_GetItemWithError
 * Address:  0x13b50
 * ============================================ */

void PyDict_GetItemWithError(void)

{
  (*(code *)PTR_PyDict_GetItemWithError_00040f50)();
  return;
}




/* ============================================
 * Function: entry
 * Address:  0x13b60
 * ============================================ */

int processEntry entry(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_00013bb8;
  iVar2 = FUN_00017f00(*(undefined4 *)(DAT_00013bb8 + 0x13b74));
  *(int *)(iVar1 + 0x13b78) = iVar2;
  if (iVar2 != 0) {
    iVar2 = FUN_00017f00(*(undefined4 *)(iVar1 + 0x13b7c));
    *(int *)(iVar1 + 0x13b80) = iVar2;
    if (iVar2 != 0) {
      iVar2 = FUN_00017f00(*(undefined4 *)(iVar1 + 0x13b84));
      *(int *)(iVar1 + 0x13b88) = iVar2;
      return -(uint)(iVar2 == 0);
    }
  }
  return -1;
}




/* ============================================
 * Function: FUN_00013bbc
 * Address:  0x13bbc
 * ============================================ */

undefined4 FUN_00013bbc(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  iVar1 = DAT_00013c3c;
  iVar4 = DAT_00013c3c + 0x13bcc;
  iVar3 = PyType_Ready(iVar4);
  iVar2 = DAT_00013c40;
  if (-1 < iVar3) {
    *(int *)(DAT_00013c40 + 0x13c10) = iVar4;
    iVar3 = PyType_Ready(iVar1 + 0x13c98);
    if (-1 < iVar3) {
      *(int *)(iVar2 + 0x13c14) = iVar1 + 0x13c98;
      iVar3 = PyType_Ready(iVar1 + 0x13d64);
      if (-1 < iVar3) {
        *(int *)(iVar2 + 0x13c18) = iVar1 + 0x13d64;
        iVar3 = PyType_Ready(iVar1 + 0x13e30);
        if (-1 < iVar3) {
          *(int *)(iVar2 + 0x13c1c) = iVar1 + 0x13e30;
          return 0;
        }
      }
    }
  }
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_00013c44
 * Address:  0x13c44
 * ============================================ */

undefined4 FUN_00013c44(void)

{
  undefined4 uVar1;
  char local_e0 [2];
  char local_de;
  char local_dc [2];
  char local_da;
  undefined1 auStack_d8 [204];
  
  PyOS_snprintf(local_e0,4,DAT_00013cf8 + 0x13c64,3,9);
  uVar1 = Py_GetVersion();
  PyOS_snprintf(local_dc,4,DAT_00013cfc + 0x13c90,uVar1);
  if ((local_e0[0] == local_dc[0]) && (local_de == local_da)) {
    uVar1 = 0;
  }
  else {
    PyOS_snprintf(auStack_d8,200,DAT_00013d04 + 0x13cd4,local_e0,DAT_00013d00 + 0x13cc8,local_dc);
    uVar1 = PyErr_WarnEx(0,auStack_d8,1);
  }
  return uVar1;
}




/* ============================================
 * Function: FUN_00013d08
 * Address:  0x13d08
 * ============================================ */

int FUN_00013d08(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 uVar4;
  int iVar5;
  
  iVar1 = DAT_00014a4c;
  iVar5 = DAT_00014a44 + 0x13d24;
  iVar2 = PyTuple_Pack(3,*(undefined4 *)(iVar5 + DAT_00014a48),*(undefined4 *)(iVar5 + DAT_00014a48)
                      );
  *(int *)(iVar1 + 0x13d5c) = iVar2;
  if (iVar2 != 0) {
    iVar2 = PyTuple_Pack(2,*(undefined4 *)(iVar1 + 0x13d64),*(undefined4 *)(iVar1 + 0x13d60));
    *(int *)(iVar1 + 0x13d68) = iVar2;
    if ((iVar2 != 0) &&
       (iVar2 = PyTuple_Pack(3,*(undefined4 *)(iVar1 + 0x13d74),*(undefined4 *)(iVar1 + 0x13d70),
                             *(undefined4 *)(iVar1 + 0x13d6c)), iVar2 != 0)) {
      uVar3 = *(undefined4 *)(iVar1 + 0x13d7c);
      iVar2 = PyCode_New(3,0,3,0,3,*(undefined4 *)(iVar1 + 0x13d78),uVar3,uVar3,iVar2,uVar3,uVar3,
                         *(undefined4 *)(iVar1 + 0x13d84),*(undefined4 *)(iVar1 + 0x13d80),0x12,
                         *(undefined4 *)(iVar1 + 0x13d78));
      *(int *)(iVar1 + 0x13d88) = iVar2;
      if (iVar2 != 0) {
        iVar2 = PyTuple_Pack(1,*(undefined4 *)(iVar1 + 0x13d8c));
        *(int *)(iVar1 + 0x13d90) = iVar2;
        if ((iVar2 != 0) &&
           (iVar2 = PyTuple_Pack(0xb,*(undefined4 *)(iVar1 + 0x13d74),
                                 *(undefined4 *)(iVar1 + 0x13d98),*(undefined4 *)(iVar1 + 0x13d94),
                                 *(undefined4 *)(iVar1 + 0x13db8),*(undefined4 *)(iVar1 + 0x13db4),
                                 *(undefined4 *)(iVar1 + 0x13db0),*(undefined4 *)(iVar1 + 0x13dac),
                                 *(undefined4 *)(iVar1 + 0x13da8),*(undefined4 *)(iVar1 + 0x13da4),
                                 *(undefined4 *)(iVar1 + 0x13da0),*(undefined4 *)(iVar1 + 0x13d9c)),
           iVar2 != 0)) {
          uVar3 = *(undefined4 *)(iVar1 + 0x13d7c);
          iVar2 = PyCode_New(1,0,0xb,0,3,*(undefined4 *)(iVar1 + 0x13d78),uVar3,uVar3,iVar2,uVar3,
                             uVar3,*(undefined4 *)(iVar1 + 0x13d84),*(undefined4 *)(iVar1 + 0x13dbc)
                             ,0x27,*(undefined4 *)(iVar1 + 0x13d78));
          *(int *)(iVar1 + 0x13dc0) = iVar2;
          if ((iVar2 != 0) &&
             (iVar2 = PyTuple_Pack(3,*(undefined4 *)(iVar1 + 0x13d74),
                                   *(undefined4 *)(iVar1 + 0x13dc8),*(undefined4 *)(iVar1 + 0x13dc4)
                                  ), iVar2 != 0)) {
            uVar3 = *(undefined4 *)(iVar1 + 0x13d7c);
            iVar2 = PyCode_New(3,0,3,0,3,*(undefined4 *)(iVar1 + 0x13d78),uVar3,uVar3,iVar2,uVar3,
                               uVar3,*(undefined4 *)(iVar1 + 0x13d84),
                               *(undefined4 *)(iVar1 + 0x13dcc),0x54,
                               *(undefined4 *)(iVar1 + 0x13d78));
            *(int *)(iVar1 + 0x13dd0) = iVar2;
            if (iVar2 != 0) {
              iVar2 = PyTuple_Pack(1,*(undefined4 *)(iVar1 + 0x13dd4));
              *(int *)(iVar1 + 0x13dd8) = iVar2;
              iVar1 = DAT_00014a50;
              if ((iVar2 != 0) &&
                 (iVar2 = PyTuple_Pack(8,*(undefined4 *)(DAT_00014a50 + 0x13f94),
                                       *(undefined4 *)(DAT_00014a50 + 0x13ffc),
                                       *(undefined4 *)(DAT_00014a50 + 0x13f84),
                                       *(undefined4 *)(DAT_00014a50 + 0x1400c),
                                       *(undefined4 *)(DAT_00014a50 + 0x14008),
                                       *(undefined4 *)(DAT_00014a50 + 0x13fe8),
                                       *(undefined4 *)(DAT_00014a50 + 0x14004),
                                       *(undefined4 *)(DAT_00014a50 + 0x14000)), iVar2 != 0)) {
                uVar3 = *(undefined4 *)(iVar1 + 0x13f9c);
                iVar2 = PyCode_New(4,0,8,0,3,*(undefined4 *)(iVar1 + 0x13f98),uVar3,uVar3,iVar2,
                                   uVar3,uVar3,*(undefined4 *)(iVar1 + 0x13fa4),
                                   *(undefined4 *)(iVar1 + 0x14010),0x5d,
                                   *(undefined4 *)(iVar1 + 0x13f98));
                *(int *)(iVar1 + 0x14014) = iVar2;
                if (iVar2 != 0) {
                  uVar3 = *(undefined4 *)(iVar5 + DAT_00014a54);
                  iVar2 = PyTuple_Pack(1,uVar3);
                  *(int *)(iVar1 + 0x14018) = iVar2;
                  if ((iVar2 != 0) &&
                     (iVar2 = PyTuple_Pack(4,*(undefined4 *)(iVar1 + 0x13f94),
                                           *(undefined4 *)(iVar1 + 0x14020),
                                           *(undefined4 *)(iVar1 + 0x1401c),
                                           *(undefined4 *)(iVar1 + 0x14024)), iVar2 != 0)) {
                    uVar4 = *(undefined4 *)(iVar1 + 0x13f9c);
                    iVar2 = PyCode_New(1,0,4,0,3,*(undefined4 *)(iVar1 + 0x13f98),uVar4,uVar4,iVar2,
                                       uVar4,uVar4,*(undefined4 *)(iVar1 + 0x13fa4),
                                       *(undefined4 *)(iVar1 + 0x14028),0x73,
                                       *(undefined4 *)(iVar1 + 0x13f98));
                    *(int *)(iVar1 + 0x1402c) = iVar2;
                    if ((iVar2 != 0) &&
                       (iVar2 = PyTuple_Pack(2,*(undefined4 *)(iVar1 + 0x13f94),
                                             *(undefined4 *)(iVar1 + 0x14030)), iVar2 != 0)) {
                      uVar4 = *(undefined4 *)(iVar1 + 0x13f9c);
                      iVar2 = PyCode_New(2,0,2,0,3,*(undefined4 *)(iVar1 + 0x13f98),uVar4,uVar4,
                                         iVar2,uVar4,uVar4,*(undefined4 *)(iVar1 + 0x13fa4),
                                         *(undefined4 *)(iVar1 + 0x14034),0x86,
                                         *(undefined4 *)(iVar1 + 0x13f98));
                      *(int *)(iVar1 + 0x14038) = iVar2;
                      if ((iVar2 != 0) &&
                         (iVar2 = PyTuple_Pack(2,*(undefined4 *)(iVar1 + 0x13f94),
                                               *(undefined4 *)(iVar1 + 0x1403c)), iVar2 != 0)) {
                        uVar4 = *(undefined4 *)(iVar1 + 0x13f9c);
                        iVar2 = PyCode_New(2,0,2,0,3,*(undefined4 *)(iVar1 + 0x13f98),uVar4,uVar4,
                                           iVar2,uVar4,uVar4,*(undefined4 *)(iVar1 + 0x13fa4),
                                           *(undefined4 *)(iVar1 + 0x14040),0x8e,
                                           *(undefined4 *)(iVar1 + 0x13f98));
                        *(int *)(iVar1 + 0x14044) = iVar2;
                        if ((iVar2 != 0) &&
                           (iVar2 = PyTuple_Pack(7,*(undefined4 *)(iVar1 + 0x13f94),
                                                 *(undefined4 *)(iVar1 + 0x1403c),
                                                 *(undefined4 *)(iVar1 + 0x13fcc),
                                                 *(undefined4 *)(iVar1 + 0x14048),
                                                 *(undefined4 *)(iVar1 + 0x13fbc),
                                                 *(undefined4 *)(iVar1 + 0x13fc0),
                                                 *(undefined4 *)(iVar1 + 0x13fc4)),
                           iVar1 = DAT_00014a58, iVar2 != 0)) {
                          uVar4 = *(undefined4 *)(DAT_00014a58 + 0x141fc);
                          iVar2 = PyCode_New(4,0,7,0,3,*(undefined4 *)(DAT_00014a58 + 0x141f8),uVar4
                                             ,uVar4,iVar2,uVar4,uVar4,
                                             *(undefined4 *)(DAT_00014a58 + 0x14204),
                                             *(undefined4 *)(DAT_00014a58 + 0x142ac),0x91,
                                             *(undefined4 *)(DAT_00014a58 + 0x141f8));
                          *(int *)(iVar1 + 0x142b0) = iVar2;
                          if ((iVar2 != 0) &&
                             (iVar2 = PyTuple_Pack(0xd,*(undefined4 *)(iVar1 + 0x141f4),
                                                   *(undefined4 *)(iVar1 + 0x1429c),
                                                   *(undefined4 *)(iVar1 + 0x142a8),
                                                   *(undefined4 *)(iVar1 + 0x14234),
                                                   *(undefined4 *)(iVar1 + 0x14230),
                                                   *(undefined4 *)(iVar1 + 0x142c0),
                                                   *(undefined4 *)(iVar1 + 0x142bc),
                                                   *(undefined4 *)(iVar1 + 0x142b8),
                                                   *(undefined4 *)(iVar1 + 0x14220),
                                                   *(undefined4 *)(iVar1 + 0x1421c),
                                                   *(undefined4 *)(iVar1 + 0x14224),
                                                   *(undefined4 *)(iVar1 + 0x142b4),
                                                   *(undefined4 *)(iVar1 + 0x142b4)), iVar2 != 0)) {
                            uVar4 = *(undefined4 *)(iVar1 + 0x141fc);
                            iVar2 = PyCode_New(6,0,0xd,0,3,*(undefined4 *)(iVar1 + 0x141f8),uVar4,
                                               uVar4,iVar2,uVar4,uVar4,
                                               *(undefined4 *)(iVar1 + 0x14204),
                                               *(undefined4 *)(iVar1 + 0x142c4),0x9d,
                                               *(undefined4 *)(iVar1 + 0x141f8));
                            *(int *)(iVar1 + 0x142c8) = iVar2;
                            if (iVar2 != 0) {
                              iVar2 = PyTuple_Pack(1,uVar3);
                              *(int *)(iVar1 + 0x142cc) = iVar2;
                              if ((iVar2 != 0) &&
                                 (iVar2 = PyTuple_Pack(4,*(undefined4 *)(iVar1 + 0x141f4),
                                                       *(undefined4 *)(iVar1 + 0x142d0),
                                                       *(undefined4 *)(iVar1 + 0x14234),
                                                       *(undefined4 *)(iVar1 + 0x14230)), iVar2 != 0
                                 )) {
                                uVar3 = *(undefined4 *)(iVar1 + 0x141fc);
                                iVar2 = PyCode_New(4,0,4,0,3,*(undefined4 *)(iVar1 + 0x141f8),uVar3,
                                                   uVar3,iVar2,uVar3,uVar3,
                                                   *(undefined4 *)(iVar1 + 0x14204),
                                                   *(undefined4 *)(iVar1 + 0x142d4),0xb7,
                                                   *(undefined4 *)(iVar1 + 0x141f8));
                                *(int *)(iVar1 + 0x142d8) = iVar2;
                                if ((iVar2 != 0) &&
                                   (iVar2 = PyTuple_Pack(2,*(undefined4 *)(iVar1 + 0x141f4),
                                                         *(undefined4 *)(iVar1 + 0x14220)),
                                   iVar2 != 0)) {
                                  uVar3 = *(undefined4 *)(iVar1 + 0x141fc);
                                  iVar2 = PyCode_New(2,0,2,0,3,*(undefined4 *)(iVar1 + 0x141f8),
                                                     uVar3,uVar3,iVar2,uVar3,uVar3,
                                                     *(undefined4 *)(iVar1 + 0x14204),
                                                     *(undefined4 *)(iVar1 + 0x142dc),0xbe,
                                                     *(undefined4 *)(iVar1 + 0x141f8));
                                  *(int *)(iVar1 + 0x142e0) = iVar2;
                                  if ((iVar2 != 0) &&
                                     (iVar2 = PyTuple_Pack(3,*(undefined4 *)(iVar1 + 0x141f4),
                                                           *(undefined4 *)(iVar1 + 0x142e8),
                                                           *(undefined4 *)(iVar1 + 0x142e4)),
                                     iVar2 != 0)) {
                                    uVar3 = *(undefined4 *)(iVar1 + 0x141fc);
                                    iVar2 = PyCode_New(2,0,3,0,3,*(undefined4 *)(iVar1 + 0x141f8),
                                                       uVar3,uVar3,iVar2,uVar3,uVar3,
                                                       *(undefined4 *)(iVar1 + 0x14204),
                                                       *(undefined4 *)(iVar1 + 0x14200),0xc2,
                                                       *(undefined4 *)(iVar1 + 0x141f8));
                                    *(int *)(iVar1 + 0x142ec) = iVar2;
                                    iVar1 = DAT_00014a5c;
                                    if ((iVar2 != 0) &&
                                       (iVar2 = PyTuple_Pack(2,*(undefined4 *)
                                                                (DAT_00014a5c + 0x1448c),
                                                             *(undefined4 *)(DAT_00014a5c + 0x144b8)
                                                            ), iVar2 != 0)) {
                                      uVar3 = *(undefined4 *)(iVar1 + 0x14494);
                                      iVar2 = PyCode_New(2,0,2,0,3,*(undefined4 *)(iVar1 + 0x14490),
                                                         uVar3,uVar3,iVar2,uVar3,uVar3,
                                                         *(undefined4 *)(iVar1 + 0x1449c),
                                                         *(undefined4 *)(iVar1 + 0x14588),0xe0,
                                                         *(undefined4 *)(iVar1 + 0x14490));
                                      *(int *)(iVar1 + 0x1458c) = iVar2;
                                      if ((iVar2 != 0) &&
                                         (iVar2 = PyTuple_Pack(1,*(undefined4 *)(iVar1 + 0x1448c)),
                                         iVar2 != 0)) {
                                        uVar3 = *(undefined4 *)(iVar1 + 0x14494);
                                        iVar2 = PyCode_New(1,0,1,0,3,
                                                           *(undefined4 *)(iVar1 + 0x14490),uVar3,
                                                           uVar3,iVar2,uVar3,uVar3,
                                                           *(undefined4 *)(iVar1 + 0x1449c),
                                                           *(undefined4 *)(iVar1 + 0x14590),0xe3,
                                                           *(undefined4 *)(iVar1 + 0x14490));
                                        *(int *)(iVar1 + 0x14594) = iVar2;
                                        if ((iVar2 != 0) &&
                                           (iVar2 = PyTuple_Pack(1,*(undefined4 *)(iVar1 + 0x1448c))
                                           , iVar2 != 0)) {
                                          uVar3 = *(undefined4 *)(iVar1 + 0x14494);
                                          iVar2 = PyCode_New(1,0,1,0,3,
                                                             *(undefined4 *)(iVar1 + 0x14490),uVar3,
                                                             uVar3,iVar2,uVar3,uVar3,
                                                             *(undefined4 *)(iVar1 + 0x1449c),
                                                             *(undefined4 *)(iVar1 + 0x14598),0xe6,
                                                             *(undefined4 *)(iVar1 + 0x14490));
                                          *(int *)(iVar1 + 0x1459c) = iVar2;
                                          if ((iVar2 != 0) &&
                                             (iVar2 = PyTuple_Pack(2,*(undefined4 *)
                                                                      (iVar1 + 0x1448c),
                                                                   *(undefined4 *)(iVar1 + 0x145a0))
                                             , iVar2 != 0)) {
                                            uVar3 = *(undefined4 *)(iVar1 + 0x14494);
                                            iVar2 = PyCode_New(1,0,2,0,3,
                                                               *(undefined4 *)(iVar1 + 0x14490),
                                                               uVar3,uVar3,iVar2,uVar3,uVar3,
                                                               *(undefined4 *)(iVar1 + 0x1449c),
                                                               *(undefined4 *)(iVar1 + 0x145a4),0xe9
                                                               ,*(undefined4 *)(iVar1 + 0x14490));
                                            *(int *)(iVar1 + 0x145a8) = iVar2;
                                            if ((iVar2 != 0) &&
                                               (iVar2 = PyTuple_Pack(1,*(undefined4 *)
                                                                        (iVar1 + 0x1448c)),
                                               iVar2 != 0)) {
                                              uVar3 = *(undefined4 *)(iVar1 + 0x14494);
                                              iVar2 = PyCode_New(1,0,1,0,3,
                                                                 *(undefined4 *)(iVar1 + 0x14490),
                                                                 uVar3,uVar3,iVar2,uVar3,uVar3,
                                                                 *(undefined4 *)(iVar1 + 0x1449c),
                                                                 *(undefined4 *)(iVar1 + 0x145ac),
                                                                 0xee,*(undefined4 *)
                                                                       (iVar1 + 0x14490));
                                              *(int *)(iVar1 + 0x145b0) = iVar2;
                                              iVar1 = DAT_00014a60;
                                              if ((iVar2 != 0) &&
                                                 (iVar2 = PyTuple_Pack(4,*(undefined4 *)
                                                                          (DAT_00014a60 + 0x146b8),
                                                                       *(undefined4 *)
                                                                        (DAT_00014a60 + 0x147e0),
                                                                       *(undefined4 *)
                                                                        (DAT_00014a60 + 0x146f8),
                                                                       *(undefined4 *)
                                                                        (DAT_00014a60 + 0x146f4)),
                                                 iVar2 != 0)) {
                                                uVar3 = *(undefined4 *)(iVar1 + 0x146c0);
                                                iVar2 = PyCode_New(4,0,4,0,3,
                                                                   *(undefined4 *)(iVar1 + 0x146bc),
                                                                   uVar3,uVar3,iVar2,uVar3,uVar3,
                                                                   *(undefined4 *)(iVar1 + 0x146c8),
                                                                   *(undefined4 *)(iVar1 + 0x14798),
                                                                   0xf1,*(undefined4 *)
                                                                         (iVar1 + 0x146bc));
                                                *(int *)(iVar1 + 0x147e4) = iVar2;
                                                if ((iVar2 != 0) &&
                                                   (iVar2 = PyTuple_Pack(3,*(undefined4 *)
                                                                            (iVar1 + 0x146b8),
                                                                         *(undefined4 *)
                                                                          (iVar1 + 0x147ec),
                                                                         *(undefined4 *)
                                                                          (iVar1 + 0x147e8)),
                                                   iVar2 != 0)) {
                                                  uVar3 = *(undefined4 *)(iVar1 + 0x146c0);
                                                  iVar2 = PyCode_New(2,0,3,0,3,
                                                                     *(undefined4 *)
                                                                      (iVar1 + 0x146bc),uVar3,uVar3,
                                                                     iVar2,uVar3,uVar3,
                                                                     *(undefined4 *)
                                                                      (iVar1 + 0x146c8),
                                                                     *(undefined4 *)
                                                                      (iVar1 + 0x147f0),0xf4,
                                                                     *(undefined4 *)
                                                                      (iVar1 + 0x146bc));
                                                  *(int *)(iVar1 + 0x147f4) = iVar2;
                                                  if ((iVar2 != 0) &&
                                                     (iVar2 = PyTuple_Pack(0xe,*(undefined4 *)
                                                                                (iVar1 + 0x146b8),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x147e8),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x1476c),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14784),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x147fc),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14760),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146f8),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146f4),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146f0),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146e0),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146e4),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x147f8),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14778),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14778)),
                                                     iVar2 != 0)) {
                                                    uVar3 = *(undefined4 *)(iVar1 + 0x146c0);
                                                    iVar2 = PyCode_New(4,0,0xe,0,3,
                                                                       *(undefined4 *)
                                                                        (iVar1 + 0x146bc),uVar3,
                                                                       uVar3,iVar2,uVar3,uVar3,
                                                                       *(undefined4 *)
                                                                        (iVar1 + 0x146c8),
                                                                       *(undefined4 *)
                                                                        (iVar1 + 0x14800),0xf9,
                                                                       *(undefined4 *)
                                                                        (iVar1 + 0x146bc));
                                                    *(int *)(iVar1 + 0x14804) = iVar2;
                                                    if (iVar2 != 0) {
                                                      iVar2 = PyTuple_Pack(1,*(undefined4 *)
                                                                              (iVar5 + DAT_00014a54)
                                                                          );
                                                      *(int *)(iVar1 + 0x14808) = iVar2;
                                                      if ((iVar2 != 0) &&
                                                         (iVar2 = PyTuple_Pack(2,*(undefined4 *)
                                                                                  (iVar1 + 0x146b8),
                                                                               *(undefined4 *)
                                                                                (iVar1 + 0x147cc)),
                                                         iVar2 != 0)) {
                                                        uVar3 = *(undefined4 *)(iVar1 + 0x146c0);
                                                        iVar2 = PyCode_New(1,0,2,0,7,
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146bc),uVar3,
                                                                           uVar3,iVar2,uVar3,uVar3,
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146c8),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x1480c),0x114,
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x146bc));
                                                        *(int *)(iVar1 + 0x14810) = iVar2;
                                                        if ((iVar2 != 0) &&
                                                           (iVar2 = PyTuple_Pack(4,*(undefined4 *)
                                                                                    (iVar1 + 0x146b8
                                                                                    ),*(undefined4 *
                                                                                       )(iVar1 + 
                                                  0x14754),*(undefined4 *)(iVar1 + 0x14814),
                                                  *(undefined4 *)(iVar1 + 0x147cc)),
                                                  iVar1 = DAT_00014a64, iVar2 != 0)) {
                                                    uVar3 = *(undefined4 *)(DAT_00014a64 + 0x1493c);
                                                    iVar2 = PyCode_New(2,0,4,0,3,
                                                                       *(undefined4 *)
                                                                        (DAT_00014a64 + 0x14938),
                                                                       uVar3,uVar3,iVar2,uVar3,uVar3
                                                                       ,*(undefined4 *)
                                                                         (DAT_00014a64 + 0x14944),
                                                                       *(undefined4 *)
                                                                        (DAT_00014a64 + 0x14a94),
                                                                       0x117,*(undefined4 *)
                                                                              (DAT_00014a64 +
                                                                              0x14938));
                                                    *(int *)(iVar1 + 0x14a98) = iVar2;
                                                    if ((iVar2 != 0) &&
                                                       (iVar2 = PyTuple_Pack(2,*(undefined4 *)
                                                                                (iVar1 + 0x14934),
                                                                             *(undefined4 *)
                                                                              ((int)&DAT_00014a48 +
                                                                              iVar1)), iVar2 != 0))
                                                    {
                                                      uVar3 = *(undefined4 *)(iVar1 + 0x1493c);
                                                      iVar2 = PyCode_New(2,0,2,0,3,
                                                                         *(undefined4 *)
                                                                          (iVar1 + 0x14938),uVar3,
                                                                         uVar3,iVar2,uVar3,uVar3,
                                                                         *(undefined4 *)
                                                                          (iVar1 + 0x14944),
                                                                         *(undefined4 *)
                                                                          (iVar1 + 0x14a9c),0x11f,
                                                                         *(undefined4 *)
                                                                          (iVar1 + 0x14938));
                                                      *(int *)(iVar1 + 0x14aa0) = iVar2;
                                                      if ((iVar2 != 0) &&
                                                         (iVar2 = PyTuple_Pack(6,*(undefined4 *)
                                                                                  (iVar1 + 0x14934),
                                                                               *(undefined4 *)
                                                                                ((int)&DAT_00014a64
                                                                                + iVar1),
                                                                               *(undefined4 *)
                                                                                (iVar1 + 0x149e8),
                                                                               *(undefined4 *)
                                                                                (iVar1 + 0x14974),
                                                                               *(undefined4 *)
                                                                                (iVar1 + 0x14970),
                                                                               *(undefined4 *)
                                                                                ((int)&DAT_00014a48
                                                                                + iVar1)),
                                                         iVar2 != 0)) {
                                                        uVar3 = *(undefined4 *)(iVar1 + 0x1493c);
                                                        iVar2 = PyCode_New(3,0,6,0,3,
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14938),uVar3,
                                                                           uVar3,iVar2,uVar3,uVar3,
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14944),
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14aa4),0x123,
                                                                           *(undefined4 *)
                                                                            (iVar1 + 0x14938));
                                                        *(int *)(iVar1 + 0x14aa8) = iVar2;
                                                        return -(uint)(iVar2 == 0);
                                                      }
                                                    }
                                                  }
                                                  }
                                                  }
                                                  }
                                                }
                                              }
                                            }
                                          }
                                        }
                                      }
                                    }
                                  }
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return -1;
}




/* ============================================
 * Function: FUN_00014a68
 * Address:  0x14a68
 * ============================================ */

undefined4
FUN_00014a68(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
            uint param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = DAT_00014af8;
  iVar1 = PyObject_GetAttrString(param_1,param_3);
  if (iVar1 == 0) {
    iVar3 = PyErr_ExceptionMatches(**(undefined4 **)(iVar3 + 0x14a88 + DAT_00014b00));
    if (iVar3 == 0) {
      uVar2 = 0xffffffff;
    }
    else {
      PyErr_Clear();
      uVar2 = 0;
    }
  }
  else {
    param_5 = param_5 & 1;
    if (iVar1 != *(int *)(iVar3 + 0x14a88 + DAT_00014afc)) {
      param_5 = 1;
    }
    uVar2 = 0;
    if (param_5 != 0) {
      uVar2 = PyDict_SetItemString(param_2,param_4,iVar1);
    }
    FUN_00017fec(iVar1);
  }
  return uVar2;
}




/* ============================================
 * Function: FUN_00014b04
 * Address:  0x14b04
 * ============================================ */

int FUN_00014b04(void)

{
  int iVar1;
  int iVar2;
  longlong *plVar3;
  longlong lVar4;
  
  iVar2 = PyThreadState_Get();
  iVar1 = DAT_00014b8c;
  lVar4 = PyInterpreterState_GetID(*(undefined4 *)(iVar2 + 8));
  plVar3 = (longlong *)(DAT_00014b90 + 0x14b30);
  if (*(int *)(DAT_00014b90 + 0x14b34) == -1 && *(int *)plVar3 == -1) {
    *plVar3 = lVar4;
    return -(uint)(lVar4 == -1);
  }
  if (lVar4 == *plVar3) {
    return 0;
  }
  PyErr_SetString(**(undefined4 **)(iVar1 + 0x14b2c + DAT_00014b94),DAT_00014b98 + 0x14b78);
  return -1;
}




/* ============================================
 * Function: FUN_00014b9c
 * Address:  0x14b9c
 * ============================================ */

void FUN_00014b9c(int param_1,undefined4 param_2)

{
  *(undefined4 *)(param_1 + 0x4c) = param_2;
  FUN_00018934(param_2);
  return;
}




/* ============================================
 * Function: FUN_00014ba8
 * Address:  0x14ba8
 * ============================================ */

int FUN_00014ba8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = *(int *)(param_2 + 8);
  iVar6 = 0;
  iVar5 = DAT_00014c4c + 0x14bc8;
  piVar3 = (int *)(param_2 + 0xc);
  while( true ) {
    if (iVar7 <= iVar6) {
      if (param_1 == 0) {
        param_1 = *(int *)(iVar5 + DAT_00014c50);
      }
      FUN_00018934(param_1);
      return param_1;
    }
    iVar4 = *(int *)(*piVar3 + 4);
    iVar1 = iVar4;
    if (((param_1 != 0) && (iVar2 = PyType_IsSubtype(param_1,iVar4), iVar1 = param_1, iVar2 == 0))
       && (iVar2 = PyType_IsSubtype(iVar4,param_1), iVar1 = iVar4, iVar2 == 0)) break;
    param_1 = iVar1;
    iVar6 = iVar6 + 1;
    piVar3 = piVar3 + 1;
  }
  PyErr_SetString(**(undefined4 **)(iVar5 + DAT_00014c54),DAT_00014c58 + 0x14c30);
  return 0;
}




/* ============================================
 * Function: FUN_00014c5c
 * Address:  0x14c5c
 * ============================================ */

int FUN_00014c5c(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar1 = FUN_00014b04();
  if (iVar1 != 0) {
    return 0;
  }
  iVar1 = *(int *)(DAT_00014d98 + 0x14ef0);
  if (iVar1 != 0) {
    FUN_00018934(iVar1);
    return iVar1;
  }
  iVar1 = PyObject_GetAttrString(param_1,DAT_00014d9c + 0x14cac);
  if (iVar1 != 0) {
    iVar3 = PyModule_NewObject();
    FUN_00017fec(iVar1);
    if (iVar3 != 0) {
      iVar1 = PyModule_GetDict(iVar3);
      if ((((iVar1 != 0) &&
           (iVar2 = FUN_00014a68(param_1,iVar1,DAT_00014da4 + 0x14d14,DAT_00014da0 + 0x14d10,1),
           -1 < iVar2)) &&
          (iVar2 = FUN_00014a68(param_1,iVar1,DAT_00014dac + 0x14d3c,DAT_00014da8 + 0x14d38,1),
          -1 < iVar2)) &&
         ((iVar2 = FUN_00014a68(param_1,iVar1,DAT_00014db4 + 0x14d64,DAT_00014db0 + 0x14d60,1),
          -1 < iVar2 &&
          (iVar1 = FUN_00014a68(param_1,iVar1,DAT_00014dbc + 0x14d8c,DAT_00014db8 + 0x14d88,0),
          -1 < iVar1)))) {
        return iVar3;
      }
      goto LAB_00014cb8;
    }
  }
  iVar3 = 0;
LAB_00014cb8:
  FUN_000182bc(iVar3);
  return 0;
}




/* ============================================
 * Function: FUN_00014dc0
 * Address:  0x14dc0
 * ============================================ */

int FUN_00014dc0(int param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  int iVar6;
  
  iVar6 = DAT_00014ec8 + 0x14ddc;
  iVar1 = PyImport_AddModule(DAT_00014ec4 + 0x14dd8);
  if (iVar1 == 0) {
    return 0;
  }
  FUN_00018934();
  iVar2 = PyObject_GetAttrString(iVar1,*(undefined4 *)(param_1 + 0xc));
  if (iVar2 == 0) {
    iVar6 = PyErr_ExceptionMatches(**(undefined4 **)(iVar6 + DAT_00014ed8));
    if (iVar6 != 0) {
      PyErr_Clear();
      iVar6 = PyType_Ready(param_1);
      if ((-1 < iVar6) &&
         (iVar6 = PyObject_SetAttrString(iVar1,*(undefined4 *)(param_1 + 0xc),param_1), -1 < iVar6))
      {
        FUN_00018934(param_1);
        iVar2 = param_1;
        goto LAB_00014eb0;
      }
    }
  }
  else {
    iVar3 = FUN_00019a38(*(undefined4 *)(iVar2 + 4));
    if (iVar3 == 0) {
      puVar5 = *(undefined4 **)(iVar6 + DAT_00014ecc);
      uVar4 = *(undefined4 *)(param_1 + 0xc);
      iVar6 = DAT_00014ed0 + 0x14e24;
    }
    else {
      if (*(int *)(iVar2 + 0x10) == *(int *)(param_1 + 0x10)) goto LAB_00014eb0;
      puVar5 = *(undefined4 **)(iVar6 + DAT_00014ecc);
      uVar4 = *(undefined4 *)(param_1 + 0xc);
      iVar6 = DAT_00014ed4 + 0x14e60;
    }
    PyErr_Format(*puVar5,iVar6,uVar4);
  }
  FUN_000182bc(iVar2);
  iVar2 = 0;
LAB_00014eb0:
  FUN_00017fec(iVar1);
  return iVar2;
}




/* ============================================
 * Function: FUN_00014edc
 * Address:  0x14edc
 * ============================================ */

int FUN_00014edc(void)

{
  int iVar1;
  
  iVar1 = FUN_00014dc0(DAT_00014f0c + 0x1521c);
  *(int *)(DAT_00014f10 + 0x15174) = iVar1;
  return -(uint)(iVar1 == 0);
}




/* ============================================
 * Function: FUN_00014f14
 * Address:  0x14f14
 * ============================================ */

int FUN_00014f14(void)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_00014f68;
  iVar2 = DAT_00014f64 + 0x14f24;
  *(undefined4 *)(DAT_00014f68 + 0x15374) = *(undefined4 *)(iVar2 + DAT_00014f6c);
  *(undefined4 *)(iVar1 + 0x15398) = *(undefined4 *)(iVar2 + DAT_00014f70);
  iVar1 = FUN_00014dc0();
  *(int *)(DAT_00014f74 + 0x151d0) = iVar1;
  return -(uint)(iVar1 == 0);
}




/* ============================================
 * Function: FUN_00014f78
 * Address:  0x14f78
 * ============================================ */

undefined4 FUN_00014f78(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  iVar3 = DAT_0001509c;
  iVar1 = PyDict_New();
  if ((iVar1 != 0) &&
     (iVar2 = PyDict_SetItemString
                        (iVar1,DAT_000150a4 + 0x14fac,
                         *(undefined4 *)(iVar3 + 0x14f94 + DAT_000150a0)), -1 < iVar2)) {
    puVar5 = (undefined4 *)(DAT_000150a8 + 0x14fd0);
    iVar2 = PyDict_SetItemString
                      (iVar1,DAT_000150ac + 0x14fd4,*(undefined4 *)(DAT_000150a8 + 0x1524c));
    if ((-1 < iVar2) &&
       (((iVar2 = PyDict_SetItemString(iVar1,DAT_000150b0 + 0x14ff4,param_1), -1 < iVar2 &&
         (iVar2 = PyDict_SetItemString(iVar1,DAT_000150b4 + 0x15010,*puVar5), -1 < iVar2)) &&
        (iVar2 = PyRun_StringFlags(DAT_000150b8 + 0x15030,0x101,iVar1,iVar1,0), iVar2 != 0)))) {
      FUN_00017fec();
      FUN_00017fec(iVar1);
      return param_1;
    }
  }
  FUN_000182bc(iVar1);
  PyErr_WriteUnraisable(param_1);
  iVar3 = PyErr_WarnEx(**(undefined4 **)(iVar3 + 0x14f94 + DAT_000150bc),DAT_000150c0 + 0x15080,1);
  uVar4 = param_1;
  if (iVar3 < 0) {
    uVar4 = 0;
    FUN_00017fec(param_1);
  }
  return uVar4;
}




/* ============================================
 * Function: thunk_FUN_00014f78
 * Address:  0x150c4
 * ============================================ */

undefined4 thunk_FUN_00014f78(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 *puVar5;
  
  iVar3 = DAT_0001509c;
  iVar1 = PyDict_New();
  if ((iVar1 != 0) &&
     (iVar2 = PyDict_SetItemString
                        (iVar1,DAT_000150a4 + 0x14fac,
                         *(undefined4 *)(iVar3 + 0x14f94 + DAT_000150a0)), -1 < iVar2)) {
    puVar5 = (undefined4 *)(DAT_000150a8 + 0x14fd0);
    iVar2 = PyDict_SetItemString
                      (iVar1,DAT_000150ac + 0x14fd4,*(undefined4 *)(DAT_000150a8 + 0x1524c));
    if ((-1 < iVar2) &&
       (((iVar2 = PyDict_SetItemString(iVar1,DAT_000150b0 + 0x14ff4,param_1), -1 < iVar2 &&
         (iVar2 = PyDict_SetItemString(iVar1,DAT_000150b4 + 0x15010,*puVar5), -1 < iVar2)) &&
        (iVar2 = PyRun_StringFlags(DAT_000150b8 + 0x15030,0x101,iVar1,iVar1,0), iVar2 != 0)))) {
      FUN_00017fec();
      FUN_00017fec(iVar1);
      return param_1;
    }
  }
  FUN_000182bc(iVar1);
  PyErr_WriteUnraisable(param_1);
  iVar3 = PyErr_WarnEx(**(undefined4 **)(iVar3 + 0x14f94 + DAT_000150bc),DAT_000150c0 + 0x15080,1);
  uVar4 = param_1;
  if (iVar3 < 0) {
    uVar4 = 0;
    FUN_00017fec(param_1);
  }
  return uVar4;
}




/* ============================================
 * Function: FUN_000150c8
 * Address:  0x150c8
 * ============================================ */

undefined4 FUN_000150c8(void)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = DAT_00015184;
  iVar4 = DAT_00015188 + 0x150e0;
  if (*(int *)(DAT_00015184 + 0x15364) == 0) {
    iVar1 = PyImport_ImportModule(DAT_0001518c + 0x15100);
    if (iVar1 == 0) {
      PyErr_WriteUnraisable();
      iVar2 = PyErr_WarnEx(**(undefined4 **)(iVar4 + DAT_00015190),DAT_00015194 + 0x15124,1);
      if (-1 < iVar2) {
LAB_00015150:
        iVar2 = PyImport_ImportModule(DAT_00015198 + 0x1515c);
        if (iVar2 == 0) {
LAB_00015164:
          PyErr_Clear();
          return 0;
        }
        iVar2 = thunk_FUN_00014f78();
        FUN_000182bc();
        if (iVar2 == 0) goto LAB_00015164;
        goto LAB_000150e8;
      }
    }
    else {
      iVar4 = thunk_FUN_00014f78();
      *(undefined4 *)(iVar2 + 0x15364) = 1;
      if (iVar4 != 0) {
        FUN_00017fec();
        goto LAB_00015150;
      }
    }
    uVar3 = 0xffffffff;
  }
  else {
LAB_000150e8:
    uVar3 = 0;
  }
  return uVar3;
}




/* ============================================
 * Function: FUN_0001519c
 * Address:  0x1519c
 * ============================================ */

int FUN_0001519c(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar5 = DAT_0001526c;
  iVar1 = PyList_New(0);
  if (iVar1 == 0) {
    iVar3 = 0;
    iVar4 = 0;
  }
  else {
    iVar2 = PyModule_GetDict(*(undefined4 *)(DAT_00015270 + 0x15444));
    if (iVar2 == 0) {
      iVar3 = 0;
      iVar4 = iVar3;
    }
    else {
      iVar3 = PyDict_New();
      iVar4 = 0;
      if (((iVar3 != 0) &&
          (iVar4 = PyImport_ImportModuleLevelObject(param_1,iVar2,iVar3,iVar1,1,param_2,param_3),
          iVar4 == 0)) &&
         (iVar5 = PyErr_ExceptionMatches(**(undefined4 **)(iVar5 + 0x151b8 + DAT_00015274)),
         iVar5 != 0)) {
        PyErr_Clear();
        iVar4 = PyImport_ImportModuleLevelObject(param_1,iVar2,iVar3,iVar1,0);
      }
    }
  }
  FUN_000182bc(iVar1);
  FUN_000182bc(iVar3);
  return iVar4;
}




/* ============================================
 * Function: FUN_00015278
 * Address:  0x15278
 * ============================================ */

int FUN_00015278(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  iVar3 = DAT_00015380 + 0x15290;
  if (param_1 != 0) {
    iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_00015384 + 0x15530));
    if (iVar1 != 0) {
      iVar2 = PyTuple_Pack(2,param_3,param_2);
      if (iVar2 == 0) {
        FUN_00017fec(iVar1);
        return 0;
      }
      iVar3 = PyObject_Call(iVar1,iVar2,0);
      FUN_00017fec(iVar1);
      FUN_00017fec(iVar2);
      goto LAB_00015300;
    }
    iVar3 = PyErr_ExceptionMatches(**(undefined4 **)(iVar3 + DAT_0001538c));
    if (iVar3 == 0) {
      return 0;
    }
    PyErr_Clear();
  }
  iVar3 = PyDict_New();
LAB_00015300:
  iVar1 = DAT_00015388;
  if (iVar3 != 0) {
    iVar2 = PyObject_SetItem(iVar3,*(undefined4 *)(DAT_00015388 + 0x155ac),param_5);
    if ((-1 < iVar2) &&
       (iVar1 = PyObject_SetItem(iVar3,*(undefined4 *)(iVar1 + 0x155b0),param_4), -1 < iVar1)) {
      return iVar3;
    }
    FUN_00017fec(iVar3);
  }
  return 0;
}




/* ============================================
 * Function: FUN_00015390
 * Address:  0x15390
 * ============================================ */

int FUN_00015390(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6)

{
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  
  if (param_1 != 0) {
    *(undefined4 *)(param_1 + 8) = param_2;
    *(undefined4 *)(param_1 + 0x48) = 0;
    *(undefined4 *)(param_1 + 0x14) = 0;
    *(int *)(param_1 + 0xc) = param_1;
    FUN_00018944(0);
    *(undefined4 *)(param_1 + 0x34) = 0;
    FUN_00018944(param_4);
    *(undefined4 *)(param_1 + 0x10) = param_4;
    *(undefined4 *)(param_1 + 0x1c) = 0;
    *(undefined4 *)(param_1 + 0x20) = 0;
    FUN_00018934(extraout_r2);
    *(undefined4 *)(param_1 + 0x24) = extraout_r2_00;
    *(undefined4 *)(param_1 + 0x28) = 0;
    *(undefined4 *)(param_1 + 0x38) = 0;
    *(undefined4 *)(param_1 + 0x2c) = param_5;
    FUN_00018934(param_5);
    FUN_00018944(param_6);
    *(undefined4 *)(param_1 + 0x30) = param_6;
    *(undefined4 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(param_1 + 0x44) = 0;
    *(undefined4 *)(param_1 + 0x3c) = 0;
    *(undefined4 *)(param_1 + 0x4c) = 0;
    *(undefined4 *)(param_1 + 0x50) = 0;
    *(undefined4 *)(param_1 + 0x54) = 0;
    *(undefined4 *)(param_1 + 0x58) = 0;
  }
  return param_1;
}




/* ============================================
 * Function: FUN_00015430
 * Address:  0x15430
 * ============================================ */

int FUN_00015430(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = param_3;
  uVar1 = _PyObject_GC_New(*(undefined4 *)(DAT_00015488 + 0x156c8));
  iVar2 = FUN_00015390(uVar1,param_1,param_2,param_3,param_4,param_5,uVar3);
  if (iVar2 != 0) {
    PyObject_GC_Track();
  }
  return iVar2;
}




/* ============================================
 * Function: FUN_0001548c
 * Address:  0x1548c
 * ============================================ */

undefined4 FUN_0001548c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = DAT_00015538 + 0x154b4;
  iVar1 = PyObject_GetItem(param_4,*(undefined4 *)(DAT_00015534 + 0x15744));
  iVar2 = iVar1;
  if (iVar1 == 0) {
    iVar2 = PyErr_ExceptionMatches(**(undefined4 **)(iVar4 + DAT_0001553c));
    if (iVar2 == 0) {
      return 0;
    }
    PyErr_Clear();
    iVar2 = param_1;
  }
  iVar4 = PyTuple_Pack(3,param_2,param_3,param_4);
  uVar3 = 0;
  if (iVar4 != 0) {
    uVar3 = PyObject_Call(iVar2,iVar4,0);
    FUN_00017fec(iVar4);
  }
  FUN_000182bc(iVar1);
  return uVar3;
}




/* ============================================
 * Function: FUN_00015540
 * Address:  0x15540
 * ============================================ */

undefined4 FUN_00015540(void)

{
  undefined4 uVar1;
  int iVar2;
  int *piVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar4 = DAT_000155ec + 0x15564;
  while( true ) {
    puVar5 = *(undefined4 **)(iVar4 + -0x14);
    if (puVar5 == (undefined4 *)0x0) {
      return 0;
    }
    if (*(char *)(iVar4 + -4) == '\0' && *(char *)(iVar4 + -3) == '\0') {
      uVar1 = PyBytes_FromStringAndSize(*(undefined4 *)(iVar4 + -0x10),*(int *)(iVar4 + -0xc) + -1);
    }
    else if (*(char *)(iVar4 + -2) == '\0') {
      if (*(int *)(iVar4 + -8) == 0) {
        uVar1 = PyUnicode_FromStringAndSize
                          (*(undefined4 *)(iVar4 + -0x10),*(int *)(iVar4 + -0xc) + -1);
      }
      else {
        uVar1 = PyUnicode_Decode();
      }
    }
    else {
      uVar1 = PyUnicode_InternFromString();
    }
    piVar3 = *(int **)(iVar4 + -0x14);
    *puVar5 = uVar1;
    if (*piVar3 == 0) break;
    iVar4 = iVar4 + 0x14;
    iVar2 = PyObject_Hash();
    if (iVar2 == -1) {
      return 0xffffffff;
    }
  }
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_000155f0
 * Address:  0x155f0
 * ============================================ */

int FUN_000155f0(void)

{
  int iVar1;
  int iVar2;
  
  iVar2 = FUN_00015540();
  iVar1 = DAT_00015770;
  if (-1 < iVar2) {
    iVar2 = PyFloat_FromDouble(0);
    *(int *)(iVar1 + 0x158bc) = iVar2;
    if (iVar2 != 0) {
      iVar2 = PyFloat_FromDouble((int)DAT_00015760);
      *(int *)(iVar1 + 0x158c0) = iVar2;
      if (iVar2 != 0) {
        iVar2 = PyFloat_FromDouble((int)DAT_00015768);
        *(int *)(iVar1 + 0x158c4) = iVar2;
        if (iVar2 != 0) {
          iVar2 = PyLong_FromLong(0);
          *(int *)(iVar1 + 0x158c8) = iVar2;
          if (iVar2 != 0) {
            iVar2 = PyLong_FromLong(1);
            *(int *)(iVar1 + 0x158cc) = iVar2;
            if (iVar2 != 0) {
              iVar2 = PyLong_FromLong(2);
              *(int *)(iVar1 + 0x158d0) = iVar2;
              if (iVar2 != 0) {
                iVar2 = PyLong_FromLong(3);
                *(int *)(iVar1 + 0x158d4) = iVar2;
                if (iVar2 != 0) {
                  iVar2 = PyLong_FromLong(4);
                  *(int *)(iVar1 + 0x158d8) = iVar2;
                  if (iVar2 != 0) {
                    iVar2 = PyLong_FromLong(5);
                    *(int *)(iVar1 + 0x158dc) = iVar2;
                    iVar1 = DAT_00015774;
                    if (iVar2 != 0) {
                      iVar2 = PyLong_FromLong(0xa0);
                      *(int *)(iVar1 + 0x15998) = iVar2;
                      if (iVar2 != 0) {
                        iVar2 = PyLong_FromLong(0xfc);
                        *(int *)(iVar1 + 0x1599c) = iVar2;
                        if (iVar2 != 0) {
                          iVar2 = PyLong_FromLong(0xfe);
                          *(int *)(iVar1 + 0x159a0) = iVar2;
                          if (iVar2 != 0) {
                            iVar2 = PyLong_FromLong(0x960);
                            *(int *)(iVar1 + 0x159a4) = iVar2;
                            if (iVar2 != 0) {
                              iVar2 = PyLong_FromLong(0xe10);
                              *(int *)(iVar1 + 0x159a8) = iVar2;
                              if (iVar2 != 0) {
                                iVar2 = PyLong_FromLong(DAT_00015778);
                                *(int *)(iVar1 + 0x15708) = iVar2;
                                if (iVar2 != 0) {
                                  iVar2 = PyLong_FromLong(0xffffffec);
                                  *(int *)(iVar1 + 0x159ac) = iVar2;
                                  return -(uint)(iVar2 == 0);
                                }
                              }
                            }
                          }
                        }
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  return -1;
}




/* ============================================
 * Function: FUN_0001577c
 * Address:  0x1577c
 * ============================================ */

int FUN_0001577c(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int *piVar6;
  undefined4 *puVar7;
  int iVar8;
  undefined4 uVar9;
  undefined4 uVar10;
  int iVar11;
  int iVar12;
  
  iVar3 = DAT_000159c8;
  piVar6 = (int *)(DAT_000159c8 + 0x15794);
  iVar12 = DAT_000159cc + 0x15798;
  iVar11 = *(int *)((int)&DAT_00015a08 + DAT_000159c8);
  if (iVar11 != 0) {
    if (iVar11 != param_1) {
      PyErr_SetString(**(undefined4 **)(iVar12 + DAT_000159d0),DAT_000159d4 + 88000,param_3,
                      *(undefined4 **)(iVar12 + DAT_000159d0),param_1,param_2,param_3,param_4);
      return -1;
    }
    return 0;
  }
  iVar1 = FUN_00013c44();
  iVar2 = 0;
  iVar5 = iVar2;
  iVar4 = iVar2;
  if (iVar1 < 0) {
    uVar9 = 0x32f6;
    uVar10 = 1;
LAB_00016ce0:
    FUN_000182bc(iVar5);
    FUN_000182bc(iVar2);
    FUN_000182bc(iVar11);
    FUN_000182bc(iVar4);
    if (*(int *)(DAT_00017390 + 0x16f80) == 0) {
      iVar11 = PyErr_Occurred();
      if (iVar11 == 0) {
        PyErr_SetString(**(undefined4 **)(iVar12 + DAT_000173a4),DAT_000173a8 + 0x17388);
      }
      goto LAB_00016d5c;
    }
    if (*(int *)(DAT_00017390 + 0x16f78) != 0) {
      FUN_00019490(DAT_00017398 + 0x16d3c,uVar9,uVar10,DAT_00017394 + 0x16d38);
    }
    iVar5 = *(int *)(DAT_0001739c + 0x16fbc);
    if (iVar5 == 0) goto LAB_00016d5c;
    *(undefined4 *)(DAT_0001739c + 0x16fbc) = 0;
  }
  else {
    *(int *)((int)&DAT_00015a04 + iVar3) = *(int *)(*(int *)(iVar12 + DAT_000159d8) + 0x10) + -4;
    iVar1 = PyTuple_New(0);
    *(int *)(iVar3 + 0x157e0) = iVar1;
    if (iVar1 == 0) {
      uVar9 = 0x32fa;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar8 = DAT_000159dc + 0x15818;
    iVar1 = PyBytes_FromStringAndSize(iVar8,0);
    *(int *)(iVar3 + 0x157dc) = iVar1;
    if (iVar1 == 0) {
      uVar9 = 0x32fb;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar1 = PyUnicode_FromStringAndSize(iVar8,0);
    if (iVar1 == 0) {
      uVar9 = 0x32fc;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar1 = FUN_00014edc();
    if (iVar1 < 0) {
      uVar9 = 0x32fe;
      uVar10 = 1;
      goto LAB_00016ce0;
    }
    iVar1 = FUN_00014f14();
    if (iVar1 < 0) {
      uVar9 = 0x3307;
      uVar10 = 1;
      goto LAB_00016ce0;
    }
    *(int *)((int)&DAT_00015a08 + iVar3) = param_1;
    FUN_00018934(param_1);
    iVar2 = PyModule_GetDict();
    *(int *)((int)&DAT_00015a00 + iVar3) = iVar2;
    if (iVar2 == 0) {
      uVar9 = 0x3322;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00018934();
    iVar2 = PyImport_AddModule(DAT_000159e0 + 0x15888);
    *piVar6 = iVar2;
    if (iVar2 == 0) {
      uVar9 = 0x3324;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00018934();
    iVar2 = PyImport_AddModule(DAT_000159e4 + 0x158a8);
    *(int *)((int)&DAT_000159e0 + iVar3) = iVar2;
    iVar3 = DAT_000159e8;
    if (iVar2 == 0) {
      uVar9 = 0x3326;
      iVar11 = 0;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00018934();
    iVar2 = PyObject_SetAttrString
                      (*(undefined4 *)(iVar3 + 0x15b40),DAT_000159ec + 0x158d0,
                       *(undefined4 *)(iVar3 + 0x158cc));
    if (iVar2 < 0) {
      uVar9 = 0x3328;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = FUN_000155f0();
    if (iVar2 < 0) {
      uVar9 = 0x332a;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    if ((**(int **)(iVar12 + DAT_000159f0) != 0) &&
       (iVar3 = PyObject_SetAttr(*(undefined4 *)(iVar3 + 0x15b40),*(undefined4 *)(iVar3 + 89000),
                                 *(undefined4 *)(iVar3 + 0x15ba4)), iVar3 < 0)) {
      uVar9 = 0x332f;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = PyImport_GetModuleDict();
    if (iVar3 == 0) {
      uVar9 = 0x3333;
      uVar10 = 1;
      iVar2 = 0;
      iVar5 = 0;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar5 = DAT_000159f4 + 0x15960;
    iVar2 = PyDict_GetItemString(iVar3,iVar5);
    if ((iVar2 == 0) &&
       (iVar3 = PyDict_SetItemString(iVar3,iVar5,*(undefined4 *)(DAT_000159f8 + 0x15c18)), iVar3 < 0
       )) {
      uVar9 = 0x3335;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = entry();
    if (iVar3 < 0) {
      uVar9 = 0x333a;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00013d08();
    if (iVar3 < 0) {
      uVar9 = 0x333c;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00013bbc();
    if (iVar3 < 0) {
      uVar9 = 0x3341;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = FUN_000150c8();
    iVar3 = DAT_000159fc;
    if (iVar2 < 0) {
      uVar9 = 0x3347;
      iVar2 = 0;
      uVar10 = 1;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar5 = FUN_0001519c(*(undefined4 *)(DAT_000159fc + 0x15de8));
    if (iVar5 == 0) {
      uVar9 = 0x334f;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15d74),*(undefined4 *)(iVar3 + 0x15de8),iVar5);
    if (iVar2 < 0) {
      uVar9 = 0x3351;
      iVar2 = 0;
      uVar10 = 1;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar5);
    iVar5 = FUN_0001519c(*(undefined4 *)(iVar3 + 0x15dec));
    if (iVar5 == 0) {
      uVar9 = 0x3353;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15d74),*(undefined4 *)(iVar3 + 0x15dec),iVar5);
    if (iVar2 < 0) {
      uVar9 = 0x3355;
      iVar2 = 0;
      uVar10 = 1;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar5);
    iVar5 = FUN_0001519c(*(undefined4 *)(iVar3 + 0x15df0));
    if (iVar5 == 0) {
      uVar9 = 0x3357;
      uVar10 = 1;
      iVar2 = 0;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15d74),*(undefined4 *)(iVar3 + 0x15df0),iVar5);
    iVar3 = DAT_00015a00;
    if (iVar2 < 0) {
      uVar9 = 0x3359;
      iVar2 = 0;
      uVar10 = 1;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar5);
    iVar5 = FUN_0001519c(*(undefined4 *)(iVar3 + 0x15e8c));
    if (iVar5 == 0) {
      uVar9 = 0x3362;
      uVar10 = 2;
      iVar2 = 0;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15e0c),*(undefined4 *)(iVar3 + 0x15e8c),iVar5);
    if (iVar2 < 0) {
      uVar9 = 0x3364;
      iVar2 = 0;
      uVar10 = 2;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar5);
    iVar5 = FUN_0001519c(*(undefined4 *)(iVar3 + 0x15e90));
    if (iVar5 == 0) {
      uVar9 = 0x3366;
      uVar10 = 2;
      iVar2 = 0;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15e0c),*(undefined4 *)(iVar3 + 0x15e90),iVar5);
    if (iVar2 < 0) {
      uVar9 = 0x3368;
      iVar2 = 0;
      uVar10 = 2;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar5);
    iVar5 = FUN_0001519c(*(undefined4 *)(iVar3 + 0x15e94));
    if (iVar5 == 0) {
      uVar9 = 0x336a;
      uVar10 = 2;
      iVar2 = 0;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15e0c),*(undefined4 *)(iVar3 + 0x15e94),iVar5);
    if (iVar2 < 0) {
      uVar9 = 0x336c;
      iVar2 = 0;
      uVar10 = 2;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar5);
    iVar5 = PyTuple_New(1);
    if (iVar5 == 0) {
      uVar9 = 0x3376;
      uVar10 = 4;
      iVar2 = 0;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    puVar7 = *(undefined4 **)(iVar12 + DAT_00015a04);
    FUN_00018934(*puVar7);
    *(undefined4 *)(iVar5 + 0xc) = *puVar7;
    iVar2 = FUN_00014ba8(0,iVar5);
    if (iVar2 == 0) {
      uVar9 = 0x337b;
      uVar10 = 4;
      iVar11 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar1 = FUN_00015278(iVar2,iVar5,*(undefined4 *)(iVar3 + 0x15e98),
                         *(undefined4 *)(iVar3 + 0x15e98),*(undefined4 *)(iVar3 + 0x15e9c));
    if (iVar1 == 0) {
      uVar9 = 0x337d;
      uVar10 = 4;
      iVar4 = 0;
      iVar11 = iVar1;
      goto LAB_00016ce0;
    }
    iVar4 = FUN_0001548c(iVar2,*(undefined4 *)(iVar3 + 0x15e98),iVar5,iVar1);
    iVar3 = DAT_00015a08;
    if (iVar4 == 0) {
      uVar9 = 0x337f;
      uVar10 = 4;
      iVar11 = iVar1;
      goto LAB_00016ce0;
    }
    iVar8 = PyDict_SetItem(*(undefined4 *)(DAT_00015a08 + 0x15f20),
                           *(undefined4 *)(DAT_00015a08 + 0x15fac),iVar4);
    if (iVar8 < 0) {
      uVar9 = 0x3381;
      uVar10 = 4;
      iVar11 = iVar1;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar4);
    FUN_00017fec(iVar1);
    FUN_00017fec(iVar2);
    FUN_00017fec(iVar5);
    iVar5 = PyDict_New();
    if (iVar5 == 0) {
      uVar9 = 0x338e;
      uVar10 = 8;
      iVar2 = 0;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(iVar5,*(undefined4 *)(iVar3 + 0x15fb4),*(undefined4 *)(iVar3 + 0x15f5c));
    if (iVar2 < 0) {
      uVar9 = 0x3390;
      iVar2 = 0;
      uVar10 = 8;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15f20),*(undefined4 *)(iVar3 + 0x15fb8),iVar5);
    if (iVar2 < 0) {
      uVar9 = 0x3391;
      iVar2 = 0;
      uVar10 = 7;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar5);
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15f20),*(undefined4 *)(iVar3 + 0x15fbc),
                           *(undefined4 *)(iVar3 + 0x15f84));
    if (iVar2 < 0) {
      uVar9 = 0x339b;
      iVar2 = 0;
      uVar10 = 10;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15f20),*(undefined4 *)(iVar3 + 0x15fc0),
                           *(undefined4 *)(iVar3 + 0x15f5c));
    if (iVar2 < 0) {
      uVar9 = 0x33a4;
      iVar2 = 0;
      uVar10 = 0xb;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15f20),*(undefined4 *)(iVar3 + 0x15fc4),
                           *(undefined4 *)(iVar3 + 0x15f60));
    if (iVar2 < 0) {
      uVar9 = 0x33ad;
      iVar2 = 0;
      uVar10 = 0xc;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15f20),*(undefined4 *)(iVar3 + 0x15fc8),
                           *(undefined4 *)(iVar3 + 0x15f64));
    if (iVar2 < 0) {
      uVar9 = 0x33b6;
      iVar2 = 0;
      uVar10 = 0xd;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15f20),*(undefined4 *)(iVar3 + 0x15fcc),
                           *(undefined4 *)(iVar3 + 0x15f68));
    if (iVar2 < 0) {
      uVar9 = 0x33bf;
      iVar2 = 0;
      uVar10 = 0xe;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(iVar3 + 0x15f20),*(undefined4 *)(iVar3 + 0x15fd0),
                           *(undefined4 *)(iVar3 + 0x15f6c));
    iVar3 = DAT_00015a0c;
    if (iVar2 < 0) {
      uVar9 = 0x33c8;
      iVar2 = 0;
      uVar10 = 0xf;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = PyDict_SetItem(*(undefined4 *)(DAT_00015a0c + 0x1602c),
                           *(undefined4 *)(DAT_00015a0c + 0x160e0),
                           *(undefined4 *)(DAT_00015a0c + 0x1607c));
    if (iVar2 < 0) {
      uVar9 = 0x33d1;
      iVar2 = 0;
      uVar10 = 0x10;
      iVar5 = 0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    iVar5 = FUN_00015278(0,*(undefined4 *)(iVar3 + 0x15e0c),*(undefined4 *)(iVar3 + 0x160e4),
                         *(undefined4 *)(iVar3 + 0x160e4),*(undefined4 *)(iVar3 + 0x160bc));
    if (iVar5 == 0) {
      uVar9 = 0x33da;
      uVar10 = 0x11;
      iVar2 = 0;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = FUN_00015430(DAT_00015a10 + 0x162d0,*(undefined4 *)(iVar3 + 0x160e8),
                         *(undefined4 *)(iVar3 + 0x160bc),*(undefined4 *)(iVar3 + 0x1602c),
                         *(undefined4 *)(iVar3 + 0x15e18));
    if (iVar2 == 0) {
      uVar9 = 0x33e4;
      uVar10 = 0x12;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    FUN_00014b9c(iVar2,*(undefined4 *)(iVar3 + 0x15e20));
    uVar9 = *(undefined4 *)(iVar12 + DAT_00015ac4);
    iVar4 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    if (iVar4 == 0) {
      iVar3 = PyObject_SetItem(iVar5,*(undefined4 *)(iVar3 + 0x15e10),iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash
                        (iVar5,*(int *)(iVar3 + 0x15e10),iVar2,
                         *(undefined4 *)(*(int *)(iVar3 + 0x15e10) + 0xc));
    }
    iVar4 = DAT_00015a14;
    if (iVar3 < 0) {
      uVar9 = 0x33e7;
      uVar10 = 0x12;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a18 + 0x16370,*(undefined4 *)(iVar4 + 0x161b8),
                         *(undefined4 *)(iVar4 + 0x16188),*(undefined4 *)(iVar4 + 0x160f8),
                         *(undefined4 *)(iVar4 + 0x15f1c));
    if (iVar2 == 0) {
      uVar9 = 0x33f1;
      uVar10 = 0x27;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x15f18);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a1c;
    if (iVar3 < 0) {
      uVar9 = 0x33f3;
      uVar10 = 0x27;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a20 + 0x16400,*(undefined4 *)(iVar4 + 0x1623c),
                         *(undefined4 *)(iVar4 + 0x16208),*(undefined4 *)(iVar4 + 0x16178),
                         *(undefined4 *)(iVar4 + 0x15fac));
    if (iVar2 == 0) {
      uVar9 = 0x33fd;
      uVar10 = 0x54;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    FUN_00014b9c(iVar2,*(undefined4 *)(iVar4 + 0x15fb4));
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,*(undefined4 *)(iVar4 + 0x15fa8),iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash
                        (iVar5,*(int *)(iVar4 + 0x15fa8),iVar2,
                         *(undefined4 *)(*(int *)(iVar4 + 0x15fa8) + 0xc));
    }
    iVar4 = DAT_00015a24;
    if (iVar3 < 0) {
      uVar9 = 0x3400;
      uVar10 = 0x54;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a28 + 0x16498,*(undefined4 *)(iVar4 + 0x162c8),
                         *(undefined4 *)(iVar4 + 0x16290),*(undefined4 *)(iVar4 + 0x16200),
                         *(undefined4 *)(iVar4 + 0x16058));
    if (iVar2 == 0) {
      uVar9 = 0x340a;
      uVar10 = 0x5d;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    FUN_00014b9c(iVar2,*(undefined4 *)(iVar4 + 0x1605c));
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,*(undefined4 *)(iVar4 + 0x16054),iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash
                        (iVar5,*(int *)(iVar4 + 0x16054),iVar2,
                         *(undefined4 *)(*(int *)(iVar4 + 0x16054) + 0xc));
    }
    iVar4 = DAT_00015a2c;
    if (iVar3 < 0) {
      uVar9 = 0x340d;
      uVar10 = 0x5d;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a30 + 0x16530,*(undefined4 *)(iVar4 + 0x16354),
                         *(undefined4 *)(iVar4 + 0x16318),*(undefined4 *)(iVar4 + 0x16288),
                         *(undefined4 *)(iVar4 + 0x160f8));
    if (iVar2 == 0) {
      uVar9 = 0x3417;
      uVar10 = 0x73;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x160f4);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a34;
    if (iVar3 < 0) {
      uVar9 = 0x3419;
      uVar10 = 0x73;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a38 + 0x165c0,*(undefined4 *)(iVar4 + 0x163d8),
                         *(undefined4 *)(iVar4 + 0x16398),*(undefined4 *)(iVar4 + 0x16308),
                         *(undefined4 *)(iVar4 + 0x16184));
    if (iVar2 == 0) {
      uVar9 = 0x3423;
      uVar10 = 0x86;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16180);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a3c;
    if (iVar3 < 0) {
      uVar9 = 0x3425;
      uVar10 = 0x86;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a40 + 0x16650,*(undefined4 *)(iVar4 + 0x1645c),
                         *(undefined4 *)(iVar4 + 0x16418),*(undefined4 *)(iVar4 + 0x16388),
                         *(undefined4 *)(iVar4 + 0x16210));
    if (iVar2 == 0) {
      uVar9 = 0x342f;
      uVar10 = 0x8e;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x1620c);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a44;
    if (iVar3 < 0) {
      uVar9 = 0x3431;
      uVar10 = 0x8e;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a48 + 0x166e0,*(undefined4 *)(iVar4 + 0x164e0),
                         *(undefined4 *)(iVar4 + 0x16498),*(undefined4 *)(iVar4 + 0x16408),
                         *(undefined4 *)(iVar4 + 0x1629c));
    if (iVar2 == 0) {
      uVar9 = 0x343b;
      uVar10 = 0x91;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16298);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a4c;
    if (iVar3 < 0) {
      uVar9 = 0x343d;
      uVar10 = 0x91;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a50 + 0x16770,*(undefined4 *)(iVar4 + 0x16564),
                         *(undefined4 *)(iVar4 + 0x16518),*(undefined4 *)(iVar4 + 0x16488),
                         *(undefined4 *)(iVar4 + 0x16334));
    if (iVar2 == 0) {
      uVar9 = 0x3447;
      uVar10 = 0x9d;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    FUN_00014b9c(iVar2,*(undefined4 *)(iVar4 + 0x16338));
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,*(undefined4 *)(iVar4 + 0x16330),iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash
                        (iVar5,*(int *)(iVar4 + 0x16330),iVar2,
                         *(undefined4 *)(*(int *)(iVar4 + 0x16330) + 0xc));
    }
    iVar4 = DAT_00015a54;
    if (iVar3 < 0) {
      uVar9 = 0x344a;
      uVar10 = 0x9d;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a58 + 0x16808,*(undefined4 *)(iVar4 + 0x165f0),
                         *(undefined4 *)(iVar4 + 0x165a0),*(undefined4 *)(iVar4 + 0x16510),
                         *(undefined4 *)(iVar4 + 0x163cc));
    if (iVar2 == 0) {
      uVar9 = 0x3454;
      uVar10 = 0xb7;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x163c8);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a5c;
    if (iVar3 < 0) {
      uVar9 = 0x3456;
      uVar10 = 0xb7;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a60 + 0x16898,*(undefined4 *)(iVar4 + 0x16674),
                         *(undefined4 *)(iVar4 + 0x16620),*(undefined4 *)(iVar4 + 0x16590),
                         *(undefined4 *)(iVar4 + 0x16454));
    if (iVar2 == 0) {
      uVar9 = 0x3460;
      uVar10 = 0xbe;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16450);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a64;
    if (iVar3 < 0) {
      uVar9 = 0x3462;
      uVar10 = 0xbe;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_0001548c(*(undefined4 *)(iVar12 + DAT_00015ad4),*(undefined4 *)(iVar4 + 0x166cc),
                         *(undefined4 *)(iVar4 + 0x163f4),iVar5);
    if (iVar2 == 0) {
      uVar9 = 0x346c;
      uVar10 = 0x11;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = PyDict_SetItem(*(undefined4 *)(iVar4 + 0x16614),*(undefined4 *)(iVar4 + 0x166cc),iVar2);
    if (iVar3 < 0) {
      uVar9 = 0x346e;
      uVar10 = 0x11;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    FUN_00017fec(iVar5);
    iVar5 = FUN_00015278(0,*(undefined4 *)(iVar4 + 0x163f4),*(undefined4 *)(iVar4 + 0x166fc),
                         *(undefined4 *)(iVar4 + 0x166fc),*(undefined4 *)(iVar4 + 0x166a4));
    if (iVar5 == 0) {
      uVar9 = 0x3479;
      uVar10 = 0xc1;
      iVar2 = 0;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar2 = FUN_00015430(DAT_00015a68 + 0x1699c,*(undefined4 *)(iVar4 + 0x16700),
                         *(undefined4 *)(iVar4 + 0x166a4),*(undefined4 *)(iVar4 + 0x16614),
                         *(undefined4 *)(iVar4 + 0x164e4));
    if (iVar2 == 0) {
      uVar9 = 0x3483;
      uVar10 = 0xc2;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    uVar9 = *(undefined4 *)(iVar12 + DAT_00015ac4);
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x163f8);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a6c;
    if (iVar3 < 0) {
      uVar9 = 0x3485;
      uVar10 = 0xc2;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a70 + 0x16a34,*(undefined4 *)(iVar4 + 0x167fc),
                         *(undefined4 *)(iVar4 + 0x1679c),*(undefined4 *)(iVar4 + 0x1670c),
                         *(undefined4 *)(iVar4 + 0x165e4));
    if (iVar2 == 0) {
      uVar9 = 0x348f;
      uVar10 = 0xe0;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x165e0);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a74;
    if (iVar3 < 0) {
      uVar9 = 0x3491;
      uVar10 = 0xe0;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a78 + 0x16ac4,*(undefined4 *)(iVar4 + 0x16880),
                         *(undefined4 *)(iVar4 + 0x1681c),*(undefined4 *)(iVar4 + 0x1678c),
                         *(undefined4 *)(iVar4 + 0x1666c));
    if (iVar2 == 0) {
      uVar9 = 0x349b;
      uVar10 = 0xe3;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16668);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a7c;
    if (iVar3 < 0) {
      uVar9 = 0x349d;
      uVar10 = 0xe3;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a80 + 0x16b54,*(undefined4 *)(iVar4 + 0x16904),
                         *(undefined4 *)(iVar4 + 0x1689c),*(undefined4 *)(iVar4 + 0x1680c),
                         *(undefined4 *)(iVar4 + 0x166f4));
    if (iVar2 == 0) {
      uVar9 = 0x34a7;
      uVar10 = 0xe6;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x166f0);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a84;
    if (iVar3 < 0) {
      uVar9 = 0x34a9;
      uVar10 = 0xe6;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a88 + 0x16be4,*(undefined4 *)(iVar4 + 0x16988),
                         *(undefined4 *)(iVar4 + 0x1691c),*(undefined4 *)(iVar4 + 0x1688c),
                         *(undefined4 *)(iVar4 + 0x16780));
    if (iVar2 == 0) {
      uVar9 = 0x34b3;
      uVar10 = 0xe9;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x1677c);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a8c;
    if (iVar3 < 0) {
      uVar9 = 0x34b5;
      uVar10 = 0xe9;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a90 + 0x16c74,*(undefined4 *)(iVar4 + 0x16a0c),
                         *(undefined4 *)(iVar4 + 0x1699c),*(undefined4 *)(iVar4 + 0x1690c),
                         *(undefined4 *)(iVar4 + 0x16808));
    if (iVar2 == 0) {
      uVar9 = 0x34bf;
      uVar10 = 0xee;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16804);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a94;
    if (iVar3 < 0) {
      uVar9 = 0x34c1;
      uVar10 = 0xee;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015a98 + 0x16d04,*(undefined4 *)(iVar4 + 0x16a90),
                         *(undefined4 *)(iVar4 + 0x16a1c),*(undefined4 *)(iVar4 + 0x1698c),
                         *(undefined4 *)(iVar4 + 0x16890));
    if (iVar2 == 0) {
      uVar9 = 0x34cb;
      uVar10 = 0xf1;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16844);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015a9c;
    if (iVar3 < 0) {
      uVar9 = 0x34cd;
      uVar10 = 0xf1;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015aa0 + 0x16d94,*(undefined4 *)(iVar4 + 0x16b14),
                         *(undefined4 *)(iVar4 + 0x16a9c),*(undefined4 *)(iVar4 + 0x16a0c),
                         *(undefined4 *)(iVar4 + 0x16920));
    if (iVar2 == 0) {
      uVar9 = 0x34d7;
      uVar10 = 0xf4;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x1691c);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015aa4;
    if (iVar3 < 0) {
      uVar9 = 0x34d9;
      uVar10 = 0xf4;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015aa8 + 0x16e24,*(undefined4 *)(iVar4 + 0x16b98),
                         *(undefined4 *)(iVar4 + 0x16b1c),*(undefined4 *)(iVar4 + 0x16a8c),
                         *(undefined4 *)(iVar4 + 0x169b0));
    if (iVar2 == 0) {
      uVar9 = 0x34e3;
      uVar10 = 0xf9;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    FUN_00014b9c(iVar2,*(undefined4 *)(iVar4 + 0x169b4));
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,*(undefined4 *)(iVar4 + 0x169ac),iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash
                        (iVar5,*(int *)(iVar4 + 0x169ac),iVar2,
                         *(undefined4 *)(*(int *)(iVar4 + 0x169ac) + 0xc));
    }
    iVar4 = DAT_00015aac;
    if (iVar3 < 0) {
      uVar9 = 0x34e6;
      uVar10 = 0xf9;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015ab0 + 0x16ebc,*(undefined4 *)(iVar4 + 0x16c24),
                         *(undefined4 *)(iVar4 + 0x16ba4),*(undefined4 *)(iVar4 + 0x16b14),
                         *(undefined4 *)(iVar4 + 0x16a44));
    if (iVar2 == 0) {
      uVar9 = 0x34f0;
      uVar10 = 0x114;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16a40);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015ab4;
    if (iVar3 < 0) {
      uVar9 = 0x34f2;
      uVar10 = 0x114;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015ab8 + 0x16f4c,*(undefined4 *)(iVar4 + 0x16ca8),
                         *(undefined4 *)(iVar4 + 0x16c24),*(undefined4 *)(iVar4 + 0x16b94),
                         *(undefined4 *)(iVar4 + 0x16ad0));
    if (iVar2 == 0) {
      uVar9 = 0x34fc;
      uVar10 = 0x117;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16acc);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015abc;
    if (iVar3 < 0) {
      uVar9 = 0x34fe;
      uVar10 = 0x117;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015ac0 + 0x16fdc,*(undefined4 *)(iVar4 + 0x16d2c),
                         *(undefined4 *)(iVar4 + 0x16ca4),*(undefined4 *)(iVar4 + 0x16c14),
                         *(undefined4 *)(iVar4 + 0x16b58));
    if (iVar2 == 0) {
      uVar9 = 0x3508;
      uVar10 = 0x11f;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    uVar9 = *(undefined4 *)(iVar12 + DAT_00015ac4);
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16b54);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar4 = DAT_00015ac8;
    if (iVar3 < 0) {
      uVar9 = 0x350a;
      uVar10 = 0x11f;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_00015430(DAT_00015acc + 0x17078,*(undefined4 *)(iVar4 + 0x16dbc),
                         *(undefined4 *)(iVar4 + 0x16d30),*(undefined4 *)(iVar4 + 0x16ca0),
                         *(undefined4 *)(iVar4 + 0x16bec));
    if (iVar2 == 0) {
      uVar9 = 0x3514;
      uVar10 = 0x123;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar9);
    iVar4 = *(int *)(iVar4 + 0x16be8);
    if (iVar3 == 0) {
      iVar3 = PyObject_SetItem(iVar5,iVar4,iVar2);
    }
    else {
      iVar3 = _PyDict_SetItem_KnownHash(iVar5,iVar4,iVar2,*(undefined4 *)(iVar4 + 0xc));
    }
    iVar1 = DAT_00015ad0;
    if (iVar3 < 0) {
      uVar9 = 0x3516;
      uVar10 = 0x123;
      iVar4 = 0;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    iVar2 = FUN_0001548c(*(undefined4 *)(iVar12 + DAT_00015ad4),*(undefined4 *)(iVar1 + 0x16e0c),
                         *(undefined4 *)(iVar1 + 0x16b04),iVar5);
    if (iVar2 == 0) {
      uVar9 = 0x3520;
      uVar10 = 0xc1;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = PyDict_SetItem(*(undefined4 *)(iVar1 + 0x16d24),*(undefined4 *)(iVar1 + 0x16e0c),iVar2);
    iVar4 = 0;
    if (iVar3 < 0) {
      uVar9 = 0x3522;
      uVar10 = 0xc1;
      goto LAB_00016ce0;
    }
    FUN_00017fec(iVar2);
    FUN_00017fec(iVar5);
    iVar5 = PyDict_New();
    if (iVar5 == 0) {
      uVar9 = 0x352b;
      uVar10 = 1;
      iVar2 = 0;
      iVar4 = 0;
      iVar11 = 0;
      goto LAB_00016ce0;
    }
    iVar3 = PyDict_SetItem(*(undefined4 *)(iVar1 + 0x16d24),*(undefined4 *)(iVar1 + 0x16e44),iVar5);
    if (iVar3 < 0) {
      uVar9 = 0x352d;
      uVar10 = 1;
      iVar2 = 0;
      goto LAB_00016ce0;
    }
  }
  FUN_00017fec(iVar5);
LAB_00016d5c:
  return -(uint)(*(int *)(DAT_000173a0 + 0x16fdc) == 0);
}




/* ============================================
 * Function: PyInit_serial_485_wrapper
 * Address:  0x173ac
 * ============================================ */

void PyInit_serial_485_wrapper(void)

{
  (*(code *)PTR_PyModuleDef_Init_00040dc4)(DAT_000173bc + 0x17b18);
  return;
}




/* ============================================
 * Function: FUN_000173c0
 * Address:  0x173c0
 * ============================================ */

void FUN_000173c0(void)

{
  if (*(int *)(DAT_000173dc + 0x173d0 + DAT_000173e0) == 0) {
    return;
  }
  (*(code *)PTR___gmon_start___00040e80)();
  return;
}




/* ============================================
 * Function: FUN_000173e4
 * Address:  0x173e4
 * ============================================ */

void FUN_000173e4(void)

{
  code *pcVar1;
  
  if (DAT_00017430 + 0x173fc == DAT_0001742c + 0x173f4) {
    return;
  }
  pcVar1 = *(code **)(DAT_00017434 + 0x17404 + DAT_00017438);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)();
    return;
  }
  return;
}




/* ============================================
 * Function: FUN_0001743c
 * Address:  0x1743c
 * ============================================ */

void FUN_0001743c(void)

{
  code *pcVar1;
  
  if (((DAT_00017494 + 0x17450) - (DAT_00017490 + 0x1744c) >> 2) / 2 == 0) {
    return;
  }
  pcVar1 = *(code **)(DAT_00017498 + 0x17460 + DAT_0001749c);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)();
    return;
  }
  return;
}




/* ============================================
 * Function: _FINI_0
 * Address:  0x174a0
 * ============================================ */

void _FINI_0(void)

{
  if (*(char *)(DAT_000174f4 + 0x174b0) != '\0') {
    return;
  }
  if (*(int *)(DAT_000174f8 + 0x174b4 + DAT_000174fc) != 0) {
    __cxa_finalize(*(undefined4 *)(DAT_00017500 + 0x174dc));
  }
  FUN_000173e4();
  *(undefined1 *)(DAT_00017504 + 0x174f0) = 1;
  return;
}




/* ============================================
 * Function: _INIT_0
 * Address:  0x17508
 * ============================================ */

void _INIT_0(void)

{
  code *pcVar1;
  
  if (((DAT_00017494 + 0x17450) - (DAT_00017490 + 0x1744c) >> 2) / 2 == 0) {
    return;
  }
  pcVar1 = *(code **)(DAT_00017498 + 0x17460 + DAT_0001749c);
  if (pcVar1 != (code *)0x0) {
    (*pcVar1)();
    return;
  }
  return;
}




/* ============================================
 * Function: FUN_00017510
 * Address:  0x17510
 * ============================================ */

bool FUN_00017510(uint param_1,uint param_2)

{
  return param_1 < param_2;
}




/* ============================================
 * Function: FUN_00017538
 * Address:  0x17538
 * ============================================ */

void FUN_00017538(int param_1,code *UNRECOVERED_JUMPTABLE,undefined4 param_3)

{
  int iVar1;
  
  if ((*(int *)(param_1 + 8) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 8),param_3), iVar1 != 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0xc) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0xc),param_3), iVar1 != 0)) {
    return;
  }
  if (*(int *)(param_1 + 0x10) == 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00017578. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0x10),param_3);
  return;
}




/* ============================================
 * Function: FUN_000175bc
 * Address:  0x175bc
 * ============================================ */

void FUN_000175bc(int param_1,code *UNRECOVERED_JUMPTABLE,undefined4 param_3)

{
  int iVar1;
  
  if ((*(int *)(param_1 + 8) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 8),param_3), iVar1 != 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0xc) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0xc),param_3), iVar1 != 0)) {
    return;
  }
  if (*(int *)(param_1 + 0x10) == 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000175fc. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0x10),param_3);
  return;
}




/* ============================================
 * Function: FUN_00017628
 * Address:  0x17628
 * ============================================ */

void FUN_00017628(int param_1)

{
  undefined4 uVar1;
  uint uVar2;
  code *UNRECOVERED_JUMPTABLE_00;
  
  UNRECOVERED_JUMPTABLE_00 = *(code **)(*(int *)(param_1 + 8) + 4);
  uVar2 = *(uint *)(*(int *)(param_1 + 8) + 8);
  if ((uVar2 & 0x20) == 0) {
    uVar1 = *(undefined4 *)(param_1 + 0xc);
  }
  else {
    uVar1 = 0;
  }
  if ((uVar2 & 2) == 0) {
                    /* WARNING: Could not recover jumptable at 0x00017664. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE_00)(uVar1);
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00017658. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE_00)();
  return;
}




/* ============================================
 * Function: FUN_00017668
 * Address:  0x17668
 * ============================================ */

void FUN_00017668(int param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  *param_2 = *(undefined4 *)(param_1 + 0x34);
  *param_3 = *(undefined4 *)(param_1 + 0x38);
  *param_4 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  return;
}




/* ============================================
 * Function: FUN_000176d8
 * Address:  0x176d8
 * ============================================ */

bool FUN_000176d8(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  
  if (param_1 != param_2) {
    iVar2 = *(int *)(param_1 + 0xac);
    if (iVar2 == 0) {
      do {
        if (param_1 == 0) {
          return param_2 == *(int *)(DAT_000176d0 + 0x176a0 + DAT_000176d4);
        }
        param_1 = *(int *)(param_1 + 0x80);
      } while (param_1 != param_2);
      return true;
    }
    iVar1 = 0;
    piVar3 = (int *)(iVar2 + 0xc);
    while( true ) {
      if (*(int *)(iVar2 + 8) <= iVar1) {
        return false;
      }
      if (*piVar3 == param_2) break;
      iVar1 = iVar1 + 1;
      piVar3 = piVar3 + 1;
    }
  }
  return true;
}




/* ============================================
 * Function: FUN_00017728
 * Address:  0x17728
 * ============================================ */

void FUN_00017728(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  
  if ((param_2 != 0) && (iVar1 = FUN_000176d8(), iVar1 != 0)) {
    return;
  }
  FUN_000176d8(param_1,param_3);
  return;
}




/* ============================================
 * Function: FUN_00017758
 * Address:  0x17758
 * ============================================ */

int FUN_00017758(int param_1,code *param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  
  if ((*(int *)(param_1 + 0x34) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x34),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x10) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x10),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x1c) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x1c),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x20) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x20),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x24) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x24),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x28) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x28),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x2c) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x2c),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x30) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x30),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x38) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x38),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x4c) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x4c),param_3), iVar3 != 0)) {
    return iVar3;
  }
  if ((*(int *)(param_1 + 0x50) != 0) &&
     (iVar3 = (*param_2)(*(int *)(param_1 + 0x50),param_3), iVar3 != 0)) {
    return iVar3;
  }
  iVar3 = *(int *)(param_1 + 0x3c);
  if (iVar3 != 0) {
    for (iVar2 = 0; iVar2 < *(int *)(param_1 + 0x40); iVar2 = iVar2 + 1) {
      iVar1 = *(int *)(iVar3 + iVar2 * 4);
      if ((iVar1 != 0) && (iVar1 = (*param_2)(iVar1,param_3), iVar1 != 0)) {
        return iVar1;
      }
    }
  }
  return 0;
}




/* ============================================
 * Function: FUN_00017914
 * Address:  0x17914
 * ============================================ */

int FUN_00017914(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  
  iVar3 = param_2 + -1;
  if ((iVar3 < 0) || (param_3 <= *(int *)(param_1 + iVar3 * 8 + 4))) {
    param_2 = 0;
    iVar2 = 0;
    if (0 < iVar3) {
      do {
        iVar1 = iVar2 + (iVar3 - iVar2 >> 1);
        iVar5 = *(int *)(param_1 + iVar1 * 8 + 4);
        iVar4 = iVar1;
        if (iVar5 <= param_3) {
          if (param_3 <= iVar5) {
            return iVar1;
          }
          iVar2 = iVar1 + 1;
          iVar4 = iVar3;
        }
        iVar3 = iVar4;
      } while (iVar2 < iVar4);
      if (*(int *)(param_1 + iVar1 * 8 + 4) < param_3) {
        iVar1 = iVar1 + 1;
      }
      return iVar1;
    }
    if (*(int *)(param_1 + 4) < param_3) {
      param_2 = 1;
    }
  }
  return param_2;
}




/* ============================================
 * Function: FUN_00017a0c
 * Address:  0x17a0c
 * ============================================ */

void FUN_00017a0c(int param_1,code *UNRECOVERED_JUMPTABLE,undefined4 param_3)

{
  int iVar1;
  
  if ((*(int *)(param_1 + 0xc) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0xc),param_3), iVar1 != 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0x24) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0x24),param_3), iVar1 != 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0x28) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0x28),param_3), iVar1 != 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0x10) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0x10),param_3), iVar1 != 0)) {
    return;
  }
  if ((*(int *)(param_1 + 0x14) != 0) &&
     (iVar1 = (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0x14),param_3), iVar1 != 0)) {
    return;
  }
  if (*(int *)(param_1 + 0x18) == 0) {
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000179e0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (*UNRECOVERED_JUMPTABLE)(*(int *)(param_1 + 0x18),param_3);
  return;
}




/* ============================================
 * Function: FUN_00017a90
 * Address:  0x17a90
 * ============================================ */

void FUN_00017a90(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 4) + 0x4c);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00017aa0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  PyObject_SetAttr();
  return;
}




/* ============================================
 * Function: FUN_00017aa8
 * Address:  0x17aa8
 * ============================================ */

void FUN_00017aa8(undefined4 param_1,undefined4 param_2)

{
  PyErr_Format(**(undefined4 **)(DAT_00017ad0 + 0x17ab8 + DAT_00017ad4),
               (int)&DAT_00017ad0 + DAT_00017ad8,param_1,param_2);
  return;
}




/* ============================================
 * Function: FUN_00017adc
 * Address:  0x17adc
 * ============================================ */

void FUN_00017adc(undefined4 param_1,int param_2,int param_3,int param_4,int param_5)

{
  int iVar1;
  int iVar2;
  
  if (param_5 < param_3) {
    iVar2 = DAT_00017b7c + 0x17b58;
  }
  else {
    iVar2 = DAT_00017b68 + 0x17b08;
    param_3 = param_4;
  }
  if (param_2 != 0) {
    iVar2 = DAT_00017b6c + 0x17b14;
  }
  if (param_3 == 1) {
    iVar1 = (int)&DAT_00017b64 + DAT_00017b80;
  }
  else {
    iVar1 = DAT_00017b74 + 0x17b30;
  }
  PyErr_Format(**(undefined4 **)(DAT_00017b64 + 0x17af8 + DAT_00017b70),DAT_00017b78 + 0x17b44,
               param_1,iVar2,param_3,iVar1,param_5,param_4);
  return;
}




/* ============================================
 * Function: FUN_00017b84
 * Address:  0x17b84
 * ============================================ */

void FUN_00017b84(undefined4 param_1)

{
  PyErr_Format(**(undefined4 **)(DAT_00017ba8 + 0x17b94 + DAT_00017bac),DAT_00017bb0 + 0x17ba4,
               param_1);
  return;
}




/* ============================================
 * Function: FUN_00017bb4
 * Address:  0x17bb4
 * ============================================ */

void FUN_00017bb4(int param_1)

{
  int iVar1;
  
  if (param_1 == 1) {
    iVar1 = (int)&DAT_00017bf4 + DAT_00017c04;
  }
  else {
    iVar1 = DAT_00017bfc + 0x17be0;
  }
  PyErr_Format(**(undefined4 **)(DAT_00017bf4 + 0x17bcc + DAT_00017bf8),DAT_00017c00 + 0x17be8,
               param_1,iVar1);
  return;
}




/* ============================================
 * Function: FUN_00017c08
 * Address:  0x17c08
 * ============================================ */

undefined4 FUN_00017c08(int param_1,undefined4 param_2,int param_3,int param_4)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  code *UNRECOVERED_JUMPTABLE_00;
  
  iVar4 = DAT_00017d78 + 0x17c28;
  UNRECOVERED_JUMPTABLE_00 = *(code **)(*(int *)(param_1 + 8) + 4);
  switch(*(uint *)(*(int *)(param_1 + 8) + 8) & 0xf) {
  case 1:
    if ((param_4 == 0) || (iVar2 = PyDict_Size(), iVar2 == 0)) {
LAB_00017c70:
                    /* WARNING: Could not recover jumptable at 0x00017c7c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      uVar3 = (*UNRECOVERED_JUMPTABLE_00)(param_2,param_3);
      return uVar3;
    }
    goto LAB_00017c8c;
  case 2:
    break;
  case 3:
                    /* WARNING: Could not recover jumptable at 0x00017cc4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar3 = (*UNRECOVERED_JUMPTABLE_00)(param_2,param_3,param_4);
    return uVar3;
  case 4:
    if ((param_4 == 0) || (iVar2 = PyDict_Size(), iVar2 == 0)) {
      if (*(int *)(param_3 + 8) != 0) {
        puVar1 = *(undefined4 **)(iVar4 + DAT_00017d7c);
        uVar3 = **(undefined4 **)(param_1 + 8);
        iVar4 = DAT_00017d84 + 0x17cfc;
LAB_00017cf8:
        PyErr_Format(*puVar1,iVar4,uVar3);
        return 0;
      }
      param_3 = 0;
      goto LAB_00017c70;
    }
    goto LAB_00017c8c;
  case 5:
    break;
  case 6:
    break;
  case 7:
    break;
  case 8:
    if ((param_4 == 0) || (iVar2 = PyDict_Size(), iVar2 == 0)) {
      if (*(int *)(param_3 + 8) != 1) {
        puVar1 = *(undefined4 **)(iVar4 + DAT_00017d7c);
        uVar3 = **(undefined4 **)(param_1 + 8);
        iVar4 = DAT_00017d88 + 0x17d4c;
        goto LAB_00017cf8;
      }
      param_3 = *(int *)(param_3 + 0xc);
      goto LAB_00017c70;
    }
LAB_00017c8c:
    PyErr_Format(**(undefined4 **)(iVar4 + DAT_00017d7c),DAT_00017d80 + 0x17ca8,
                 **(undefined4 **)(param_1 + 8));
    return 0;
  }
  PyErr_SetString(**(undefined4 **)(iVar4 + DAT_00017d8c),DAT_00017d90 + 0x17d70);
  return 0;
}




/* ============================================
 * Function: FUN_00017da4
 * Address:  0x17da4
 * ============================================ */

int FUN_00017da4(int param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  code *pcVar4;
  
  pcVar4 = *(code **)(*(int *)(param_1 + 8) + 4);
  iVar3 = DAT_00017e30 + 0x17dc8;
  if ((*(uint *)(*(int *)(param_1 + 8) + 8) & 0x20) == 0) {
    uVar2 = *(undefined4 *)(param_1 + 0xc);
  }
  else {
    uVar2 = 0;
  }
  iVar1 = Py_EnterRecursiveCall(DAT_00017e34 + 0x17dd8);
  if (iVar1 == 0) {
    iVar1 = (*pcVar4)(uVar2,param_2);
    Py_LeaveRecursiveCall();
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = PyErr_Occurred();
    if (iVar1 == 0) {
      PyErr_SetString(**(undefined4 **)(iVar3 + DAT_00017e38),DAT_00017e3c + 0x17e28);
      return 0;
    }
  }
  return 0;
}




/* ============================================
 * Function: FUN_00017e40
 * Address:  0x17e40
 * ============================================ */

int FUN_00017e40(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  code *pcVar3;
  
  pcVar3 = *(code **)(*(int *)(param_1 + 4) + 0x40);
  iVar2 = DAT_00017ed8 + 0x17e5c;
  if (pcVar3 == (code *)0x0) {
    iVar2 = PyObject_Call();
    return iVar2;
  }
  iVar1 = Py_EnterRecursiveCall(DAT_00017edc + 0x17e7c);
  if (iVar1 == 0) {
    iVar1 = (*pcVar3)(param_1,param_2,param_3);
    Py_LeaveRecursiveCall();
    if (iVar1 != 0) {
      return iVar1;
    }
    iVar1 = PyErr_Occurred();
    if (iVar1 == 0) {
      PyErr_SetString(**(undefined4 **)(iVar2 + DAT_00017ee0),DAT_00017ee4 + 98000);
      return 0;
    }
  }
  return 0;
}




/* ============================================
 * Function: FUN_00017ee8
 * Address:  0x17ee8
 * ============================================ */

void FUN_00017ee8(int param_1)

{
  code *UNRECOVERED_JUMPTABLE;
  
  UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(param_1 + 4) + 0x48);
  if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00017ef8. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    (*UNRECOVERED_JUMPTABLE)();
    return;
  }
  (*(code *)PTR_PyObject_GetAttr_00040f34)();
  return;
}




/* ============================================
 * Function: FUN_00017f00
 * Address:  0x17f00
 * ============================================ */

int FUN_00017f00(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_00017f50;
  iVar2 = FUN_00017ee8(*(undefined4 *)(DAT_00017f4c + 0x17f18),param_1);
  if (iVar2 == 0) {
    PyErr_Format(**(undefined4 **)(iVar1 + 0x17f28 + DAT_00017f54),DAT_00017f58 + 0x17f40,param_1);
  }
  return iVar2;
}




/* ============================================
 * Function: FUN_00017f5c
 * Address:  0x17f5c
 * ============================================ */

uint FUN_00017f5c(int param_1)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = DAT_00017fb8 + 0x17f6c;
  uVar1 = (uint)(param_1 == *(int *)(iVar2 + DAT_00017fbc));
  uVar3 = uVar1;
  if (param_1 == *(int *)(iVar2 + DAT_00017fc0)) {
    uVar3 = 1;
  }
  if (param_1 == *(int *)(iVar2 + DAT_00017fc4)) {
    uVar3 = 1;
  }
  if (uVar3 == 0) {
    uVar1 = (*(code *)PTR_PyObject_IsTrue_00040ec8)();
    return uVar1;
  }
  return uVar1;
}




/* ============================================
 * Function: FUN_00017fec
 * Address:  0x17fec
 * ============================================ */

void FUN_00017fec(int *param_1)

{
  int iVar1;
  
  iVar1 = *param_1;
  *param_1 = iVar1 + -1;
  if (iVar1 + -1 != 0) {
    return;
  }
  (*(code *)PTR__Py_Dealloc_00040df0)();
  return;
}




/* ============================================
 * Function: FUN_000180ac
 * Address:  0x180ac
 * ============================================ */

void FUN_000180ac(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  PyObject_GC_UnTrack();
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(param_1 + 8) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x10) != 0) {
    *(undefined4 *)(param_1 + 0x10) = 0;
    FUN_00017fec();
  }
  iVar1 = DAT_00018144;
  iVar2 = *(int *)(FUN_000182c8 + DAT_00018144 + 4);
  bVar3 = iVar2 == 7;
  if (iVar2 < 8) {
    bVar3 = *(int *)(*(int *)(param_1 + 4) + 0x10) == 0x1c;
  }
  if (bVar3) {
    *(int *)(FUN_000182c8 + DAT_00018144 + 4) = iVar2 + 1;
    *(int *)(iVar1 + iVar2 * 4 + 0x182d0) = param_1;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00018140. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0xa0))(param_1);
  return;
}




/* ============================================
 * Function: FUN_00018148
 * Address:  0x18148
 * ============================================ */

void FUN_00018148(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  PyObject_GC_UnTrack();
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(param_1 + 8) = 0;
    FUN_00017fec();
  }
  iVar1 = DAT_000181b0;
  iVar2 = *(int *)(DAT_000181b0 + 0x1835c);
  bVar3 = iVar2 == 7;
  if (iVar2 < 8) {
    bVar3 = *(int *)(*(int *)(param_1 + 4) + 0x10) == 0xc;
  }
  if (bVar3) {
    *(int *)(DAT_000181b0 + 0x1835c) = iVar2 + 1;
    *(int *)(iVar1 + iVar2 * 4 + 0x18360) = param_1;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000181ac. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0xa0))(param_1);
  return;
}




/* ============================================
 * Function: FUN_000181b4
 * Address:  0x181b4
 * ============================================ */

void FUN_000181b4(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  PyObject_GC_UnTrack();
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(param_1 + 8) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0xc) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x10) != 0) {
    *(undefined4 *)(param_1 + 0x10) = 0;
    FUN_00017fec();
  }
  iVar1 = DAT_0001824c;
  iVar2 = *(int *)(DAT_0001824c + 0x1841c);
  bVar3 = iVar2 == 7;
  if (iVar2 < 8) {
    bVar3 = *(int *)(*(int *)(param_1 + 4) + 0x10) == 0x1c;
  }
  if (bVar3) {
    *(int *)(DAT_0001824c + 0x1841c) = iVar2 + 1;
    *(int *)(iVar1 + iVar2 * 4 + 0x18420) = param_1;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x00018248. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0xa0))(param_1);
  return;
}




/* ============================================
 * Function: FUN_00018250
 * Address:  0x18250
 * ============================================ */

void FUN_00018250(int param_1)

{
  int iVar1;
  int iVar2;
  bool bVar3;
  
  PyObject_GC_UnTrack();
  if (*(int *)(param_1 + 8) != 0) {
    *(undefined4 *)(param_1 + 8) = 0;
    FUN_00017fec();
  }
  iVar1 = DAT_000182b8;
  iVar2 = *(int *)(DAT_000182b8 + 0x184ac);
  bVar3 = iVar2 == 7;
  if (iVar2 < 8) {
    bVar3 = *(int *)(*(int *)(param_1 + 4) + 0x10) == 0xc;
  }
  if (bVar3) {
    *(int *)(DAT_000182b8 + 0x184ac) = iVar2 + 1;
    *(int *)(iVar1 + iVar2 * 4 + 0x184b0) = param_1;
    return;
  }
                    /* WARNING: Could not recover jumptable at 0x000182b4. Too many branches */
                    /* WARNING: Treating indirect jump as call */
  (**(code **)(*(int *)(param_1 + 4) + 0xa0))(param_1);
  return;
}




/* ============================================
 * Function: FUN_000182bc
 * Address:  0x182bc
 * ============================================ */

void FUN_000182bc(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  FUN_00017fec();
  return;
}




/* ============================================
 * Function: FUN_000182c8
 * Address:  0x182c8
 * ============================================ */

void FUN_000182c8(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar3 = *(undefined4 *)(param_1 + 0x34);
  uVar2 = *(undefined4 *)(param_1 + 0x38);
  uVar1 = *(undefined4 *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x34) = param_2;
  *(undefined4 *)(param_1 + 0x38) = param_3;
  *(undefined4 *)(param_1 + 0x3c) = param_4;
  FUN_000182bc(uVar3);
  FUN_000182bc(uVar2);
  FUN_000182bc(uVar1);
  return;
}




/* ============================================
 * Function: FUN_000182fc
 * Address:  0x182fc
 * ============================================ */

void FUN_000182fc(undefined4 *param_1)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar1 = *param_1;
  uVar3 = param_1[1];
  uVar2 = param_1[2];
  *param_1 = 0;
  param_1[1] = 0;
  param_1[2] = 0;
  FUN_000182bc(uVar1);
  FUN_000182bc(uVar3);
  FUN_000182bc(uVar2);
  return;
}




/* ============================================
 * Function: FUN_00018334
 * Address:  0x18334
 * ============================================ */

undefined4 FUN_00018334(int param_1)

{
  if (*(int *)(param_1 + 0xc) != 0) {
    *(undefined4 *)(param_1 + 0xc) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    *(undefined4 *)(param_1 + 0x24) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x28) != 0) {
    *(undefined4 *)(param_1 + 0x28) = 0;
    FUN_00017fec();
  }
  FUN_000182fc(param_1 + 0x10);
  if (*(int *)(param_1 + 0x38) != 0) {
    *(undefined4 *)(param_1 + 0x38) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x2c) != 0) {
    *(undefined4 *)(param_1 + 0x2c) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x30) != 0) {
    *(undefined4 *)(param_1 + 0x30) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x34) != 0) {
    *(undefined4 *)(param_1 + 0x34) = 0;
    FUN_00017fec();
  }
  return 0;
}




/* ============================================
 * Function: FUN_000183f4
 * Address:  0x183f4
 * ============================================ */

void FUN_000183f4(int param_1)

{
  int iVar1;
  
  PyObject_GC_UnTrack();
  if (*(int *)(param_1 + 0x20) != 0) {
    PyObject_ClearWeakRefs(param_1);
  }
  if (-1 < *(int *)(param_1 + 0x3c)) {
    PyObject_GC_Track(param_1);
    iVar1 = PyObject_CallFinalizerFromDealloc(param_1);
    if (iVar1 != 0) {
      return;
    }
    PyObject_GC_UnTrack(param_1);
  }
  FUN_00018334(param_1);
  (*(code *)PTR_PyObject_GC_Del_00040dfc)(param_1);
  return;
}




/* ============================================
 * Function: FUN_00018454
 * Address:  0x18454
 * ============================================ */

undefined4 FUN_00018454(int param_1)

{
  int iVar1;
  int iVar2;
  
  if (*(int *)(param_1 + 0x34) != 0) {
    *(undefined4 *)(param_1 + 0x34) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x10) != 0) {
    *(undefined4 *)(param_1 + 0x10) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x1c) != 0) {
    *(undefined4 *)(param_1 + 0x1c) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x20) != 0) {
    *(undefined4 *)(param_1 + 0x20) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x24) != 0) {
    *(undefined4 *)(param_1 + 0x24) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x28) != 0) {
    *(undefined4 *)(param_1 + 0x28) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x2c) != 0) {
    *(undefined4 *)(param_1 + 0x2c) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x30) != 0) {
    *(undefined4 *)(param_1 + 0x30) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x38) != 0) {
    *(undefined4 *)(param_1 + 0x38) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x4c) != 0) {
    *(undefined4 *)(param_1 + 0x4c) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x50) != 0) {
    *(undefined4 *)(param_1 + 0x50) = 0;
    FUN_00017fec();
  }
  if (*(int *)(param_1 + 0x58) != 0) {
    *(undefined4 *)(param_1 + 0x58) = 0;
    FUN_00017fec();
  }
  iVar2 = *(int *)(param_1 + 0x3c);
  if (iVar2 != 0) {
    for (iVar1 = 0; iVar1 < *(int *)(param_1 + 0x40); iVar1 = iVar1 + 1) {
      FUN_000182bc(*(undefined4 *)(iVar2 + iVar1 * 4));
    }
    PyObject_Free(*(undefined4 *)(param_1 + 0x3c));
    *(undefined4 *)(param_1 + 0x3c) = 0;
  }
  return 0;
}




/* ============================================
 * Function: FUN_000185ec
 * Address:  0x185ec
 * ============================================ */

void FUN_000185ec(int param_1)

{
  PyObject_GC_UnTrack();
  if (*(int *)(param_1 + 0x14) != 0) {
    PyObject_ClearWeakRefs();
  }
  FUN_00018454(param_1);
  (*(code *)PTR_PyObject_GC_Del_00040dfc)(param_1);
  return;
}




/* ============================================
 * Function: FUN_00018604
 * Address:  0x18604
 * ============================================ */

undefined4 FUN_00018604(undefined4 param_1,undefined4 param_2)

{
  int *piVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  int iVar6;
  int iVar7;
  undefined4 local_34;
  undefined4 local_30;
  undefined4 auStack_2c [2];
  
  iVar3 = DAT_00018740;
  iVar6 = DAT_00018744 + 0x18624;
  iVar7 = *(int *)(DAT_00018740 + 0x1886c);
  if (iVar7 == 0) {
    return param_2;
  }
  FUN_00017668(param_1,&local_34,&local_30,auStack_2c);
  piVar1 = (int *)_PyObject_GetDictPtr(iVar7);
  iVar7 = *(int *)(iVar6 + DAT_00018748);
  if (piVar1 == (int *)0x0) {
    iVar3 = FUN_00017ee8(*(undefined4 *)(iVar3 + 0x1886c),*(undefined4 *)(iVar3 + 0x1887c));
    if (iVar3 != 0) {
      iVar4 = PyObject_Not();
      iVar2 = iVar7;
      if (iVar4 == 0) {
        iVar2 = *(int *)(iVar6 + DAT_0001874c);
      }
      FUN_00017fec(iVar3);
      goto LAB_000186d8;
    }
    PyErr_Clear();
LAB_00018720:
    PyObject_SetAttr(*(undefined4 *)(DAT_00018750 + 0x1897c),*(undefined4 *)(DAT_00018750 + 0x1898c)
                     ,iVar7);
  }
  else {
    iVar2 = *piVar1;
    if (*(int *)(iVar2 + 0x14) == *(int *)(iVar3 + 0x18874) &&
        *(int *)(iVar2 + 0x10) == *(int *)(iVar3 + 0x18870)) {
      iVar2 = *(int *)(iVar3 + 0x18878);
    }
    else {
      iVar2 = _PyDict_GetItem_KnownHash
                        (iVar2,*(int *)(iVar3 + 0x1887c),
                         *(undefined4 *)(*(int *)(iVar3 + 0x1887c) + 0xc));
      iVar4 = *piVar1;
      *(int *)(iVar3 + 0x18878) = iVar2;
      uVar5 = *(undefined4 *)(iVar4 + 0x14);
      *(undefined4 *)(iVar3 + 0x18870) = *(undefined4 *)(iVar4 + 0x10);
      *(undefined4 *)(iVar3 + 0x18874) = uVar5;
    }
    if (iVar2 == 0) goto LAB_00018720;
LAB_000186d8:
    if ((iVar2 != iVar7) &&
       ((iVar2 == *(int *)(iVar6 + DAT_0001874c) || (iVar3 = PyObject_Not(iVar2), iVar3 == 0))))
    goto LAB_00018700;
  }
  param_2 = 0;
LAB_00018700:
  FUN_000182c8(param_1,local_34,local_30,auStack_2c[0]);
  return param_2;
}




/* ============================================
 * Function: FUN_00018754
 * Address:  0x18754
 * ============================================ */

undefined4 FUN_00018754(undefined4 param_1,int param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = PyUnicode_FromString(param_4);
  if (iVar1 != 0) {
    if (param_2 == 0) {
      iVar2 = PyUnicode_FromString(param_1);
    }
    else {
      iVar2 = PyUnicode_FromFormat(DAT_00018838 + 0x1879c,param_1,DAT_00018834 + 0x18798,param_2);
    }
    if (iVar2 != 0) {
      uVar3 = *(undefined4 *)(DAT_0001883c + 0x18800);
      uVar3 = PyCode_New(0,0,0,0,0,*(undefined4 *)(DAT_0001883c + 0x187fc),uVar3,uVar3,uVar3,uVar3,
                         uVar3,iVar1,iVar2,param_3,*(undefined4 *)(DAT_0001883c + 0x187fc));
      FUN_00017fec(iVar1);
      FUN_00017fec(iVar2);
      return uVar3;
    }
  }
  FUN_000182bc(iVar1);
  FUN_000182bc(0);
  return 0;
}




/* ============================================
 * Function: FUN_00018840
 * Address:  0x18840
 * ============================================ */

bool FUN_00018840(int param_1,int param_2)

{
  return param_2 == param_1;
}




/* ============================================
 * Function: FUN_00018850
 * Address:  0x18850
 * ============================================ */

uint FUN_00018850(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  
  uVar2 = *(undefined4 *)(DAT_0001891c + 0x18864 + DAT_00018920);
  iVar1 = FUN_00018840(*(undefined4 *)(param_1 + 4),uVar2,DAT_00018920,uVar2,param_1,uVar2,param_3);
  if (iVar1 == 0) {
    iVar1 = PyNumber_Index(param_1);
    if (iVar1 == 0) {
      uVar3 = 0xffffffff;
    }
    else {
      uVar3 = PyLong_AsSsize_t();
      FUN_00017fec(iVar1);
    }
  }
  else {
    iVar1 = *(int *)(param_1 + 8);
    if (iVar1 + 1U < 3) {
      uVar3 = 0;
      if ((iVar1 != 0) && (uVar3 = (uint)*(ushort *)(param_1 + 0xc), iVar1 == -1)) {
        uVar3 = -uVar3;
      }
    }
    else if (iVar1 == -2) {
      uVar3 = -((uint)*(ushort *)(param_1 + 0xc) | (uint)*(ushort *)(param_1 + 0xe) << 0xf);
    }
    else {
      if (iVar1 != 2) {
        uVar3 = PyLong_AsSsize_t(param_1);
        return uVar3;
      }
      uVar3 = (uint)*(ushort *)(param_1 + 0xc) | (uint)*(ushort *)(param_1 + 0xe) << 0xf;
    }
  }
  return uVar3;
}




/* ============================================
 * Function: FUN_00018924
 * Address:  0x18924
 * ============================================ */

void FUN_00018924(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  return;
}




/* ============================================
 * Function: FUN_0001892c
 * Address:  0x1892c
 * ============================================ */

void FUN_0001892c(undefined4 *param_1,undefined4 param_2)

{
  *param_1 = param_2;
  return;
}




/* ============================================
 * Function: FUN_00018934
 * Address:  0x18934
 * ============================================ */

void FUN_00018934(int *param_1)

{
  *param_1 = *param_1 + 1;
  return;
}




/* ============================================
 * Function: FUN_00018944
 * Address:  0x18944
 * ============================================ */

void FUN_00018944(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  FUN_00018934();
  return;
}




/* ============================================
 * Function: FUN_00018950
 * Address:  0x18950
 * ============================================ */

undefined4 FUN_00018950(int param_1,undefined4 *param_2,undefined4 *param_3,int *param_4)

{
  undefined4 uVar1;
  int iVar2;
  undefined4 *puVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  undefined4 local_24;
  undefined4 local_20;
  int local_1c [2];
  
  local_24 = *(undefined4 *)(param_1 + 0x34);
  local_20 = *(undefined4 *)(param_1 + 0x38);
  local_1c[0] = *(int *)(param_1 + 0x3c);
  *(undefined4 *)(param_1 + 0x34) = 0;
  *(undefined4 *)(param_1 + 0x38) = 0;
  *(undefined4 *)(param_1 + 0x3c) = 0;
  PyErr_NormalizeException(&local_24,&local_20,local_1c);
  if ((*(int *)(param_1 + 0x34) == 0) &&
     ((local_1c[0] == 0 || (iVar2 = PyException_SetTraceback(local_20), -1 < iVar2)))) {
    FUN_00018944(local_1c[0]);
    FUN_00018944(local_24);
    FUN_00018944(local_20);
    puVar3 = *(undefined4 **)(param_1 + 0x50);
    *param_2 = local_24;
    *param_3 = local_20;
    *param_4 = local_1c[0];
    uVar1 = *puVar3;
    uVar5 = puVar3[1];
    uVar4 = puVar3[2];
    *puVar3 = local_24;
    puVar3[1] = local_20;
    puVar3[2] = local_1c[0];
    FUN_000182bc(uVar1);
    FUN_000182bc(uVar5);
    FUN_000182bc(uVar4);
    uVar1 = 0;
  }
  else {
    *param_2 = 0;
    *param_3 = 0;
    *param_4 = 0;
    FUN_000182bc(local_24);
    FUN_000182bc(local_20);
    FUN_000182bc(local_1c[0]);
    uVar1 = 0xffffffff;
  }
  return uVar1;
}




/* ============================================
 * Function: FUN_00018a5c
 * Address:  0x18a5c
 * ============================================ */

undefined4 FUN_00018a5c(int param_1)

{
  FUN_00018934(*(undefined4 *)(param_1 + 0x24));
  return *(undefined4 *)(param_1 + 0x24);
}




/* ============================================
 * Function: FUN_00018a74
 * Address:  0x18a74
 * ============================================ */

void FUN_00018a74(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x34);
  if (iVar1 == 0) {
    iVar1 = *(int *)(DAT_00018a9c + 0x18a8c + DAT_00018aa0);
  }
  FUN_00018934(iVar1);
  return;
}




/* ============================================
 * Function: FUN_00018af0
 * Address:  0x18af0
 * ============================================ */

void FUN_00018af0(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if (iVar1 == 0) {
    iVar1 = *(int *)(DAT_00018b18 + 0x18b08 + DAT_00018b1c);
  }
  FUN_00018934(iVar1);
  return;
}




/* ============================================
 * Function: FUN_00018b20
 * Address:  0x18b20
 * ============================================ */

void FUN_00018b20(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x30);
  if (iVar1 == 0) {
    iVar1 = *(int *)(DAT_00018b48 + 0x18b38 + DAT_00018b4c);
  }
  FUN_00018934(iVar1);
  return;
}




/* ============================================
 * Function: FUN_00018b50
 * Address:  0x18b50
 * ============================================ */

void FUN_00018b50(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x2c);
  if (iVar1 == 0) {
    iVar1 = *(int *)(DAT_00018b78 + 0x18b68 + DAT_00018b7c);
  }
  FUN_00018934(iVar1);
  return;
}




/* ============================================
 * Function: FUN_00018b80
 * Address:  0x18b80
 * ============================================ */

undefined4 FUN_00018b80(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  if (param_1 != 0) {
    iVar2 = *(int *)(DAT_00018be8 + 0x18e00);
    if (iVar2 == 0) {
      return 0;
    }
    iVar4 = *(int *)(DAT_00018be8 + 0x18df8);
    iVar1 = FUN_00017914(iVar2,iVar4,param_1);
    if ((iVar1 < iVar4) && (*(int *)(iVar2 + iVar1 * 8 + 4) == param_1)) {
      uVar3 = *(undefined4 *)(iVar2 + iVar1 * 8);
      FUN_00018934(uVar3);
      return uVar3;
    }
  }
  return 0;
}




/* ============================================
 * Function: FUN_00018bec
 * Address:  0x18bec
 * ============================================ */

int FUN_00018bec(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x58);
  if (iVar1 == 0) {
    iVar1 = PyDict_New();
    if (iVar1 == 0) {
      return 0;
    }
    *(int *)(param_1 + 0x58) = iVar1;
  }
  FUN_00018934(iVar1);
  return iVar1;
}




/* ============================================
 * Function: FUN_00018c58
 * Address:  0x18c58
 * ============================================ */

int FUN_00018c58(int param_1,undefined4 *param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_00018cc0;
  iVar1 = _PyDict_GetItem_KnownHash
                    (*(undefined4 *)(FUN_00018ee0 + DAT_00018cc0 + 4),param_1,
                     *(undefined4 *)(param_1 + 0xc));
  uVar3 = *(undefined4 *)(*(int *)(FUN_00018ee0 + iVar2 + 4) + 0x14);
  *param_2 = *(undefined4 *)(*(int *)(FUN_00018ee0 + iVar2 + 4) + 0x10);
  param_2[1] = uVar3;
  *param_3 = iVar1;
  if (iVar1 == 0) {
    iVar2 = PyErr_Occurred();
    if (iVar2 == 0) {
      iVar2 = FUN_00017f00(param_1);
      return iVar2;
    }
  }
  else {
    FUN_00018934();
  }
  return iVar1;
}




/* ============================================
 * Function: FUN_00018d24
 * Address:  0x18d24
 * ============================================ */

int FUN_00018d24(int param_1,undefined4 param_2)

{
  uint uVar1;
  undefined4 extraout_r1;
  
  FUN_00018924(param_1 + 4);
  uVar1 = PyType_GetFlags(extraout_r1);
  if ((uVar1 & 0x200) != 0) {
    FUN_00018934(param_2);
  }
  _Py_NewReference(param_1);
  return param_1;
}




/* ============================================
 * Function: FUN_00018de0
 * Address:  0x18de0
 * ============================================ */

undefined8 * FUN_00018de0(int param_1)

{
  int iVar1;
  undefined8 *puVar2;
  int iVar3;
  
  iVar1 = DAT_00018e5c;
  if (*(int *)(DAT_00018e5c + 0x18fac) < 1 || *(int *)(param_1 + 0x10) != 0x1c) {
                    /* WARNING: Could not recover jumptable at 0x00018e1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    puVar2 = (undefined8 *)(**(code **)(param_1 + 0x98))(param_1,0);
    return puVar2;
  }
  iVar3 = *(int *)(DAT_00018e5c + 0x18fac) + -1;
  *(int *)(DAT_00018e5c + 0x18fac) = iVar3;
  puVar2 = *(undefined8 **)(iVar1 + iVar3 * 4 + 0x18fb0);
  *puVar2 = 0;
  puVar2[1] = 0;
  *(undefined8 *)((int)puVar2 + 0xc) = 0;
  *(undefined8 *)((int)puVar2 + 0x14) = 0;
  FUN_00018d24(puVar2,param_1);
  PyObject_GC_Track(puVar2);
  return puVar2;
}




/* ============================================
 * Function: FUN_00018e60
 * Address:  0x18e60
 * ============================================ */

undefined8 * FUN_00018e60(int param_1)

{
  int iVar1;
  undefined8 *puVar2;
  int iVar3;
  
  iVar1 = DAT_00018edc;
  if (*(int *)(DAT_00018edc + 0x19098) < 1 || *(int *)(param_1 + 0x10) != 0xc) {
                    /* WARNING: Could not recover jumptable at 0x00018e9c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    puVar2 = (undefined8 *)(**(code **)(param_1 + 0x98))(param_1,0);
    return puVar2;
  }
  iVar3 = *(int *)(DAT_00018edc + 0x19098) + -1;
  *(int *)(DAT_00018edc + 0x19098) = iVar3;
  puVar2 = *(undefined8 **)(iVar1 + iVar3 * 4 + 0x1909c);
  *puVar2 = 0;
  *(undefined8 *)((int)puVar2 + 4) = 0;
  FUN_00018d24(puVar2,param_1);
  PyObject_GC_Track(puVar2);
  return puVar2;
}




/* ============================================
 * Function: FUN_00018ee0
 * Address:  0x18ee0
 * ============================================ */

undefined8 * FUN_00018ee0(int param_1)

{
  int iVar1;
  undefined8 *puVar2;
  int iVar3;
  
  iVar1 = DAT_00018f5c;
  if (*(int *)(DAT_00018f5c + 0x190f4) < 1 || *(int *)(param_1 + 0x10) != 0x1c) {
                    /* WARNING: Could not recover jumptable at 0x00018f1c. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    puVar2 = (undefined8 *)(**(code **)(param_1 + 0x98))(param_1,0);
    return puVar2;
  }
  iVar3 = *(int *)(DAT_00018f5c + 0x190f4) + -1;
  *(int *)(DAT_00018f5c + 0x190f4) = iVar3;
  puVar2 = *(undefined8 **)(iVar1 + iVar3 * 4 + 0x190f8);
  *puVar2 = 0;
  puVar2[1] = 0;
  *(undefined8 *)((int)puVar2 + 0xc) = 0;
  *(undefined8 *)((int)puVar2 + 0x14) = 0;
  FUN_00018d24(puVar2,param_1);
  PyObject_GC_Track(puVar2);
  return puVar2;
}




/* ============================================
 * Function: FUN_00018f60
 * Address:  0x18f60
 * ============================================ */

int FUN_00018f60(int param_1,undefined4 param_2)

{
  int iVar1;
  code *UNRECOVERED_JUMPTABLE;
  int iVar2;
  undefined4 uVar3;
  
  uVar3 = *(undefined4 *)(param_1 + 4);
  iVar2 = DAT_00018fcc + 0x18f80;
  iVar1 = _PyType_Lookup(uVar3);
  if (iVar1 == 0) {
    PyErr_SetObject(**(undefined4 **)(iVar2 + DAT_00018fd0),param_2);
  }
  else {
    UNRECOVERED_JUMPTABLE = *(code **)(*(int *)(iVar1 + 4) + 0x88);
    if (UNRECOVERED_JUMPTABLE != (code *)0x0) {
                    /* WARNING: Could not recover jumptable at 0x00018fb0. Too many branches */
                    /* WARNING: Treating indirect jump as call */
      iVar1 = (*UNRECOVERED_JUMPTABLE)(iVar1,param_1,uVar3);
      return iVar1;
    }
    FUN_00018934();
  }
  return iVar1;
}




/* ============================================
 * Function: FUN_00018fe0
 * Address:  0x18fe0
 * ============================================ */

void FUN_00018fe0(void)

{
  FUN_00018934();
  return;
}




/* ============================================
 * Function: FUN_000190a8
 * Address:  0x190a8
 * ============================================ */

undefined4 FUN_000190a8(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  
  iVar1 = _PyThreadState_UncheckedGet();
  iVar2 = PyFrame_New(iVar1,param_1,param_4,0);
  uVar3 = 0;
  if (iVar2 != 0) {
    puVar5 = (undefined4 *)(iVar2 + *(int *)(FUN_0001935c + DAT_0001914c));
    for (iVar4 = 0; iVar4 < param_3; iVar4 = iVar4 + 1) {
      FUN_00018934(*(undefined4 *)(param_2 + iVar4 * 4));
      *puVar5 = *(undefined4 *)(param_2 + iVar4 * 4);
      puVar5 = puVar5 + 1;
    }
    uVar3 = PyEval_EvalFrameEx(iVar2,0);
    *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + 1;
    FUN_00017fec(iVar2);
    *(int *)(iVar1 + 0x10) = *(int *)(iVar1 + 0x10) + -1;
  }
  return uVar3;
}




/* ============================================
 * Function: FUN_00019150
 * Address:  0x19150
 * ============================================ */

undefined4 FUN_00019150(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  
  iVar1 = PyTuple_New(1);
  uVar2 = 0;
  if (iVar1 != 0) {
    FUN_00018934(param_2);
    *(undefined4 *)(iVar1 + 0xc) = param_2;
    uVar2 = FUN_00017e40(param_1,iVar1,0);
    FUN_00017fec(iVar1);
  }
  return uVar2;
}




/* ============================================
 * Function: FUN_000191a0
 * Address:  0x191a0
 * ============================================ */

undefined4 FUN_000191a0(int param_1)

{
  int iVar1;
  
  iVar1 = (**(code **)(param_1 + 0x54))();
  if (iVar1 != 0) {
    *(undefined4 *)(param_1 + 0x4c) = *(undefined4 *)(iVar1 + 0xc);
    FUN_00018934();
    *(undefined4 *)(param_1 + 0x50) = *(undefined4 *)(iVar1 + 0x10);
    FUN_00018934();
    FUN_00017fec(iVar1);
    return 0;
  }
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_000191e8
 * Address:  0x191e8
 * ============================================ */

int FUN_000191e8(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x50);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x54) == 0) {
      iVar1 = *(int *)(DAT_0001923c + 0x19200 + DAT_00019240);
    }
    else {
      iVar1 = FUN_000191a0();
      if (iVar1 < 0) {
        return 0;
      }
      iVar1 = *(int *)(param_1 + 0x50);
    }
  }
  FUN_00018934(iVar1);
  return iVar1;
}




/* ============================================
 * Function: FUN_00019244
 * Address:  0x19244
 * ============================================ */

int FUN_00019244(int param_1)

{
  int iVar1;
  
  iVar1 = *(int *)(param_1 + 0x4c);
  if (iVar1 == 0) {
    if (*(int *)(param_1 + 0x54) == 0) {
      iVar1 = *(int *)(DAT_00019298 + 0x1925c + DAT_0001929c);
    }
    else {
      iVar1 = FUN_000191a0();
      if (iVar1 < 0) {
        return 0;
      }
      iVar1 = *(int *)(param_1 + 0x4c);
    }
  }
  FUN_00018934(iVar1);
  return iVar1;
}




/* ============================================
 * Function: FUN_000192a0
 * Address:  0x192a0
 * ============================================ */

undefined4 FUN_000192a0(int param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = *(undefined4 *)(param_1 + 0x28);
  if (param_2 == 0) {
    param_2 = *(int *)(DAT_000192dc + 0x192bc + DAT_000192e0);
  }
  FUN_00018934(param_2);
  *(int *)(param_1 + 0x28) = param_2;
  FUN_000182bc(uVar1);
  return 0;
}




/* ============================================
 * Function: FUN_0001935c
 * Address:  0x1935c
 * ============================================ */

void FUN_0001935c(int param_1,undefined4 param_2)

{
  undefined4 *puVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 *puVar7;
  
  iVar6 = DAT_00019480;
  iVar4 = *(int *)(DAT_00019480 + 0x195d8);
  if (param_1 == 0) {
    return;
  }
  if (iVar4 == 0) {
    puVar1 = (undefined4 *)PyMem_Malloc(0x200);
    if (puVar1 == (undefined4 *)0x0) {
      return;
    }
    *(undefined4 **)(iVar6 + 0x195d8) = puVar1;
    *(undefined4 *)(iVar6 + 0x195d4) = 0x40;
    *(undefined4 *)(iVar6 + 0x195d0) = 1;
    *puVar1 = param_2;
    puVar1[1] = param_1;
  }
  else {
    iVar5 = *(int *)(DAT_00019480 + 0x195d0);
    iVar2 = FUN_00017914(iVar4,iVar5,param_1);
    iVar6 = DAT_00019484;
    if ((iVar2 < iVar5) && (*(int *)(iVar4 + iVar2 * 8 + 4) == param_1)) {
      uVar3 = *(undefined4 *)(iVar4 + iVar2 * 8);
      *(undefined4 *)(iVar4 + iVar2 * 8) = param_2;
      FUN_00017fec(uVar3);
      return;
    }
    if (iVar5 == *(int *)(DAT_00019484 + 0x19664)) {
      iVar4 = PyMem_Realloc(iVar4,(iVar5 + 0x40) * 8);
      if (iVar4 == 0) {
        return;
      }
      *(int *)(iVar6 + 0x19668) = iVar4;
      *(int *)(iVar6 + 0x19664) = iVar5 + 0x40;
    }
    iVar5 = *(int *)(FUN_00019694 + DAT_00019488 + 4);
    for (iVar6 = iVar5; iVar2 < iVar6; iVar6 = iVar6 + -1) {
      puVar7 = (undefined4 *)(iVar4 + iVar6 * 8);
      puVar1 = (undefined4 *)(iVar6 * 8 + iVar4 + -8);
      uVar3 = puVar1[1];
      *puVar7 = *puVar1;
      puVar7[1] = uVar3;
    }
    *(int *)(iVar4 + iVar2 * 8 + 4) = param_1;
    iVar6 = DAT_0001948c;
    *(undefined4 *)(iVar4 + iVar2 * 8) = param_2;
    *(int *)(iVar6 + 0x196c0) = iVar5 + 1;
  }
  FUN_00018934(param_2);
  return;
}




/* ============================================
 * Function: FUN_00019490
 * Address:  0x19490
 * ============================================ */

void FUN_00019490(undefined4 param_1,int param_2,int param_3,undefined4 param_4)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  
  uVar1 = _PyThreadState_UncheckedGet();
  iVar2 = 0;
  iVar4 = param_3;
  if ((param_2 != 0) && (iVar2 = FUN_00018604(uVar1,param_2), iVar2 != 0)) {
    iVar4 = -iVar2;
  }
  iVar3 = FUN_00018b80(iVar4);
  if (iVar3 == 0) {
    iVar3 = FUN_00018754(param_1,iVar2,param_3,param_4);
    if (iVar3 == 0) {
      iVar2 = 0;
      goto LAB_00019534;
    }
    FUN_0001935c(iVar4,iVar3);
  }
  iVar2 = PyFrame_New(uVar1,iVar3,*(undefined4 *)(DAT_00019548 + 0x1978c),0);
  if (iVar2 != 0) {
    *(int *)(iVar2 + 0x38) = param_3;
    PyTraceBack_Here();
  }
LAB_00019534:
  FUN_000182bc(iVar3);
  FUN_000182bc(iVar2);
  return;
}




/* ============================================
 * Function: FUN_0001954c
 * Address:  0x1954c
 * ============================================ */

bool FUN_0001954c(uint param_1,uint param_2)

{
  return (param_2 & param_1) != 0;
}




/* ============================================
 * Function: FUN_0001955c
 * Address:  0x1955c
 * ============================================ */

int FUN_0001955c(undefined4 param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_000195fc;
  iVar2 = PyDict_GetItemWithError();
  if (iVar2 != 0) {
    FUN_00018934();
    return iVar2;
  }
  iVar2 = PyErr_Occurred();
  if (iVar2 == 0) {
    iVar2 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x4000000);
    if (iVar2 == 0) {
      PyErr_SetObject(**(undefined4 **)(iVar1 + 0x19578 + DAT_00019600),param_2);
      return 0;
    }
    iVar2 = PyTuple_Pack(1,param_2);
    if (iVar2 != 0) {
      PyErr_SetObject(**(undefined4 **)(iVar1 + 0x19578 + DAT_00019600),iVar2);
      FUN_00017fec(iVar2);
      return 0;
    }
  }
  return 0;
}




/* ============================================
 * Function: FUN_00019604
 * Address:  0x19604
 * ============================================ */

undefined4 FUN_00019604(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = DAT_00019684 + 0x1961c;
  if (param_2 == *(int *)(iVar3 + DAT_00019688) || param_2 == 0) {
    param_2 = 0;
  }
  else {
    iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x20000000);
    if (iVar1 == 0) {
      PyErr_SetString(**(undefined4 **)(iVar3 + DAT_0001968c),DAT_00019690 + 0x19658);
      return 0xffffffff;
    }
  }
  FUN_00018944(param_2);
  uVar2 = *(undefined4 *)(param_1 + 0x58);
  *(int *)(param_1 + 0x58) = param_2;
  FUN_000182bc(uVar2);
  return 0;
}




/* ============================================
 * Function: FUN_00019694
 * Address:  0x19694
 * ============================================ */

undefined4 FUN_00019694(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = DAT_00019714 + 0x196ac;
  iVar3 = *(int *)(iVar4 + DAT_00019718);
  if ((param_2 != 0 && param_2 != iVar3) &&
     (iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x20000000),
     iVar3 = param_2, iVar1 == 0)) {
    PyErr_SetString(**(undefined4 **)(iVar4 + DAT_0001971c),DAT_00019720 + 0x196e8);
    return 0xffffffff;
  }
  FUN_00018934(iVar3);
  uVar2 = *(undefined4 *)(param_1 + 0x50);
  *(int *)(param_1 + 0x50) = iVar3;
  FUN_000182bc(uVar2);
  return 0;
}




/* ============================================
 * Function: FUN_00019724
 * Address:  0x19724
 * ============================================ */

undefined4 FUN_00019724(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = DAT_000197a4 + 0x1973c;
  iVar3 = *(int *)(iVar4 + DAT_000197a8);
  if ((param_2 != 0 && param_2 != iVar3) &&
     (iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x4000000), iVar3 = param_2
     , iVar1 == 0)) {
    PyErr_SetString(**(undefined4 **)(iVar4 + DAT_000197ac),DAT_000197b0 + 0x19778);
    return 0xffffffff;
  }
  FUN_00018934(iVar3);
  uVar2 = *(undefined4 *)(param_1 + 0x4c);
  *(int *)(param_1 + 0x4c) = iVar3;
  FUN_000182bc(uVar2);
  return 0;
}




/* ============================================
 * Function: FUN_000197b4
 * Address:  0x197b4
 * ============================================ */

undefined4 FUN_000197b4(int param_1,int param_2)

{
  int iVar1;
  undefined4 *puVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = DAT_00019838 + 0x197c8;
  if (param_2 == 0) {
    puVar2 = *(undefined4 **)(iVar3 + DAT_0001983c);
    iVar3 = DAT_00019840 + 0x197dc;
  }
  else {
    iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x20000000);
    if (iVar1 != 0) {
      uVar4 = *(undefined4 *)(param_1 + 0x1c);
      FUN_00018934(param_2);
      *(int *)(param_1 + 0x1c) = param_2;
      FUN_000182bc(uVar4);
      return 0;
    }
    puVar2 = *(undefined4 **)(iVar3 + DAT_0001983c);
    iVar3 = DAT_00019844 + 0x19818;
  }
  PyErr_SetString(*puVar2,iVar3);
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_00019848
 * Address:  0x19848
 * ============================================ */

undefined4 FUN_00019848(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_000198b8 + 0x1985c;
  if ((param_2 != 0) &&
     (iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x10000000), iVar1 != 0)) {
    uVar3 = *(undefined4 *)(param_1 + 0x24);
    FUN_00018934(param_2);
    *(int *)(param_1 + 0x24) = param_2;
    FUN_000182bc(uVar3);
    return 0;
  }
  PyErr_SetString(**(undefined4 **)(iVar2 + DAT_000198bc),DAT_000198c0 + 0x1988c);
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_000198c4
 * Address:  0x198c4
 * ============================================ */

undefined4 FUN_000198c4(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_00019934 + 0x198d8;
  if ((param_2 != 0) &&
     (iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x10000000), iVar1 != 0)) {
    uVar3 = *(undefined4 *)(param_1 + 0x20);
    FUN_00018934(param_2);
    *(int *)(param_1 + 0x20) = param_2;
    FUN_000182bc(uVar3);
    return 0;
  }
  PyErr_SetString(**(undefined4 **)(iVar2 + DAT_00019938),DAT_0001993c + 0x19908);
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_00019940
 * Address:  0x19940
 * ============================================ */

undefined4 FUN_00019940(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_000199b0 + 0x19954;
  if ((param_2 != 0) &&
     (iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x10000000), iVar1 != 0)) {
    uVar3 = *(undefined4 *)(param_1 + 0x30);
    FUN_00018934(param_2);
    *(int *)(param_1 + 0x30) = param_2;
    FUN_000182bc(uVar3);
    return 0;
  }
  PyErr_SetString(**(undefined4 **)(iVar2 + DAT_000199b4),DAT_000199b8 + 0x19984);
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_000199bc
 * Address:  0x199bc
 * ============================================ */

undefined4 FUN_000199bc(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_00019a2c + 0x199d0;
  if ((param_2 != 0) &&
     (iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x10000000), iVar1 != 0)) {
    uVar3 = *(undefined4 *)(param_1 + 0x2c);
    FUN_00018934(param_2);
    *(int *)(param_1 + 0x2c) = param_2;
    FUN_000182bc(uVar3);
    return 0;
  }
  PyErr_SetString(**(undefined4 **)(iVar2 + DAT_00019a30),DAT_00019a34 + 0x19a00);
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_00019a38
 * Address:  0x19a38
 * ============================================ */

void FUN_00019a38(int param_1)

{
  FUN_0001954c(*(undefined4 *)(param_1 + 0x54),0x80000000);
  return;
}




/* ============================================
 * Function: FUN_00019adc
 * Address:  0x19adc
 * ============================================ */

undefined4 FUN_00019adc(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  int iVar6;
  
  if (param_1 == param_2) {
    return 1;
  }
  iVar2 = FUN_00019a38(*(undefined4 *)(param_1 + 4));
  if ((iVar2 != 0) && (iVar2 = FUN_0001954c(*(undefined4 *)(param_1 + 0x54),0x40000000), iVar2 != 0)
     ) {
    iVar5 = *(int *)(param_2 + 4);
    iVar2 = FUN_00019a38(iVar5);
    if ((iVar2 != 0) &&
       (iVar2 = FUN_0001954c(*(undefined4 *)(param_2 + 0x54),0x40000000), iVar2 != 0)) {
      uVar3 = FUN_00017728(param_1,0,param_2);
      return uVar3;
    }
    iVar2 = FUN_0001954c(*(undefined4 *)(iVar5 + 0x54),0x4000000);
    if (iVar2 != 0) {
      iVar5 = *(int *)(param_2 + 8);
      piVar4 = (int *)(param_2 + 0xc);
      for (iVar2 = 0; iVar2 < iVar5; iVar2 = iVar2 + 1) {
        if (*piVar4 == param_1) {
          return 1;
        }
        piVar4 = piVar4 + 1;
      }
      iVar2 = 0;
      piVar4 = (int *)(param_2 + 0xc);
      while( true ) {
        if (iVar5 <= iVar2) {
          return 0;
        }
        iVar6 = *piVar4;
        iVar1 = FUN_00019a38(*(undefined4 *)(iVar6 + 4));
        if (((iVar1 != 0) &&
            (iVar1 = FUN_0001954c(*(undefined4 *)(iVar6 + 0x54),0x40000000), iVar1 != 0)) &&
           (iVar1 = FUN_00017728(param_1,0,iVar6), iVar1 != 0)) break;
        iVar2 = iVar2 + 1;
        piVar4 = piVar4 + 1;
      }
      return 1;
    }
  }
  uVar3 = PyErr_GivenExceptionMatches(param_1,param_2);
  return uVar3;
}




/* ============================================
 * Function: FUN_00019bf8
 * Address:  0x19bf8
 * ============================================ */

undefined4 FUN_00019bf8(void)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  
  iVar1 = _PyThreadState_UncheckedGet();
  iVar3 = *(int *)(iVar1 + 0x34);
  if (iVar3 == 0) {
    return 0;
  }
  iVar2 = FUN_00019adc(iVar3,**(undefined4 **)(DAT_00019c7c + 0x19c14 + DAT_00019c80));
  if (iVar2 != 0) {
    uVar5 = *(undefined4 *)(iVar1 + 0x38);
    uVar4 = *(undefined4 *)(iVar1 + 0x3c);
    *(undefined4 *)(iVar1 + 0x34) = 0;
    *(undefined4 *)(iVar1 + 0x38) = 0;
    *(undefined4 *)(iVar1 + 0x3c) = 0;
    FUN_00017fec(iVar3);
    FUN_000182bc(uVar5);
    FUN_000182bc(uVar4);
    return 0;
  }
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_00019c84
 * Address:  0x19c84
 * ============================================ */

undefined4 FUN_00019c84(undefined4 param_1,int *param_2)

{
  undefined4 uVar1;
  int iVar2;
  int iVar3;
  int *piVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int local_34;
  int local_30;
  undefined4 local_2c [2];
  
  iVar7 = DAT_00019e5c + 0x19ca4;
  uVar1 = FUN_00017668(param_1,&local_34,&local_30,local_2c);
  iVar5 = local_30;
  iVar3 = local_34;
  if (local_34 == 0) {
    FUN_000182bc(local_2c[0]);
    FUN_000182bc(local_30);
    iVar5 = *(int *)(iVar7 + DAT_00019e60);
    FUN_00018934(iVar5);
    goto LAB_00019ce4;
  }
  piVar4 = *(int **)(iVar7 + DAT_00019e64);
  if (local_34 == *piVar4) {
    if (local_30 == 0) {
      iVar5 = *(int *)(iVar7 + DAT_00019e60);
      FUN_00018934(iVar5);
    }
    else {
      iVar8 = *(int *)(local_30 + 4);
      if (local_34 == iVar8) {
        iVar5 = *(int *)(local_30 + 0x20);
LAB_00019d78:
        FUN_00018934(iVar5);
      }
      else {
        iVar2 = FUN_0001954c(*(undefined4 *)(iVar8 + 0x54),0x4000000);
        if (iVar2 == 0) {
          iVar3 = FUN_000176d8(iVar8,iVar3);
          if (iVar3 != 0) goto LAB_00019d90;
          goto LAB_00019d30;
        }
        if (0 < *(int *)(iVar5 + 8)) {
          iVar5 = *(int *)(iVar5 + 0xc);
          goto LAB_00019d78;
        }
        iVar5 = *(int *)(iVar7 + DAT_00019e60);
        FUN_00018934(iVar5);
      }
      FUN_00017fec(local_30);
      if (iVar5 == 0) goto LAB_00019d90;
    }
LAB_00019d30:
    FUN_000182bc(local_2c[0]);
  }
  else {
    iVar3 = FUN_00019adc(local_34);
    if (iVar3 == 0) goto LAB_00019e40;
LAB_00019d90:
    PyErr_NormalizeException(&local_34,&local_30,local_2c);
    uVar6 = *(undefined4 *)(local_30 + 4);
    iVar3 = FUN_00018840(uVar6,*piVar4);
    if ((iVar3 == 0) && (iVar3 = PyType_IsSubtype(uVar6), iVar3 == 0)) {
LAB_00019e40:
      FUN_000182c8(uVar1,local_34,local_30,local_2c[0]);
      return 0xffffffff;
    }
    FUN_000182bc(local_2c[0]);
    FUN_00017fec(local_34);
    iVar5 = *(int *)(local_30 + 0x20);
    FUN_00018934(iVar5);
    local_34 = local_30;
  }
  FUN_00017fec(local_34);
LAB_00019ce4:
  *param_2 = iVar5;
  return 0;
}




/* ============================================
 * Function: FUN_00019e68
 * Address:  0x19e68
 * ============================================ */

uint FUN_00019e68(int param_1,int param_2,int param_3)

{
  int iVar1;
  uint uVar2;
  
  if (param_1 == param_3 || param_1 == param_2) {
    return 1;
  }
  iVar1 = FUN_00019a38(*(undefined4 *)(param_1 + 4));
  if ((iVar1 != 0) && (iVar1 = FUN_0001954c(*(undefined4 *)(param_1 + 0x54),0x40000000), iVar1 != 0)
     ) {
    uVar2 = FUN_00017728(param_1,param_2);
    return uVar2;
  }
  iVar1 = PyErr_GivenExceptionMatches(param_1,param_2);
  if (iVar1 == 0) {
    iVar1 = PyErr_GivenExceptionMatches(param_1,param_3);
    return (uint)(iVar1 != 0);
  }
  return 1;
}




/* ============================================
 * Function: FUN_00019ef4
 * Address:  0x19ef4
 * ============================================ */

void FUN_00019ef4(int *param_1)

{
  do {
    if (*param_1 != 0 && *param_1 != *(int *)(DAT_00019f28 + 0x19f04 + DAT_00019f2c)) {
      return;
    }
    param_1 = (int *)param_1[3];
  } while (param_1 != (int *)0x0);
  return;
}




/* ============================================
 * Function: FUN_00019f30
 * Address:  0x19f30
 * ============================================ */

void FUN_00019f30(int param_1,undefined4 param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 *puVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  uVar3 = FUN_00019ef4(*(undefined4 *)(param_1 + 0x50));
  puVar2 = (undefined4 *)((ulonglong)uVar3 >> 0x20);
  puVar1 = (undefined4 *)uVar3;
  *puVar2 = *puVar1;
  *param_3 = puVar1[1];
  *param_4 = puVar1[2];
  FUN_00018944(*puVar2);
  FUN_00018944(*param_3);
  FUN_00018944(*param_4);
  return;
}




/* ============================================
 * Function: FUN_00019f78
 * Address:  0x19f78
 * ============================================ */

void FUN_00019f78(void)

{
  PyErr_SetString(**(undefined4 **)(DAT_00019f98 + 0x19f88 + DAT_00019f9c),DAT_00019fa0 + 0x19f94);
  return;
}




/* ============================================
 * Function: FUN_00019fa4
 * Address:  0x19fa4
 * ============================================ */

void FUN_00019fa4(void)

{
  PyErr_SetString(**(undefined4 **)(DAT_00019fc4 + 0x19fb4 + DAT_00019fc8),DAT_00019fcc + 0x19fc0);
  return;
}




/* ============================================
 * Function: FUN_00019fd0
 * Address:  0x19fd0
 * ============================================ */

undefined4 FUN_00019fd0(int param_1,int param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int *piVar4;
  int iVar5;
  
  if (param_2 == param_1) {
    return 1;
  }
  if (param_1 != 0) {
    iVar2 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x4000000);
    if (iVar2 == 0) {
      uVar3 = FUN_00019adc();
      return uVar3;
    }
    iVar5 = *(int *)(param_2 + 8);
    piVar4 = (int *)(param_2 + 0xc);
    for (iVar2 = 0; iVar2 < iVar5; iVar2 = iVar2 + 1) {
      if (*piVar4 == param_1) {
        return 1;
      }
      piVar4 = piVar4 + 1;
    }
    iVar2 = 0;
    piVar4 = (int *)(param_2 + 0xc);
    while( true ) {
      if (iVar5 <= iVar2) {
        return 0;
      }
      iVar1 = FUN_00019adc(param_1,*piVar4);
      if (iVar1 != 0) break;
      iVar2 = iVar2 + 1;
      piVar4 = piVar4 + 1;
    }
    return 1;
  }
  return 0;
}




/* ============================================
 * Function: FUN_0001a024
 * Address:  0x1a024
 * ============================================ */

void FUN_0001a024(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  PyErr_SetNone(**(undefined4 **)(DAT_0001a044 + 0x1a034 + DAT_0001a048));
  return;
}




/* ============================================
 * Function: FUN_0001a04c
 * Address:  0x1a04c
 * ============================================ */

void FUN_0001a04c(int param_1)

{
  if (param_1 == 0) {
    return;
  }
  if (*(int *)(*(int *)(param_1 + 0xc) + 0xc) == 0) {
    return;
  }
  *(undefined4 *)(*(int *)(param_1 + 0xc) + 0xc) = 0;
  FUN_00017fec();
  return;
}




/* ============================================
 * Function: FUN_0001a070
 * Address:  0x1a070
 * ============================================ */

undefined4 FUN_0001a070(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  if (*(int *)(param_1 + 0x3c) == 0 &&
      (param_2 != 0 && param_2 != *(int *)(DAT_0001a158 + 0x1a084 + DAT_0001a15c))) {
    uVar2 = 0;
    FUN_00019fa4();
  }
  else if (*(int *)(param_1 + 0x3c) == -1) {
    FUN_0001a024(param_2);
    uVar2 = 0;
  }
  else {
    iVar1 = _PyThreadState_UncheckedGet();
    if ((*(int *)(param_1 + 0x10) != 0) && (*(int *)(param_1 + 0x18) != 0)) {
      iVar3 = *(int *)(*(int *)(param_1 + 0x18) + 0xc);
      FUN_00018944(*(undefined4 *)(iVar1 + 0xc));
      *(undefined4 *)(iVar3 + 0xc) = *(undefined4 *)(iVar1 + 0xc);
    }
    *(undefined4 *)(param_1 + 0x1c) = *(undefined4 *)(iVar1 + 0x50);
    *(int *)(iVar1 + 0x50) = param_1 + 0x10;
    *(undefined1 *)(param_1 + 0x40) = 1;
    uVar2 = (**(code **)(param_1 + 8))(param_1,iVar1,param_2);
    *(undefined1 *)(param_1 + 0x40) = 0;
    *(undefined4 *)(iVar1 + 0x50) = *(undefined4 *)(param_1 + 0x1c);
    *(undefined4 *)(param_1 + 0x1c) = 0;
    FUN_0001a04c(*(undefined4 *)(param_1 + 0x18));
  }
  return uVar2;
}




/* ============================================
 * Function: FUN_0001a160
 * Address:  0x1a160
 * ============================================ */

undefined4 FUN_0001a160(int param_1)

{
  undefined4 uVar1;
  undefined4 local_c;
  
  local_c = 0;
  if (*(int *)(param_1 + 0x28) != 0) {
    *(undefined4 *)(param_1 + 0x28) = 0;
    FUN_00017fec();
  }
  uVar1 = _PyThreadState_UncheckedGet();
  FUN_00019c84(uVar1,&local_c);
  uVar1 = FUN_0001a070(param_1,local_c);
  FUN_000182bc(local_c);
  return uVar1;
}




/* ============================================
 * Function: FUN_0001a1b4
 * Address:  0x1a1b4
 * ============================================ */

int FUN_0001a1b4(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(param_1 + 0x28);
  iVar1 = DAT_0001a290 + 0x1a1d0;
  if (*(char *)(param_1 + 0x40) == '\0') {
    if (iVar3 == 0) {
      iVar1 = FUN_0001a070(param_1,*(undefined4 *)(iVar1 + DAT_0001a29c));
      return iVar1;
    }
    *(undefined1 *)(param_1 + 0x40) = 1;
    iVar4 = *(int *)(iVar3 + 4);
    if (iVar4 == *(int *)(DAT_0001a294 + 0x1a480)) {
      iVar1 = FUN_0001a1b4(iVar3);
    }
    else {
      uVar2 = *(undefined4 *)(iVar1 + DAT_0001a298);
      iVar1 = FUN_00018840(iVar4,uVar2,DAT_0001a298,uVar2,param_1,uVar2,param_3);
      if (iVar1 == 0) {
        iVar1 = (**(code **)(iVar4 + 0x70))(iVar3);
      }
      else {
        iVar1 = _PyGen_Send(iVar3,0);
      }
    }
    *(undefined1 *)(param_1 + 0x40) = 0;
    if (iVar1 == 0) {
      iVar1 = FUN_0001a160(param_1);
      return iVar1;
    }
  }
  else {
    FUN_00019f78();
    iVar1 = 0;
  }
  return iVar1;
}




/* ============================================
 * Function: FUN_0001a2a0
 * Address:  0x1a2a0
 * ============================================ */

int FUN_0001a2a0(int param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar2 = DAT_0001a2f8 + 0x1a2b4;
  if ((param_1 == 0) && (iVar1 = _PyThreadState_UncheckedGet(), *(int *)(iVar1 + 0x34) == 0)) {
    uVar3 = **(undefined4 **)(iVar2 + DAT_0001a2fc);
    FUN_00018934(uVar3);
    FUN_000182c8(iVar1,uVar3,0,0);
  }
  return param_1;
}




/* ============================================
 * Function: FUN_0001a300
 * Address:  0x1a300
 * ============================================ */

void FUN_0001a300(undefined4 *param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  
  uVar3 = *param_1;
  uVar2 = param_1[1];
  uVar1 = param_1[2];
  *param_1 = param_2;
  param_1[1] = param_3;
  param_1[2] = param_4;
  FUN_000182bc(uVar3);
  FUN_000182bc(uVar2);
  FUN_000182bc(uVar1);
  return;
}




/* ============================================
 * Function: FUN_0001a330
 * Address:  0x1a330
 * ============================================ */

int FUN_0001a330(undefined1 *param_1,int param_2)

{
  int iVar1;
  int iVar2;
  
  iVar1 = DAT_0001a3fc;
  iVar2 = DAT_0001a400 + 0x1a358;
  if (*(int *)(param_2 + 4) == *(int *)(FUN_0001a5c0 + DAT_0001a3fc)) {
    iVar2 = FUN_0001a408(param_2);
    if (iVar2 == 0) {
      return -1;
    }
    iVar1 = 0;
  }
  else {
    *param_1 = 1;
    iVar1 = FUN_00017ee8(param_2,*(undefined4 *)(iVar1 + 0x1a5c4));
    if (iVar1 == 0) {
      iVar1 = PyErr_ExceptionMatches(**(undefined4 **)(iVar2 + DAT_0001a404));
      if (iVar1 == 0) {
        PyErr_WriteUnraisable(param_2);
      }
      iVar1 = 0;
      PyErr_Clear();
      iVar2 = 0;
    }
    else {
      iVar2 = _PyObject_CallFunction_SizeT(iVar1,0);
      FUN_00017fec(iVar1);
      iVar1 = -(uint)(iVar2 == 0);
    }
    *param_1 = 0;
  }
  FUN_000182bc(iVar2);
  return iVar1;
}




/* ============================================
 * Function: FUN_0001a408
 * Address:  0x1a408
 * ============================================ */

undefined4 FUN_0001a408(int param_1)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = *(int *)(param_1 + 0x28);
  iVar3 = DAT_0001a518 + 0x1a424;
  if (*(char *)(param_1 + 0x40) != '\0') {
    FUN_00019f78();
    return 0;
  }
  if (iVar4 != 0) {
    FUN_00018934(iVar4);
    iVar1 = FUN_0001a330(param_1 + 0x40,iVar4);
    if (*(int *)(param_1 + 0x28) != 0) {
      *(undefined4 *)(param_1 + 0x28) = 0;
      FUN_00017fec();
    }
    FUN_00017fec(iVar4);
    if (iVar1 != 0) goto LAB_0001a454;
  }
  PyErr_SetNone(**(undefined4 **)(iVar3 + DAT_0001a51c));
LAB_0001a454:
  iVar4 = FUN_0001a070(param_1,0);
  if (iVar4 != 0) {
    FUN_00017fec();
    PyErr_SetString(**(undefined4 **)(iVar3 + DAT_0001a520),DAT_0001a524 + 0x1a480);
    return 0;
  }
  iVar4 = PyErr_Occurred();
  if (iVar4 != 0) {
    iVar4 = FUN_00019e68(iVar4,**(undefined4 **)(iVar3 + DAT_0001a51c),
                         **(undefined4 **)(iVar3 + DAT_0001a528));
    if (iVar4 == 0) {
      return 0;
    }
    PyErr_Clear();
  }
  uVar2 = *(undefined4 *)(iVar3 + DAT_0001a52c);
  FUN_00018934(uVar2);
  return uVar2;
}




/* ============================================
 * Function: FUN_0001a5c0
 * Address:  0x1a5c0
 * ============================================ */

undefined4 FUN_0001a5c0(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  
  iVar3 = DAT_0001a630 + 0x1a5e0;
  iVar1 = FUN_00017a90(param_1,*(undefined4 *)(DAT_0001a62c + 0x1a858),param_2,
                       DAT_0001a62c + 0x1a5d4,param_1,param_2);
  if (iVar1 < 0) {
    FUN_00019490(DAT_0001a638 + 0x1a604,0x2372,0xe1,DAT_0001a634 + 0x1a600);
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(iVar3 + DAT_0001a63c);
    FUN_00018934(uVar2);
  }
  return uVar2;
}




/* ============================================
 * Function: FUN_0001a640
 * Address:  0x1a640
 * ============================================ */

undefined4 FUN_0001a640(undefined4 param_1,int *param_2,int param_3,int param_4,undefined4 param_5)

{
  int iVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  int local_34;
  undefined4 local_30;
  undefined4 local_2c [2];
  
  piVar5 = param_2 + param_4;
  iVar4 = DAT_0001a80c + 0x1a660;
  local_34 = 0;
  local_30 = 0;
  local_2c[0] = 0;
LAB_0001a684:
  do {
    iVar1 = PyDict_Next(param_1,local_2c,&local_34,&local_30);
    piVar3 = piVar5;
    if (iVar1 == 0) {
      return 0;
    }
    do {
      piVar2 = piVar3;
      if ((int *)*piVar2 == (int *)0x0) {
        iVar1 = FUN_0001954c(*(undefined4 *)(*(int *)(local_34 + 4) + 0x54),0x10000000);
        piVar3 = piVar5;
        if (iVar1 == 0) {
          PyErr_Format(**(undefined4 **)(iVar4 + DAT_0001a810),DAT_0001a818 + 0x1a804,param_5);
          return 0xffffffff;
        }
        goto LAB_0001a710;
      }
      piVar3 = piVar2 + 1;
    } while (*(int *)*piVar2 != local_34);
    *(undefined4 *)((int)piVar2 + (param_3 - (int)param_2)) = local_30;
  } while( true );
  while (iVar1 != 0) {
LAB_0001a710:
    do {
      piVar2 = piVar3;
      piVar3 = piVar2 + 1;
      if ((int *)*piVar2 == (int *)0x0) goto LAB_0001a73c;
      iVar1 = *(int *)*piVar2;
      if (iVar1 == local_34) goto LAB_0001a730;
    } while (*(int *)(iVar1 + 8) != *(int *)(local_34 + 8));
    iVar1 = PyUnicode_Compare();
    if (iVar1 < 0) {
      iVar1 = PyErr_Occurred();
      if (iVar1 != 0) {
        return 0xffffffff;
      }
      goto LAB_0001a710;
    }
  }
LAB_0001a730:
  *(undefined4 *)((int)piVar2 + (param_3 - (int)param_2)) = local_30;
LAB_0001a73c:
  if (*piVar2 == 0) goto LAB_0001a748;
  goto LAB_0001a684;
LAB_0001a748:
  if (piVar5 == param_2) {
    PyErr_Format(**(undefined4 **)(iVar4 + DAT_0001a810),DAT_0001a814 + 0x1a76c,param_5);
    return 0xffffffff;
  }
  piVar3 = (int *)*param_2;
  param_2 = param_2 + 1;
  iVar1 = *piVar3;
  if (iVar1 == local_34) {
LAB_0001a78c:
    FUN_00017aa8(param_5,local_34);
    return 0xffffffff;
  }
  if (*(int *)(iVar1 + 8) == *(int *)(local_34 + 8)) {
    iVar1 = PyUnicode_Compare(iVar1,local_34);
    if (iVar1 < 0) {
      iVar1 = PyErr_Occurred();
      if (iVar1 != 0) {
        return 0xffffffff;
      }
    }
    else if (iVar1 == 0) goto LAB_0001a78c;
  }
  goto LAB_0001a748;
}




/* ============================================
 * Function: FUN_0001a81c
 * Address:  0x1a81c
 * ============================================ */

undefined4 FUN_0001a81c(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_20;
  int local_1c;
  
  iVar3 = *(int *)(param_2 + 8);
  local_20 = 0;
  local_1c = 0;
  if (param_3 == 0) {
    if (iVar3 == 2) {
      local_20 = *(int *)(param_2 + 0xc);
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001a974;
    }
LAB_0001a984:
    FUN_00017adc(DAT_0001a9c8 + 0x1a9a0,1,2,2,*(undefined4 *)(param_2 + 8));
    uVar2 = 0x2356;
    goto LAB_0001a93c;
  }
  if (iVar3 == 1) {
LAB_0001a8c0:
    local_20 = *(int *)(param_2 + 0xc);
  }
  else {
    if (iVar3 == 2) {
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001a8c0;
    }
    if (iVar3 != 0) goto LAB_0001a984;
  }
  iVar1 = PyDict_Size(param_3);
  if (iVar3 == 0) {
    local_20 = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0001a9b4 + 0x1a920),
                          *(undefined4 *)(*(int *)(DAT_0001a9b4 + 0x1a920) + 0xc));
    if (local_20 == 0) goto LAB_0001a984;
    iVar1 = iVar1 + -1;
LAB_0001a8f4:
    local_1c = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0001a9b8 + 0x1a974),
                          *(undefined4 *)(*(int *)(DAT_0001a9b8 + 0x1a974) + 0xc));
    if (local_1c == 0) {
      FUN_00017adc(DAT_0001a9bc + 0x1a934,1,2,2,1);
      uVar2 = 0x2345;
      goto LAB_0001a93c;
    }
    iVar1 = iVar1 + -1;
  }
  else if (iVar3 == 1) goto LAB_0001a8f4;
  if ((iVar1 < 1) ||
     (iVar3 = FUN_0001a640(param_3,DAT_0001a9ac + 0x1aedc,&local_20,iVar3,DAT_0001a9b0 + 0x1a898),
     -1 < iVar3)) {
LAB_0001a974:
    uVar2 = FUN_0001a5c0(local_20,local_1c);
    return uVar2;
  }
  uVar2 = 0x2349;
LAB_0001a93c:
  FUN_00019490(DAT_0001a9c4 + 0x1a954,uVar2,0xe0,DAT_0001a9c0 + 0x1a950);
  return 0;
}




/* ============================================
 * Function: FUN_0001a9cc
 * Address:  0x1a9cc
 * ============================================ */

void FUN_0001a9cc(int param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  undefined4 *puVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  
  iVar7 = DAT_0001ac18 + 0x1a9e8;
  iVar6 = *(int *)(iVar7 + DAT_0001ac1c);
  if (param_3 == 0 || param_3 == iVar6) {
    param_3 = 0;
  }
  else {
    uVar3 = *(undefined4 *)(iVar7 + DAT_0001ac20);
    iVar1 = FUN_00018840(*(undefined4 *)(param_3 + 4),uVar3,param_3,uVar3,param_1,uVar3,param_3);
    if (iVar1 == 0) {
      PyErr_SetString(**(undefined4 **)(iVar7 + DAT_0001ac24),DAT_0001ac28 + 0x1aa3c);
      param_2 = 0;
      goto LAB_0001aa40;
    }
  }
  iVar1 = *(int *)(param_1 + 4);
  if (param_2 == iVar6) {
    param_2 = 0;
  }
  iVar6 = FUN_0001954c(*(undefined4 *)(iVar1 + 0x54),0x40000000);
  if (iVar6 == 0) {
    iVar6 = FUN_00019a38(iVar1);
    if ((iVar6 == 0) ||
       (iVar6 = FUN_0001954c(*(undefined4 *)(param_1 + 0x54),0x40000000), iVar6 == 0)) {
      puVar4 = *(undefined4 **)(iVar7 + DAT_0001ac24);
      iVar6 = DAT_0001ac34 + 0x1ab98;
      goto LAB_0001aa90;
    }
    if (param_2 != 0) {
      iVar1 = *(int *)(param_2 + 4);
      iVar6 = FUN_0001954c(*(undefined4 *)(iVar1 + 0x54),0x40000000);
      if (iVar6 == 0) {
LAB_0001abe4:
        iVar6 = FUN_0001954c(*(undefined4 *)(*(int *)(param_2 + 4) + 0x54),0x4000000);
        if (iVar6 == 0) {
          iVar6 = PyTuple_Pack(1,param_2);
          goto LAB_0001ac08;
        }
        FUN_00018934(param_2);
        iVar6 = param_2;
        goto LAB_0001ab18;
      }
      iVar6 = 0;
      if (param_1 != iVar1) {
        iVar2 = PyObject_IsSubclass(iVar1,param_1);
        if (iVar2 == 0) goto LAB_0001abe4;
        if (iVar2 != -1) goto LAB_0001ab98;
        goto LAB_0001ab04;
      }
LAB_0001ab98:
      PyErr_SetObject(iVar1,param_2);
      param_2 = iVar6;
      if (param_3 != 0) {
        iVar6 = _PyThreadState_UncheckedGet();
        iVar7 = *(int *)(iVar6 + 0x3c);
        if (param_3 != iVar7) {
          FUN_00018934(param_3);
          *(int *)(iVar6 + 0x3c) = param_3;
          FUN_000182bc(iVar7);
        }
      }
      goto LAB_0001aa40;
    }
    iVar6 = PyTuple_New(0);
LAB_0001ac08:
    if (iVar6 != 0) {
LAB_0001ab18:
      param_2 = PyObject_Call(param_1,iVar6,0);
      FUN_00017fec(iVar6);
      if (param_2 != 0) {
        iVar5 = *(int *)(param_2 + 4);
        iVar2 = FUN_0001954c(*(undefined4 *)(iVar5 + 0x54),0x40000000);
        iVar6 = param_2;
        iVar1 = param_1;
        if (iVar2 == 0) {
          PyErr_Format(**(undefined4 **)(iVar7 + DAT_0001ac24),DAT_0001ac30 + 0x1ab78,param_1,iVar5)
          ;
          goto LAB_0001aa40;
        }
        goto LAB_0001ab98;
      }
    }
  }
  else {
    if (param_2 == 0) {
      param_2 = param_1;
      iVar6 = 0;
      goto LAB_0001ab98;
    }
    puVar4 = *(undefined4 **)(iVar7 + DAT_0001ac24);
    iVar6 = DAT_0001ac2c + 0x1aa94;
LAB_0001aa90:
    PyErr_SetString(*puVar4,iVar6);
  }
LAB_0001ab04:
  param_2 = 0;
LAB_0001aa40:
  FUN_000182bc(param_2);
  return;
}




/* ============================================
 * Function: FUN_0001ac38
 * Address:  0x1ac38
 * ============================================ */

undefined4
FUN_0001ac38(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,int param_5)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar4 = DAT_0001adfc + 0x1ac54;
  iVar3 = *(int *)(param_1 + 0x28);
  if (*(char *)(param_1 + 0x40) != '\0') {
    FUN_00019f78();
    return 0;
  }
  if (iVar3 == 0) {
LAB_0001adb0:
    FUN_0001a9cc(param_2,param_3,param_4);
  }
  else {
    FUN_00018934(iVar3);
    iVar1 = FUN_00019adc(param_2,**(undefined4 **)(iVar4 + DAT_0001ae00));
    if (iVar1 == 0) {
      *(undefined1 *)(param_1 + 0x40) = 1;
      if (*(int *)(iVar3 + 4) == *(int *)(DAT_0001ae04 + 0x1af7c)) {
        iVar4 = FUN_0001ac38(iVar3,param_2,param_3,param_4,param_5);
      }
      else {
        iVar1 = FUN_00017ee8(iVar3,*(undefined4 *)(DAT_0001ae04 + 0x1b090));
        if (iVar1 == 0) {
          FUN_00017fec(iVar3);
          iVar3 = PyErr_ExceptionMatches(**(undefined4 **)(iVar4 + DAT_0001ae08));
          if (iVar3 == 0) {
            *(undefined1 *)(param_1 + 0x40) = 0;
            return 0;
          }
          PyErr_Clear();
          if (*(int *)(param_1 + 0x28) != 0) {
            *(undefined4 *)(param_1 + 0x28) = 0;
            FUN_00017fec();
          }
          *(undefined1 *)(param_1 + 0x40) = 0;
          goto LAB_0001adb0;
        }
        if (param_5 == 0) {
          iVar4 = PyObject_CallFunctionObjArgs(iVar1,param_2,param_3,param_4,0);
        }
        else {
          iVar4 = PyObject_CallObject(iVar1,param_5);
        }
        FUN_00017fec(iVar1);
      }
      *(undefined1 *)(param_1 + 0x40) = 0;
      FUN_00017fec(iVar3);
      if (iVar4 == 0) {
        iVar4 = FUN_0001a160(param_1);
      }
      goto LAB_0001ad4c;
    }
    iVar4 = FUN_0001a330(param_1 + 0x40,iVar3);
    FUN_00017fec(iVar3);
    if (*(int *)(param_1 + 0x28) != 0) {
      *(undefined4 *)(param_1 + 0x28) = 0;
      FUN_00017fec();
    }
    if (-1 < iVar4) goto LAB_0001adb0;
  }
  iVar4 = FUN_0001a070(param_1,0);
LAB_0001ad4c:
  uVar2 = FUN_0001a2a0(iVar4);
  return uVar2;
}




/* ============================================
 * Function: FUN_0001ae0c
 * Address:  0x1ae0c
 * ============================================ */

void FUN_0001ae0c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 local_1c;
  undefined4 local_18;
  undefined4 local_14 [2];
  
  local_18 = 0;
  local_14[0] = 0;
  iVar1 = PyArg_UnpackTuple(param_2,DAT_0001ae7c + 0x1ae54,1,3,&local_1c,&local_18,local_14);
  if (iVar1 != 0) {
    FUN_0001ac38(param_1,local_1c,local_18,local_14[0],param_2);
  }
  return;
}




/* ============================================
 * Function: FUN_0001ae80
 * Address:  0x1ae80
 * ============================================ */

void FUN_0001ae80(void)

{
  PyErr_Format(**(undefined4 **)(DAT_0001aea4 + 0x1ae90 + DAT_0001aea8),DAT_0001aeac + 0x1aea0,2);
  return;
}




/* ============================================
 * Function: FUN_0001aeb0
 * Address:  0x1aeb0
 * ============================================ */

undefined4 FUN_0001aeb0(int param_1)

{
  undefined4 uVar1;
  
  if (param_1 == 0) {
    uVar1 = FUN_00019bf8();
    return uVar1;
  }
  FUN_00017fec();
  FUN_0001ae80();
  return 0xffffffff;
}




/* ============================================
 * Function: FUN_0001aed0
 * Address:  0x1aed0
 * ============================================ */

void FUN_0001aed0(void)

{
  PyErr_Format(**(undefined4 **)(DAT_0001aef8 + 0x1aee0 + DAT_0001aefc),DAT_0001af00 + 0x1aef0,
               DAT_0001af04 + 0x1aef4);
  return;
}




/* ============================================
 * Function: FUN_0001af94
 * Address:  0x1af94
 * ============================================ */

int FUN_0001af94(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  
  iVar1 = _PyObject_GC_New();
  if (iVar1 == 0) {
    return 0;
  }
  *(undefined4 *)(iVar1 + 8) = param_2;
  *(undefined4 *)(iVar1 + 0xc) = param_3;
  FUN_00018944(param_3);
  *(undefined1 *)(iVar1 + 0x40) = 0;
  *(undefined4 *)(iVar1 + 0x3c) = 0;
  *(undefined4 *)(iVar1 + 0x24) = 0;
  *(undefined4 *)(iVar1 + 0x28) = 0;
  *(undefined4 *)(iVar1 + 0x10) = 0;
  *(undefined4 *)(iVar1 + 0x14) = 0;
  *(undefined4 *)(iVar1 + 0x18) = 0;
  *(undefined4 *)(iVar1 + 0x1c) = 0;
  *(undefined4 *)(iVar1 + 0x20) = 0;
  FUN_00018944(param_5);
  *(undefined4 *)(iVar1 + 0x30) = param_5;
  FUN_00018944(param_4);
  *(undefined4 *)(iVar1 + 0x2c) = param_4;
  FUN_00018944(param_6);
  *(undefined4 *)(iVar1 + 0x34) = param_6;
  FUN_00018944(0);
  *(undefined4 *)(iVar1 + 0x38) = 0;
  PyObject_GC_Track(iVar1);
  return iVar1;
}




/* ============================================
 * Function: FUN_0001afd4
 * Address:  0x1afd4
 * ============================================ */

int FUN_0001afd4(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = DAT_0001b0a4;
  iVar4 = DAT_0001b0a8 + 0x1aff8;
  iVar1 = FUN_00018ee0(*(undefined4 *)(DAT_0001b0a4 + 0x1b014),
                       *(undefined4 *)(DAT_0001b0a4 + 0x1b040),0);
  if (iVar1 == 0) {
    iVar1 = *(int *)(iVar4 + DAT_0001b0ac);
    FUN_00018934(iVar1);
    uVar3 = 0x1a6a;
  }
  else {
    *(undefined4 *)(iVar1 + 8) = param_1;
    FUN_00018934(param_1);
    iVar2 = FUN_0001af94(*(undefined4 *)(iVar2 + 0x1b270),DAT_0001b0b8 + 0x1b074,iVar1,
                         *(undefined4 *)(iVar2 + 0x1b0f8),*(undefined4 *)(iVar2 + 0x1b388),
                         *(undefined4 *)(iVar2 + 0x1b2f0));
    if (iVar2 != 0) {
      FUN_00017fec(iVar1);
      return iVar2;
    }
    uVar3 = 0x1a72;
  }
  FUN_00019490(DAT_0001b0b4 + 0x1b040,uVar3,0x9e,DAT_0001b0b0 + 0x1b03c);
  FUN_00017fec(iVar1);
  return 0;
}




/* ============================================
 * Function: FUN_0001b0bc
 * Address:  0x1b0bc
 * ============================================ */

int FUN_0001b0bc(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar2 = DAT_0001b18c;
  iVar4 = DAT_0001b190 + 0x1b0e0;
  iVar1 = FUN_00018de0(*(undefined4 *)(DAT_0001b18c + 0x1b104),
                       *(undefined4 *)(DAT_0001b18c + 0x1b128),0);
  if (iVar1 == 0) {
    iVar1 = *(int *)(iVar4 + DAT_0001b194);
    FUN_00018934(iVar1);
    uVar3 = 0x278e;
  }
  else {
    *(undefined4 *)(iVar1 + 8) = param_1;
    FUN_00018934(param_1);
    iVar2 = FUN_0001af94(*(undefined4 *)(iVar2 + 0x1b358),DAT_0001b1a0 + 0x1b15c,iVar1,
                         *(undefined4 *)(iVar2 + 0x1b1e0),*(undefined4 *)(iVar2 + 0x1b474),
                         *(undefined4 *)((int)&DAT_0001b3d8 + iVar2));
    if (iVar2 != 0) {
      FUN_00017fec(iVar1);
      return iVar2;
    }
    uVar3 = 0x2796;
  }
  FUN_00019490(DAT_0001b19c + 0x1b128,uVar3,0x110,DAT_0001b198 + 0x1b124);
  FUN_00017fec(iVar1);
  return 0;
}




/* ============================================
 * Function: FUN_0001b1a4
 * Address:  0x1b1a4
 * ============================================ */

int FUN_0001b1a4(int param_1,int param_2,int *param_3)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined4 uVar4;
  int iVar5;
  code *pcVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  
  iVar8 = *(int *)(param_1 + 4);
  iVar7 = DAT_0001b3c4 + 0x1b1c0;
  if (*(int *)(iVar8 + 0x48) == *(int *)(iVar7 + DAT_0001b3c8)) {
    if ((*(int *)(iVar8 + 0x84) == 0) && (iVar2 = PyType_Ready(iVar8), iVar2 < 0)) {
      return 0;
    }
    iVar2 = _PyType_Lookup(iVar8,param_2);
    if (iVar2 != 0) {
      FUN_00018934();
      iVar9 = *(int *)(iVar2 + 4);
      iVar5 = FUN_00018840(iVar9,*(undefined4 *)(iVar7 + DAT_0001b3d0));
      if (iVar9 == *(int *)(iVar7 + DAT_0001b3d4) || iVar5 != 0) {
        iVar5 = 1;
        goto LAB_0001b218;
      }
      iVar5 = FUN_000176d8(iVar9,*(undefined4 *)(DAT_0001b3d8 + 0x1b5a4));
      if (iVar5 != 0) {
        iVar5 = 1;
        pcVar6 = (code *)0x0;
        goto LAB_0001b21c;
      }
      pcVar6 = *(code **)(iVar9 + 0x88);
      if (pcVar6 == (code *)0x0) goto LAB_0001b214;
      iVar5 = 0;
      if (*(int *)(iVar9 + 0x8c) == 0) goto LAB_0001b21c;
LAB_0001b354:
      iVar1 = (*pcVar6)(iVar2,param_1,*(undefined4 *)(param_1 + 4));
      FUN_00017fec(iVar2);
      goto LAB_0001b1dc;
    }
LAB_0001b214:
    iVar5 = 0;
LAB_0001b218:
    pcVar6 = (code *)0x0;
LAB_0001b21c:
    piVar3 = (int *)_PyObject_GetDictPtr(param_1);
    if ((piVar3 == (int *)0x0) || (iVar9 = *piVar3, iVar9 == 0)) {
LAB_0001b37c:
      if (iVar5 != 0) {
LAB_0001b384:
        *param_3 = iVar2;
        return iVar5;
      }
      if (pcVar6 == (code *)0x0) {
        if (iVar2 == 0) {
          PyErr_Format(**(undefined4 **)(iVar7 + DAT_0001b3dc),DAT_0001b3e0 + 0x1b3bc,
                       *(undefined4 *)(iVar8 + 0xc),param_2);
          return 0;
        }
        goto LAB_0001b384;
      }
      goto LAB_0001b354;
    }
    uVar4 = FUN_00018934(iVar9);
    iVar1 = _PyDict_GetItem_KnownHash(uVar4,param_2,*(undefined4 *)(param_2 + 0xc));
    if (iVar1 == 0) {
      FUN_00017fec(iVar9);
      goto LAB_0001b37c;
    }
    FUN_00018934();
    FUN_00017fec(iVar9);
    FUN_000182bc(iVar2);
  }
  else {
    iVar1 = FUN_00017ee8();
LAB_0001b1dc:
    if (iVar1 == 0) goto LAB_0001b1e4;
  }
  iVar7 = FUN_00018840(*(undefined4 *)(iVar1 + 4),*(undefined4 *)(iVar7 + DAT_0001b3cc));
  if ((iVar7 != 0) && (param_1 == *(int *)(iVar1 + 0xc))) {
    iVar7 = *(int *)(iVar1 + 8);
    FUN_00018934(iVar7);
    FUN_00017fec(iVar1);
    *param_3 = iVar7;
    return 1;
  }
LAB_0001b1e4:
  *param_3 = iVar1;
  return 0;
}




/* ============================================
 * Function: FUN_0001b3e4
 * Address:  0x1b3e4
 * ============================================ */

undefined4 FUN_0001b3e4(int param_1,undefined4 *param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  
  iVar2 = *(int *)(param_1 + 4);
  iVar5 = *(int *)(iVar2 + 0x38);
  iVar4 = DAT_0001b4a8 + 0x1b400;
  if ((iVar5 == 0) || (*(int *)(iVar5 + 4) == 0)) {
    PyErr_Format(**(undefined4 **)(iVar4 + DAT_0001b4b0),DAT_0001b4b4 + 0x1b49c,
                 *(undefined4 *)(iVar2 + 0xc),iVar2,param_1,param_2);
  }
  else {
    iVar2 = param_1;
    iVar1 = PyLong_FromSsize_t(0);
    if (iVar1 != 0) {
      uVar3 = *(undefined4 *)(iVar4 + DAT_0001b4ac);
      iVar2 = PySlice_New(iVar1,*param_2,uVar3,uVar3,iVar2,uVar3);
      FUN_000182bc(iVar1);
      FUN_000182bc(0);
      if (iVar2 != 0) {
        uVar3 = (**(code **)(iVar5 + 4))(param_1,iVar2);
        FUN_00017fec(iVar2);
        return uVar3;
      }
    }
  }
  return 0;
}




/* ============================================
 * Function: FUN_0001b6f4
 * Address:  0x1b6f4
 * ============================================ */

undefined4 FUN_0001b6f4(int param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int iVar3;
  code *UNRECOVERED_JUMPTABLE;
  int iVar4;
  int iVar5;
  undefined4 *puVar6;
  int iVar7;
  
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x38);
  if ((iVar3 != 0) &&
     (UNRECOVERED_JUMPTABLE = *(code **)(iVar3 + 4), UNRECOVERED_JUMPTABLE != (code *)0x0)) {
                    /* WARNING: Could not recover jumptable at 0x0001b718. Too many branches */
                    /* WARNING: Treating indirect jump as call */
    uVar1 = (*UNRECOVERED_JUMPTABLE)();
    return uVar1;
  }
  iVar3 = *(int *)(*(int *)(param_1 + 4) + 0x34);
  iVar4 = DAT_0001b6dc + 0x1b638;
  if ((iVar3 == 0) || (*(int *)(iVar3 + 0xc) == 0)) {
    iVar3 = DAT_0001b6e4 + 0x1b658;
    uVar2 = *(undefined4 *)(*(int *)(param_1 + 4) + 0xc);
    uVar1 = **(undefined4 **)(iVar4 + DAT_0001b6e0);
  }
  else {
    iVar3 = FUN_00018850(param_2);
    if ((iVar3 != -1) || (iVar5 = PyErr_Occurred(), iVar5 == 0)) {
      iVar7 = DAT_0001b60c + 0x1b4d4;
      iVar5 = *(int *)(param_1 + 4);
      iVar4 = FUN_00018840(iVar5,*(undefined4 *)(iVar7 + DAT_0001b610));
      if (iVar4 == 0) {
        iVar4 = FUN_00018840(iVar5,*(undefined4 *)(iVar7 + DAT_0001b614));
        if (iVar4 == 0) {
          puVar6 = *(undefined4 **)(iVar5 + 0x34);
          if ((puVar6 != (undefined4 *)0x0) && (puVar6[3] != 0)) {
            if ((iVar3 < 0) && ((code *)*puVar6 != (code *)0x0)) {
              iVar4 = (*(code *)*puVar6)(param_1);
              if (iVar4 < 0) {
                iVar4 = PyErr_ExceptionMatches(**(undefined4 **)(iVar7 + DAT_0001b618));
                if (iVar4 == 0) {
                  return 0;
                }
                PyErr_Clear();
              }
              else {
                iVar3 = iVar3 + iVar4;
              }
            }
                    /* WARNING: Could not recover jumptable at 0x0001b600. Too many branches */
                    /* WARNING: Treating indirect jump as call */
            uVar1 = (*(code *)puVar6[3])(param_1,iVar3);
            return uVar1;
          }
        }
        else {
          iVar4 = iVar3;
          if (iVar3 < 0) {
            iVar4 = iVar3 + *(int *)(param_1 + 8);
          }
          iVar5 = FUN_00017510(iVar4);
          if (iVar5 != 0) {
            uVar1 = *(undefined4 *)(param_1 + iVar4 * 4 + 0xc);
            goto LAB_0001b57c;
          }
        }
      }
      else {
        iVar4 = iVar3;
        if (iVar3 < 0) {
          iVar4 = iVar3 + *(int *)(param_1 + 8);
        }
        iVar5 = FUN_00017510(iVar4);
        if (iVar5 != 0) {
          uVar1 = *(undefined4 *)(*(int *)(param_1 + 0xc) + iVar4 * 4);
LAB_0001b57c:
          FUN_00018934(uVar1);
          return uVar1;
        }
      }
      iVar3 = PyLong_FromSsize_t(iVar3);
      uVar1 = 0;
      if (iVar3 != 0) {
        uVar1 = PyObject_GetItem(param_1);
        FUN_00017fec(iVar3);
      }
      return uVar1;
    }
    iVar3 = PyErr_GivenExceptionMatches(iVar5,**(undefined4 **)(iVar4 + DAT_0001b6e8));
    if (iVar3 == 0) {
      return 0;
    }
    PyErr_Clear();
    uVar2 = *(undefined4 *)(*(int *)(param_2 + 4) + 0xc);
    iVar3 = DAT_0001b6f0 + 0x1b6d8;
    uVar1 = **(undefined4 **)(iVar4 + DAT_0001b6ec);
  }
  PyErr_Format(uVar1,iVar3,uVar2);
  return 0;
}




/* ============================================
 * Function: FUN_0001b728
 * Address:  0x1b728
 * ============================================ */

undefined4 FUN_0001b728(int param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  
  iVar3 = *(int *)(param_1 + 0x10);
  iVar4 = *(int *)(param_1 + 8);
  uVar5 = *(undefined4 *)(param_1 + 0xc);
  iVar1 = Py_EnterRecursiveCall(DAT_0001b828 + 0x1b754);
  if (iVar1 != 0) {
    return 0;
  }
  if ((*(int *)(iVar4 + 0x10) == 0) && (*(int *)(iVar4 + 0x1c) == 0x43)) {
    if (iVar3 == 0) {
      iVar1 = *(int *)(iVar4 + 8);
      if (iVar1 != param_3) goto LAB_0001b794;
    }
    else {
      if ((param_3 != 0) || (iVar1 = *(int *)(iVar4 + 8), iVar1 != *(int *)(iVar3 + 8)))
      goto LAB_0001b794;
      param_2 = iVar3 + 0xc;
    }
    uVar5 = FUN_000190a8(iVar4,param_2,iVar1,uVar5);
  }
  else {
LAB_0001b794:
    uVar2 = 0;
    if (iVar3 != 0) {
      uVar2 = *(undefined4 *)(iVar3 + 8);
      iVar3 = iVar3 + 0xc;
    }
    uVar5 = PyEval_EvalCodeEx(iVar4,uVar5,0,param_2,param_3,0,0,iVar3,uVar2,
                              *(undefined4 *)(param_1 + 0x14),*(undefined4 *)(param_1 + 0x18));
    FUN_000182bc(0);
  }
  Py_LeaveRecursiveCall();
  return uVar5;
}




/* ============================================
 * Function: FUN_0001b82c
 * Address:  0x1b82c
 * ============================================ */

undefined4 FUN_0001b82c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  int local_34 [4];
  
  iVar3 = DAT_0001bb50;
  iVar9 = DAT_0001bb54 + 0x1b850;
  iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_0001bb50 + 0x1bbe8));
  if (iVar1 == 0) {
    uVar10 = 0x17a2;
    iVar3 = 0;
    iVar2 = 0;
    iVar4 = 0;
    iVar5 = 0;
LAB_0001ba18:
    FUN_000182bc(0);
    FUN_000182bc(iVar1);
    FUN_000182bc(iVar2);
    FUN_000182bc(iVar4);
    FUN_000182bc(iVar3);
    FUN_000182bc(iVar5);
    FUN_00019490(DAT_0001bb6c + 0x1ba64,uVar10,0x8f,DAT_0001bb68 + 0x1ba60);
    return 0;
  }
  iVar2 = FUN_00017ee8(iVar1,*(undefined4 *)(iVar3 + 0x1bbec));
  if (iVar2 == 0) {
    uVar10 = 0x17a4;
    iVar3 = 0;
    iVar4 = 0;
    iVar5 = 0;
    goto LAB_0001ba18;
  }
  FUN_00017fec(iVar1);
  iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(iVar3 + 0x1bbf0));
  if (iVar1 == 0) {
    uVar10 = 0x17a7;
    iVar3 = 0;
    iVar4 = 0;
    iVar5 = 0;
    goto LAB_0001ba18;
  }
  iVar3 = PyObject_Size(param_2);
  if (iVar3 == -1) {
    iVar5 = 0;
    uVar10 = 0x17a9;
    iVar3 = 0;
    iVar4 = 0;
    goto LAB_0001ba18;
  }
  iVar4 = PyLong_FromSsize_t();
  if (iVar4 == 0) {
    uVar10 = 0x17aa;
    iVar3 = 0;
    iVar5 = 0;
    goto LAB_0001ba18;
  }
  iVar3 = FUN_00018840(*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar9 + DAT_0001bb58));
  iVar7 = iVar2;
  if (iVar3 == 0) {
    iVar3 = 0;
    iVar8 = 0;
  }
  else {
    iVar3 = *(int *)(iVar2 + 0xc);
    if (iVar3 == 0) {
      iVar8 = 0;
    }
    else {
      iVar7 = *(int *)(iVar2 + 8);
      FUN_00018934(iVar3);
      FUN_00018934(iVar7);
      iVar8 = 1;
      FUN_00017fec(iVar2);
    }
  }
  uVar10 = *(undefined4 *)(iVar7 + 4);
  iVar5 = FUN_00018840(uVar10,*(undefined4 *)(iVar9 + DAT_0001bb5c));
  iVar2 = iVar7;
  if (iVar5 == 0) {
    uVar6 = *(undefined4 *)(iVar9 + DAT_0001bb64);
    iVar5 = FUN_00018840(uVar10,uVar6);
    if (((iVar5 == 0) && (iVar5 = PyType_IsSubtype(uVar10,uVar6), iVar5 == 0)) ||
       ((*(uint *)(*(int *)(iVar7 + 8) + 8) & 0xffffff8d) != 0x80)) {
      iVar5 = PyTuple_New(iVar8 + 3);
      if (iVar5 == 0) {
        uVar10 = 0x17cd;
        goto LAB_0001ba18;
      }
      iVar8 = iVar5 + iVar8 * 4;
      if (iVar3 != 0) {
        *(int *)(iVar5 + 0xc) = iVar3;
      }
      *(int *)(iVar8 + 0xc) = iVar1;
      FUN_00018934(param_2);
      *(undefined4 *)(iVar8 + 0x10) = param_2;
      *(int *)(iVar8 + 0x14) = iVar4;
      iVar8 = FUN_00017e40(iVar7,iVar5,0);
      if (iVar8 == 0) {
        uVar10 = 0x17db;
        iVar1 = 0;
        iVar3 = 0;
        iVar4 = 0;
        goto LAB_0001ba18;
      }
      FUN_00017fec(iVar5);
      goto LAB_0001b97c;
    }
    local_34[0] = iVar1;
    local_34[1] = param_2;
    local_34[2] = iVar4;
    iVar8 = FUN_00017628(iVar7,local_34 + -iVar8,iVar8 + 3);
    if (iVar8 == 0) {
      uVar10 = 0x17c5;
      iVar5 = 0;
      goto LAB_0001ba18;
    }
  }
  else {
    local_34[0] = iVar1;
    local_34[1] = param_2;
    local_34[2] = iVar4;
    iVar8 = FUN_0001b728(iVar7,local_34 + -iVar8,iVar8 + 3);
    if (iVar8 == 0) {
      uVar10 = 0x17bb;
      iVar5 = 0;
      goto LAB_0001ba18;
    }
  }
  FUN_000182bc(iVar3);
  FUN_00017fec(iVar1);
  FUN_00017fec(iVar4);
LAB_0001b97c:
  FUN_00017fec(iVar7);
  FUN_00017fec(iVar8);
  uVar10 = *(undefined4 *)(iVar9 + DAT_0001bb60);
  FUN_00018934(uVar10);
  return uVar10;
}




/* ============================================
 * Function: FUN_0001bb70
 * Address:  0x1bb70
 * ============================================ */

undefined4 FUN_0001bb70(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_20;
  int local_1c;
  
  iVar3 = *(int *)(param_2 + 8);
  local_20 = 0;
  local_1c = 0;
  if (param_3 == 0) {
    if (iVar3 == 2) {
      local_20 = *(int *)(param_2 + 0xc);
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001bcc8;
    }
LAB_0001bcd8:
    FUN_00017adc(DAT_0001bd1c + 0x1bcf4,1,2,2,*(undefined4 *)(param_2 + 8));
    uVar2 = 0x177e;
    goto LAB_0001bc90;
  }
  if (iVar3 == 1) {
LAB_0001bc14:
    local_20 = *(int *)(param_2 + 0xc);
  }
  else {
    if (iVar3 == 2) {
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001bc14;
    }
    if (iVar3 != 0) goto LAB_0001bcd8;
  }
  iVar1 = PyDict_Size(param_3);
  if (iVar3 == 0) {
    local_20 = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0001bd08 + 0x1bc74),
                          *(undefined4 *)(*(int *)(DAT_0001bd08 + 0x1bc74) + 0xc));
    if (local_20 == 0) goto LAB_0001bcd8;
    iVar1 = iVar1 + -1;
LAB_0001bc48:
    local_1c = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0001bd0c + 0x1bd44),
                          *(undefined4 *)(*(int *)(DAT_0001bd0c + 0x1bd44) + 0xc));
    if (local_1c == 0) {
      FUN_00017adc(DAT_0001bd10 + 0x1bc88,1,2,2,1);
      uVar2 = 0x176d;
      goto LAB_0001bc90;
    }
    iVar1 = iVar1 + -1;
  }
  else if (iVar3 == 1) goto LAB_0001bc48;
  if ((iVar1 < 1) ||
     (iVar3 = FUN_0001a640(param_3,(int)&DAT_0001c23c + DAT_0001bd00,&local_20,iVar3,
                           DAT_0001bd04 + 0x1bbec), -1 < iVar3)) {
LAB_0001bcc8:
    uVar2 = FUN_0001b82c(local_20,local_1c);
    return uVar2;
  }
  uVar2 = 0x1771;
LAB_0001bc90:
  FUN_00019490(DAT_0001bd18 + 0x1bca8,uVar2,0x8e,DAT_0001bd14 + 0x1bca4);
  return 0;
}




/* ============================================
 * Function: FUN_0001bd20
 * Address:  0x1bd20
 * ============================================ */

undefined4 FUN_0001bd20(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  undefined4 uVar10;
  int local_34 [4];
  
  iVar5 = DAT_0001c064;
  iVar9 = DAT_0001c068 + 0x1bd44;
  if (*(int *)(*(int *)(DAT_0001c064 + 0x1bfac) + 0x14) == *(int *)(DAT_0001c064 + 0x1c0ec) &&
      *(int *)(*(int *)(DAT_0001c064 + 0x1bfac) + 0x10) == *(int *)(DAT_0001c064 + 0x1c0e8)) {
    if (*(int *)(DAT_0001c064 + 0x1c0f0) == 0) {
      iVar5 = FUN_00017f00(*(undefined4 *)(DAT_0001c064 + 0x1c020));
    }
    else {
      FUN_00018934();
      iVar5 = *(int *)(iVar5 + 0x1c0f0);
    }
  }
  else {
    iVar5 = FUN_00018c58(*(undefined4 *)(DAT_0001c064 + 0x1c020),DAT_0001c064 + 0x1c0e8,
                         DAT_0001c064 + 0x1c0f0);
  }
  iVar2 = DAT_0001c06c;
  if (iVar5 == 0) {
    uVar10 = 0x1f65;
    iVar2 = 0;
    iVar1 = 0;
    iVar3 = 0;
LAB_0001bf54:
    FUN_000182bc(0);
    FUN_000182bc(iVar5);
    FUN_000182bc(iVar1);
    FUN_000182bc(iVar2);
    FUN_000182bc(iVar3);
    FUN_00019490(DAT_0001c08c + 0x1bf98,uVar10,0xbf,DAT_0001c088 + 0x1bf94);
    return 0;
  }
  iVar1 = FUN_00017ee8(iVar5,*(undefined4 *)(DAT_0001c06c + 0x1c13c));
  if (iVar1 == 0) {
    uVar10 = 0x1f67;
    iVar2 = 0;
    iVar3 = 0;
    goto LAB_0001bf54;
  }
  FUN_00017fec(iVar5);
  iVar5 = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x1bdc4));
  if (iVar5 == 0) {
    uVar10 = 0x1f6a;
    iVar2 = 0;
    iVar3 = 0;
    goto LAB_0001bf54;
  }
  iVar2 = FUN_00018840(*(undefined4 *)(iVar1 + 4),*(undefined4 *)(iVar9 + DAT_0001c070));
  iVar6 = iVar1;
  if (iVar2 == 0) {
    iVar2 = 0;
    iVar8 = 0;
  }
  else {
    iVar2 = *(int *)(iVar1 + 0xc);
    if (iVar2 == 0) {
      iVar8 = 0;
    }
    else {
      iVar6 = *(int *)(iVar1 + 8);
      iVar8 = 1;
      FUN_00018934(iVar2);
      FUN_00018934(iVar6);
      FUN_00017fec(iVar1);
    }
  }
  iVar7 = iVar8 + 3;
  uVar10 = *(undefined4 *)(iVar6 + 4);
  iVar3 = FUN_00018840(uVar10,*(undefined4 *)(iVar9 + DAT_0001c074));
  iVar1 = iVar6;
  if (iVar3 == 0) {
    uVar4 = *(undefined4 *)(iVar9 + DAT_0001c080);
    iVar3 = FUN_00018840(uVar10,uVar4);
    if (((iVar3 == 0) && (iVar3 = PyType_IsSubtype(uVar10,uVar4), iVar3 == 0)) ||
       ((*(uint *)(*(int *)(iVar6 + 8) + 8) & 0xffffff8d) != 0x80)) {
      iVar3 = PyTuple_New(iVar7);
      if (iVar3 == 0) {
        uVar10 = 0x1f8b;
        goto LAB_0001bf54;
      }
      iVar8 = iVar3 + iVar8 * 4;
      if (iVar2 != 0) {
        *(int *)(iVar3 + 0xc) = iVar2;
      }
      iVar2 = DAT_0001c090;
      FUN_00018934(*(undefined4 *)(DAT_0001c090 + 0x1c394));
      uVar10 = *(undefined4 *)(iVar2 + 0x1c394);
      *(int *)(iVar8 + 0x10) = iVar5;
      *(undefined4 *)(iVar8 + 0xc) = uVar10;
      FUN_00018934(param_2);
      *(undefined4 *)(iVar8 + 0x14) = param_2;
      iVar8 = FUN_00017e40(iVar6,iVar3,0);
      if (iVar8 == 0) {
        uVar10 = 0x1f99;
        iVar5 = 0;
        iVar2 = 0;
        goto LAB_0001bf54;
      }
      FUN_00017fec(iVar3);
      goto LAB_0001be88;
    }
    local_34[0] = *(int *)(DAT_0001c084 + 0x1c2e0);
    local_34[1] = iVar5;
    local_34[2] = param_2;
    iVar8 = FUN_00017628(iVar6,local_34 + -iVar8,iVar7);
    if (iVar8 == 0) {
      uVar10 = 0x1f84;
      iVar3 = 0;
      goto LAB_0001bf54;
    }
  }
  else {
    local_34[0] = *(int *)(DAT_0001c078 + 0x1c200);
    local_34[1] = iVar5;
    local_34[2] = param_2;
    iVar8 = FUN_0001b728(iVar6,local_34 + -iVar8,iVar7);
    if (iVar8 == 0) {
      uVar10 = 0x1f7b;
      iVar3 = 0;
      goto LAB_0001bf54;
    }
  }
  FUN_000182bc(iVar2);
  FUN_00017fec(iVar5);
LAB_0001be88:
  FUN_00017fec(iVar6);
  FUN_00017fec(iVar8);
  uVar10 = *(undefined4 *)(iVar9 + DAT_0001c07c);
  FUN_00018934(uVar10);
  return uVar10;
}




/* ============================================
 * Function: FUN_0001c094
 * Address:  0x1c094
 * ============================================ */

undefined4 FUN_0001c094(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_20;
  int local_1c;
  
  iVar3 = *(int *)(param_2 + 8);
  local_20 = 0;
  local_1c = 0;
  if (param_3 == 0) {
    if (iVar3 == 2) {
      local_20 = *(int *)(param_2 + 0xc);
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001c1e8;
    }
LAB_0001c1f8:
    FUN_00017adc(DAT_0001c23c + 0x1c214,1,2,2,*(undefined4 *)(param_2 + 8));
    uVar2 = 0x1f43;
    goto LAB_0001c1b0;
  }
  if (iVar3 == 1) {
LAB_0001c134:
    local_20 = *(int *)(param_2 + 0xc);
  }
  else {
    if (iVar3 == 2) {
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001c134;
    }
    if (iVar3 != 0) goto LAB_0001c1f8;
  }
  iVar1 = PyDict_Size(param_3);
  if (iVar3 == 0) {
    local_20 = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0001c228 + 0x1c194),
                          *(undefined4 *)(*(int *)(DAT_0001c228 + 0x1c194) + 0xc));
    if (local_20 == 0) goto LAB_0001c1f8;
    iVar1 = iVar1 + -1;
LAB_0001c168:
    local_1c = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0001c22c + 0x1c1e8),
                          *(undefined4 *)(*(int *)(DAT_0001c22c + 0x1c1e8) + 0xc));
    if (local_1c == 0) {
      FUN_00017adc(DAT_0001c230 + 0x1c1a8,1,2,2,1);
      uVar2 = 0x1f32;
      goto LAB_0001c1b0;
    }
    iVar1 = iVar1 + -1;
  }
  else if (iVar3 == 1) goto LAB_0001c168;
  if ((iVar1 < 1) ||
     (iVar3 = FUN_0001a640(param_3,&UNK_0001c770 + DAT_0001c224,&local_20,iVar3,
                           DAT_0001c220 + 0x1c10c), -1 < iVar3)) {
LAB_0001c1e8:
    uVar2 = FUN_0001bd20(local_20,local_1c);
    return uVar2;
  }
  uVar2 = 0x1f36;
LAB_0001c1b0:
  FUN_00019490(DAT_0001c238 + 0x1c1c8,uVar2,0xbe,DAT_0001c234 + 0x1c1c4);
  return 0;
}




/* ============================================
 * Function: FUN_0001c240
 * Address:  0x1c240
 * ============================================ */

undefined4 FUN_0001c240(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  undefined4 uVar11;
  int local_30 [3];
  
  iVar4 = DAT_0001c52c;
  iVar10 = DAT_0001c530 + 0x1c260;
  iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(&UNK_0001c618 + DAT_0001c52c));
  if (iVar1 == 0) {
    uVar11 = 0x23b4;
    iVar4 = 0;
    iVar2 = 0;
    iVar5 = 0;
    iVar3 = 0;
LAB_0001c414:
    FUN_000182bc(0);
    FUN_000182bc(iVar1);
    FUN_000182bc(iVar2);
    FUN_000182bc(iVar3);
    FUN_000182bc(iVar4);
    FUN_000182bc(iVar5);
    FUN_00019490(DAT_0001c548 + 0x1c460,uVar11,0xe4,DAT_0001c544 + 0x1c45c);
    return 0;
  }
  iVar2 = FUN_00017ee8(iVar1,*(undefined4 *)(iVar4 + 0x1c31c));
  if (iVar2 == 0) {
    uVar11 = 0x23b6;
    iVar4 = 0;
    iVar5 = 0;
    iVar3 = 0;
    goto LAB_0001c414;
  }
  FUN_00017fec(iVar1);
  iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(&UNK_0001c61c + iVar4));
  if (iVar1 == 0) {
    uVar11 = 0x23b9;
    iVar4 = 0;
    iVar5 = 0;
    iVar3 = 0;
    goto LAB_0001c414;
  }
  iVar3 = FUN_00017ee8(param_1,*(undefined4 *)(iVar4 + 0x1c290));
  if (iVar3 == 0) {
    uVar11 = 0x23bb;
    iVar4 = 0;
    iVar5 = 0;
    goto LAB_0001c414;
  }
  iVar4 = FUN_00018840(*(undefined4 *)(iVar2 + 4),*(undefined4 *)(iVar10 + DAT_0001c534));
  iVar7 = iVar2;
  if (iVar4 == 0) {
    iVar4 = 0;
    iVar9 = 0;
  }
  else {
    iVar4 = *(int *)(iVar2 + 0xc);
    if (iVar4 == 0) {
      iVar9 = 0;
    }
    else {
      iVar7 = *(int *)(iVar2 + 8);
      iVar9 = 1;
      FUN_00018934(iVar4);
      FUN_00018934(iVar7);
      FUN_00017fec(iVar2);
    }
  }
  iVar8 = iVar9 + 2;
  uVar11 = *(undefined4 *)(iVar7 + 4);
  iVar5 = FUN_00018840(uVar11,*(undefined4 *)(iVar10 + DAT_0001c538));
  iVar2 = iVar7;
  if (iVar5 == 0) {
    uVar6 = *(undefined4 *)(iVar10 + DAT_0001c540);
    iVar5 = FUN_00018840(uVar11,uVar6);
    if (((iVar5 == 0) && (iVar5 = PyType_IsSubtype(uVar11,uVar6), iVar5 == 0)) ||
       ((*(uint *)(*(int *)(iVar7 + 8) + 8) & 0xffffff8d) != 0x80)) {
      iVar5 = PyTuple_New(iVar8);
      if (iVar5 == 0) {
        uVar11 = 0x23de;
        goto LAB_0001c414;
      }
      iVar9 = iVar5 + iVar9 * 4;
      if (iVar4 != 0) {
        *(int *)(iVar5 + 0xc) = iVar4;
      }
      *(int *)(iVar9 + 0xc) = iVar1;
      *(int *)(iVar9 + 0x10) = iVar3;
      iVar9 = FUN_00017e40(iVar7,iVar5,0);
      if (iVar9 == 0) {
        uVar11 = 0x23e9;
        iVar1 = 0;
        iVar4 = 0;
        iVar3 = 0;
        goto LAB_0001c414;
      }
      FUN_00017fec(iVar5);
      goto LAB_0001c37c;
    }
    local_30[0] = iVar1;
    local_30[1] = iVar3;
    iVar9 = FUN_00017628(iVar7,local_30 + -iVar9,iVar8);
    if (iVar9 == 0) {
      uVar11 = 0x23d6;
      iVar5 = 0;
      goto LAB_0001c414;
    }
  }
  else {
    local_30[0] = iVar1;
    local_30[1] = iVar3;
    iVar9 = FUN_0001b728(iVar7,local_30 + -iVar9,iVar8);
    if (iVar9 == 0) {
      uVar11 = 0x23cc;
      iVar5 = 0;
      goto LAB_0001c414;
    }
  }
  FUN_000182bc(iVar4);
  FUN_00017fec(iVar1);
  FUN_00017fec(iVar3);
LAB_0001c37c:
  FUN_00017fec(iVar7);
  FUN_00017fec(iVar9);
  uVar11 = *(undefined4 *)(iVar10 + DAT_0001c53c);
  FUN_00018934(uVar11);
  return uVar11;
}




/* ============================================
 * Function: FUN_0001caa0
 * Address:  0x1caa0
 * ============================================ */

undefined4 FUN_0001caa0(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 local_20;
  undefined4 local_1c;
  
  iVar4 = DAT_0001cbc0 + 0x1cac0;
  uVar3 = *(undefined4 *)(param_1 + 4);
  uVar2 = *(undefined4 *)(iVar4 + DAT_0001cbc4);
  local_20 = param_3;
  local_1c = param_4;
  iVar1 = FUN_00018840(uVar3,uVar2,param_3,uVar2,param_1,uVar2);
  if (iVar1 == 0) {
    uVar2 = *(undefined4 *)(iVar4 + DAT_0001cbc8);
    iVar1 = FUN_00018840(uVar3,uVar2);
    if (((iVar1 == 0) && (iVar1 = PyType_IsSubtype(uVar3,uVar2), iVar1 == 0)) ||
       ((*(uint *)(*(int *)(param_1 + 8) + 8) & 0xffffff8d) != 0x80)) {
      iVar1 = PyTuple_New(2);
      uVar2 = 0;
      if (iVar1 != 0) {
        FUN_00018934(param_2);
        *(undefined4 *)(iVar1 + 0xc) = param_2;
        FUN_00018934(param_3);
        *(undefined4 *)(iVar1 + 0x10) = param_3;
        uVar2 = FUN_00018934(param_1);
        uVar2 = FUN_00017e40(uVar2,iVar1,0);
        FUN_00017fec(iVar1);
        FUN_00017fec(param_1);
      }
    }
    else {
      local_20 = param_2;
      local_1c = param_3;
      uVar2 = FUN_00017628(param_1,&local_20,2);
    }
  }
  else {
    local_20 = param_2;
    uVar2 = FUN_0001b728(param_1,&local_20,2);
  }
  return uVar2;
}




/* ============================================
 * Function: FUN_0001cbcc
 * Address:  0x1cbcc
 * ============================================ */

void FUN_0001cbcc(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  undefined4 uVar3;
  int iVar4;
  
  iVar4 = DAT_0001ccb0 + 0x1cbe4;
  uVar3 = *(undefined4 *)(param_1 + 4);
  uVar2 = *(undefined4 *)(iVar4 + DAT_0001ccb4);
  iVar1 = FUN_00018840(uVar3,uVar2,param_3,uVar2,param_1,uVar2);
  if (iVar1 != 0) {
    FUN_0001b728(param_1,0);
    return;
  }
  uVar2 = *(undefined4 *)(iVar4 + DAT_0001ccb8);
  iVar1 = FUN_00018840(uVar3,uVar2);
  if ((((iVar1 != 0) || (iVar1 = PyType_IsSubtype(uVar3,uVar2), iVar1 != 0)) ||
      (iVar1 = FUN_000176d8(*(undefined4 *)(param_1 + 4),*(undefined4 *)(DAT_0001ccc0 + 0x1cf04)),
      iVar1 != 0)) && ((*(uint *)(*(int *)(param_1 + 8) + 8) & 4) != 0)) {
    FUN_00017da4(param_1,0);
    return;
  }
  FUN_00017e40(param_1,*(undefined4 *)(DAT_0001ccbc + 0x1cca8),0);
  return;
}




/* ============================================
 * Function: FUN_0001ccc4
 * Address:  0x1ccc4
 * ============================================ */

void FUN_0001ccc4(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  uint uVar3;
  undefined4 uVar4;
  int iVar5;
  undefined4 local_14;
  
  iVar5 = DAT_0001cd94 + 0x1ccdc;
  uVar4 = *(undefined4 *)(param_1 + 4);
  uVar2 = *(undefined4 *)(iVar5 + DAT_0001cd98);
  local_14 = param_2;
  iVar1 = FUN_00018840(uVar4,uVar2,param_3,uVar2,uVar2);
  if (iVar1 != 0) {
    FUN_0001b728(param_1,&local_14,1);
    return;
  }
  uVar2 = *(undefined4 *)(iVar5 + DAT_0001cd9c);
  iVar1 = FUN_00018840(uVar4,uVar2);
  if ((iVar1 != 0) || (iVar1 = PyType_IsSubtype(uVar4,uVar2), iVar1 != 0)) {
    uVar3 = *(uint *)(*(int *)(param_1 + 8) + 8);
    if ((uVar3 & 8) != 0) {
      FUN_00017da4(param_1,local_14);
      return;
    }
    if ((uVar3 & 0x80) != 0) {
      FUN_00017628(param_1,&local_14,1);
      return;
    }
  }
  FUN_00019150(param_1,local_14);
  return;
}




/* ============================================
 * Function: FUN_0001cda0
 * Address:  0x1cda0
 * ============================================ */

undefined4 FUN_0001cda0(undefined4 param_1)

{
  undefined4 uVar1;
  
  uVar1 = FUN_0001ccc4();
  FUN_00017fec(param_1);
  return uVar1;
}




/* ============================================
 * Function: FUN_0001ce2c
 * Address:  0x1ce2c
 * ============================================ */

undefined4 FUN_0001ce2c(undefined4 param_1,undefined4 param_2)

{
  int iVar1;
  undefined4 uVar2;
  int local_14;
  undefined4 uStack_10;
  
  local_14 = 0;
  uStack_10 = param_2;
  iVar1 = FUN_0001b1a4(param_1,*(undefined4 *)(&UNK_0001d200 + DAT_0001ce40),&local_14,0,param_1);
  if (iVar1 == 0) {
    uVar2 = 0;
    if (local_14 != 0) {
      uVar2 = FUN_0001cda0(local_14,param_2);
    }
  }
  else {
    uVar2 = FUN_0001caa0(local_14,param_1,param_2);
    FUN_00017fec(local_14);
  }
  return uVar2;
}




/* ============================================
 * Function: FUN_0001ce44
 * Address:  0x1ce44
 * ============================================ */

undefined4 FUN_0001ce44(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  
  uVar1 = 0;
  if (param_2 != 0) {
    uVar1 = FUN_0001ce2c();
    FUN_00017fec(param_2);
  }
  return uVar1;
}




/* ============================================
 * Function: FUN_0001ce6c
 * Address:  0x1ce6c
 * ============================================ */

undefined4 FUN_0001ce6c(int param_1,int param_2)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int iVar4;
  
  iVar3 = *(int *)(param_1 + 8);
  iVar4 = DAT_0001cf0c + 0x1ce90;
  if ((*(int *)(param_1 + 0x10) >> 1 < iVar3) && (iVar1 = FUN_00017510(0,iVar3), iVar1 != 0)) {
    uVar2 = **(undefined4 **)(param_1 + 0xc);
    FUN_0001892c(param_1 + 8,iVar3 + -1);
    memmove(*(void **)(param_1 + 0xc),(void *)((int)*(void **)(param_1 + 0xc) + 4),(iVar3 + -1) * 4)
    ;
    return uVar2;
  }
  if (param_2 == *(int *)(iVar4 + DAT_0001cf10)) {
    uVar2 = PyLong_FromSsize_t(0);
    uVar2 = FUN_0001ce44(param_1,uVar2);
    return uVar2;
  }
  uVar2 = FUN_0001ce2c(param_1,param_2);
  return uVar2;
}




/* ============================================
 * Function: FUN_0001d300
 * Address:  0x1d300
 * ============================================ */

int FUN_0001d300(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  code *pcVar7;
  int iVar8;
  
  iVar5 = *(int *)(param_1 + 0xc);
  iVar6 = DAT_0001d5d0 + 0x1d324;
  iVar8 = param_1;
  if (*(int *)(param_1 + 0x3c) == 0) {
    if (param_3 == 0) {
      uVar4 = 0x27bb;
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(*(int *)(iVar5 + 8) + 8);
      if (iVar2 == 0) {
        uVar4 = 0x27bc;
        FUN_00017b84(DAT_0001d5d4 + 0x1d390);
        param_3 = 0;
        iVar2 = 0;
      }
      else {
        param_2 = *(undefined4 *)(iVar6 + DAT_0001d5e0);
        iVar3 = FUN_00018840(*(undefined4 *)(iVar2 + 4),param_2,param_3,param_2,param_1,param_2);
        if (iVar3 == 0) {
          param_3 = PyObject_GetItem(iVar2,*(undefined4 *)(DAT_0001d5e4 + 0x1d7c0));
        }
        else {
          param_3 = FUN_0001955c();
        }
        iVar2 = param_3;
        if (param_3 != 0) {
          uVar4 = *(undefined4 *)(param_3 + 4);
          param_2 = *(undefined4 *)(iVar6 + DAT_0001d5e8);
          iVar3 = FUN_00018840(uVar4,param_2);
          if (iVar3 == 0) {
            param_2 = *(undefined4 *)(iVar6 + DAT_0001d5ec);
            iVar3 = FUN_00018840(uVar4,param_2);
            if (iVar3 != 0) goto LAB_0001d444;
            iVar2 = PyObject_GetIter(param_3);
            if (iVar2 == 0) {
              uVar4 = 0x27c3;
              goto LAB_0001d390;
            }
            pcVar7 = *(code **)(*(int *)(iVar2 + 4) + 0x70);
            if (pcVar7 == (code *)0x0) {
              uVar4 = 0x27c5;
              goto LAB_0001d390;
            }
            iVar3 = -1;
          }
          else {
LAB_0001d444:
            pcVar7 = (code *)0x0;
            FUN_00018934(param_3);
            iVar3 = 0;
          }
          FUN_00017fec(param_3);
          goto LAB_0001d45c;
        }
        uVar4 = 0x27bd;
      }
    }
  }
  else {
    if (*(int *)(param_1 + 0x3c) != 1) {
      return 0;
    }
    iVar2 = *(int *)(iVar5 + 0x10);
    *(undefined4 *)(iVar5 + 0x10) = 0;
    iVar3 = *(int *)(iVar5 + 0x14);
    pcVar7 = *(code **)(iVar5 + 0x18);
    if (param_3 == 0) {
      uVar4 = 0x27ff;
      goto LAB_0001d390;
    }
LAB_0001d45c:
    if (pcVar7 == (code *)0x0) {
      param_2 = *(undefined4 *)(iVar6 + DAT_0001d5e8);
      iVar1 = FUN_00018840(*(undefined4 *)(iVar2 + 4),param_2);
      if (iVar1 == 0) {
        if (iVar3 < *(int *)(iVar2 + 8)) {
          iVar1 = *(int *)(iVar2 + iVar3 * 4 + 0xc);
          goto LAB_0001d50c;
        }
      }
      else if (iVar3 < *(int *)(iVar2 + 8)) {
        iVar1 = *(int *)(*(int *)(iVar2 + 0xc) + iVar3 * 4);
LAB_0001d50c:
        iVar3 = iVar3 + 1;
        FUN_00018934(iVar1);
        goto LAB_0001d518;
      }
LAB_0001d498:
      FUN_00017fec(iVar2);
      PyErr_SetNone(**(undefined4 **)(iVar6 + DAT_0001d5f0));
      goto LAB_0001d4b0;
    }
    iVar1 = (*pcVar7)(iVar2);
    if (iVar1 == 0) {
      iVar5 = PyErr_Occurred();
      if (iVar5 != 0) {
        iVar5 = FUN_00019adc(iVar5,**(undefined4 **)(iVar6 + DAT_0001d5f0));
        if (iVar5 == 0) {
          uVar4 = 0x27e1;
          param_3 = 0;
          goto LAB_0001d390;
        }
        PyErr_Clear();
      }
      goto LAB_0001d498;
    }
LAB_0001d518:
    uVar4 = *(undefined4 *)(iVar5 + 0xc);
    *(int *)(iVar5 + 0xc) = iVar1;
    FUN_000182bc(uVar4);
    iVar6 = FUN_0001ccc4(*(undefined4 *)(DAT_0001d5f4 + 0x1d54c),*(undefined4 *)(iVar5 + 0xc));
    if (iVar6 != 0) {
      *(int *)(iVar5 + 0x10) = iVar2;
      *(int *)(iVar5 + 0x14) = iVar3;
      *(code **)(iVar5 + 0x18) = pcVar7;
      FUN_000182fc(param_1 + 0x10);
      *(undefined4 *)(param_1 + 0x3c) = 1;
      return iVar6;
    }
    uVar4 = 0x27eb;
    param_3 = 0;
  }
LAB_0001d390:
  FUN_000182bc(param_3);
  FUN_000182bc(iVar2);
  FUN_00019490(DAT_0001d5dc + 0x1d3bc,uVar4,0x110,DAT_0001d5d8 + 0x1d3b8,iVar8,param_2);
LAB_0001d4b0:
  FUN_000182bc(0);
  *(undefined4 *)(param_1 + 0x3c) = 0xffffffff;
  FUN_00018334(param_1);
  return 0;
}




/* ============================================
 * Function: FUN_0001d5f8
 * Address:  0x1d5f8
 * ============================================ */

int FUN_0001d5f8(undefined4 param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  
  iVar4 = DAT_0001db80;
  iVar5 = DAT_0001db84 + 0x1d618;
  if (*(int *)(*(int *)(DAT_0001db80 + 0x1d880) + 0x14) == *(int *)(DAT_0001db80 + 0x1d9f0) &&
      *(int *)(*(int *)(DAT_0001db80 + 0x1d880) + 0x10) == *(int *)(DAT_0001db80 + 0x1d9ec)) {
    if (*(int *)(DAT_0001db80 + 0x1d9f4) == 0) {
      iVar4 = FUN_00017f00(*(undefined4 *)(DAT_0001db80 + 0x1d8f4));
    }
    else {
      FUN_00018934();
      iVar4 = *(int *)(iVar4 + 0x1d9f4);
    }
  }
  else {
    iVar4 = FUN_00018c58(*(undefined4 *)(DAT_0001db80 + 0x1d8f4),DAT_0001db80 + 0x1d9ec,
                         DAT_0001db80 + 0x1d9f4,*(int *)(DAT_0001db80 + 0x1d9f0),param_1,param_2,
                         param_3);
  }
  iVar8 = DAT_0001db88;
  if (iVar4 == 0) {
    uVar3 = 0x2687;
    iVar1 = 0;
LAB_0001da74:
    iVar5 = 0;
    uVar9 = 0xf5;
    iVar2 = iVar5;
  }
  else {
    iVar1 = FUN_00017ee8(iVar4,*(undefined4 *)(DAT_0001db88 + 0x1da40));
    if (iVar1 == 0) {
      uVar3 = 0x2689;
      goto LAB_0001da74;
    }
    FUN_00017fec(iVar4);
    iVar4 = *(int *)(iVar8 + 0x1da44);
    iVar8 = *(int *)(iVar5 + DAT_0001db8c);
    if (iVar4 == iVar8) {
LAB_0001d9d0:
      iVar4 = PyNumber_Remainder(iVar4,param_2);
    }
    else {
      iVar6 = *(int *)(param_2 + 4);
      iVar2 = FUN_0001954c(*(undefined4 *)(iVar6 + 0x54),0x10000000);
      if ((iVar2 != 0) &&
         (iVar2 = FUN_00018840(iVar6,*(undefined4 *)(iVar5 + DAT_0001db90)), iVar2 == 0))
      goto LAB_0001d9d0;
      iVar4 = PyUnicode_Format(iVar4,param_2);
    }
    if (iVar4 == 0) {
      uVar3 = 0x268c;
      iVar4 = 0;
      goto LAB_0001da74;
    }
    uVar3 = *(undefined4 *)(iVar5 + DAT_0001db94);
    iVar5 = FUN_00018840(*(undefined4 *)(iVar1 + 4),uVar3);
    if ((iVar5 == 0) || (iVar5 = *(int *)(iVar1 + 0xc), iVar5 == 0)) {
      iVar5 = 0;
      iVar2 = FUN_0001ccc4(iVar1,iVar4);
    }
    else {
      iVar6 = *(int *)(iVar1 + 8);
      FUN_00018934(iVar5);
      FUN_00018934(iVar6);
      FUN_00017fec(iVar1);
      iVar2 = FUN_0001caa0(iVar6,iVar5,iVar4);
      iVar1 = iVar6;
    }
    FUN_000182bc(iVar5);
    FUN_00017fec(iVar4);
    if (iVar2 == 0) {
      uVar3 = 0x269b;
      iVar4 = 0;
      goto LAB_0001da74;
    }
    FUN_00017fec(iVar1);
    FUN_00017fec(iVar2);
    iVar4 = FUN_00017ee8(param_2,*(undefined4 *)(DAT_0001db98 + 0x1db58));
    if (iVar4 == 0) {
      uVar3 = 0x26a7;
      iVar1 = 0;
      iVar5 = 0;
LAB_0001db04:
      uVar9 = 0xf6;
      iVar2 = iVar5;
    }
    else {
      iVar5 = FUN_00018840(*(undefined4 *)(iVar4 + 4),uVar3);
      if ((iVar5 == 0) || (iVar5 = *(int *)(iVar4 + 0xc), iVar5 == 0)) {
        iVar5 = 0;
        iVar1 = FUN_0001cbcc(iVar4);
      }
      else {
        iVar2 = *(int *)(iVar4 + 8);
        FUN_00018934(iVar5);
        FUN_00018934(iVar2);
        FUN_00017fec(iVar4);
        iVar1 = FUN_0001ccc4(iVar2,iVar5);
        iVar4 = iVar2;
      }
      FUN_000182bc(iVar5);
      iVar5 = DAT_0001db9c;
      if (iVar1 == 0) {
        uVar3 = 0x26b5;
        iVar5 = 0;
        goto LAB_0001db04;
      }
      FUN_00017fec(iVar4);
      iVar4 = FUN_00017ee8(iVar1,*(undefined4 *)(iVar5 + 0x1dbd8));
      if (iVar4 == 0) {
        uVar3 = 0x26b8;
        iVar5 = 0;
        goto LAB_0001db04;
      }
      FUN_00017fec(iVar1);
      iVar1 = FUN_00018840(*(undefined4 *)(iVar4 + 4),uVar3);
      if ((iVar1 == 0) || (iVar1 = *(int *)(iVar4 + 0xc), iVar1 == 0)) {
        iVar1 = 0;
        iVar5 = FUN_0001ccc4(iVar4,*(undefined4 *)(&UNK_0001de1c + DAT_0001dba4));
      }
      else {
        iVar2 = *(int *)(iVar4 + 8);
        FUN_00018934(iVar1);
        FUN_00018934(iVar2);
        FUN_00017fec(iVar4);
        iVar5 = FUN_0001caa0(iVar2,iVar1,*(undefined4 *)(iVar5 + 0x1dbdc));
        iVar4 = iVar2;
      }
      FUN_000182bc(iVar1);
      iVar2 = DAT_0001dba0;
      if (iVar5 == 0) {
        uVar3 = 0x26c7;
        iVar1 = 0;
        goto LAB_0001db04;
      }
      FUN_00017fec(iVar4);
      iVar4 = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x1dc30));
      if (iVar4 == 0) {
        uVar3 = 0x26d4;
        iVar1 = 0;
        iVar2 = 0;
      }
      else {
        iVar1 = FUN_00017ee8(iVar4,*(undefined4 *)(iVar2 + 0x1d964));
        if (iVar1 == 0) {
          uVar3 = 0x26d6;
          iVar2 = 0;
        }
        else {
          FUN_00017fec(iVar4);
          iVar2 = FUN_00017ee8(iVar5,*(undefined4 *)(iVar2 + 0x1dc6c));
          if (iVar2 == 0) {
            uVar3 = 0x26d9;
            iVar4 = 0;
          }
          else {
            iVar4 = FUN_00018840(*(undefined4 *)(iVar2 + 4),uVar3);
            if ((iVar4 == 0) || (iVar4 = *(int *)(iVar2 + 0xc), iVar4 == 0)) {
              iVar4 = 0;
              iVar6 = FUN_0001cbcc(iVar2);
            }
            else {
              iVar7 = *(int *)(iVar2 + 8);
              FUN_00018934(iVar4);
              FUN_00018934(iVar7);
              FUN_00017fec(iVar2);
              iVar6 = FUN_0001ccc4(iVar7,iVar4);
              iVar2 = iVar7;
            }
            FUN_000182bc(iVar4);
            if (iVar6 == 0) {
              uVar3 = 0x26e7;
              iVar4 = 0;
            }
            else {
              FUN_00017fec(iVar2);
              iVar4 = FUN_00018840(*(undefined4 *)(iVar1 + 4),uVar3);
              if ((iVar4 == 0) || (iVar4 = *(int *)(iVar1 + 0xc), iVar4 == 0)) {
                iVar4 = 0;
                iVar2 = FUN_0001ccc4(iVar1,iVar6);
              }
              else {
                iVar7 = *(int *)(iVar1 + 8);
                FUN_00018934(iVar4);
                FUN_00018934(iVar7);
                FUN_00017fec(iVar1);
                iVar2 = FUN_0001caa0(iVar7,iVar4,iVar6);
                iVar1 = iVar7;
              }
              FUN_000182bc(iVar4);
              FUN_00017fec(iVar6);
              if (iVar2 != 0) {
                FUN_00017fec(iVar1);
                FUN_00017fec(iVar2);
                FUN_00018934(iVar8);
                goto LAB_0001d998;
              }
              uVar3 = 0x26f7;
              iVar4 = 0;
              iVar2 = 0;
            }
          }
        }
      }
      uVar9 = 0xf7;
    }
  }
  FUN_000182bc(0);
  FUN_000182bc(iVar4);
  FUN_000182bc(iVar1);
  FUN_000182bc(iVar2);
  FUN_000182bc(0);
  iVar8 = 0;
  FUN_00019490(DAT_0001dbac + 0x1dac0,uVar3,uVar9,DAT_0001dba8 + 0x1dab8);
LAB_0001d998:
  FUN_000182bc(iVar5);
  return iVar8;
}




/* ============================================
 * Function: FUN_0001dbb0
 * Address:  0x1dbb0
 * ============================================ */

undefined4 FUN_0001dbb0(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_20;
  int local_1c;
  
  iVar3 = *(int *)(param_2 + 8);
  local_20 = 0;
  local_1c = 0;
  if (param_3 == 0) {
    if (iVar3 == 2) {
      local_20 = *(int *)(param_2 + 0xc);
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001dd08;
    }
LAB_0001dd18:
    FUN_00017adc(DAT_0001dd5c + 0x1dd34,1,2,2,*(undefined4 *)(param_2 + 8));
    uVar2 = 0x2665;
    goto LAB_0001dcd0;
  }
  if (iVar3 == 1) {
LAB_0001dc54:
    local_20 = *(int *)(param_2 + 0xc);
  }
  else {
    if (iVar3 == 2) {
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_0001dc54;
    }
    if (iVar3 != 0) goto LAB_0001dd18;
  }
  iVar1 = PyDict_Size(param_3);
  if (iVar3 == 0) {
    local_20 = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0001dd48 + 0x1dcb4),
                          *(undefined4 *)(*(int *)(DAT_0001dd48 + 0x1dcb4) + 0xc));
    if (local_20 == 0) goto LAB_0001dd18;
    iVar1 = iVar1 + -1;
LAB_0001dc88:
    local_1c = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(&UNK_0001de10 + DAT_0001dd4c),
                          *(undefined4 *)(*(int *)(&UNK_0001de10 + DAT_0001dd4c) + 0xc));
    if (local_1c == 0) {
      FUN_00017adc(DAT_0001dd50 + 0x1dcc8,1,2,2,1);
      uVar2 = 0x2654;
      goto LAB_0001dcd0;
    }
    iVar1 = iVar1 + -1;
  }
  else if (iVar3 == 1) goto LAB_0001dc88;
  if ((iVar1 < 1) ||
     (iVar3 = FUN_0001a640(param_3,&UNK_0001e2b0 + DAT_0001dd40,&local_20,iVar3,
                           DAT_0001dd44 + 0x1dc2c), -1 < iVar3)) {
LAB_0001dd08:
    uVar2 = FUN_0001d5f8(local_20,local_1c);
    return uVar2;
  }
  uVar2 = 0x2658;
LAB_0001dcd0:
  FUN_00019490(DAT_0001dd58 + 0x1dce8,uVar2,0xf4,DAT_0001dd54 + 0x1dce4);
  return 0;
}




/* ============================================
 * Function: FUN_00020d58
 * Address:  0x20d58
 * ============================================ */

int FUN_00020d58(int param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  code *pcVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  
  iVar5 = *(int *)(param_1 + 0xc);
  iVar8 = DAT_00020fc4 + 0x20d78;
  iVar9 = param_1;
  if (*(int *)(param_1 + 0x3c) == 0) {
    if (param_3 == 0) {
      uVar4 = 0x1a97;
      iVar2 = 0;
    }
    else {
      iVar2 = *(int *)(*(int *)(iVar5 + 8) + 8);
      if (iVar2 != 0) {
        uVar7 = *(undefined4 *)(iVar2 + 4);
        uVar4 = *(undefined4 *)(iVar8 + DAT_00020fd4);
        iVar3 = FUN_00018840(uVar7,uVar4,param_3,uVar4,param_1,uVar4);
        if (iVar3 == 0) {
          param_2 = *(undefined4 *)(iVar8 + DAT_00020fd8);
          iVar3 = FUN_00018840(uVar7,param_2);
          if (iVar3 == 0) {
            iVar2 = PyObject_GetIter(iVar2);
            if (iVar2 == 0) {
              uVar4 = 0x1a9d;
            }
            else {
              pcVar6 = *(code **)(*(int *)(iVar2 + 4) + 0x70);
              if (pcVar6 != (code *)0x0) {
                iVar3 = -1;
                goto LAB_00020f1c;
              }
              uVar4 = 0x1a9f;
            }
            goto LAB_00020de4;
          }
        }
        FUN_00018934(iVar2);
        iVar3 = 0;
LAB_00020e60:
        param_2 = *(undefined4 *)(iVar8 + DAT_00020fd4);
        iVar1 = FUN_00018840(*(undefined4 *)(iVar2 + 4),param_2);
        if (iVar1 == 0) {
          if (iVar3 < *(int *)(iVar2 + 8)) {
            iVar8 = iVar3 * 4;
            iVar3 = iVar3 + 1;
            iVar1 = *(int *)(iVar2 + iVar8 + 0xc);
            FUN_00018934(iVar1);
            pcVar6 = (code *)0x0;
            goto LAB_00020ea4;
          }
        }
        else if (iVar3 < *(int *)(iVar2 + 8)) {
          pcVar6 = (code *)0x0;
          iVar1 = *(int *)(*(int *)(iVar2 + 0xc) + iVar3 * 4);
          iVar3 = iVar3 + 1;
          FUN_00018934(iVar1);
LAB_00020ea4:
          uVar4 = *(undefined4 *)(iVar5 + 0xc);
          *(int *)(iVar5 + 0xc) = iVar1;
          FUN_000182bc(uVar4);
          iVar8 = FUN_0001ccc4(*(undefined4 *)(DAT_00020fdc + 0x20ed8),*(undefined4 *)(iVar5 + 0xc))
          ;
          if (iVar8 != 0) {
            *(int *)(iVar5 + 0x10) = iVar2;
            *(int *)(iVar5 + 0x14) = iVar3;
            *(code **)(iVar5 + 0x18) = pcVar6;
            FUN_000182fc(param_1 + 0x10);
            *(undefined4 *)(param_1 + 0x3c) = 1;
            return iVar8;
          }
          uVar4 = 0x1ac4;
          goto LAB_00020de4;
        }
LAB_00020f54:
        FUN_00017fec(iVar2);
        PyErr_SetNone(**(undefined4 **)(iVar8 + DAT_00020fe0));
        goto LAB_00020f6c;
      }
      uVar4 = 0x1a98;
      FUN_00017b84(DAT_00020fc8 + 0x20de4);
    }
  }
  else {
    if (*(int *)(param_1 + 0x3c) != 1) {
      return 0;
    }
    iVar2 = *(int *)(iVar5 + 0x10);
    *(undefined4 *)(iVar5 + 0x10) = 0;
    iVar3 = *(int *)(iVar5 + 0x14);
    pcVar6 = *(code **)(iVar5 + 0x18);
    if (param_3 != 0) {
      if (pcVar6 == (code *)0x0) goto LAB_00020e60;
LAB_00020f1c:
      iVar1 = (*pcVar6)(iVar2);
      if (iVar1 != 0) goto LAB_00020ea4;
      iVar5 = PyErr_Occurred();
      if (iVar5 != 0) {
        iVar5 = FUN_00019adc(iVar5,**(undefined4 **)(iVar8 + DAT_00020fe0));
        if (iVar5 == 0) {
          uVar4 = 0x1aba;
          goto LAB_00020de4;
        }
        PyErr_Clear();
      }
      goto LAB_00020f54;
    }
    uVar4 = 0x1ad8;
  }
LAB_00020de4:
  FUN_000182bc(iVar2);
  FUN_000182bc(0);
  FUN_00019490(DAT_00020fd0 + 0x20e10,uVar4,0x9e,DAT_00020fcc + 0x20e0c,iVar9,param_2);
LAB_00020f6c:
  FUN_000182bc(0);
  *(undefined4 *)(param_1 + 0x3c) = 0xffffffff;
  FUN_00018334(param_1);
  return 0;
}




/* ============================================
 * Function: FUN_00020fe4
 * Address:  0x20fe4
 * ============================================ */

int FUN_00020fe4(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 extraout_r2;
  undefined4 extraout_r2_00;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  int iVar11;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  int local_34 [4];
  
  iVar7 = DAT_00021b2c;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_4c = FUN_00017ee8(param_1,*(undefined4 *)(DAT_00021b2c + 0x21044));
  iVar11 = DAT_00021b30 + 0x21038;
  if (local_4c == 0) {
    uVar9 = 0x187a;
    iVar7 = 0;
LAB_00021998:
    uVar4 = 0x92;
    iVar6 = iVar7;
    iVar5 = iVar7;
    iVar3 = iVar7;
    iVar8 = iVar7;
    iVar10 = iVar7;
  }
  else {
    local_48 = FUN_00017ee8(local_4c,*(undefined4 *)(iVar7 + 0x21070));
    if (local_48 == 0) {
      uVar9 = 0x187c;
      iVar7 = 0;
      goto LAB_00021998;
    }
    FUN_00017fec(local_4c);
    iVar7 = local_48;
    local_4c = 0;
    uVar4 = *(undefined4 *)(iVar11 + DAT_00021b34);
    iVar1 = FUN_00018840(*(undefined4 *)(local_48 + 4),uVar4);
    if ((iVar1 != 0) && (local_4c = *(int *)(iVar7 + 0xc), local_4c != 0)) {
      iVar1 = *(int *)(iVar7 + 8);
      FUN_00018934();
      FUN_00018934(iVar1);
      iVar7 = local_48;
      local_48 = iVar1;
      FUN_00017fec(iVar7);
    }
    if (local_4c == 0) {
      local_50 = FUN_0001cbcc(local_48);
    }
    else {
      local_50 = FUN_0001ccc4();
    }
    iVar7 = 0;
    FUN_000182bc(local_4c);
    iVar1 = DAT_00021b38;
    local_4c = 0;
    if (local_50 == 0) {
      uVar9 = 0x188b;
      iVar7 = local_50;
      goto LAB_00021998;
    }
    FUN_00017fec(local_48);
    iVar10 = local_50;
    local_48 = 0;
    local_50 = 0;
    local_50 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x21574));
    if (local_50 == 0) {
      uVar9 = 0x1898;
      uVar4 = 0x93;
      iVar7 = 0;
      iVar6 = 0;
      iVar5 = 0;
      iVar3 = 0;
      iVar8 = 0;
    }
    else {
      iVar2 = PyObject_SetItem(local_50,param_3,iVar10);
      iVar8 = iVar7;
      iVar5 = iVar7;
      iVar6 = iVar7;
      iVar3 = iVar7;
      if (iVar2 < 0) {
        uVar9 = 0x189a;
        uVar4 = 0x93;
      }
      else {
        FUN_00017fec(local_50);
        local_50 = 0;
        local_48 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x21490));
        if (local_48 == 0) {
          uVar9 = 0x18a4;
          iVar6 = 0;
          iVar5 = 0;
          iVar3 = 0;
        }
        else {
          local_4c = FUN_00017ee8(local_48,*(undefined4 *)(iVar1 + 0x21494));
          if (local_4c == 0) {
            uVar9 = 0x18a6;
            iVar6 = 0;
            iVar5 = 0;
            iVar3 = 0;
          }
          else {
            FUN_00017fec(local_48);
            local_48 = 0;
            local_48 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x21498));
            if (local_48 == 0) {
              uVar9 = 0x18a9;
              iVar6 = 0;
              iVar5 = 0;
              iVar3 = 0;
            }
            else {
              iVar1 = PyObject_Size(param_2);
              if (iVar1 == -1) {
                uVar9 = 0x18ab;
                uVar4 = 0x94;
                goto LAB_000218fc;
              }
              iVar3 = PyLong_FromSsize_t();
              iVar7 = local_4c;
              if (iVar3 == 0) {
                uVar9 = 0x18ac;
                iVar6 = 0;
                iVar5 = 0;
              }
              else {
                iVar1 = FUN_00018840(*(undefined4 *)(local_4c + 4),uVar4);
                if (iVar1 == 0) {
                  iVar7 = 0;
                  iVar6 = 0;
                }
                else {
                  iVar6 = *(int *)(iVar7 + 0xc);
                  if (iVar6 == 0) {
                    iVar7 = 0;
                  }
                  else {
                    iVar5 = *(int *)(iVar7 + 8);
                    FUN_00018934(iVar6);
                    FUN_00018934(iVar5);
                    iVar1 = local_4c;
                    iVar7 = 1;
                    local_4c = iVar5;
                    FUN_00017fec(iVar1);
                  }
                }
                iVar1 = local_4c;
                iVar8 = iVar7 + 3;
                iVar5 = FUN_00018840(*(undefined4 *)(local_4c + 4),
                                     *(undefined4 *)(iVar11 + DAT_00021b3c));
                if (iVar5 == 0) {
                  uVar9 = *(undefined4 *)(iVar11 + DAT_00021b4c);
                  iVar1 = FUN_00018840(extraout_r2,uVar9);
                  if (((iVar1 == 0) && (iVar1 = PyType_IsSubtype(extraout_r2_00,uVar9), iVar1 == 0))
                     || ((*(uint *)(*(int *)(local_4c + 8) + 8) & 0xffffff8d) != 0x80)) {
                    iVar5 = PyTuple_New(iVar8);
                    if (iVar5 == 0) {
                      uVar9 = 0x18cf;
                    }
                    else {
                      iVar7 = iVar5 + iVar7 * 4;
                      if (iVar6 != 0) {
                        *(int *)(iVar5 + 0xc) = iVar6;
                      }
                      *(int *)(iVar7 + 0xc) = local_48;
                      FUN_00018934(param_2);
                      *(undefined4 *)(iVar7 + 0x10) = param_2;
                      *(int *)(iVar7 + 0x14) = iVar3;
                      local_48 = 0;
                      local_50 = FUN_00017e40(local_4c,iVar5);
                      if (local_50 != 0) goto LAB_000212a0;
                      uVar9 = 0x18dd;
                      iVar6 = 0;
                      iVar3 = 0;
                      local_50 = 0;
                    }
                  }
                  else {
                    local_34[0] = local_48;
                    local_38 = iVar6;
                    local_34[1] = param_2;
                    local_34[2] = iVar3;
                    local_50 = FUN_00017628(local_4c,local_34 + -iVar7,iVar8);
                    if (local_50 != 0) goto LAB_00021284;
                    uVar9 = 0x18c7;
                    iVar5 = 0;
                    local_50 = 0;
                  }
                }
                else {
                  local_34[0] = local_48;
                  local_38 = iVar6;
                  local_34[1] = param_2;
                  local_34[2] = iVar3;
                  local_50 = FUN_0001b728(iVar1,local_34 + -iVar7,iVar8);
                  if (local_50 != 0) {
LAB_00021284:
                    FUN_000182bc(iVar6);
                    FUN_00017fec(local_48);
                    local_48 = 0;
                    iVar5 = iVar3;
LAB_000212a0:
                    iVar7 = DAT_00021b40;
                    FUN_00017fec(iVar5);
                    FUN_00017fec(local_4c);
                    local_4c = 0;
                    FUN_00017fec(local_50);
                    local_50 = 0;
                    local_4c = FUN_00017ee8(iVar10,*(undefined4 *)(iVar7 + 0x2173c));
                    if (local_4c == 0) {
                      uVar9 = 0x18eb;
                      iVar5 = 0;
                      iVar3 = 0;
                      iVar7 = 0;
                    }
                    else {
                      iVar3 = FUN_00017ee8(param_1,*(undefined4 *)(iVar7 + 0x212f8));
                      if (iVar3 == 0) {
                        uVar9 = 0x18ed;
                        iVar5 = 0;
                        iVar7 = 0;
                      }
                      else {
                        local_48 = FUN_00017ee8(iVar3,*(undefined4 *)(iVar7 + 0x21740));
                        if (local_48 == 0) {
                          uVar9 = 0x18ef;
                          iVar5 = 0;
                          iVar7 = 0;
                        }
                        else {
                          FUN_00017fec(iVar3);
                          iVar7 = local_48;
                          iVar1 = FUN_00018840(*(undefined4 *)(local_48 + 4),uVar4);
                          if ((iVar1 == 0) || (iVar1 = *(int *)(iVar7 + 0xc), iVar1 == 0)) {
                            iVar1 = 0;
                            iVar5 = FUN_0001cbcc(iVar7);
                          }
                          else {
                            iVar6 = *(int *)(iVar7 + 8);
                            FUN_00018934(iVar1);
                            FUN_00018934(iVar6);
                            iVar7 = local_48;
                            local_48 = iVar6;
                            FUN_00017fec(iVar7);
                            iVar5 = FUN_0001ccc4(local_48,iVar1);
                          }
                          FUN_000182bc(iVar1);
                          if (iVar5 == 0) {
                            uVar9 = 0x18fe;
                            iVar3 = 0;
                            iVar7 = 0;
                          }
                          else {
                            FUN_00017fec(local_48);
                            local_48 = 0;
                            local_48 = PyNumber_Add(iVar5,param_4);
                            if (local_48 == 0) {
                              uVar9 = 0x1901;
                              iVar3 = 0;
                              iVar7 = 0;
                              local_48 = 0;
                            }
                            else {
                              FUN_00017fec(iVar5);
                              iVar7 = local_4c;
                              iVar1 = FUN_00018840(*(undefined4 *)(local_4c + 4),uVar4);
                              if ((iVar1 == 0) || (iVar1 = *(int *)(iVar7 + 0xc), iVar1 == 0)) {
                                iVar1 = 0;
                                local_50 = FUN_0001ccc4(iVar7,local_48);
                              }
                              else {
                                iVar6 = *(int *)(iVar7 + 8);
                                FUN_00018934(iVar1);
                                FUN_00018934(iVar6);
                                iVar7 = local_4c;
                                local_4c = iVar6;
                                FUN_00017fec(iVar7);
                                local_50 = FUN_0001caa0(local_4c,iVar1,local_48);
                              }
                              iVar8 = 0;
                              FUN_000182bc(iVar1);
                              FUN_00017fec(local_48);
                              local_48 = 0;
                              if (local_50 != 0) {
                                FUN_00017fec(local_4c);
                                iVar7 = local_50;
                                iVar1 = DAT_00021b48;
                                local_4c = 0;
                                local_50 = 0;
                                if (iVar7 != *(int *)(iVar11 + DAT_00021b44)) {
LAB_00021560:
                                  FUN_000182bc(0);
                                  FUN_00018934(iVar7);
                                  iVar11 = iVar7;
                                  goto LAB_00021574;
                                }
                                iVar5 = _PyThreadState_UncheckedGet();
                                FUN_00019f30(iVar5,&local_44,&local_40,&local_3c);
                                local_4c = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x218e8));
                                if (local_4c == 0) {
                                  uVar9 = 0x1939;
                                }
                                else {
                                  local_48 = FUN_00017ee8(local_4c,*(undefined4 *)(iVar1 + 0x2182c))
                                  ;
                                  if (local_48 == 0) {
                                    uVar9 = 0x193b;
                                  }
                                  else {
                                    FUN_00017fec(local_4c);
                                    iVar1 = local_48;
                                    local_4c = 0;
                                    iVar6 = FUN_00018840(*(undefined4 *)(local_48 + 4),uVar4);
                                    if ((iVar6 != 0) &&
                                       (local_4c = *(int *)(iVar1 + 0xc), local_4c != 0)) {
                                      iVar6 = *(int *)(iVar1 + 8);
                                      FUN_00018934();
                                      FUN_00018934(iVar6);
                                      iVar1 = local_48;
                                      local_48 = iVar6;
                                      FUN_00017fec(iVar1);
                                    }
                                    if (local_4c == 0) {
                                      local_50 = FUN_0001ccc4(local_48,param_3);
                                    }
                                    else {
                                      local_50 = FUN_0001caa0(local_48,local_4c,param_3);
                                    }
                                    iVar8 = 0;
                                    FUN_000182bc(local_4c);
                                    local_4c = 0;
                                    if (local_50 != 0) {
                                      FUN_00017fec(local_48);
                                      local_48 = 0;
                                      FUN_00017fec(local_50);
                                      local_50 = 0;
                                      FUN_000182bc(local_44);
                                      local_44 = 0;
                                      FUN_000182bc(local_40);
                                      local_40 = 0;
                                      FUN_000182bc(local_3c);
                                      local_3c = 0;
                                      goto LAB_00021560;
                                    }
                                    uVar9 = 0x194a;
                                  }
                                }
                                FUN_000182bc(local_50);
                                local_50 = 0;
                                FUN_000182bc(local_4c);
                                local_4c = 0;
                                FUN_000182bc(local_48);
                                local_48 = 0;
                                FUN_000182bc(0);
                                FUN_000182bc(0);
                                FUN_000182bc(0);
                                iVar11 = FUN_00019fd0(*(undefined4 *)(iVar5 + 0x34),
                                                      **(undefined4 **)(iVar11 + DAT_00021b50));
                                if (iVar11 == 0) {
                                  uVar4 = 0x98;
LAB_000218e0:
                                  iVar6 = 0;
                                  iVar3 = iVar6;
                                  iVar8 = iVar6;
                                }
                                else {
                                  FUN_00019490(DAT_00021b58 + 0x2174c,uVar9,0x98,
                                               DAT_00021b54 + 0x21748);
                                  iVar1 = FUN_00018950(iVar5,&local_50,&local_48,&local_4c);
                                  iVar11 = DAT_00021b5c;
                                  if (iVar1 < 0) {
                                    uVar9 = 0x196d;
                                    uVar4 = 0x99;
                                    goto LAB_000218e0;
                                  }
                                  FUN_00018934(local_48);
                                  iVar8 = local_48;
                                  if (*(int *)(*(int *)(iVar11 + 0x219e4) + 0x14) ==
                                      *(int *)(&UNK_00021c0c + iVar11) &&
                                      *(int *)(*(int *)(iVar11 + 0x219e4) + 0x10) ==
                                      *(int *)(&UNK_00021c08 + iVar11)) {
                                    if (*(int *)(&UNK_00021c10 + iVar11) == 0) {
                                      iVar3 = FUN_00017f00(*(undefined4 *)(iVar11 + 0x21a58));
                                    }
                                    else {
                                      FUN_00018934();
                                      iVar3 = *(int *)(&UNK_00021c10 + iVar11);
                                    }
                                  }
                                  else {
                                    iVar3 = FUN_00018c58(*(undefined4 *)(iVar11 + 0x21a58),
                                                         &UNK_00021c08 + iVar11,
                                                         &UNK_00021c10 + iVar11);
                                  }
                                  if (iVar3 == 0) {
                                    uVar9 = 0x197b;
                                    iVar6 = 0;
                                  }
                                  else {
                                    iVar6 = FUN_00017ee8(iVar3,*(undefined4 *)
                                                                (&UNK_00021c60 + DAT_00021b60));
                                    if (iVar6 == 0) {
                                      uVar9 = 0x197d;
                                    }
                                    else {
                                      FUN_00017fec(iVar3);
                                      iVar11 = FUN_00018840(*(undefined4 *)(iVar6 + 4),uVar4);
                                      if ((iVar11 == 0) ||
                                         (iVar11 = *(int *)(iVar6 + 0xc), iVar11 == 0)) {
                                        iVar11 = 0;
                                        iVar1 = FUN_0001ccc4(iVar6,iVar8);
                                      }
                                      else {
                                        iVar3 = *(int *)(iVar6 + 8);
                                        FUN_00018934(iVar11);
                                        FUN_00018934(iVar3);
                                        FUN_00017fec(iVar6);
                                        iVar1 = FUN_0001caa0(iVar3,iVar11,iVar8);
                                        iVar6 = iVar3;
                                      }
                                      FUN_000182bc(iVar11);
                                      if (iVar1 != 0) {
                                        FUN_00017fec(iVar6);
                                        FUN_00017fec(iVar1);
                                        FUN_000182bc(local_50);
                                        local_50 = 0;
                                        FUN_000182bc(local_48);
                                        local_48 = 0;
                                        FUN_000182bc(local_4c);
                                        local_4c = 0;
                                        FUN_0001a300(*(undefined4 *)(iVar5 + 0x50),local_44,local_40
                                                     ,local_3c);
                                        goto LAB_00021560;
                                      }
                                      uVar9 = 0x198c;
                                      iVar3 = 0;
                                    }
                                  }
                                  uVar4 = 0x9a;
                                }
                                FUN_0001a300(*(undefined4 *)(iVar5 + 0x50),local_44,local_40,
                                             local_3c);
                                iVar5 = 0;
                                goto LAB_000218fc;
                              }
                              uVar9 = 0x1911;
                              iVar5 = 0;
                              iVar3 = 0;
                              iVar7 = local_50;
                            }
                          }
                        }
                      }
                    }
                    uVar4 = 0x95;
                    iVar6 = iVar7;
                    iVar8 = iVar7;
                    goto LAB_000218fc;
                  }
                  uVar9 = 0x18bd;
                  iVar5 = 0;
                  local_50 = 0;
                }
              }
            }
          }
        }
        iVar7 = 0;
        uVar4 = 0x94;
        iVar8 = iVar7;
      }
    }
  }
LAB_000218fc:
  FUN_000182bc(local_50);
  FUN_000182bc(local_4c);
  FUN_000182bc(local_48);
  FUN_000182bc(iVar3);
  iVar11 = 0;
  FUN_000182bc(iVar6);
  FUN_000182bc(iVar5);
  FUN_00019490(DAT_00021b68 + 0x2194c,uVar9,uVar4,DAT_00021b64 + 0x21948);
LAB_00021574:
  FUN_000182bc(iVar10);
  FUN_000182bc(iVar7);
  FUN_000182bc(iVar8);
  return iVar11;
}




/* ============================================
 * Function: FUN_0002393c
 * Address:  0x2393c
 * ============================================ */

undefined4 FUN_0002393c(undefined4 param_1,undefined4 param_2,int param_3)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  undefined4 uVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 uVar11;
  int iVar12;
  int iVar13;
  undefined4 local_4c;
  int local_30 [3];
  
  iVar13 = DAT_000242dc;
  iVar6 = DAT_000242d8;
  iVar1 = FUN_00017a90(param_1,*(undefined4 *)(DAT_000242d8 + 0x239f4),param_2);
  iVar13 = iVar13 + 0x23974;
  if (iVar1 < 0) {
    uVar7 = 0x55;
    iVar1 = 0;
    local_4c = 0xfed;
LAB_00024058:
    iVar4 = 0;
    iVar10 = 0;
    iVar6 = iVar10;
    iVar2 = iVar10;
    iVar5 = 0;
    iVar3 = iVar10;
    goto LAB_00023e78;
  }
  iVar2 = FUN_00017ee8(param_1,*(undefined4 *)(iVar6 + 0x23e04));
  if (iVar2 == 0) {
    local_4c = 0xff6;
    iVar6 = 0;
    iVar1 = 0;
    iVar4 = 0;
    iVar10 = 0;
    iVar3 = 0;
  }
  else {
    iVar3 = FUN_00017ee8(iVar2,*(undefined4 *)(iVar6 + 0x23e30));
    if (iVar3 != 0) {
      FUN_00017fec(iVar2);
      iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(iVar6 + 0x23cf8));
      if (iVar1 == 0) {
        local_4c = 0x1003;
        iVar6 = 0;
        iVar4 = 0;
        iVar10 = 0;
        iVar5 = 0;
      }
      else {
        iVar4 = FUN_00017ee8(iVar1,*(undefined4 *)(iVar6 + 0x23e34));
        if (iVar4 == 0) {
          local_4c = 0x1005;
          iVar6 = 0;
          iVar10 = 0;
          iVar5 = 0;
        }
        else {
          FUN_00017fec(iVar1);
          iVar5 = FUN_00017ee8(param_2,*(undefined4 *)(iVar6 + 0x23e38));
          if (iVar5 == 0) {
            local_4c = 0x1008;
            iVar6 = 0;
            iVar1 = 0;
            iVar10 = 0;
          }
          else {
            uVar7 = *(undefined4 *)(iVar13 + DAT_000242e0);
            iVar6 = FUN_00018840(*(undefined4 *)(iVar5 + 4),uVar7);
            if ((iVar6 == 0) || (iVar6 = *(int *)(iVar5 + 0xc), iVar6 == 0)) {
              iVar6 = 0;
              iVar1 = FUN_0001cbcc(iVar5);
            }
            else {
              iVar2 = *(int *)(iVar5 + 8);
              FUN_00018934(iVar6);
              FUN_00018934(iVar2);
              FUN_00017fec(iVar5);
              iVar1 = FUN_0001ccc4(iVar2,iVar6);
              iVar5 = iVar2;
            }
            FUN_000182bc(iVar6);
            if (iVar1 == 0) {
              local_4c = 0x1016;
              iVar6 = 0;
              iVar10 = 0;
            }
            else {
              FUN_00017fec(iVar5);
              iVar6 = FUN_00018840(*(undefined4 *)(iVar4 + 4),uVar7);
              iVar10 = iVar4;
              if (iVar6 == 0) {
                iVar2 = 0;
                iVar5 = 0;
              }
              else {
                iVar5 = *(int *)(iVar4 + 0xc);
                if (iVar5 == 0) {
                  iVar2 = 0;
                }
                else {
                  iVar10 = *(int *)(iVar4 + 8);
                  FUN_00018934(iVar5);
                  FUN_00018934(iVar10);
                  iVar2 = 1;
                  FUN_00017fec(iVar4);
                }
              }
              iVar12 = iVar2 + 2;
              uVar11 = *(undefined4 *)(iVar10 + 4);
              uVar8 = *(undefined4 *)(iVar13 + DAT_000242e4);
              iVar6 = FUN_00018840(uVar11,uVar8);
              iVar4 = iVar10;
              if (iVar6 == 0) {
                uVar9 = *(undefined4 *)(iVar13 + DAT_000242f8);
                iVar6 = FUN_00018840(uVar11,uVar9);
                if (((iVar6 == 0) && (iVar6 = PyType_IsSubtype(uVar11,uVar9), iVar6 == 0)) ||
                   ((*(uint *)(*(int *)(iVar10 + 8) + 8) & 0xffffff8d) != 0x80)) {
                  iVar6 = PyTuple_New(iVar12);
                  if (iVar6 == 0) {
                    local_4c = 0x1038;
                    iVar10 = 0;
                  }
                  else {
                    iVar2 = iVar6 + iVar2 * 4;
                    if (iVar5 != 0) {
                      *(int *)(iVar6 + 0xc) = iVar5;
                    }
                    *(int *)(iVar2 + 0xc) = iVar1;
                    FUN_00018934(param_3);
                    *(int *)(iVar2 + 0x10) = param_3;
                    iVar2 = FUN_00017e40(iVar10,iVar6,0);
                    if (iVar2 != 0) goto LAB_00023b10;
                    local_4c = 0x1043;
                    iVar1 = 0;
                    iVar5 = 0;
                    iVar10 = iVar2;
                  }
                }
                else {
                  local_30[0] = iVar1;
                  local_30[1] = param_3;
                  iVar2 = FUN_00017628(iVar10,local_30 + -iVar2,iVar12);
                  if (iVar2 != 0) goto LAB_00023b04;
                  local_4c = 0x1031;
                  iVar6 = 0;
                  iVar10 = iVar2;
                }
              }
              else {
                local_30[0] = iVar1;
                local_30[1] = param_3;
                iVar2 = FUN_0001b728(iVar10,local_30 + -iVar2,iVar12);
                if (iVar2 != 0) {
LAB_00023b04:
                  FUN_000182bc(iVar5);
                  iVar6 = iVar1;
LAB_00023b10:
                  iVar1 = DAT_000242e8;
                  FUN_00017fec(iVar6);
                  FUN_00017fec(iVar10);
                  iVar4 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x23ec4));
                  if (iVar4 == 0) {
                    local_4c = 0x1050;
                    iVar10 = 0;
                  }
                  else {
                    iVar6 = FUN_00017ee8(iVar4,*(undefined4 *)(iVar1 + 0x24008));
                    if (iVar6 != 0) {
                      FUN_00017fec(iVar4);
                      iVar1 = FUN_00018840(*(undefined4 *)(iVar3 + 4),uVar7);
                      iVar5 = iVar3;
                      if (iVar1 == 0) {
                        iVar4 = 0;
                        iVar10 = 0;
                      }
                      else {
                        iVar4 = *(int *)(iVar3 + 0xc);
                        if (iVar4 == 0) {
                          iVar10 = 0;
                        }
                        else {
                          iVar5 = *(int *)(iVar3 + 8);
                          iVar10 = 1;
                          FUN_00018934(iVar4);
                          FUN_00018934(iVar5);
                          FUN_00017fec(iVar3);
                        }
                      }
                      uVar11 = *(undefined4 *)(iVar5 + 4);
                      iVar1 = FUN_00018840(uVar11,uVar8);
                      iVar3 = iVar5;
                      if (iVar1 == 0) {
                        uVar8 = *(undefined4 *)(iVar13 + DAT_000242f8);
                        iVar1 = FUN_00018840(uVar11,uVar8);
                        if (((iVar1 == 0) && (iVar1 = PyType_IsSubtype(uVar11,uVar8), iVar1 == 0))
                           || ((*(uint *)(*(int *)(iVar5 + 8) + 8) & 0xffffff8d) != 0x80)) {
                          iVar1 = PyTuple_New(iVar10 + 2);
                          if (iVar1 == 0) {
                            local_4c = 0x1076;
                            iVar10 = 0;
                          }
                          else {
                            iVar10 = iVar1 + iVar10 * 4;
                            if (iVar4 != 0) {
                              *(int *)(iVar1 + 0xc) = iVar4;
                            }
                            *(int *)(iVar10 + 0xc) = iVar2;
                            *(int *)(iVar10 + 0x10) = iVar6;
                            iVar10 = FUN_00017e40(iVar5,iVar1,0);
                            if (iVar10 != 0) goto LAB_00023c0c;
                            local_4c = 0x1081;
                            iVar6 = 0;
                            iVar4 = 0;
                            iVar2 = 0;
                          }
                        }
                        else {
                          local_30[0] = iVar2;
                          local_30[1] = iVar6;
                          iVar10 = FUN_00017628(iVar5,local_30 + -iVar10,iVar10 + 2);
                          if (iVar10 != 0) goto LAB_00023bf8;
                          local_4c = 0x106e;
                          iVar1 = 0;
                        }
                      }
                      else {
                        local_30[0] = iVar2;
                        local_30[1] = iVar6;
                        iVar10 = FUN_0001b728(iVar5,local_30 + -iVar10,iVar10 + 2);
                        if (iVar10 != 0) {
LAB_00023bf8:
                          FUN_000182bc(iVar4);
                          FUN_00017fec(iVar2);
                          iVar1 = iVar6;
LAB_00023c0c:
                          iVar6 = DAT_000242ec;
                          FUN_00017fec(iVar1);
                          FUN_00017fec(iVar5);
                          iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar6 + 0x23fc4),iVar10);
                          if (iVar1 < 0) {
                            local_4c = 0x108e;
                            uVar7 = 0x56;
                            iVar4 = 0;
                            iVar3 = 0;
                            iVar6 = 0;
                            iVar1 = 0;
                            iVar2 = 0;
                            iVar5 = 0;
                            goto LAB_00023e78;
                          }
                          FUN_00017fec(iVar10);
                          if (*(int *)(*(int *)(iVar6 + 0x23e8c) + 0x14) ==
                              *(int *)(iVar6 + 0x2410c) &&
                              *(int *)(*(int *)(iVar6 + 0x23e8c) + 0x10) ==
                              *(int *)(iVar6 + 0x24108)) {
                            if (*(int *)(iVar6 + 0x24110) == 0) {
                              iVar10 = FUN_00017f00(*(undefined4 *)(iVar6 + 0x23f04));
                            }
                            else {
                              FUN_00018934();
                              iVar10 = *(int *)(iVar6 + 0x24110);
                            }
                          }
                          else {
                            iVar10 = FUN_00018c58(*(undefined4 *)(iVar6 + 0x23f04),iVar6 + 0x24108);
                          }
                          iVar6 = DAT_000242f0;
                          if (iVar10 == 0) {
                            local_4c = 0x1098;
                            iVar4 = 0;
                            iVar3 = 0;
                          }
                          else {
                            iVar3 = FUN_00017ee8(iVar10,*(undefined4 *)(DAT_000242f0 + 0x2417c));
                            if (iVar3 == 0) {
                              local_4c = 0x109a;
                              iVar4 = 0;
                            }
                            else {
                              FUN_00017fec(iVar10);
                              iVar10 = PyDict_New();
                              if (iVar10 == 0) {
                                local_4c = 0x109d;
                                iVar4 = 0;
                              }
                              else {
                                iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(iVar6 + 0x23d14));
                                if (iVar1 == 0) {
                                  local_4c = 0x109f;
                                  iVar4 = iVar1;
                                }
                                else {
                                  iVar2 = PyDict_SetItem(iVar10,*(undefined4 *)(iVar6 + 0x24180),
                                                         iVar1);
                                  if (iVar2 < 0) {
                                    iVar4 = 0;
                                    local_4c = 0x10a1;
                                    uVar7 = 0x59;
                                    iVar6 = iVar4;
                                    iVar2 = 0;
                                    iVar5 = iVar4;
                                    goto LAB_00023e78;
                                  }
                                  FUN_00017fec(iVar1);
                                  iVar1 = FUN_00017e40(iVar3,*(undefined4 *)(iVar6 + 0x23cd4),iVar10
                                                      );
                                  if (iVar1 != 0) {
                                    FUN_00017fec(iVar3);
                                    FUN_00017fec(iVar10);
                                    iVar2 = FUN_00017a90(param_1,*(undefined4 *)(iVar6 + 0x24140),
                                                         iVar1);
                                    if (-1 < iVar2) {
                                      FUN_00017fec(iVar1);
                                      iVar10 = FUN_00017ee8(param_1,*(undefined4 *)(iVar6 + 0x24140)
                                                           );
                                      if (iVar10 == 0) {
                                        local_4c = 0x10b1;
                                        iVar3 = 0;
                                      }
                                      else {
                                        iVar3 = FUN_00017ee8(iVar10,*(undefined4 *)(iVar6 + 0x24184)
                                                            );
                                        if (iVar3 == 0) {
                                          local_4c = 0x10b3;
                                        }
                                        else {
                                          FUN_00017fec(iVar10);
                                          iVar6 = FUN_00018840(*(undefined4 *)(iVar3 + 4),uVar7);
                                          if ((iVar6 == 0) ||
                                             (iVar6 = *(int *)(iVar3 + 0xc), iVar6 == 0)) {
                                            iVar6 = 0;
                                            iVar1 = FUN_0001cbcc(iVar3);
                                          }
                                          else {
                                            iVar2 = *(int *)(iVar3 + 8);
                                            FUN_00018934(iVar6);
                                            FUN_00018934(iVar2);
                                            FUN_00017fec(iVar3);
                                            iVar1 = FUN_0001ccc4(iVar2,iVar6);
                                            iVar3 = iVar2;
                                          }
                                          FUN_000182bc(iVar6);
                                          if (iVar1 != 0) {
                                            FUN_00017fec(iVar3);
                                            FUN_00017fec(iVar1);
                                            FUN_000182bc(0);
                                            uVar7 = *(undefined4 *)(iVar13 + DAT_000242f4);
                                            FUN_00018934(uVar7);
                                            return uVar7;
                                          }
                                          local_4c = 0x10c2;
                                          iVar10 = 0;
                                        }
                                      }
                                      iVar4 = 0;
                                      uVar7 = 0x5a;
                                      iVar6 = iVar4;
                                      iVar1 = iVar4;
                                      iVar2 = iVar4;
                                      iVar5 = iVar4;
                                      goto LAB_00023e78;
                                    }
                                    local_4c = 0x10a7;
                                    uVar7 = 0x59;
                                    goto LAB_00024058;
                                  }
                                  local_4c = 0x10a3;
                                  iVar4 = iVar1;
                                }
                              }
                            }
                          }
                          uVar7 = 0x59;
                          iVar6 = iVar4;
                          iVar1 = iVar4;
                          iVar2 = iVar4;
                          iVar5 = iVar4;
                          goto LAB_00023e78;
                        }
                        local_4c = 0x1064;
                        iVar1 = 0;
                      }
                      goto LAB_00023fa4;
                    }
                    local_4c = 0x1052;
                    iVar10 = iVar6;
                  }
                  uVar7 = 0x58;
                  iVar6 = iVar10;
                  iVar1 = iVar10;
                  iVar5 = iVar10;
                  goto LAB_00023e78;
                }
                local_4c = 0x1028;
                iVar6 = 0;
                iVar10 = iVar2;
              }
            }
          }
        }
      }
      uVar7 = 0x57;
      iVar2 = iVar10;
      goto LAB_00023e78;
    }
    local_4c = 0xff8;
    iVar6 = 0;
    iVar1 = 0;
    iVar4 = 0;
    iVar10 = 0;
  }
LAB_00023fa4:
  uVar7 = 0x56;
  iVar5 = iVar10;
LAB_00023e78:
  FUN_000182bc(iVar10);
  FUN_000182bc(iVar2);
  FUN_000182bc(iVar3);
  FUN_000182bc(iVar1);
  FUN_000182bc(iVar4);
  FUN_000182bc(iVar5);
  FUN_000182bc(iVar6);
  FUN_00019490(DAT_00024300 + 0x23ec8,local_4c,uVar7,DAT_000242fc + 0x23ec4);
  return 0;
}




/* ============================================
 * Function: FUN_00024304
 * Address:  0x24304
 * ============================================ */

undefined4 FUN_00024304(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_24;
  int local_20;
  int local_1c;
  
  iVar4 = *(int *)(param_2 + 8);
  local_24 = 0;
  local_20 = 0;
  local_1c = *(int *)(DAT_00024500 + 0x243d4);
  if (param_3 == 0) {
    if (iVar4 != 2) {
      if (iVar4 != 3) goto switchD_0002433c_default;
      local_1c = *(int *)(param_2 + 0x14);
    }
    local_20 = *(int *)(param_2 + 0x10);
    local_24 = *(int *)(param_2 + 0xc);
    goto LAB_00024498;
  }
  switch(iVar4) {
  case 0:
    goto LAB_0002436c;
  case 1:
    goto LAB_00024364;
  case 2:
    break;
  case 3:
    local_1c = *(int *)(param_2 + 0x14);
    break;
  default:
    goto switchD_0002433c_default;
  }
  local_20 = *(int *)(param_2 + 0x10);
LAB_00024364:
  local_24 = *(int *)(param_2 + 0xc);
LAB_0002436c:
  iVar1 = PyDict_Size(param_3);
  if (iVar4 == 1) {
LAB_000243b8:
    local_20 = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_00024508 + 0x24460),
                          *(undefined4 *)(*(int *)(DAT_00024508 + 0x24460) + 0xc));
    if (local_20 == 0) {
      FUN_00017adc(DAT_0002450c + 0x243fc,0,2,3,1);
      uVar3 = 0xfad;
      goto LAB_00024404;
    }
    iVar1 = iVar1 + -1;
LAB_00024424:
    if (iVar1 < 1) goto LAB_00024498;
    iVar2 = _PyDict_GetItem_KnownHash
                      (param_3,*(int *)(DAT_00024518 + 0x244d0),
                       *(undefined4 *)(*(int *)(DAT_00024518 + 0x244d0) + 0xc));
    if (iVar2 != 0) {
      iVar1 = iVar1 + -1;
      local_1c = iVar2;
      goto LAB_00024490;
    }
  }
  else {
    if (iVar4 == 2) goto LAB_00024424;
    if (iVar4 == 0) {
      local_24 = _PyDict_GetItem_KnownHash
                           (param_3,*(int *)(DAT_00024504 + 0x243e4),
                            *(undefined4 *)(*(int *)(DAT_00024504 + 0x243e4) + 0xc));
      if (local_24 == 0) {
switchD_0002433c_default:
        FUN_00017adc(DAT_00024524 + 0x244f8,0,2,3,*(undefined4 *)(param_2 + 8));
        uVar3 = 0xfc9;
        goto LAB_00024404;
      }
      iVar1 = iVar1 + -1;
      goto LAB_000243b8;
    }
LAB_00024490:
    if (iVar1 < 1) goto LAB_00024498;
  }
  iVar4 = FUN_0001a640(param_3,DAT_0002451c + 0x24b40,&local_24,iVar4,DAT_00024520 + 0x24470);
  if (iVar4 < 0) {
    uVar3 = 0xfb7;
LAB_00024404:
    FUN_00019490(DAT_00024514 + 0x2441c,uVar3,0x54,DAT_00024510 + 0x24418);
    return 0;
  }
LAB_00024498:
  uVar3 = FUN_0002393c(local_24,local_20,local_1c);
  return uVar3;
}




/* ============================================
 * Function: FUN_00024528
 * Address:  0x24528
 * ============================================ */

undefined4 FUN_00024528(undefined4 param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  int *piVar2;
  int iVar3;
  undefined4 uVar4;
  undefined4 uVar5;
  code *pcVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  
  iVar3 = DAT_000250e0;
  iVar10 = DAT_000250e4 + 0x24550;
  iVar1 = FUN_00017a90(param_1,*(undefined4 *)(DAT_000250e0 + 0x24588),param_2);
  if (iVar1 < 0) {
    uVar4 = 0x8e1;
    uVar5 = 0x13;
LAB_00024de4:
    iVar3 = 0;
LAB_00024dec:
    piVar2 = (int *)0x0;
  }
  else {
    iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar3 + 0x24584),param_3);
    if (iVar1 < 0) {
      uVar4 = 0x8ea;
      uVar5 = 0x14;
      goto LAB_00024de4;
    }
    uVar4 = *(undefined4 *)(iVar10 + DAT_000250e8);
    iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar3 + 0x245e0),uVar4);
    if (iVar1 < 0) {
      uVar4 = 0x8f3;
      uVar5 = 0x16;
      goto LAB_00024de4;
    }
    if (*(int *)(*(int *)(iVar3 + 0x247b4) + 0x14) == *(int *)(iVar3 + 0x24a4c) &&
        *(int *)(*(int *)(iVar3 + 0x247b4) + 0x10) == *(int *)(iVar3 + 0x24a48)) {
      if (*(int *)(iVar3 + 0x24a50) == 0) {
        iVar1 = FUN_00017f00(*(undefined4 *)(iVar3 + 0x24838));
      }
      else {
        FUN_00018934();
        iVar1 = *(int *)(iVar3 + 0x24a50);
      }
    }
    else {
      iVar1 = FUN_00018c58(*(undefined4 *)(iVar3 + 0x24838),(int *)(iVar3 + 0x24a48),iVar3 + 0x24a50
                          );
    }
    iVar9 = DAT_000250ec;
    if (iVar1 == 0) {
      uVar4 = 0x8fc;
      iVar3 = 0;
      piVar2 = (int *)0x0;
LAB_00024e1c:
      uVar5 = 0x17;
      iVar9 = iVar3;
      goto LAB_00024e20;
    }
    piVar2 = (int *)FUN_00017ee8(iVar1,*(undefined4 *)(DAT_000250ec + 0x24af0));
    if (piVar2 == (int *)0x0) {
      uVar4 = 0x8fe;
      iVar3 = 0;
      goto LAB_00024e1c;
    }
    FUN_00017fec(iVar1);
    iVar1 = PyDict_New();
    if (iVar1 == 0) {
      uVar4 = 0x901;
      iVar3 = 0;
      goto LAB_00024e1c;
    }
    iVar3 = PyDict_SetItem(iVar1,*(undefined4 *)(iVar9 + 0x24620),param_3);
    if (iVar3 < 0) {
      uVar4 = 0x903;
      uVar5 = 0x17;
LAB_00024e8c:
      iVar3 = 0;
      iVar9 = 0;
      goto LAB_00024e20;
    }
    iVar3 = FUN_00017e40(piVar2,*(undefined4 *)(iVar9 + 0x24630),iVar1);
    if (iVar3 == 0) {
      uVar4 = 0x904;
      goto LAB_00024e1c;
    }
    FUN_00017fec(piVar2);
    FUN_00017fec(iVar1);
    iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar9 + 0x24af4),iVar3);
    if (iVar1 < 0) {
      uVar4 = 0x908;
      uVar5 = 0x17;
      goto LAB_00024dec;
    }
    FUN_00017fec(iVar3);
    if (*(int *)(*(int *)(iVar9 + 0x24850) + 0x14) == *(int *)(iVar9 + 0x24b00) &&
        *(int *)(*(int *)(iVar9 + 0x24850) + 0x10) == *(int *)(iVar9 + 0x24afc)) {
      if (*(int *)(iVar9 + 0x24b04) == 0) {
        iVar1 = FUN_00017f00(*(undefined4 *)(iVar9 + 0x248d8));
      }
      else {
        FUN_00018934();
        iVar1 = *(int *)(iVar9 + 0x24b04);
      }
    }
    else {
      iVar1 = FUN_00018c58(*(undefined4 *)(iVar9 + 0x248d8),iVar9 + 0x24afc);
    }
    if (iVar1 == 0) {
      uVar4 = 0x912;
      iVar3 = 0;
      iVar9 = 0;
      piVar2 = (int *)0x0;
LAB_00024ec4:
      uVar5 = 0x19;
      goto LAB_00024e20;
    }
    piVar2 = (int *)FUN_00017ee8(iVar1,*(undefined4 *)(DAT_000250f0 + 0x24bcc));
    if (piVar2 == (int *)0x0) {
      uVar4 = 0x914;
      iVar3 = 0;
      iVar9 = 0;
      goto LAB_00024ec4;
    }
    FUN_00017fec(iVar1);
    uVar5 = *(undefined4 *)(iVar10 + DAT_000250f4);
    iVar3 = FUN_00018840(*(undefined4 *)((int)piVar2 + 4),uVar5);
    if ((iVar3 == 0) || (iVar1 = *(int *)((int)piVar2 + 0xc), iVar1 == 0)) {
      iVar1 = 0;
      iVar3 = FUN_0001cbcc(piVar2);
    }
    else {
      iVar9 = *(int *)((int)piVar2 + 8);
      FUN_00018934(iVar1);
      FUN_00018934(iVar9);
      FUN_00017fec(piVar2);
      iVar3 = FUN_0001ccc4(iVar9,iVar1);
      piVar2 = (int *)iVar9;
    }
    FUN_000182bc(iVar1);
    if (iVar3 == 0) {
      uVar4 = 0x923;
      iVar9 = 0;
      iVar1 = 0;
      goto LAB_00024ec4;
    }
    FUN_00017fec(piVar2);
    uVar7 = *(undefined4 *)(iVar3 + 4);
    iVar1 = FUN_00018840(uVar7,*(undefined4 *)(iVar10 + DAT_000250f8));
    if ((iVar1 != 0) ||
       (iVar9 = FUN_00018840(uVar7,*(undefined4 *)(iVar10 + DAT_000250fc)), iVar9 != 0)) {
      iVar9 = *(int *)(iVar3 + 8);
      if (iVar9 != 2) {
        if (iVar9 < 3) {
          if (-1 < iVar9) {
            FUN_00017bb4();
          }
        }
        else {
          FUN_0001ae80();
        }
        uVar4 = 0x92c;
        uVar5 = 0x19;
        goto LAB_00024dec;
      }
      piVar2 = *(int **)(iVar3 + 0xc);
      if (iVar1 == 0) {
        iVar1 = piVar2[1];
        piVar2 = (int *)*piVar2;
      }
      else {
        iVar1 = *(int *)(iVar3 + 0x10);
      }
      FUN_00018934(piVar2);
      FUN_00018934(iVar1);
      iVar9 = iVar3;
LAB_00024824:
      iVar3 = DAT_00025100;
      FUN_00017fec(iVar9);
      iVar9 = FUN_00017a90(param_1,*(undefined4 *)(iVar3 + 0x24ce4),piVar2);
      if (iVar9 < 0) {
        uVar4 = 0x954;
        uVar5 = 0x19;
        goto LAB_00024e8c;
      }
      FUN_00017fec(piVar2);
      iVar9 = FUN_00017a90(param_1,*(undefined4 *)(iVar3 + 0x24bd8),iVar1);
      if (iVar9 < 0) {
        iVar3 = 0;
        uVar4 = 0x956;
        uVar5 = 0x19;
        piVar2 = (int *)0x0;
        iVar9 = iVar3;
        goto LAB_00024e20;
      }
      FUN_00017fec(iVar1);
      iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar3 + 0x24be0),uVar4);
      if (iVar1 < 0) {
        uVar4 = 0x960;
        uVar5 = 0x1a;
        iVar3 = 0;
LAB_00024f44:
        piVar2 = (int *)0x0;
        iVar9 = 0;
        iVar1 = (int)piVar2;
      }
      else {
        iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(iVar3 + 0x24ce4));
        if (iVar1 == 0) {
          uVar4 = 0x969;
          iVar3 = 0;
          piVar2 = (int *)0x0;
        }
        else {
          piVar2 = (int *)FUN_00017ee8(iVar1,*(undefined4 *)(iVar3 + 0x24d64));
          if (piVar2 == (int *)0x0) {
            uVar4 = 0x96b;
            iVar3 = 0;
          }
          else {
            FUN_00017fec(iVar1);
            iVar1 = FUN_00018840(*(undefined4 *)((int)piVar2 + 4),uVar5);
            if ((iVar1 == 0) || (iVar1 = *(int *)((int)piVar2 + 0xc), iVar1 == 0)) {
              iVar1 = 0;
              iVar3 = FUN_0001ccc4(piVar2,*(undefined4 *)(DAT_0002511c + 0x2526c));
            }
            else {
              iVar9 = *(int *)((int)piVar2 + 8);
              FUN_00018934(iVar1);
              FUN_00018934(iVar9);
              FUN_00017fec(piVar2);
              iVar3 = FUN_0001caa0(iVar9,iVar1,*(undefined4 *)(iVar3 + 0x24d68));
              piVar2 = (int *)iVar9;
            }
            FUN_000182bc(iVar1);
            iVar1 = DAT_00025104;
            if (iVar3 != 0) {
              FUN_00017fec(piVar2);
              iVar9 = FUN_00017a90(param_1,*(undefined4 *)(iVar1 + 0x24dd0),iVar3);
              if (-1 < iVar9) {
                FUN_00017fec(iVar3);
                if (*(int *)(*(int *)(iVar1 + 0x24b98) + 0x14) == *(int *)(iVar1 + 0x24e60) &&
                    *(int *)(*(int *)(iVar1 + 0x24b98) + 0x10) == *(int *)(iVar1 + 0x24e5c)) {
                  if (*(int *)(iVar1 + 0x24e64) == 0) {
                    piVar2 = (int *)FUN_00017f00(*(undefined4 *)(iVar1 + 0x24c10));
                  }
                  else {
                    FUN_00018934();
                    piVar2 = *(int **)(iVar1 + 0x24e64);
                  }
                }
                else {
                  piVar2 = (int *)FUN_00018c58(*(undefined4 *)(iVar1 + 0x24c10),
                                               (int *)(iVar1 + 0x24e5c),iVar1 + 0x24e64);
                }
                if (piVar2 == (int *)0x0) {
                  uVar4 = 0x987;
                  iVar3 = 0;
                  iVar1 = 0;
                }
                else {
                  iVar1 = FUN_00017ee8(piVar2,*(undefined4 *)(DAT_00025108 + 0x24ecc));
                  if (iVar1 == 0) {
                    uVar4 = 0x989;
                    iVar3 = 0;
                  }
                  else {
                    FUN_00017fec(piVar2);
                    iVar3 = FUN_00018840(*(undefined4 *)(iVar1 + 4),uVar5);
                    if ((iVar3 == 0) || (iVar9 = *(int *)(iVar1 + 0xc), iVar9 == 0)) {
                      iVar9 = 0;
                      iVar3 = FUN_0001cbcc(iVar1);
                    }
                    else {
                      iVar8 = *(int *)(iVar1 + 8);
                      FUN_00018934(iVar9);
                      FUN_00018934(iVar8);
                      FUN_00017fec(iVar1);
                      iVar3 = FUN_0001ccc4(iVar8,iVar9);
                      iVar1 = iVar8;
                    }
                    FUN_000182bc(iVar9);
                    iVar9 = DAT_0002510c;
                    if (iVar3 != 0) {
                      FUN_00017fec(iVar1);
                      iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar9 + 0x24e88),iVar3);
                      if (iVar1 < 0) {
                        uVar4 = 0x99b;
                        uVar5 = 0x1d;
                      }
                      else {
                        FUN_00017fec(iVar3);
                        iVar3 = FUN_00017a90(param_1,*(undefined4 *)(iVar9 + 0x24ed0),uVar4);
                        if (iVar3 < 0) {
                          iVar3 = 0;
                          uVar4 = 0x9a5;
                          uVar5 = 0x1e;
                          piVar2 = (int *)0x0;
                          iVar1 = 0;
                          iVar9 = 0;
                          goto LAB_00024e20;
                        }
                        iVar3 = PyDict_New();
                        if (iVar3 == 0) {
                          uVar4 = 0x9ae;
                          uVar5 = 0x20;
                          piVar2 = (int *)0x0;
                          iVar1 = 0;
                          iVar9 = 0;
                          goto LAB_00024e20;
                        }
                        iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar9 + 0x24e94),iVar3);
                        if (iVar1 < 0) {
                          uVar4 = 0x9b0;
                          uVar5 = 0x20;
                        }
                        else {
                          FUN_00017fec(iVar3);
                          iVar3 = PyDict_New();
                          if (iVar3 == 0) {
                            uVar4 = 0x9ba;
                            uVar5 = 0x22;
                            piVar2 = (int *)0x0;
                            iVar1 = 0;
                            iVar9 = 0;
                            goto LAB_00024e20;
                          }
                          iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar9 + 0x24ee8),iVar3);
                          if (iVar1 < 0) {
                            uVar4 = 0x9bc;
                            uVar5 = 0x22;
                          }
                          else {
                            FUN_00017fec(iVar3);
                            iVar3 = PyDict_New();
                            if (iVar3 == 0) {
                              uVar4 = 0x9c6;
                              uVar5 = 0x23;
                              piVar2 = (int *)0x0;
                              iVar1 = 0;
                              iVar9 = 0;
                              goto LAB_00024e20;
                            }
                            iVar1 = FUN_00017a90(param_1,*(undefined4 *)(iVar9 + 0x24e98),iVar3);
                            if (-1 < iVar1) {
                              FUN_00017fec(iVar3);
                              iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(iVar9 + 0x24f28));
                              iVar3 = DAT_00025110;
                              if (iVar1 == 0) {
                                uVar4 = 0x9d2;
                                piVar2 = (int *)0x0;
                              }
                              else {
                                piVar2 = (int *)FUN_00017ee8(iVar1,*(undefined4 *)
                                                                    (DAT_00025110 + 0x25034));
                                if (piVar2 == (int *)0x0) {
                                  uVar4 = 0x9d4;
                                }
                                else {
                                  FUN_00017fec(iVar1);
                                  if (*(int *)(*(int *)(iVar3 + 0x24d60) + 0x14) ==
                                      *(int *)(iVar3 + 0x25040) &&
                                      *(int *)(*(int *)(iVar3 + 0x24d60) + 0x10) ==
                                      *(int *)(iVar3 + 0x2503c)) {
                                    if (*(int *)(iVar3 + 0x25044) == 0) {
                                      iVar3 = FUN_00017f00(*(undefined4 *)(iVar3 + 0x24df8));
                                    }
                                    else {
                                      FUN_00018934();
                                      iVar3 = *(int *)(iVar3 + 0x25044);
                                    }
                                  }
                                  else {
                                    iVar3 = FUN_00018c58(*(undefined4 *)(iVar3 + 0x24df8),
                                                         iVar3 + 0x2503c,iVar3 + 0x25044);
                                  }
                                  if (iVar3 == 0) {
                                    uVar4 = 0x9d7;
                                    iVar1 = 0;
                                  }
                                  else {
                                    iVar1 = FUN_00018840(*(undefined4 *)((int)piVar2 + 4),uVar5);
                                    if ((iVar1 == 0) ||
                                       (iVar1 = *(int *)((int)piVar2 + 0xc), iVar1 == 0)) {
                                      iVar1 = 0;
                                      iVar9 = FUN_0001ccc4(piVar2,iVar3);
                                    }
                                    else {
                                      iVar8 = *(int *)((int)piVar2 + 8);
                                      FUN_00018934(iVar1);
                                      FUN_00018934(iVar8);
                                      FUN_00017fec(piVar2);
                                      iVar9 = FUN_0001caa0(iVar8,iVar1,iVar3);
                                      piVar2 = (int *)iVar8;
                                    }
                                    FUN_000182bc(iVar1);
                                    FUN_00017fec(iVar3);
                                    if (iVar9 != 0) {
                                      FUN_00017fec(piVar2);
                                      FUN_00017fec(iVar9);
                                      piVar2 = (int *)FUN_00017ee8(param_2,*(undefined4 *)
                                                                            ((int)&DAT_00025120 +
                                                                            DAT_00025114));
                                      if (piVar2 == (int *)0x0) {
                                        uVar4 = 0x9f2;
                                        iVar3 = 0;
                                      }
                                      else {
                                        iVar3 = FUN_00018840(*(undefined4 *)((int)piVar2 + 4),
                                                             *(undefined4 *)(iVar10 + DAT_000250f4))
                                        ;
                                        if ((iVar3 == 0) ||
                                           (iVar1 = *(int *)((int)piVar2 + 0xc), iVar1 == 0)) {
                                          iVar1 = 0;
                                          iVar3 = FUN_0001cbcc(piVar2);
                                        }
                                        else {
                                          iVar9 = *(int *)((int)piVar2 + 8);
                                          FUN_00018934(iVar1);
                                          FUN_00018934(iVar9);
                                          FUN_00017fec(piVar2);
                                          iVar3 = FUN_0001ccc4(iVar9,iVar1);
                                          piVar2 = (int *)iVar9;
                                        }
                                        FUN_000182bc(iVar1);
                                        if (iVar3 != 0) {
                                          FUN_00017fec(piVar2);
                                          iVar1 = FUN_00017a90(param_1,*(undefined4 *)
                                                                        (DAT_00025118 + 0x251b0),
                                                               iVar3);
                                          if (-1 < iVar1) {
                                            FUN_00017fec(iVar3);
                                            uVar4 = *(undefined4 *)(iVar10 + DAT_000250e8);
                                            FUN_00018934(uVar4);
                                            return uVar4;
                                          }
                                          uVar4 = 0xa03;
                                          uVar5 = 0x25;
                                          goto LAB_00024f44;
                                        }
                                        uVar4 = 0xa00;
                                      }
                                      uVar5 = 0x25;
                                      iVar9 = iVar3;
                                      iVar1 = iVar3;
                                      goto LAB_00024e20;
                                    }
                                    uVar4 = 0x9e6;
                                    iVar1 = 0;
                                  }
                                }
                              }
                              iVar3 = 0;
                              uVar5 = 0x24;
                              iVar9 = iVar3;
                              goto LAB_00024e20;
                            }
                            uVar4 = 0x9c8;
                            uVar5 = 0x23;
                          }
                        }
                      }
                      goto LAB_00024dec;
                    }
                    uVar4 = 0x998;
                    piVar2 = (int *)0x0;
                  }
                }
                uVar5 = 0x1d;
                iVar9 = iVar3;
                goto LAB_00024e20;
              }
              uVar4 = 0x97d;
              uVar5 = 0x1b;
              goto LAB_00024f44;
            }
            uVar4 = 0x97a;
            iVar1 = 0;
          }
        }
        uVar5 = 0x1b;
        iVar9 = iVar3;
      }
      goto LAB_00024e20;
    }
    iVar9 = PyObject_GetIter(iVar3);
    if (iVar9 == 0) {
      uVar4 = 0x941;
      piVar2 = (int *)0x0;
      iVar1 = 0;
      goto LAB_00024ec4;
    }
    FUN_00017fec(iVar3);
    pcVar6 = *(code **)(*(int *)(iVar9 + 4) + 0x70);
    piVar2 = (int *)(*pcVar6)(iVar9);
    uVar7 = 0;
    if (piVar2 != (int *)0x0) {
      iVar1 = (*pcVar6)(iVar9);
      if (iVar1 != 0) {
        (*pcVar6)(iVar9);
        iVar3 = FUN_0001aeb0();
        if (iVar3 < 0) {
          uVar4 = 0x949;
          uVar5 = 0x19;
          iVar3 = 0;
          goto LAB_00024e20;
        }
        goto LAB_00024824;
      }
      uVar7 = 1;
    }
    FUN_00017fec(iVar9);
    iVar3 = FUN_00019bf8();
    if (iVar3 == 0) {
      FUN_00017bb4(uVar7);
    }
    iVar3 = 0;
    uVar5 = 0x19;
    uVar4 = 0x951;
  }
  iVar9 = 0;
  iVar1 = 0;
LAB_00024e20:
  FUN_000182bc(iVar1);
  FUN_000182bc(piVar2);
  FUN_000182bc(iVar3);
  FUN_000182bc(iVar9);
  FUN_00019490(DAT_00025124 + 0x24e5c,uVar4,uVar5,DAT_00025120 + 0x24e58);
  return 0;
}




/* ============================================
 * Function: FUN_00025128
 * Address:  0x25128
 * ============================================ */

undefined4 FUN_00025128(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  int iVar4;
  int local_24;
  int local_20;
  int local_1c;
  
  iVar4 = *(int *)(param_2 + 8);
  local_24 = 0;
  local_20 = 0;
  local_1c = *(int *)(DAT_00025324 + 0x251b0);
  if (param_3 == 0) {
    if (iVar4 != 2) {
      if (iVar4 != 3) goto switchD_00025160_default;
      local_1c = *(int *)(param_2 + 0x14);
    }
    local_20 = *(int *)(param_2 + 0x10);
    local_24 = *(int *)(param_2 + 0xc);
    goto LAB_000252bc;
  }
  switch(iVar4) {
  case 0:
    goto LAB_00025190;
  case 1:
    goto LAB_00025188;
  case 2:
    break;
  case 3:
    local_1c = *(int *)(param_2 + 0x14);
    break;
  default:
    goto switchD_00025160_default;
  }
  local_20 = *(int *)(param_2 + 0x10);
LAB_00025188:
  local_24 = *(int *)(param_2 + 0xc);
LAB_00025190:
  iVar1 = PyDict_Size(param_3);
  if (iVar4 == 1) {
LAB_000251dc:
    local_20 = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_0002532c + 0x2522c),
                          *(undefined4 *)(*(int *)(DAT_0002532c + 0x2522c) + 0xc));
    if (local_20 == 0) {
      FUN_00017adc(DAT_00025330 + 0x25220,0,2,3,1);
      uVar3 = 0x8a4;
      goto LAB_00025228;
    }
    iVar1 = iVar1 + -1;
LAB_00025248:
    if (iVar1 < 1) goto LAB_000252bc;
    iVar2 = _PyDict_GetItem_KnownHash
                      (param_3,*(int *)(DAT_0002533c + 0x2529c),
                       *(undefined4 *)(*(int *)(DAT_0002533c + 0x2529c) + 0xc));
    if (iVar2 != 0) {
      iVar1 = iVar1 + -1;
      local_1c = iVar2;
      goto LAB_000252b4;
    }
  }
  else {
    if (iVar4 == 2) goto LAB_00025248;
    if (iVar4 == 0) {
      local_24 = _PyDict_GetItem_KnownHash
                           (param_3,*(int *)(DAT_00025328 + 0x25208),
                            *(undefined4 *)(*(int *)(DAT_00025328 + 0x25208) + 0xc));
      if (local_24 == 0) {
switchD_00025160_default:
        FUN_00017adc(DAT_00025348 + 0x2531c,0,2,3,*(undefined4 *)(param_2 + 8));
        uVar3 = 0x8c0;
        goto LAB_00025228;
      }
      iVar1 = iVar1 + -1;
      goto LAB_000251dc;
    }
LAB_000252b4:
    if (iVar1 < 1) goto LAB_000252bc;
  }
  iVar4 = FUN_0001a640(param_3,DAT_00025340 + 0x25974,&local_24,iVar4,DAT_00025344 + 0x25294);
  if (iVar4 < 0) {
    uVar3 = 0x8ae;
LAB_00025228:
    FUN_00019490(DAT_00025338 + 0x25240,uVar3,0x12,DAT_00025334 + 0x2523c);
    return 0;
  }
LAB_000252bc:
  uVar3 = FUN_00024528(local_24,local_20,local_1c);
  return uVar3;
}




/* ============================================
 * Function: FUN_0002534c
 * Address:  0x2534c
 * ============================================ */

uint FUN_0002534c(undefined4 param_1,undefined4 param_2)

{
  uint uVar1;
  
  uVar1 = PySequence_Contains(param_2,param_1);
  if (-1 < (int)uVar1) {
    uVar1 = (uint)(uVar1 == 1);
  }
  return uVar1;
}




/* ============================================
 * Function: FUN_00025374
 * Address:  0x25374
 * ============================================ */

undefined4 FUN_00025374(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  undefined4 uVar7;
  
  iVar3 = DAT_00025534;
  iVar6 = DAT_00025538 + 0x25394;
  iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_00025534 + 0x2575c),param_3,param_4,param_1,
                       param_2,param_3);
  if (iVar1 == 0) {
    uVar4 = 0x2c8f;
    uVar7 = 0x120;
    iVar3 = 0;
    iVar2 = 0;
  }
  else {
    iVar2 = FUN_0002534c(param_2,iVar1);
    if (iVar2 < 0) {
      iVar3 = 0;
      uVar4 = 0x2c91;
      uVar7 = 0x120;
      iVar2 = iVar3;
    }
    else {
      FUN_00017fec(iVar1);
      if (iVar2 == 0) {
LAB_0002546c:
        uVar4 = *(undefined4 *)(iVar6 + DAT_00025540);
        FUN_00018934(uVar4);
        return uVar4;
      }
      iVar2 = FUN_00017ee8(param_1,*(undefined4 *)(iVar3 + 0x2575c));
      if (iVar2 == 0) {
        uVar4 = 0x2c9d;
        iVar3 = 0;
      }
      else {
        iVar3 = FUN_00017ee8(iVar2,*(undefined4 *)(iVar3 + 0x2578c));
        if (iVar3 == 0) {
          uVar4 = 0x2c9f;
        }
        else {
          FUN_00017fec(iVar2);
          iVar1 = FUN_00018840(*(undefined4 *)(iVar3 + 4),*(undefined4 *)(iVar6 + DAT_0002553c));
          if ((iVar1 == 0) || (iVar1 = *(int *)(iVar3 + 0xc), iVar1 == 0)) {
            iVar2 = FUN_0001ccc4(iVar3,param_2);
            iVar1 = 0;
          }
          else {
            iVar5 = *(int *)(iVar3 + 8);
            FUN_00018934(iVar1);
            FUN_00018934(iVar5);
            FUN_00017fec(iVar3);
            iVar2 = FUN_0001caa0(iVar5,iVar1,param_2);
            iVar3 = iVar5;
          }
          FUN_000182bc(iVar1);
          if (iVar2 != 0) {
            FUN_00017fec(iVar3);
            FUN_00017fec(iVar2);
            goto LAB_0002546c;
          }
          uVar4 = 0x2cae;
          iVar2 = 0;
        }
      }
      iVar1 = 0;
      uVar7 = 0x121;
    }
  }
  FUN_000182bc(iVar1);
  FUN_000182bc(iVar2);
  FUN_000182bc(iVar3);
  FUN_00019490(DAT_00025548 + 0x254ec,uVar4,uVar7,DAT_00025544 + 0x254e8);
  return 0;
}




/* ============================================
 * Function: FUN_0002554c
 * Address:  0x2554c
 * ============================================ */

undefined4 FUN_0002554c(undefined4 param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  int local_20;
  int local_1c;
  
  iVar3 = *(int *)(param_2 + 8);
  local_20 = 0;
  local_1c = 0;
  if (param_3 == 0) {
    if (iVar3 == 2) {
      local_20 = *(int *)(param_2 + 0xc);
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_000256a4;
    }
LAB_000256b4:
    FUN_00017adc(DAT_000256f8 + 0x256d0,1,2,2,*(undefined4 *)(param_2 + 8));
    uVar2 = 0x2c6e;
    goto LAB_0002566c;
  }
  if (iVar3 == 1) {
LAB_000255f0:
    local_20 = *(int *)(param_2 + 0xc);
  }
  else {
    if (iVar3 == 2) {
      local_1c = *(int *)(param_2 + 0x10);
      goto LAB_000255f0;
    }
    if (iVar3 != 0) goto LAB_000256b4;
  }
  iVar1 = PyDict_Size(param_3);
  if (iVar3 == 0) {
    local_20 = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_000256e4 + 0x25650),
                          *(undefined4 *)(*(int *)(DAT_000256e4 + 0x25650) + 0xc));
    if (local_20 == 0) goto LAB_000256b4;
    iVar1 = iVar1 + -1;
LAB_00025624:
    local_1c = _PyDict_GetItem_KnownHash
                         (param_3,*(int *)(DAT_000256e8 + 0x2578c),
                          *(undefined4 *)(*(int *)(DAT_000256e8 + 0x2578c) + 0xc));
    if (local_1c == 0) {
      FUN_00017adc(DAT_000256ec + 0x25664,1,2,2,1);
      uVar2 = 0x2c5d;
      goto LAB_0002566c;
    }
    iVar1 = iVar1 + -1;
  }
  else if (iVar3 == 1) goto LAB_00025624;
  if ((iVar1 < 1) ||
     (iVar3 = FUN_0001a640(param_3,DAT_000256dc + 0x25cb8,&local_20,iVar3,DAT_000256e0 + 0x255c8),
     -1 < iVar3)) {
LAB_000256a4:
    uVar2 = FUN_00025374(local_20,local_1c);
    return uVar2;
  }
  uVar2 = 0x2c61;
LAB_0002566c:
  FUN_00019490(DAT_000256f4 + 0x25684,uVar2,0x11f,DAT_000256f0 + 0x25680);
  return 0;
}




/* ============================================
 * Function: FUN_000256fc
 * Address:  0x256fc
 * ============================================ */

undefined4 FUN_000256fc(int param_1,int param_2,undefined4 param_3)

{
  int iVar1;
  undefined4 uVar2;
  int iVar3;
  undefined4 uVar4;
  
  iVar3 = DAT_000257d8 + 0x25710;
  if (param_1 != param_2) {
    uVar4 = *(undefined4 *)(param_1 + 4);
    uVar2 = *(undefined4 *)(iVar3 + DAT_000257e0);
    iVar1 = FUN_00018840(uVar4,uVar2,param_3,uVar2,param_1,uVar2,param_3);
    if (iVar1 == 0) {
      iVar1 = FUN_00018840(uVar4,*(undefined4 *)(iVar3 + DAT_000257e8));
      if (iVar1 == 0) {
        uVar2 = PyObject_RichCompare(param_1,param_2,2);
        return uVar2;
      }
      iVar1 = DAT_000257e4;
      if (*(double *)(param_1 + 8) != DAT_000257d0) goto LAB_00025714;
    }
    else {
      iVar1 = DAT_000257e4;
      if ((*(int *)(param_1 + 8) != 1) || (*(short *)(param_1 + 0xc) != 0xa0)) goto LAB_00025714;
    }
  }
  iVar1 = DAT_000257dc;
LAB_00025714:
  uVar2 = *(undefined4 *)(iVar3 + iVar1);
  FUN_00018934(uVar2);
  return uVar2;
}




/* ============================================
 * Function: FUN_000257ec
 * Address:  0x257ec
 * ============================================ */

undefined4 FUN_000257ec(undefined4 param_1)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  undefined4 uVar6;
  undefined4 uVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  int iVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  int iVar16;
  undefined4 uVar17;
  int iVar18;
  int local_ac;
  int local_a8;
  int local_a4;
  int local_a0;
  int local_9c;
  int local_98;
  int local_94;
  int local_90;
  int local_88;
  int local_84;
  int local_80;
  int local_68;
  int local_64;
  int local_60;
  undefined4 local_5c;
  undefined4 local_58;
  undefined4 local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  int local_34 [4];
  
  iVar3 = DAT_00026560;
  local_68 = 0;
  local_64 = 0;
  local_60 = 0;
  local_5c = 0;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_00026560 + 0x25cb0));
  iVar18 = DAT_00026564 + 0x2584c;
  if (iVar1 == 0) {
    uVar15 = 0xa60;
    local_84 = 0;
  }
  else {
    local_60 = FUN_00017ee8(iVar1,*(undefined4 *)(iVar3 + 0x25d30));
    if (local_60 == 0) {
      uVar15 = 0xa62;
      local_84 = 0;
    }
    else {
      FUN_00017fec(iVar1);
      iVar1 = local_60;
      uVar6 = *(undefined4 *)(iVar18 + DAT_000265f0);
      iVar2 = FUN_00018840(*(undefined4 *)(local_60 + 4),uVar6);
      if ((iVar2 == 0) || (iVar2 = *(int *)(iVar1 + 0xc), iVar2 == 0)) {
        iVar2 = 0;
        local_64 = FUN_0001ccc4(iVar1,*(undefined4 *)(DAT_00026588 + 0x262a4));
      }
      else {
        iVar9 = *(int *)(iVar1 + 8);
        FUN_00018934(iVar2);
        FUN_00018934(iVar9);
        iVar1 = local_60;
        local_60 = iVar9;
        FUN_00017fec(iVar1);
        local_64 = FUN_0001caa0(local_60,iVar2,*(undefined4 *)(iVar3 + 0x25d60));
      }
      FUN_000182bc(iVar2);
      if (local_64 != 0) {
        FUN_00017fec(local_60);
        local_ac = local_64;
        iVar1 = DAT_00026568;
        local_60 = 0;
        local_64 = 0;
        iVar3 = _PyThreadState_UncheckedGet();
        FUN_00019f30(iVar3,&local_5c,&local_58,&local_54);
        if (*(int *)(*(int *)(iVar1 + 0x25b80) + 0x14) == *(int *)(iVar1 + 0x25e78) &&
            *(int *)(*(int *)(iVar1 + 0x25b80) + 0x10) == *(int *)(iVar1 + 0x25e74)) {
          if (*(int *)(iVar1 + 0x25e7c) == 0) {
            local_60 = FUN_00017f00(*(undefined4 *)(iVar1 + 0x25bfc));
          }
          else {
            FUN_00018934();
            local_60 = *(int *)(iVar1 + 0x25e7c);
          }
        }
        else {
          local_60 = FUN_00018c58(*(undefined4 *)(iVar1 + 0x25bfc),(int *)(iVar1 + 0x25e74),
                                  iVar1 + 0x25e7c);
        }
        if (local_60 == 0) {
          uVar15 = 0xa8e;
          iVar1 = 0;
          local_88 = 0;
LAB_00025ee4:
          uVar17 = 0x2a;
          iVar2 = local_88;
LAB_00025ee8:
          iVar9 = 0;
          FUN_000182bc(local_64);
          local_64 = 0;
          FUN_000182bc(iVar1);
          FUN_000182bc(local_60);
          local_60 = 0;
          FUN_000182bc(iVar2);
          FUN_000182bc(local_50);
          local_50 = 0;
          FUN_00019490(DAT_00026598 + 0x25f38,uVar15,uVar17,DAT_00026594 + 0x25f34);
          iVar2 = FUN_00018950(iVar3,&local_64,&local_60,&local_50);
          iVar1 = DAT_0002659c;
          if (iVar2 < 0) {
            uVar15 = 0xb03;
            uVar17 = 0x2c;
            iVar2 = 0;
          }
          else {
            if (*(int *)(*(int *)(DAT_0002659c + 0x261d0) + 0x14) ==
                *(int *)(DAT_0002659c + 0x264e8) &&
                *(int *)(*(int *)(DAT_0002659c + 0x261d0) + 0x10) ==
                *(int *)(DAT_0002659c + 0x264e4)) {
              if (*(int *)(DAT_0002659c + 0x264ec) == 0) {
                iVar2 = FUN_00017f00(*(undefined4 *)(DAT_0002659c + 0x26244));
              }
              else {
                FUN_00018934();
                iVar2 = *(int *)(iVar1 + 0x264ec);
              }
            }
            else {
              iVar2 = FUN_00018c58(*(undefined4 *)(DAT_0002659c + 0x26244),
                                   (int *)(DAT_0002659c + 0x264e4),DAT_0002659c + 0x264ec);
            }
            iVar1 = DAT_000265a0;
            if (iVar2 == 0) {
              uVar15 = 0xb0f;
              iVar9 = 0;
            }
            else {
              local_4c = FUN_00017ee8(iVar2,*(undefined4 *)(DAT_000265a0 + 0x2638c));
              if (local_4c == 0) {
                uVar15 = 0xb11;
                iVar9 = 0;
              }
              else {
                FUN_00017fec(iVar2);
                iVar2 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x25fe4));
                iVar1 = local_4c;
                if (iVar2 == 0) {
                  uVar15 = 0xb14;
                  iVar9 = 0;
                }
                else {
                  iVar9 = FUN_00018840(*(undefined4 *)(local_4c + 4),uVar6);
                  if (iVar9 == 0) {
                    iVar1 = 0;
                    iVar9 = 0;
                  }
                  else {
                    iVar9 = *(int *)(iVar1 + 0xc);
                    if (iVar9 == 0) {
                      iVar1 = 0;
                    }
                    else {
                      iVar8 = *(int *)(iVar1 + 8);
                      FUN_00018934(iVar9);
                      FUN_00018934(iVar8);
                      iVar12 = local_4c;
                      iVar1 = 1;
                      local_4c = iVar8;
                      FUN_00017fec(iVar12);
                    }
                  }
                  iVar12 = local_4c;
                  iVar11 = iVar1 + 2;
                  uVar15 = *(undefined4 *)(local_4c + 4);
                  iVar8 = FUN_00018840(uVar15,*(undefined4 *)(iVar18 + DAT_000265fc));
                  if (iVar8 == 0) {
                    uVar17 = *(undefined4 *)(iVar18 + DAT_00026604);
                    iVar12 = FUN_00018840(uVar15,uVar17);
                    if (((iVar12 == 0) && (iVar12 = PyType_IsSubtype(uVar15,uVar17), iVar12 == 0))
                       || ((*(uint *)(*(int *)(local_4c + 8) + 8) & 0xffffff8d) != 0x80)) {
                      local_48 = PyTuple_New(iVar11);
                      iVar12 = DAT_000265ac;
                      if (local_48 == 0) {
                        uVar15 = 0xb35;
                      }
                      else {
                        if (iVar9 != 0) {
                          *(int *)(local_48 + 0xc) = iVar9;
                        }
                        FUN_00018934(*(undefined4 *)(iVar12 + 0x267b4));
                        uVar15 = *(undefined4 *)(iVar12 + 0x267b4);
                        iVar1 = local_48 + iVar1 * 4;
                        *(int *)(iVar1 + 0x10) = iVar2;
                        *(undefined4 *)(iVar1 + 0xc) = uVar15;
                        iVar1 = FUN_00017e40(local_4c,local_48,0);
                        if (iVar1 != 0) {
                          FUN_00017fec(local_48);
                          local_48 = 0;
                          goto LAB_000260a8;
                        }
                        uVar15 = 0xb40;
                        iVar9 = 0;
                        iVar2 = 0;
                      }
                    }
                    else {
                      local_34[0] = *(int *)(DAT_000265a8 + 0x2674c);
                      local_38 = iVar9;
                      local_34[1] = iVar2;
                      iVar1 = FUN_00017628(local_4c,local_34 + -iVar1,iVar11);
                      if (iVar1 != 0) goto LAB_00026094;
                      uVar15 = 0xb2e;
                    }
                  }
                  else {
                    local_34[0] = *(int *)((int)&DAT_000265f8 + DAT_000265a4);
                    local_38 = iVar9;
                    local_34[1] = iVar2;
                    iVar1 = FUN_0001b728(iVar12,local_34 + -iVar1,iVar11);
                    if (iVar1 != 0) {
LAB_00026094:
                      FUN_000182bc(iVar9);
                      FUN_00017fec(iVar2);
LAB_000260a8:
                      FUN_00017fec(local_4c);
                      local_4c = 0;
                      FUN_00017fec(iVar1);
                      FUN_000182bc(local_64);
                      local_64 = 0;
                      FUN_000182bc(local_60);
                      local_60 = 0;
                      FUN_000182bc(local_50);
                      local_50 = 0;
                      FUN_0001a300(*(undefined4 *)(iVar3 + 0x50),local_5c,local_58,local_54);
                      goto LAB_00025bb8;
                    }
                    uVar15 = 0xb25;
                  }
                }
              }
            }
            uVar17 = 0x2d;
          }
          iVar1 = 0;
          FUN_0001a300(*(undefined4 *)(iVar3 + 0x50),local_5c,local_58,local_54);
          local_90 = 0;
          local_84 = 0;
          local_98 = 0;
          local_a0 = 0;
          local_94 = 0;
          iVar3 = 0;
          iVar12 = 0;
          goto LAB_000262a4;
        }
        iVar1 = FUN_00017ee8(local_60,*(undefined4 *)(DAT_0002656c + 0x25edc));
        if (iVar1 == 0) {
          uVar15 = 0xa90;
          local_88 = 0;
          goto LAB_00025ee4;
        }
        FUN_00017fec(local_60);
        local_60 = 0;
        iVar9 = FUN_00018840(*(undefined4 *)(iVar1 + 4),uVar6);
        iVar2 = iVar1;
        if ((iVar9 != 0) && (local_60 = *(int *)(iVar1 + 0xc), local_60 != 0)) {
          iVar2 = *(int *)(iVar1 + 8);
          FUN_00018934();
          FUN_00018934(iVar2);
          FUN_00017fec(iVar1);
        }
        if (local_60 == 0) {
          local_64 = FUN_0001ccc4(iVar2,*(undefined4 *)(DAT_00026570 + 0x25cb4));
        }
        else {
          local_64 = FUN_0001caa0(iVar2);
        }
        FUN_000182bc(local_60);
        iVar1 = DAT_00026574;
        local_88 = local_64;
        local_60 = 0;
        if (local_64 == 0) {
          uVar15 = 0xa9f;
          iVar1 = iVar2;
          goto LAB_00025ee4;
        }
        FUN_00017fec(iVar2);
        iVar9 = local_64;
        local_88 = local_64;
        local_64 = 0;
        if (*(int *)(*(int *)(iVar1 + 0x25c90) + 0x14) == *(int *)(iVar1 + 0x25f98) &&
            *(int *)(*(int *)(iVar1 + 0x25c90) + 0x10) == *(int *)(iVar1 + 0x25f94)) {
          if (*(int *)(iVar1 + 0x25f9c) == 0) {
            iVar1 = FUN_00017f00(*(undefined4 *)(iVar1 + 0x25d04));
          }
          else {
            FUN_00018934();
            iVar1 = *(int *)(iVar1 + 0x25f9c);
          }
        }
        else {
          iVar1 = FUN_00018c58(*(undefined4 *)(iVar1 + 0x25d04),(int *)(iVar1 + 0x25f94),
                               iVar1 + 0x25f9c);
        }
        iVar2 = DAT_00026578;
        if (iVar1 == 0) {
          uVar15 = 0xaac;
          iVar2 = 0;
LAB_00025e34:
          uVar17 = 0x2b;
          goto LAB_00025ee8;
        }
        local_60 = FUN_00017ee8(iVar1,*(undefined4 *)(DAT_00026578 + 0x25e54));
        if (local_60 == 0) {
          uVar15 = 0xaae;
          iVar2 = 0;
          goto LAB_00025e34;
        }
        FUN_00017fec(iVar1);
        iVar1 = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x25aac));
        iVar12 = local_60;
        if (iVar1 == 0) {
          uVar15 = 0xab1;
          iVar2 = 0;
          goto LAB_00025e34;
        }
        iVar2 = FUN_00018840(*(undefined4 *)(local_60 + 4),uVar6);
        if (iVar2 == 0) {
          iVar2 = 0;
          iVar12 = 0;
        }
        else {
          iVar2 = *(int *)(iVar12 + 0xc);
          if (iVar2 == 0) {
            iVar12 = 0;
          }
          else {
            iVar11 = *(int *)(iVar12 + 8);
            FUN_00018934(iVar2);
            FUN_00018934(iVar11);
            iVar8 = local_60;
            iVar12 = 1;
            local_60 = iVar11;
            FUN_00017fec(iVar8);
          }
        }
        iVar8 = local_60;
        iVar14 = iVar12 + 3;
        uVar15 = *(undefined4 *)(local_60 + 4);
        iVar11 = FUN_00018840(uVar15,*(undefined4 *)(iVar18 + DAT_000265fc));
        if (iVar11 == 0) {
          uVar17 = *(undefined4 *)(iVar18 + DAT_00026604);
          iVar8 = FUN_00018840(uVar15,uVar17);
          if (((iVar8 == 0) && (iVar8 = PyType_IsSubtype(uVar15,uVar17), iVar8 == 0)) ||
             ((*(uint *)(*(int *)(local_60 + 8) + 8) & 0xffffff8d) != 0x80)) {
            local_50 = PyTuple_New(iVar14);
            if (local_50 == 0) {
              uVar15 = 0xad2;
            }
            else {
              if (iVar2 != 0) {
                *(int *)(local_50 + 0xc) = iVar2;
              }
              iVar2 = DAT_00026590;
              FUN_00018934(*(undefined4 *)(DAT_00026590 + 0x263f4));
              iVar8 = local_50 + iVar12 * 4;
              *(undefined4 *)(iVar8 + 0xc) = *(undefined4 *)(iVar2 + 0x263f4);
              *(int *)(iVar8 + 0x10) = iVar1;
              FUN_00018934(iVar9);
              *(int *)(local_50 + iVar12 * 4 + 0x14) = iVar9;
              local_64 = FUN_00017e40(local_60,local_50,0);
              if (local_64 != 0) {
                FUN_00017fec(local_50);
                local_50 = 0;
                goto LAB_00025b78;
              }
              uVar15 = 0xae0;
              iVar1 = 0;
              iVar2 = 0;
              local_64 = 0;
            }
          }
          else {
            local_34[0] = *(int *)(DAT_0002658c + 0x26380);
            local_34[2] = iVar9;
            local_38 = iVar2;
            local_34[1] = iVar1;
            local_64 = FUN_00017628(local_60,local_34 + -iVar12,iVar14);
            if (local_64 != 0) goto LAB_00025b68;
            uVar15 = 0xacb;
            local_64 = 0;
          }
          goto LAB_00025e34;
        }
        local_34[0] = *(int *)(DAT_0002657c + 0x260b0);
        local_34[2] = iVar9;
        local_38 = iVar2;
        local_34[1] = iVar1;
        local_64 = FUN_0001b728(iVar8,local_34 + -iVar12,iVar14);
        if (local_64 == 0) {
          uVar15 = 0xac2;
          local_64 = 0;
          goto LAB_00025e34;
        }
LAB_00025b68:
        FUN_000182bc(iVar2);
        FUN_00017fec(iVar1);
LAB_00025b78:
        FUN_00017fec(local_60);
        local_60 = 0;
        FUN_00017fec(local_64);
        local_64 = 0;
        FUN_000182bc(local_5c);
        local_5c = 0;
        FUN_000182bc(local_58);
        local_58 = 0;
        FUN_000182bc(local_54);
        local_54 = 0;
LAB_00025bb8:
        iVar8 = DAT_00026580;
        local_90 = 0;
        local_84 = 0;
        local_98 = 0;
        local_a0 = 0;
        local_94 = 0;
        iVar11 = DAT_00026580 + 0x2618c;
        iVar2 = DAT_00026584;
        iVar12 = 0;
        iVar3 = 0;
LAB_00025c00:
        do {
          local_60 = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x25f9c));
          if (local_60 == 0) goto LAB_0002812c;
          local_64 = FUN_00017ee8(local_60,*(undefined4 *)(iVar2 + 0x26190));
          if (local_64 == 0) {
            uVar15 = 0xb73;
            iVar1 = 0;
            goto LAB_00025d30;
          }
          FUN_00017fec(local_60);
          local_60 = 0;
          local_60 = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x25fa4));
          iVar9 = local_64;
          if (local_60 == 0) {
            uVar15 = 0xb76;
            iVar1 = 0;
            goto LAB_00025d30;
          }
          iVar1 = FUN_00018840(*(undefined4 *)(local_64 + 4),uVar6);
          if (iVar1 == 0) {
            iVar1 = 0;
            iVar9 = 0;
          }
          else {
            iVar1 = *(int *)(iVar9 + 0xc);
            if (iVar1 == 0) {
              iVar9 = 0;
            }
            else {
              iVar13 = *(int *)(iVar9 + 8);
              FUN_00018934(iVar1);
              FUN_00018934(iVar13);
              iVar14 = local_64;
              iVar9 = 1;
              local_64 = iVar13;
              FUN_00017fec(iVar14);
            }
          }
          iVar14 = local_64;
          iVar16 = iVar9 + 2;
          uVar15 = *(undefined4 *)(local_64 + 4);
          iVar13 = FUN_00018840(uVar15,*(undefined4 *)(iVar18 + DAT_000265fc));
          if (iVar13 == 0) {
            uVar17 = *(undefined4 *)(iVar18 + DAT_00026604);
            iVar14 = FUN_00018840(uVar15,uVar17);
            if (((iVar14 != 0) || (iVar14 = PyType_IsSubtype(uVar15,uVar17), iVar14 != 0)) &&
               ((*(uint *)(*(int *)(local_64 + 8) + 8) & 0xffffff8d) == 0x80)) {
              local_34[0] = local_60;
              local_34[1] = local_ac;
              local_38 = iVar1;
              local_50 = FUN_00017628(local_64,local_34 + -iVar9,iVar16);
              if (local_50 != 0) goto LAB_00026444;
              uVar15 = 0xb90;
              local_50 = 0;
              goto LAB_00025d30;
            }
            local_4c = PyTuple_New(iVar16);
            if (local_4c == 0) {
              uVar15 = 0xb97;
              goto LAB_00025d30;
            }
            if (iVar1 != 0) {
              *(int *)(local_4c + 0xc) = iVar1;
            }
            *(int *)(local_4c + iVar9 * 4 + 0xc) = local_60;
            FUN_00018934(local_ac);
            *(int *)(local_4c + iVar9 * 4 + 0x10) = local_ac;
            local_60 = 0;
            local_50 = FUN_00017e40(local_64,local_4c,0);
            if (local_50 == 0) {
              uVar15 = 0xba2;
              iVar1 = 0;
              local_50 = 0;
              goto LAB_00025d30;
            }
            FUN_00017fec(local_4c);
            local_4c = 0;
          }
          else {
            local_34[0] = local_60;
            local_34[1] = local_ac;
            local_38 = iVar1;
            local_50 = FUN_0001b728(iVar14,local_34 + -iVar9,iVar16);
            if (local_50 == 0) {
              uVar15 = 0xb87;
              local_50 = 0;
              goto LAB_00025d30;
            }
LAB_00026444:
            FUN_000182bc(iVar1);
            FUN_00017fec(local_60);
            local_60 = 0;
          }
          FUN_00017fec(local_64);
          local_64 = 0;
          FUN_00017fec(local_50);
          local_50 = 0;
          local_50 = FUN_00017ee8(local_ac,*(undefined4 *)(iVar8 + 0x26178));
          iVar1 = local_68;
          if (local_50 == 0) {
            uVar15 = 0xbb0;
            uVar17 = 0x31;
            iVar1 = 0;
            local_50 = 0;
            iVar9 = 0;
            iVar2 = 0;
            goto LAB_000262a4;
          }
          local_68 = local_50;
          FUN_000182bc(iVar1);
          local_50 = 0;
          local_50 = PyObject_RichCompare(local_68,*(undefined4 *)(iVar8 + 0x25e8c),0);
          if (local_50 == 0) {
            uVar15 = 0xbbc;
            uVar17 = 0x32;
            iVar1 = 0;
            iVar9 = 0;
            iVar2 = 0;
            goto LAB_000262a4;
          }
          iVar1 = FUN_00017f5c();
          if (iVar1 < 0) {
            uVar15 = 0xbbd;
            uVar17 = 0x32;
            goto LAB_000281ac;
          }
          FUN_00017fec(local_50);
          local_50 = 0;
          if (iVar1 != 0) {
            uVar6 = *(undefined4 *)(iVar18 + DAT_000265b8);
            FUN_00018934(uVar6);
            goto LAB_00026504;
          }
          local_50 = PyObject_RichCompare(local_68,*(undefined4 *)(iVar8 + 0x25e8c),4);
          if (local_50 == 0) {
            uVar15 = 0xbda;
            uVar17 = 0x34;
            iVar1 = 0;
            iVar9 = 0;
            iVar2 = 0;
            goto LAB_000262a4;
          }
          iVar9 = FUN_00017f5c();
          if (iVar9 < 0) {
            uVar15 = 0xbdb;
            uVar17 = 0x34;
            goto LAB_000281ac;
          }
          FUN_00017fec(local_50);
          local_50 = 0;
        } while (iVar9 == 0);
        local_50 = iVar1;
        iVar2 = _PyThreadState_UncheckedGet();
        FUN_00019f30(iVar2,&local_54,&local_58,&local_5c);
        local_50 = FUN_00017ee8(local_ac,*(undefined4 *)(iVar8 + 0x2617c));
        local_9c = iVar3;
        local_a4 = iVar12;
        if (local_50 == 0) {
          uVar15 = 0xbf6;
LAB_00026ad4:
          uVar17 = 0x37;
        }
        else {
          if (*(int *)(*(int *)(iVar8 + 0x25e50) + 0x14) == *(int *)(iVar8 + 0x26188) &&
              *(int *)(*(int *)(iVar8 + 0x25e50) + 0x10) == *(int *)(iVar8 + 0x26184)) {
            if (*(int *)(iVar8 + 0x2618c) == 0) {
              local_64 = FUN_00017f00(*(undefined4 *)(DAT_000265cc + 0x26c88));
            }
            else {
              FUN_00018934();
              local_64 = *(int *)(DAT_000265bc + 0x26c88);
            }
          }
          else {
            local_64 = FUN_00018c58(*(undefined4 *)(iVar8 + 0x25f00),(int *)(iVar8 + 0x26184),iVar11
                                   );
          }
          if (local_64 == 0) {
            uVar15 = 0xbf8;
            goto LAB_00026ad4;
          }
          local_4c = FUN_0001b6f4(local_50,local_64);
          iVar1 = DAT_000265c0;
          if (local_4c == 0) {
            uVar15 = 0xbfa;
            goto LAB_00026ad4;
          }
          FUN_00017fec(local_50);
          local_50 = 0;
          FUN_00017fec(local_64);
          local_64 = 0;
          local_64 = FUN_000256fc(local_4c,*(undefined4 *)(iVar1 + 0x269d8));
          if (local_64 == 0) {
            uVar15 = 0xbfe;
            goto LAB_00026ad4;
          }
          FUN_00017fec(local_4c);
          local_4c = 0;
          iVar9 = FUN_00017f5c(local_64);
          if (iVar9 < 0) {
            uVar15 = 0xc01;
            goto LAB_00026ad4;
          }
          FUN_00017fec(local_64);
          local_64 = 0;
          if (iVar9 == 0) {
            local_64 = FUN_00017ee8(local_ac,*(undefined4 *)(iVar1 + 0x26cb0));
            if (local_64 == 0) {
              uVar15 = 0xc21;
            }
            else {
              if (*(int *)(*(int *)(iVar1 + 0x26984) + 0x14) == *(int *)(iVar1 + 0x26ccc) &&
                  *(int *)(*(int *)(iVar1 + 0x26984) + 0x10) == *(int *)(iVar1 + 0x26cc8)) {
                if (*(int *)(iVar1 + 0x26cd0) == 0) {
                  local_4c = FUN_00017f00(*(undefined4 *)(iVar1 + 0x26a28));
                }
                else {
                  FUN_00018934();
                  local_4c = *(int *)(iVar1 + 0x26cd0);
                }
              }
              else {
                local_4c = FUN_00018c58(*(undefined4 *)(iVar1 + 0x26a28),(int *)(iVar1 + 0x26cc8),
                                        iVar1 + 0x26cd0);
              }
              if (local_4c == 0) {
                uVar15 = 0xc23;
              }
              else {
                local_50 = FUN_0001b6f4(local_64);
                if (local_50 == 0) {
                  uVar15 = 0xc25;
                }
                else {
                  FUN_00017fec(local_64);
                  local_64 = 0;
                  FUN_00017fec(local_4c);
                  local_4c = 0;
                  local_4c = FUN_0001ccc4(*(undefined4 *)(iVar18 + DAT_000265d0),local_50);
                  if (local_4c == 0) {
                    uVar15 = 0xc29;
                  }
                  else {
                    FUN_00017fec(local_50);
                    local_50 = 0;
                    local_50 = PyNumber_Add(*(undefined4 *)(DAT_000265d4 + 0x27008),local_4c);
                    if (local_50 != 0) {
                      FUN_00017fec(local_4c);
                      iVar1 = local_50;
                      local_4c = 0;
                      FUN_000182bc(local_94);
                      local_50 = 0;
                      local_94 = iVar1;
                      goto LAB_00026788;
                    }
                    uVar15 = 0xc2c;
                    local_50 = 0;
                  }
                }
              }
            }
            uVar17 = 0x3a;
            goto LAB_00026ad8;
          }
          FUN_00018934(*(undefined4 *)(iVar1 + 0x26774));
          iVar1 = *(int *)(iVar1 + 0x26774);
          FUN_000182bc(local_94);
          local_94 = iVar1;
LAB_00026788:
          iVar1 = DAT_000265c4;
          local_50 = FUN_00017ee8(local_ac,*(undefined4 *)(DAT_000265c4 + 0x26d30));
          if (local_50 == 0) {
            uVar15 = 0xc3b;
LAB_00026d38:
            uVar17 = 0x3b;
          }
          else {
            if (*(int *)(*(int *)(iVar1 + 0x26a04) + 0x14) == *(int *)(iVar1 + 0x26d5c) &&
                *(int *)(*(int *)(iVar1 + 0x26a04) + 0x10) == *(int *)(iVar1 + 0x26d58)) {
              if (*(int *)(iVar1 + 0x26d60) == 0) {
                local_4c = FUN_00017f00(*(undefined4 *)(iVar1 + 0x26ab4));
              }
              else {
                FUN_00018934();
                local_4c = *(int *)(iVar1 + 0x26d60);
              }
            }
            else {
              local_4c = FUN_00018c58(*(undefined4 *)(iVar1 + 0x26ab4),(int *)(iVar1 + 0x26d58),
                                      iVar1 + 0x26d60);
            }
            if (local_4c == 0) {
              uVar15 = 0xc3d;
              goto LAB_00026d38;
            }
            local_64 = FUN_0001b6f4(local_50,local_4c);
            if (local_64 == 0) {
              uVar15 = 0xc3f;
              goto LAB_00026d38;
            }
            FUN_00017fec(local_50);
            local_50 = 0;
            FUN_00017fec(local_4c);
            local_4c = 0;
            local_4c = FUN_0001ccc4(*(undefined4 *)(iVar18 + DAT_000265d0),local_64);
            iVar1 = DAT_000265c8;
            if (local_4c == 0) {
              uVar15 = 0xc43;
              goto LAB_00026d38;
            }
            FUN_00017fec(local_64);
            local_64 = 0;
            local_64 = PyNumber_Add(*(undefined4 *)(iVar1 + 0x26e18),local_4c);
            if (local_64 == 0) {
              uVar15 = 0xc46;
              local_64 = 0;
              goto LAB_00026d38;
            }
            FUN_00017fec(local_4c);
            local_9c = local_64;
            local_4c = 0;
            FUN_000182bc(iVar3);
            local_64 = 0;
            local_a4 = PyNumber_Add(local_94,local_9c);
            if (local_a4 == 0) {
              uVar15 = 0xc53;
              uVar17 = 0x3c;
              local_64 = 0;
              local_a4 = iVar12;
            }
            else {
              local_64 = local_a4;
              FUN_000182bc(iVar12);
              local_64 = 0;
              local_64 = PyTuple_New(2);
              if (local_64 != 0) {
                FUN_00018934(local_94);
                *(int *)(local_64 + 0xc) = local_94;
                FUN_00018934(local_9c);
                iVar2 = local_64;
                *(int *)(local_64 + 0x10) = local_9c;
                local_a8 = local_64;
                FUN_000182bc(local_a0);
                local_64 = 0;
                FUN_000182bc(local_54);
                local_54 = 0;
                FUN_000182bc(local_58);
                local_58 = 0;
                FUN_000182bc(local_5c);
                local_5c = 0;
                local_50 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x26ccc));
                iVar3 = local_9c;
                iVar12 = local_a4;
                if (local_50 == 0) {
                  local_a0 = iVar2;
                  uVar15 = 0xcdb;
                  uVar17 = 0x41;
                  iVar1 = 0;
                  iVar9 = 0;
                  iVar2 = 0;
                  goto LAB_000262a4;
                }
                iVar9 = FUN_0002534c(local_a4,local_50);
                if (iVar9 < 0) {
                  local_a0 = iVar2;
                  uVar15 = 0xcdd;
                  uVar17 = 0x41;
LAB_000281ac:
                  iVar1 = 0;
                  iVar9 = 0;
                  iVar2 = 0;
                  goto LAB_000262a4;
                }
                FUN_00017fec(local_50);
                local_50 = 0;
                if (iVar9 == 0) goto LAB_00026cd4;
                local_4c = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x26d5c));
                iVar1 = DAT_000265ec;
                if (local_4c == 0) {
                  uVar15 = 0xce9;
LAB_00028210:
                  iVar1 = 0;
                  local_a0 = iVar2;
                  uVar17 = 0x43;
                  iVar9 = 0;
                  iVar2 = 0;
                  goto LAB_000262a4;
                }
                local_64 = FUN_00017ee8(local_4c,*(undefined4 *)(DAT_000265ec + 0x27448));
                if (local_64 == 0) {
                  uVar15 = 0xceb;
                  goto LAB_00028210;
                }
                FUN_00017fec(local_4c);
                local_4c = 0;
                local_4c = FUN_00017ee8(local_ac,*(undefined4 *)(iVar1 + 0x27404));
                if (local_4c == 0) {
                  uVar15 = 0xcee;
                  goto LAB_00028210;
                }
                local_60 = FUN_0001b3e4(local_4c,&local_68);
                if (local_60 == 0) {
                  uVar15 = 0xcf0;
                  local_60 = 0;
                  goto LAB_00028210;
                }
                FUN_00017fec(local_4c);
                iVar1 = local_64;
                local_4c = 0;
                uVar7 = *(undefined4 *)(iVar18 + DAT_000265f0);
                iVar9 = FUN_00018840(*(undefined4 *)(local_64 + 4),uVar7);
                if ((iVar9 != 0) && (local_4c = *(int *)(iVar1 + 0xc), local_4c != 0)) {
                  iVar9 = *(int *)(iVar1 + 8);
                  FUN_00018934();
                  FUN_00018934(iVar9);
                  iVar1 = local_64;
                  local_64 = iVar9;
                  FUN_00017fec(iVar1);
                }
                if (local_4c == 0) {
                  local_50 = FUN_0001ccc4(local_64,local_60);
                }
                else {
                  local_50 = FUN_0001caa0();
                }
                FUN_000182bc(local_4c);
                local_4c = 0;
                FUN_00017fec(local_60);
                iVar1 = DAT_000265f4;
                local_60 = 0;
                if (local_50 == 0) {
                  uVar15 = 0xd00;
                  goto LAB_00028210;
                }
                FUN_00017fec(local_64);
                iVar14 = local_50;
                local_64 = 0;
                FUN_000182bc(local_84);
                local_50 = 0;
                iVar13 = _PyThreadState_UncheckedGet();
                FUN_00019f30(iVar13,&local_5c,&local_58,&local_54);
                local_50 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x273ec));
                if (local_50 == 0) {
                  uVar15 = 0xd1e;
LAB_000274b4:
                  iVar9 = 0;
                  FUN_000182bc(local_64);
                  local_64 = 0;
                  FUN_000182bc(local_4c);
                  local_4c = 0;
                  FUN_000182bc(0);
                  FUN_000182bc(local_48);
                  local_48 = 0;
                  FUN_000182bc(0);
                  FUN_000182bc(local_60);
                  local_60 = 0;
                  FUN_000182bc(0);
                  FUN_000182bc(local_50);
                  local_50 = 0;
                  FUN_00019490(DAT_00026614 + 0x27524,uVar15,0x46,DAT_00026610 + 0x27520);
                  iVar2 = FUN_00018950(iVar13,&local_48,&local_60,&local_50);
                  iVar1 = DAT_00026618;
                  if (iVar2 < 0) {
                    uVar15 = 0xe0c;
                    uVar17 = 0x49;
                    iVar2 = 0;
                    iVar1 = 0;
                    goto LAB_00027c18;
                  }
                  if (*(int *)(*(int *)(DAT_00026618 + 0x277bc) + 0x14) ==
                      *(int *)(DAT_00026618 + 0x27b34) &&
                      *(int *)(*(int *)(DAT_00026618 + 0x277bc) + 0x10) ==
                      *(int *)(DAT_00026618 + 0x27b30)) {
                    if (*(int *)(DAT_00026618 + 0x27b38) == 0) {
                      local_4c = FUN_00017f00(*(undefined4 *)(DAT_00026618 + 0x27830));
                    }
                    else {
                      FUN_00018934();
                      local_4c = *(int *)(iVar1 + 0x27b38);
                    }
                  }
                  else {
                    local_4c = FUN_00018c58(*(undefined4 *)(DAT_00026618 + 0x27830),
                                            (int *)(DAT_00026618 + 0x27b30),DAT_00026618 + 0x27b38);
                  }
                  iVar2 = DAT_0002661c;
                  if (local_4c == 0) {
                    uVar15 = 0xe18;
                    iVar1 = 0;
                    iVar9 = 0;
                    iVar2 = 0;
                  }
                  else {
                    iVar1 = FUN_00017ee8(local_4c,*(undefined4 *)(DAT_0002661c + 0x27b84));
                    if (iVar1 == 0) {
                      uVar15 = 0xe1a;
                      iVar9 = 0;
                      iVar2 = 0;
                    }
                    else {
                      FUN_00017fec(local_4c);
                      local_4c = 0;
                      local_4c = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x275d4));
                      if (local_4c == 0) {
                        uVar15 = 0xe25;
                        uVar17 = 0x4b;
                        iVar9 = 0;
                        iVar2 = 0;
                        goto LAB_00027c18;
                      }
                      iVar2 = FUN_00018840(*(undefined4 *)(iVar1 + 4),uVar7);
                      iVar16 = iVar1;
                      if (iVar2 == 0) {
                        iVar4 = 0;
                        iVar2 = 0;
                      }
                      else {
                        iVar2 = *(int *)(iVar1 + 0xc);
                        if (iVar2 == 0) {
                          iVar4 = 0;
                        }
                        else {
                          iVar16 = *(int *)(iVar1 + 8);
                          FUN_00018934(iVar2);
                          FUN_00018934(iVar16);
                          iVar4 = 1;
                          FUN_00017fec(iVar1);
                        }
                      }
                      iVar5 = iVar4 + 2;
                      uVar15 = *(undefined4 *)(iVar16 + 4);
                      iVar9 = FUN_00018840(uVar15,*(undefined4 *)(iVar18 + DAT_00028298));
                      iVar1 = iVar16;
                      if (iVar9 == 0) {
                        uVar17 = *(undefined4 *)(iVar18 + DAT_000282a8);
                        iVar9 = FUN_00018840(uVar15,uVar17);
                        if (((iVar9 == 0) && (iVar9 = PyType_IsSubtype(uVar15,uVar17), iVar9 == 0))
                           || ((*(uint *)(*(int *)(iVar16 + 8) + 8) & 0xffffff8d) != 0x80)) {
                          iVar9 = PyTuple_New(iVar5);
                          iVar5 = DAT_000282b0;
                          if (iVar9 == 0) {
                            uVar15 = 0xe46;
                          }
                          else {
                            if (iVar2 != 0) {
                              *(int *)(iVar9 + 0xc) = iVar2;
                            }
                            iVar4 = iVar9 + iVar4 * 4;
                            FUN_00018934(*(undefined4 *)(iVar5 + 0x28144));
                            iVar2 = local_4c;
                            *(undefined4 *)(iVar4 + 0xc) = *(undefined4 *)(iVar5 + 0x28144);
                            local_4c = 0;
                            *(int *)(iVar4 + 0x10) = iVar2;
                            local_64 = FUN_00017e40(iVar16,iVar9);
                            if (local_64 != 0) {
                              FUN_00017fec(iVar9);
                              goto LAB_00027bb4;
                            }
                            uVar15 = 0xe51;
                            iVar2 = 0;
                            local_64 = 0;
                          }
                        }
                        else {
                          local_34[0] = *(int *)(DAT_000282ac + 0x280d4);
                          local_34[1] = local_4c;
                          local_38 = iVar2;
                          local_64 = FUN_00017628(iVar16,local_34 + -iVar4,iVar5);
                          if (local_64 != 0) goto LAB_00027b9c;
                          uVar15 = 0xe3f;
                          iVar9 = 0;
                          local_64 = 0;
                        }
                      }
                      else {
                        local_34[0] = *(int *)(DAT_0002829c + 0x27c4c);
                        local_34[1] = local_4c;
                        local_38 = iVar2;
                        local_64 = FUN_0001b728(iVar16,local_34 + -iVar4,iVar5);
                        if (local_64 != 0) {
LAB_00027b9c:
                          FUN_000182bc(iVar2);
                          FUN_00017fec(local_4c);
                          local_4c = 0;
LAB_00027bb4:
                          FUN_00017fec(iVar16);
                          FUN_00017fec(local_64);
                          local_64 = 0;
                          FUN_000182bc(local_48);
                          local_48 = 0;
                          FUN_000182bc(local_60);
                          local_60 = 0;
                          FUN_000182bc(local_50);
                          local_50 = 0;
                          FUN_0001a300(*(undefined4 *)(iVar13 + 0x50),local_5c,local_58,local_54);
                          goto LAB_000277c4;
                        }
                        uVar15 = 0xe36;
                        iVar9 = 0;
                        local_64 = 0;
                      }
                    }
                  }
                  uVar17 = 0x4a;
LAB_00027c18:
                  FUN_0001a300(*(undefined4 *)(iVar13 + 0x50),local_5c,local_58,local_54);
                  local_84 = iVar14;
                  local_a0 = local_a8;
                  goto LAB_000262a4;
                }
                iVar9 = FUN_00018f60(local_50,*(undefined4 *)(iVar1 + 0x273f0));
                if (iVar9 == 0) {
                  uVar15 = 0xd20;
                  goto LAB_000274b4;
                }
                iVar1 = FUN_00018f60(local_50,*(undefined4 *)(iVar1 + 0x273f4));
                local_60 = iVar1;
                if (iVar1 == 0) {
                  uVar15 = 0xd22;
LAB_00027a4c:
                  FUN_00017fec(iVar9);
                  goto LAB_000274b4;
                }
                local_4c = 0;
                iVar16 = FUN_00018840(*(undefined4 *)(iVar1 + 4),uVar7);
                if ((iVar16 != 0) && (local_4c = *(int *)(iVar1 + 0xc), local_4c != 0)) {
                  iVar16 = *(int *)(iVar1 + 8);
                  FUN_00018934();
                  FUN_00018934(iVar16);
                  iVar1 = local_60;
                  local_60 = iVar16;
                  FUN_00017fec(iVar1);
                }
                if (local_4c == 0) {
                  local_64 = FUN_0001cbcc(local_60);
                }
                else {
                  local_64 = FUN_0001ccc4();
                }
                FUN_000182bc(local_4c);
                iVar1 = DAT_000265f8;
                local_4c = 0;
                if (local_64 == 0) {
                  uVar15 = 0xd30;
                  goto LAB_00027a4c;
                }
                FUN_00017fec(local_60);
                local_60 = 0;
                FUN_00017fec(local_64);
                local_64 = 0;
                FUN_00017fec(local_50);
                local_50 = 0;
                iVar16 = _PyThreadState_UncheckedGet();
                FUN_00019f30(iVar16,&local_44,&local_40,&local_3c);
                local_64 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x274f8));
                if (local_64 == 0) {
                  uVar15 = 0xd46;
LAB_0002737c:
                  uVar17 = 0x47;
LAB_00027380:
                  FUN_000182bc(local_64);
                  local_64 = 0;
                  FUN_000182bc(local_4c);
                  local_4c = 0;
                  FUN_000182bc(0);
                  FUN_000182bc(local_48);
                  local_48 = 0;
                  FUN_000182bc(0);
                  FUN_000182bc(local_60);
                  local_60 = 0;
                  FUN_000182bc(0);
                  FUN_000182bc(local_50);
                  local_50 = 0;
                  FUN_00019490(DAT_0002660c + 0x273f0,uVar15,uVar17,DAT_00026608 + 0x273ec);
                  iVar1 = FUN_00018950(iVar16,&local_50,&local_60,&local_48);
                  if (iVar1 < 0) {
                    uVar15 = 0xdaf;
                  }
                  else {
                    local_64 = PyTuple_Pack(3,local_50,local_60,local_48);
                    if (local_64 == 0) {
                      uVar15 = 0xdb3;
                      local_64 = 0;
                    }
                    else {
                      iVar1 = FUN_00017e40(iVar9,local_64,0);
                      FUN_00017fec(iVar9);
                      FUN_00017fec(local_64);
                      local_64 = 0;
                      if (iVar1 == 0) {
                        uVar15 = 0xdb8;
                      }
                      else {
                        iVar2 = FUN_00017f5c(iVar1);
                        FUN_00017fec(iVar1);
                        if (iVar2 < 0) {
                          uVar15 = 0xdbc;
                        }
                        else {
                          if (iVar2 != 0) {
                            FUN_000182bc(local_50);
                            local_50 = 0;
                            FUN_000182bc(local_60);
                            local_60 = 0;
                            FUN_000182bc(local_48);
                            local_48 = 0;
                            FUN_0001a300(*(undefined4 *)(iVar16 + 0x50),local_44,local_40,local_3c);
                            goto LAB_0002779c;
                          }
                          uVar15 = 0xdc4;
                          uVar17 = PyThreadState_Get();
                          FUN_000182c8(uVar17,local_50,local_60,local_48);
                          local_60 = 0;
                          local_50 = 0;
                          local_48 = 0;
                        }
                      }
                    }
                  }
                  FUN_0001a300(*(undefined4 *)(iVar16 + 0x50),local_44,local_40,local_3c);
                  goto LAB_000274b4;
                }
                local_60 = FUN_00017ee8(local_64,*(undefined4 *)(iVar1 + 0x2746c));
                if (local_60 == 0) {
                  uVar15 = 0xd48;
                  goto LAB_0002737c;
                }
                FUN_00017fec(local_64);
                local_64 = 0;
                local_64 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x271a8));
                iVar1 = local_60;
                if (local_64 == 0) {
                  uVar15 = 0xd4b;
                  goto LAB_0002737c;
                }
                local_4c = 0;
                iVar4 = FUN_00018840(*(undefined4 *)(local_60 + 4),uVar7);
                if ((iVar4 == 0) || (local_4c = *(int *)(iVar1 + 0xc), local_4c == 0)) {
                  iVar1 = 0;
                }
                else {
                  iVar4 = *(int *)(iVar1 + 8);
                  FUN_00018934();
                  FUN_00018934(iVar4);
                  iVar1 = local_60;
                  local_60 = iVar4;
                  FUN_00017fec(iVar1);
                  iVar1 = 1;
                }
                iVar4 = local_60;
                iVar10 = iVar1 + 2;
                uVar15 = *(undefined4 *)(local_60 + 4);
                iVar5 = FUN_00018840(uVar15,*(undefined4 *)(iVar18 + DAT_000265fc));
                if (iVar5 == 0) {
                  uVar17 = *(undefined4 *)(iVar18 + DAT_00026604);
                  iVar4 = FUN_00018840(uVar15,uVar17);
                  if (((iVar4 == 0) && (iVar4 = PyType_IsSubtype(uVar15,uVar17), iVar4 == 0)) ||
                     ((*(uint *)(*(int *)(local_60 + 8) + 8) & 0xffffff8d) != 0x80)) {
                    local_48 = PyTuple_New(iVar10);
                    if (local_48 == 0) {
                      uVar15 = 0xd6c;
                    }
                    else {
                      if (local_4c != 0) {
                        *(int *)(local_48 + 0xc) = local_4c;
                        local_4c = 0;
                      }
                      FUN_00018934(iVar2);
                      iVar1 = local_48 + iVar1 * 4;
                      *(int *)(iVar1 + 0xc) = iVar2;
                      *(int *)(iVar1 + 0x10) = local_64;
                      local_64 = 0;
                      local_50 = FUN_00017e40(local_60,local_48,0);
                      if (local_50 != 0) {
                        FUN_00017fec(local_48);
                        local_48 = 0;
                        goto LAB_0002719c;
                      }
                      uVar15 = 0xd77;
                      local_50 = 0;
                    }
                  }
                  else {
                    local_38 = local_4c;
                    local_34[0] = iVar2;
                    local_34[1] = local_64;
                    local_50 = FUN_00017628(local_60,local_34 + -iVar1,iVar10);
                    if (local_50 != 0) goto LAB_00027180;
                    uVar15 = 0xd65;
                    local_50 = 0;
                  }
                  goto LAB_0002737c;
                }
                local_38 = local_4c;
                local_34[0] = iVar2;
                local_34[1] = local_64;
                local_50 = FUN_0001b728(iVar4,local_34 + -iVar1,iVar10);
                if (local_50 == 0) {
                  uVar15 = 0xd5c;
                  local_50 = 0;
                  goto LAB_0002737c;
                }
LAB_00027180:
                FUN_000182bc(local_4c);
                local_4c = 0;
                FUN_00017fec(local_64);
                local_64 = 0;
LAB_0002719c:
                FUN_00017fec(local_60);
                local_a8 = local_50;
                local_60 = 0;
                FUN_00017fec(iVar2);
                local_50 = 0;
                FUN_00018934(local_a8);
                local_60 = local_a8;
                local_48 = 0;
                iVar1 = FUN_00018840(*(undefined4 *)(local_a8 + 4),uVar7);
                if ((iVar1 != 0) && (local_48 = *(int *)(local_a8 + 0xc), local_48 != 0)) {
                  iVar2 = *(int *)(local_a8 + 8);
                  FUN_00018934();
                  FUN_00018934(iVar2);
                  iVar1 = local_60;
                  local_60 = iVar2;
                  FUN_00017fec(iVar1);
                }
                if (local_48 == 0) {
                  local_50 = FUN_0001ccc4(local_60,iVar14);
                }
                else {
                  local_50 = FUN_0001caa0(local_60,local_48,iVar14);
                }
                FUN_000182bc(local_48);
                local_48 = 0;
                if (local_50 == 0) {
                  uVar15 = 0xd93;
                  uVar17 = 0x48;
                  goto LAB_00027380;
                }
                FUN_00017fec(local_60);
                local_60 = 0;
                FUN_00017fec(local_50);
                local_50 = 0;
                FUN_000182bc(local_44);
                local_44 = 0;
                FUN_000182bc(local_40);
                local_40 = 0;
                FUN_000182bc(local_3c);
                local_3c = 0;
                local_3c = FUN_00017e40(iVar9,*(undefined4 *)(DAT_00026600 + 0x272c0),0);
                FUN_00017fec(iVar9);
                if (local_3c == 0) {
                  uVar15 = 0xdde;
                  goto LAB_000274b4;
                }
                FUN_00017fec();
                local_3c = 0;
LAB_0002779c:
                FUN_000182bc(local_5c);
                local_5c = 0;
                FUN_000182bc(local_58);
                local_58 = 0;
                FUN_000182bc(local_54);
                local_54 = 0;
LAB_000277c4:
                iVar1 = DAT_000282a0;
                iVar3 = _PyThreadState_UncheckedGet();
                FUN_00019f30(iVar3,&local_54,&local_58,&local_5c);
                local_60 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x27c5c));
                if (local_60 == 0) {
                  uVar15 = 0xe89;
LAB_00027db8:
                  uVar17 = 0x4d;
                }
                else {
                  local_48 = FUN_00017ee8(local_60,*(undefined4 *)(iVar1 + 0x27ba0));
                  if (local_48 == 0) {
                    uVar15 = 0xe8b;
                    goto LAB_00027db8;
                  }
                  FUN_00017fec(local_60);
                  iVar1 = local_48;
                  local_60 = 0;
                  iVar2 = FUN_00018840(*(undefined4 *)(local_48 + 4),uVar7);
                  if ((iVar2 != 0) && (local_60 = *(int *)(iVar1 + 0xc), local_60 != 0)) {
                    iVar2 = *(int *)(iVar1 + 8);
                    FUN_00018934();
                    FUN_00018934(iVar2);
                    iVar1 = local_48;
                    local_48 = iVar2;
                    FUN_00017fec(iVar1);
                  }
                  if (local_60 == 0) {
                    local_50 = FUN_0001ccc4(local_48,local_a4);
                  }
                  else {
                    local_50 = FUN_0001caa0(local_48,local_60,local_a4);
                  }
                  FUN_000182bc(local_60);
                  iVar1 = DAT_000282a4;
                  local_60 = 0;
                  if (local_50 == 0) {
                    uVar15 = 0xe9a;
                    goto LAB_00027db8;
                  }
                  FUN_00017fec(local_48);
                  iVar2 = local_50;
                  local_48 = 0;
                  FUN_000182bc(local_90);
                  local_50 = 0;
                  local_48 = FUN_00017ee8(param_1,*(undefined4 *)(iVar1 + 0x278ec));
                  if (local_48 == 0) {
                    uVar15 = 0xea7;
                  }
                  else {
                    local_60 = FUN_00017ee8(local_48,*(undefined4 *)(iVar1 + 0x27ea0));
                    if (local_60 == 0) {
                      uVar15 = 0xea9;
                    }
                    else {
                      FUN_00017fec(local_48);
                      iVar1 = local_60;
                      local_48 = 0;
                      iVar9 = FUN_00018840(*(undefined4 *)(local_60 + 4),uVar7);
                      local_80 = 0;
                      if ((iVar9 != 0) && (local_48 = *(int *)(iVar1 + 0xc), local_48 != 0)) {
                        iVar9 = *(int *)(iVar1 + 8);
                        FUN_00018934();
                        FUN_00018934(iVar9);
                        iVar1 = local_60;
                        local_60 = iVar9;
                        FUN_00017fec(iVar1);
                        local_80 = 1;
                      }
                      iVar1 = local_60;
                      uVar15 = *(undefined4 *)(local_60 + 4);
                      iVar9 = FUN_00018840(uVar15,*(undefined4 *)(iVar18 + DAT_00028298));
                      iVar12 = local_80 + 2;
                      if (iVar9 == 0) {
                        uVar17 = *(undefined4 *)(iVar18 + DAT_000282a8);
                        iVar1 = FUN_00018840(uVar15,uVar17);
                        if (((iVar1 == 0) && (iVar1 = PyType_IsSubtype(uVar15,uVar17), iVar1 == 0))
                           || ((*(uint *)(*(int *)(local_60 + 8) + 8) & 0xffffff8d) != 0x80)) {
                          local_64 = PyTuple_New(iVar12);
                          if (local_64 == 0) {
                            uVar15 = 0xec9;
                          }
                          else {
                            if (local_48 != 0) {
                              *(int *)(local_64 + 0xc) = local_48;
                              local_48 = 0;
                            }
                            FUN_00018934(iVar2);
                            *(int *)(local_64 + local_80 * 4 + 0xc) = iVar2;
                            FUN_00018934(iVar14);
                            *(int *)(local_64 + local_80 * 4 + 0x10) = iVar14;
                            local_50 = FUN_00017e40(local_60,local_64,0);
                            if (local_50 != 0) {
                              FUN_00017fec(local_64);
                              local_64 = 0;
                              goto LAB_000279c8;
                            }
                            uVar15 = 0xed4;
                            local_50 = 0;
                          }
                        }
                        else {
                          local_34[0] = iVar2;
                          local_38 = local_48;
                          local_34[1] = iVar14;
                          local_50 = FUN_00017628(local_60,local_34 + -local_80,iVar12);
                          if (local_50 != 0) goto LAB_000279b8;
                          uVar15 = 0xec3;
                          local_50 = 0;
                        }
                      }
                      else {
                        local_34[0] = iVar2;
                        local_38 = local_48;
                        local_34[1] = iVar14;
                        local_50 = FUN_0001b728(iVar1,local_34 + -local_80,iVar12);
                        if (local_50 != 0) {
LAB_000279b8:
                          FUN_000182bc(local_48);
                          local_48 = 0;
LAB_000279c8:
                          FUN_00017fec(local_60);
                          local_60 = 0;
                          FUN_00017fec(local_50);
                          local_50 = 0;
                          FUN_000182bc(local_54);
                          local_54 = 0;
                          FUN_000182bc(local_58);
                          local_58 = 0;
                          FUN_000182bc(local_5c);
                          local_84 = iVar14;
                          local_5c = 0;
                          local_90 = iVar2;
                          goto LAB_00026cd4;
                        }
                        uVar15 = 0xebb;
                        local_50 = 0;
                      }
                    }
                  }
                  uVar17 = 0x4e;
                  local_90 = iVar2;
                }
                FUN_000182bc(local_64);
                local_64 = 0;
                FUN_000182bc(local_4c);
                local_4c = 0;
                FUN_000182bc(0);
                FUN_000182bc(local_48);
                local_48 = 0;
                FUN_000182bc(0);
                FUN_000182bc(local_60);
                local_60 = 0;
                FUN_000182bc(0);
                FUN_000182bc(local_50);
                local_50 = 0;
                iVar1 = FUN_00019fd0(*(undefined4 *)(iVar3 + 0x34),
                                     **(undefined4 **)(iVar18 + DAT_000282b4));
                if (iVar1 == 0) {
LAB_00028024:
                  iVar1 = 0;
                  iVar9 = iVar1;
                }
                else {
                  FUN_00019490(DAT_000282bc + 0x27e4c,uVar15,uVar17,DAT_000282b8 + 0x27e48);
                  iVar2 = FUN_00018950(iVar3,&local_50,&local_60,&local_64);
                  iVar1 = DAT_000282c0;
                  if (iVar2 < 0) {
                    uVar15 = 0xefb;
                    uVar17 = 0x4f;
                    goto LAB_00028024;
                  }
                  FUN_00018934(local_60);
                  iVar2 = local_60;
                  FUN_000182bc(local_98);
                  if (*(int *)(*(int *)(iVar1 + 0x280e4) + 0x14) == *(int *)(iVar1 + 0x28474) &&
                      *(int *)(*(int *)(iVar1 + 0x280e4) + 0x10) == *(int *)(iVar1 + 0x28470)) {
                    if (*(int *)(iVar1 + 0x28478) == 0) {
                      iVar1 = FUN_00017f00(*(undefined4 *)(iVar1 + 0x28158));
                    }
                    else {
                      FUN_00018934();
                      iVar1 = *(int *)(iVar1 + 0x28478);
                    }
                  }
                  else {
                    iVar1 = FUN_00018c58(*(undefined4 *)(iVar1 + 0x28158),iVar1 + 0x28470,
                                         iVar1 + 0x28478);
                  }
                  if (iVar1 == 0) {
                    uVar15 = 0xf09;
                    iVar9 = 0;
                  }
                  else {
                    iVar9 = FUN_00017ee8(iVar1,*(undefined4 *)(DAT_000282c4 + 0x28368));
                    if (iVar9 == 0) {
                      uVar15 = 0xf0b;
                    }
                    else {
                      FUN_00017fec(iVar1);
                      iVar1 = FUN_00018840(*(undefined4 *)(iVar9 + 4),uVar7);
                      if ((iVar1 == 0) || (iVar1 = *(int *)(iVar9 + 0xc), iVar1 == 0)) {
                        iVar1 = 0;
                        local_48 = FUN_0001ccc4(iVar9,iVar2);
                      }
                      else {
                        iVar12 = *(int *)(iVar9 + 8);
                        FUN_00018934(iVar1);
                        FUN_00018934(iVar12);
                        FUN_00017fec(iVar9);
                        local_48 = FUN_0001caa0(iVar12,iVar1,iVar2);
                        iVar9 = iVar12;
                      }
                      FUN_000182bc(iVar1);
                      if (local_48 != 0) {
                        FUN_00017fec(iVar9);
                        FUN_00017fec(local_48);
                        local_48 = 0;
                        FUN_000182bc(local_50);
                        local_50 = 0;
                        FUN_000182bc(local_60);
                        local_60 = 0;
                        FUN_000182bc(local_64);
                        local_64 = 0;
                        FUN_0001a300(*(undefined4 *)(iVar3 + 0x50),local_54,local_58,local_5c);
                        local_84 = iVar14;
                        local_98 = iVar2;
                        goto LAB_00026cd4;
                      }
                      uVar15 = 0xf1a;
                      iVar1 = 0;
                    }
                  }
                  uVar17 = 0x50;
                  local_98 = iVar2;
                }
                FUN_0001a300(*(undefined4 *)(iVar3 + 0x50),local_54,local_58,local_5c);
                local_84 = iVar14;
                local_a0 = local_a8;
                goto LAB_00026de4;
              }
              uVar15 = 0xc5f;
              uVar17 = 0x3d;
              local_64 = 0;
            }
          }
        }
LAB_00026ad8:
        iVar1 = 0;
        FUN_000182bc(local_64);
        local_64 = 0;
        FUN_000182bc(local_4c);
        local_4c = 0;
        FUN_000182bc(0);
        FUN_000182bc(local_48);
        local_48 = 0;
        FUN_000182bc(0);
        FUN_000182bc(local_60);
        local_60 = 0;
        FUN_000182bc(0);
        FUN_000182bc(local_50);
        local_50 = 0;
        iVar3 = FUN_00019fd0(*(undefined4 *)(iVar2 + 0x34),**(undefined4 **)(iVar18 + DAT_000265d8))
        ;
        if (iVar3 == 0) {
          iVar1 = 0;
        }
        else {
          FUN_00019490(DAT_000265e0 + 0x26b68,uVar15,uVar17,DAT_000265dc + 0x26b64);
          iVar9 = FUN_00018950(iVar2,&local_64,&local_4c,&local_50);
          iVar3 = DAT_000265e4;
          if (iVar9 < 0) {
            uVar15 = 0xc8a;
            uVar17 = 0x3e;
          }
          else {
            FUN_00018934(local_4c);
            iVar9 = local_4c;
            FUN_000182bc(local_98);
            if (*(int *)(*(int *)(iVar3 + 0x26e00) + 0x14) == *(int *)(iVar3 + 0x27168) &&
                *(int *)(*(int *)(iVar3 + 0x26e00) + 0x10) == *(int *)(iVar3 + 0x27164)) {
              if (*(int *)(iVar3 + 0x2716c) == 0) {
                iVar1 = FUN_00017f00(*(undefined4 *)(iVar3 + 0x26e74));
              }
              else {
                FUN_00018934();
                iVar1 = *(int *)(iVar3 + 0x2716c);
              }
            }
            else {
              iVar1 = FUN_00018c58(*(undefined4 *)(iVar3 + 0x26e74),(int *)(iVar3 + 0x27164),
                                   iVar3 + 0x2716c);
            }
            if (iVar1 == 0) {
              uVar15 = 0xc98;
            }
            else {
              local_48 = FUN_00017ee8(iVar1,*(undefined4 *)(DAT_000265e8 + 0x27084));
              if (local_48 == 0) {
                uVar15 = 0xc9a;
              }
              else {
                FUN_00017fec(iVar1);
                iVar1 = local_48;
                iVar3 = FUN_00018840(*(undefined4 *)(local_48 + 4),uVar6);
                if ((iVar3 == 0) || (iVar3 = *(int *)(iVar1 + 0xc), iVar3 == 0)) {
                  iVar3 = 0;
                  local_60 = FUN_0001ccc4(iVar1,iVar9);
                }
                else {
                  iVar12 = *(int *)(iVar1 + 8);
                  FUN_00018934(iVar3);
                  FUN_00018934(iVar12);
                  iVar1 = local_48;
                  local_48 = iVar12;
                  FUN_00017fec(iVar1);
                  local_60 = FUN_0001caa0(local_48,iVar3,iVar9);
                }
                FUN_000182bc(iVar3);
                if (local_60 != 0) {
                  FUN_00017fec(local_48);
                  local_48 = 0;
                  FUN_00017fec(local_60);
                  local_60 = 0;
                  FUN_00017fec(local_64);
                  local_64 = 0;
                  FUN_00017fec(local_4c);
                  local_4c = 0;
                  FUN_00017fec(local_50);
                  local_50 = 0;
                  FUN_0001a300(*(undefined4 *)(iVar2 + 0x50),local_54,local_58,local_5c);
                  local_98 = iVar9;
                  local_a8 = local_a0;
LAB_00026cd4:
                  local_a0 = local_a8;
                  iVar2 = DAT_00026584;
                  iVar12 = local_a4;
                  iVar3 = local_9c;
                  goto LAB_00025c00;
                }
                uVar15 = 0xca9;
                iVar1 = 0;
              }
            }
            uVar17 = 0x3f;
            local_98 = iVar9;
          }
        }
        FUN_0001a300(*(undefined4 *)(iVar2 + 0x50),local_54,local_58,local_5c);
        iVar9 = 0;
LAB_00026de4:
        iVar3 = local_9c;
        iVar12 = local_a4;
        iVar2 = 0;
        goto LAB_000262a4;
      }
      local_84 = local_64;
      uVar15 = 0xa71;
      iVar1 = 0;
    }
  }
  uVar17 = 0x28;
  iVar3 = local_84;
  iVar12 = local_84;
  iVar9 = local_84;
  iVar2 = local_84;
  local_ac = local_84;
  local_a0 = local_84;
  local_98 = local_84;
  local_94 = local_84;
  local_90 = local_84;
  local_88 = local_84;
LAB_000262a4:
  FUN_000182bc(local_64);
  uVar6 = 0;
  FUN_000182bc(iVar1);
  FUN_000182bc(local_60);
  FUN_000182bc(iVar2);
  FUN_000182bc(local_50);
  FUN_000182bc(local_4c);
  FUN_000182bc(iVar9);
  FUN_000182bc(local_48);
  FUN_00019490(DAT_000265b4 + 0x26304,uVar15,uVar17,DAT_000265b0 + 0x26300);
LAB_00026504:
  FUN_000182bc(local_ac);
  FUN_000182bc(local_88);
  FUN_000182bc(local_68);
  FUN_000182bc(local_94);
  FUN_000182bc(iVar3);
  FUN_000182bc(iVar12);
  FUN_000182bc(local_a0);
  FUN_000182bc(local_98);
  FUN_000182bc(local_84);
  FUN_000182bc(local_90);
  return uVar6;
LAB_0002812c:
  uVar15 = 0xb71;
  iVar1 = 0;
LAB_00025d30:
  uVar17 = 0x30;
  iVar9 = 0;
  iVar2 = 0;
  goto LAB_000262a4;
}




/* ============================================
 * Function: FUN_000282d0
 * Address:  0x282d0
 * ============================================ */

undefined4 FUN_000282d0(int param_1,undefined4 param_2)

{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  uint in_fpscr;
  double in_d0;
  undefined4 extraout_s1;
  double dVar4;
  
  iVar2 = DAT_0002840c + 0x282ec;
  uVar3 = *(undefined4 *)(param_1 + 4);
  iVar1 = FUN_00018840(uVar3,*(undefined4 *)(iVar2 + DAT_00028410));
  if (iVar1 != 0) {
    dVar4 = *(double *)(param_1 + 8);
    goto LAB_00028380;
  }
  iVar1 = FUN_00018840(uVar3,*(undefined4 *)(iVar2 + DAT_00028414));
  if (iVar1 == 0) {
    uVar3 = PyNumber_Add(param_1,param_2);
    return uVar3;
  }
  switch(*(int *)(param_1 + 8)) {
  case 0:
    dVar4 = 0.0;
    break;
  case 1:
    dVar4 = (double)VectorUnsignedToFloat
                              ((uint)*(ushort *)(param_1 + 0xc),(byte)(in_fpscr >> 0x15) & 3);
    break;
  case 2:
LAB_00028394:
    dVar4 = (double)VectorSignedToFloat((uint)*(ushort *)(param_1 + 0xc) |
                                        (uint)*(ushort *)(param_1 + 0xe) << 0xf,
                                        (byte)(in_fpscr >> 0x15) & 3);
    if (*(int *)(param_1 + 8) == -2) {
LAB_0002836c:
      dVar4 = -dVar4;
    }
    break;
  case -2:
    goto LAB_00028394;
  case -1:
    dVar4 = (double)VectorUnsignedToFloat
                              ((uint)*(ushort *)(param_1 + 0xc),(byte)(in_fpscr >> 0x15) & 3);
    goto LAB_0002836c;
  default:
    uVar3 = PyLong_AsDouble(param_1);
    dVar4 = (double)CONCAT44(extraout_s1,uVar3);
    if ((dVar4 == -1.0) && (iVar1 = PyErr_Occurred(), iVar1 != 0)) {
      return 0;
    }
  }
LAB_00028380:
  uVar3 = PyFloat_FromDouble(SUB84(dVar4 + in_d0,0));
  return uVar3;
}




/* ============================================
 * Function: FUN_00028418
 * Address:  0x28418
 * ============================================ */

undefined4 FUN_00028418(undefined4 param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  undefined4 uVar5;
  undefined4 uVar6;
  int iVar7;
  int iVar8;
  int iVar9;
  int iVar10;
  uint uVar11;
  int iVar12;
  int iVar13;
  int iVar14;
  undefined4 uVar15;
  int iVar16;
  int iVar17;
  int iVar18;
  int local_80;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  undefined4 local_3c;
  int local_38;
  int local_34 [3];
  undefined1 auStack_28 [4];
  
  iVar9 = DAT_000289e0;
  iVar4 = DAT_000289e4 + 0x28438;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  if (*(int *)(*(int *)(DAT_000289e0 + 0x286a0) + 0x14) ==
      *(int *)((int)&DAT_00028a40 + DAT_000289e0) &&
      *(int *)(*(int *)(DAT_000289e0 + 0x286a0) + 0x10) ==
      *(int *)((int)&DAT_00028a3c + DAT_000289e0)) {
    if (*(int *)((int)&DAT_00028a44 + DAT_000289e0) == 0) {
      iVar9 = FUN_00017f00(*(undefined4 *)(DAT_000289e0 + 0x28714));
    }
    else {
      FUN_00018934();
      iVar9 = *(int *)((int)&DAT_00028a44 + iVar9);
    }
  }
  else {
    iVar9 = FUN_00018c58(*(undefined4 *)(DAT_000289e0 + 0x28714),(int)&DAT_00028a3c + DAT_000289e0);
  }
  iVar10 = DAT_000289e8;
  if (iVar9 == 0) {
    uVar5 = 0x116f;
    local_80 = 0;
LAB_000297d4:
    uVar15 = 0x5f;
    iVar10 = local_80;
    iVar2 = local_80;
    iVar13 = local_80;
    iVar3 = local_80;
    iVar17 = local_80;
    iVar18 = local_80;
    iVar14 = local_80;
  }
  else {
    local_4c = FUN_00017ee8(iVar9,*(undefined4 *)(DAT_000289e8 + 0x28888));
    if (local_4c == 0) {
      uVar5 = 0x1171;
      local_80 = 0;
      goto LAB_000297d4;
    }
    FUN_00017fec(iVar9);
    iVar9 = FUN_00017ee8(param_1,*(undefined4 *)(iVar10 + 0x284e0));
    if (iVar9 == 0) {
      uVar5 = 0x1174;
      local_80 = 0;
      goto LAB_000297d4;
    }
    iVar10 = *(int *)(iVar10 + 0x28ab8);
    if (iVar10 == *(int *)(iVar4 + DAT_00028a58)) {
LAB_00028970:
      local_48 = PyNumber_Remainder(iVar10,iVar9);
    }
    else {
      iVar13 = *(int *)(iVar9 + 4);
      iVar2 = FUN_0001954c(*(undefined4 *)(iVar13 + 0x54),0x10000000);
      if (iVar2 != 0) {
        uVar5 = *(undefined4 *)(iVar4 + DAT_000289ec);
        iVar2 = FUN_00018840(iVar13,uVar5,iVar4,uVar5,uVar5);
        if (iVar2 == 0) goto LAB_00028970;
      }
      local_48 = PyUnicode_Format(iVar10,iVar9);
    }
    if (local_48 == 0) {
      uVar5 = 0x1176;
      local_80 = 0;
      local_48 = 0;
      goto LAB_000297d4;
    }
    FUN_00017fec(iVar9);
    iVar9 = local_4c;
    uVar6 = *(undefined4 *)(iVar4 + DAT_00028a40);
    iVar10 = FUN_00018840(*(undefined4 *)(local_4c + 4),uVar6);
    if ((iVar10 == 0) || (iVar10 = *(int *)(iVar9 + 0xc), iVar10 == 0)) {
      iVar10 = 0;
      local_50 = FUN_0001ccc4(iVar9,local_48);
    }
    else {
      iVar2 = *(int *)(iVar9 + 8);
      FUN_00018934(iVar10);
      FUN_00018934(iVar2);
      iVar9 = local_4c;
      local_4c = iVar2;
      FUN_00017fec(iVar9);
      local_50 = FUN_0001caa0(local_4c,iVar10,local_48);
    }
    FUN_000182bc(iVar10);
    FUN_00017fec(local_48);
    iVar9 = DAT_000289f0;
    local_80 = local_50;
    local_48 = 0;
    if (local_50 == 0) {
      uVar5 = 0x1186;
      iVar9 = 0;
      goto LAB_000297d4;
    }
    FUN_00017fec(local_4c);
    local_4c = 0;
    FUN_00017fec(local_50);
    local_50 = 0;
    local_4c = FUN_00017ee8(param_1,*(undefined4 *)(iVar9 + 0x28628));
    if (local_4c == 0) {
      uVar5 = 0x1192;
      local_80 = 0;
    }
    else {
      local_48 = FUN_00017ee8(local_4c,*(undefined4 *)(iVar9 + 0x28a70));
      if (local_48 == 0) {
        uVar5 = 0x1194;
        local_80 = 0;
      }
      else {
        FUN_00017fec(local_4c);
        iVar9 = local_48;
        local_4c = 0;
        iVar10 = FUN_00018840(*(undefined4 *)(local_48 + 4),uVar6);
        if ((iVar10 != 0) && (local_4c = *(int *)(iVar9 + 0xc), local_4c != 0)) {
          iVar10 = *(int *)(iVar9 + 8);
          FUN_00018934();
          FUN_00018934(iVar10);
          iVar9 = local_48;
          local_48 = iVar10;
          FUN_00017fec(iVar9);
        }
        if (local_4c == 0) {
          local_50 = FUN_0001cbcc(local_48);
        }
        else {
          local_50 = FUN_0001ccc4();
        }
        FUN_000182bc(local_4c);
        local_80 = local_50;
        local_4c = 0;
        if (local_50 != 0) {
          FUN_00017fec(local_48);
          iVar17 = local_50;
          iVar1 = DAT_000289f4;
          iVar7 = DAT_000289f4 + 0x28cf8;
          iVar8 = DAT_000289f4 + 0x28cf0;
          local_48 = 0;
          local_50 = 0;
          local_80 = 0;
          iVar18 = 0;
          iVar16 = 0;
LAB_000286ec:
          iVar9 = DAT_000289f8;
          local_48 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_000289f8 + 0x2873c));
          if (local_48 == 0) {
            uVar5 = 0x11b9;
LAB_00029904:
            iVar9 = 0;
            uVar15 = 0x62;
            iVar10 = iVar9;
            iVar2 = iVar9;
            iVar13 = iVar9;
            iVar3 = iVar9;
            iVar14 = iVar16;
            goto LAB_000293ac;
          }
          local_4c = FUN_00017ee8(local_48,*(undefined4 *)(iVar9 + 0x28b84));
          if (local_4c == 0) {
            uVar5 = 0x11bb;
            goto LAB_00029904;
          }
          FUN_00017fec(local_48);
          iVar9 = local_4c;
          local_48 = 0;
          iVar10 = FUN_00018840(*(undefined4 *)(local_4c + 4),uVar6);
          iVar14 = iVar16;
          if ((iVar10 != 0) && (local_48 = *(int *)(iVar9 + 0xc), local_48 != 0)) {
            iVar10 = *(int *)(iVar9 + 8);
            FUN_00018934();
            FUN_00018934(iVar10);
            iVar9 = local_4c;
            local_4c = iVar10;
            FUN_00017fec(iVar9);
            iVar14 = iVar16;
          }
          if (local_48 == 0) {
            local_50 = FUN_0001cbcc(local_4c);
          }
          else {
            local_50 = FUN_0001ccc4();
          }
          FUN_000182bc(local_48);
          local_48 = 0;
          if (local_50 == 0) {
            uVar5 = 0x11ca;
            iVar16 = iVar14;
            goto LAB_00029904;
          }
          FUN_00017fec(local_4c);
          local_4c = 0;
          local_4c = FUN_000282d0((int)DAT_000289d8,iVar17,*(undefined4 *)(iVar1 + 0x28968));
          if (local_4c == 0) {
            uVar5 = 0x11cd;
            iVar16 = iVar14;
            goto LAB_00029904;
          }
          local_48 = PyObject_RichCompare(local_50,local_4c,4);
          if (local_48 == 0) {
            uVar5 = 0x11cf;
            iVar16 = iVar14;
            goto LAB_00029904;
          }
          FUN_00017fec(local_50);
          local_50 = 0;
          FUN_00017fec(local_4c);
          local_4c = 0;
          iVar9 = FUN_00017f5c(local_48);
          if (iVar9 < 0) {
            uVar5 = 0x11d2;
            uVar15 = 0x62;
LAB_0002893c:
            iVar9 = 0;
            iVar10 = 0;
            iVar2 = 0;
            iVar13 = 0;
            iVar3 = 0;
            goto LAB_000293ac;
          }
          FUN_00017fec(local_48);
          local_48 = 0;
          if (iVar9 != 0) {
            if (*(int *)(*(int *)(iVar1 + 0x28934) + 0x14) == *(int *)(iVar1 + 0x28ce4) &&
                *(int *)(*(int *)(iVar1 + 0x28934) + 0x10) == *(int *)(iVar1 + 0x28ce0)) {
              if (*(int *)(iVar1 + 0x28ce8) == 0) {
                iVar9 = FUN_00017f00(*(undefined4 *)(iVar1 + 0x289c0));
              }
              else {
                FUN_00018934();
                iVar9 = *(int *)(iVar1 + 0x28ce8);
              }
            }
            else {
              iVar9 = FUN_00018c58(*(undefined4 *)(iVar1 + 0x289c0),iVar1 + 0x28ce0);
            }
            local_4c = iVar9;
            if (iVar9 == 0) {
              uVar5 = 0x11dd;
            }
            else {
              local_50 = 0;
              iVar4 = FUN_00018840(*(undefined4 *)(iVar9 + 4),uVar6);
              if ((iVar4 != 0) && (local_50 = *(int *)(iVar9 + 0xc), local_50 != 0)) {
                iVar4 = *(int *)(iVar9 + 8);
                FUN_00018934();
                FUN_00018934(iVar4);
                iVar9 = local_4c;
                local_4c = iVar4;
                FUN_00017fec(iVar9);
              }
              if (local_50 == 0) {
                local_48 = FUN_0001ccc4(local_4c,*(undefined4 *)(DAT_000289fc + 0x28f08));
              }
              else {
                local_48 = FUN_0001caa0();
              }
              FUN_000182bc(local_50);
              local_50 = 0;
              if (local_48 != 0) {
                uVar5 = 0x11f0;
                uVar15 = 99;
                FUN_00017fec(local_4c);
                local_4c = 0;
                FUN_0001a9cc(local_48,0,0);
                FUN_00017fec(local_48);
                local_48 = 0;
                goto LAB_0002893c;
              }
              uVar5 = 0x11eb;
            }
            iVar9 = 0;
            uVar15 = 99;
            iVar10 = iVar9;
            iVar2 = iVar9;
            iVar13 = iVar9;
            iVar3 = iVar9;
            goto LAB_000293ac;
          }
          iVar3 = _PyThreadState_UncheckedGet();
          FUN_00019f30(iVar3,&local_44,&local_40,&local_3c);
          if (*(int *)(*(int *)(iVar1 + 0x28934) + 0x14) == *(int *)(iVar1 + 0x28cf4) &&
              *(int *)(*(int *)(iVar1 + 0x28934) + 0x10) == *(int *)(iVar1 + 0x28cf0)) {
            if (*(int *)(iVar1 + 0x28cf8) == 0) {
              local_48 = FUN_00017f00(*(undefined4 *)(iVar1 + 0x289b4));
              iVar9 = iVar18;
            }
            else {
              FUN_00018934();
              local_48 = *(int *)(iVar1 + 0x28cf8);
              iVar9 = iVar18;
            }
          }
          else {
            local_48 = FUN_00018c58(*(undefined4 *)(iVar1 + 0x289b4),iVar8,iVar7);
            iVar9 = iVar18;
          }
          iVar10 = DAT_00028a00;
          if (local_48 != 0) {
            local_4c = FUN_00017ee8(local_48,*(undefined4 *)(DAT_00028a00 + 0x290fc));
            if (local_4c == 0) {
              uVar5 = 0x1214;
              iVar18 = iVar9;
              goto LAB_00028d04;
            }
            FUN_00017fec(local_48);
            local_48 = 0;
            local_48 = PyDict_New();
            if (local_48 == 0) {
              uVar5 = 0x1217;
              iVar18 = iVar9;
              goto LAB_00028d04;
            }
            iVar2 = PyDict_SetItem(local_48,*(undefined4 *)(iVar10 + 0x29100),param_3);
            if (iVar2 < 0) {
              uVar5 = 0x1219;
              iVar18 = iVar9;
              goto LAB_00028d04;
            }
            iVar2 = PyDict_SetItem(local_48,*(undefined4 *)(iVar10 + 0x28bc0),
                                   *(undefined4 *)(iVar10 + 0x28d70));
            if (iVar2 < 0) {
              uVar5 = 0x121a;
              iVar18 = iVar9;
              goto LAB_00028d04;
            }
            iVar2 = PyDict_SetItem(local_48,*(undefined4 *)(iVar10 + 0x29104),
                                   *(undefined4 *)(iVar4 + DAT_00028a04));
            if (iVar2 < 0) {
              uVar5 = 0x1223;
              iVar18 = iVar9;
              goto LAB_00028d04;
            }
            local_50 = FUN_00017e40(local_4c,*(undefined4 *)(iVar10 + 0x28b14),local_48);
            if (local_50 == 0) {
              uVar5 = 0x122c;
              local_50 = 0;
              iVar18 = iVar9;
              goto LAB_00028d04;
            }
            FUN_00017fec(local_4c);
            local_4c = 0;
            FUN_00017fec(local_48);
            iVar18 = local_50;
            local_48 = 0;
            FUN_000182bc(iVar9);
            local_50 = 0;
            iVar9 = FUN_00017a90(iVar18,*(undefined4 *)(iVar10 + 0x29108),param_2);
            if (iVar9 < 0) {
              uVar15 = 0x67;
              uVar5 = 0x123a;
              goto LAB_00028d08;
            }
            iVar9 = FUN_00017a90(iVar18,*(undefined4 *)(iVar10 + 0x28b84),param_4);
            if (iVar9 < 0) {
              uVar15 = 0x68;
              uVar5 = 0x1243;
              goto LAB_00028d08;
            }
            iVar9 = FUN_00017ee8(iVar18,*(undefined4 *)(iVar10 + 0x2910c));
            local_48 = iVar9;
            if (iVar9 == 0) {
              uVar5 = 0x124c;
LAB_00028fdc:
              uVar15 = 0x69;
              goto LAB_00028d08;
            }
            local_4c = 0;
            iVar10 = FUN_00018840(*(undefined4 *)(iVar9 + 4),uVar6);
            if ((iVar10 != 0) && (local_4c = *(int *)(iVar9 + 0xc), local_4c != 0)) {
              iVar10 = *(int *)(iVar9 + 8);
              FUN_00018934();
              FUN_00018934(iVar10);
              iVar9 = local_48;
              local_48 = iVar10;
              FUN_00017fec(iVar9);
            }
            if (local_4c == 0) {
              local_50 = FUN_0001cbcc(local_48);
            }
            else {
              local_50 = FUN_0001ccc4();
            }
            FUN_000182bc(local_4c);
            local_4c = 0;
            if (local_50 == 0) {
              uVar5 = 0x125a;
              goto LAB_00028fdc;
            }
            FUN_00017fec(local_48);
            local_48 = 0;
            FUN_00017fec(local_50);
            local_50 = 0;
            FUN_000182bc(local_44);
            local_44 = 0;
            FUN_000182bc(local_40);
            local_40 = 0;
            FUN_000182bc(local_3c);
            local_3c = 0;
            iVar9 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_00028a08 + 0x28d38));
            local_48 = iVar9;
            if (iVar9 == 0) {
              uVar5 = 0x1337;
              iVar3 = 0;
LAB_000295f4:
              iVar9 = 0;
              uVar15 = 0x6f;
              iVar10 = iVar9;
              iVar2 = iVar9;
              iVar13 = iVar9;
              goto LAB_000293ac;
            }
            local_4c = 0;
            uVar5 = *(undefined4 *)(iVar4 + DAT_00028a40);
            iVar2 = FUN_00018840(*(undefined4 *)(iVar9 + 4),uVar5,iVar4,uVar5,uVar5);
            iVar10 = 0;
            if ((iVar2 != 0) && (local_4c = *(int *)(iVar9 + 0xc), local_4c != 0)) {
              iVar2 = *(int *)(iVar9 + 8);
              FUN_00018934();
              iVar10 = 1;
              FUN_00018934(iVar2);
              iVar9 = local_48;
              local_48 = iVar2;
              FUN_00017fec(iVar9);
            }
            iVar9 = local_48;
            iVar13 = iVar10 + 2;
            uVar15 = *(undefined4 *)(local_48 + 4);
            uVar5 = *(undefined4 *)(iVar4 + DAT_00028a44);
            iVar2 = FUN_00018840(uVar15,uVar5,iVar4,uVar5,uVar5);
            if (iVar2 == 0) {
              uVar5 = *(undefined4 *)(iVar4 + DAT_00028a4c);
              iVar9 = FUN_00018840(uVar15,uVar5);
              if (((iVar9 == 0) && (iVar9 = PyType_IsSubtype(uVar15,uVar5), iVar9 == 0)) ||
                 ((*(uint *)(*(int *)(local_48 + 8) + 8) & 0xffffff8d) != 0x80)) {
                iVar3 = PyTuple_New(iVar13);
                iVar9 = DAT_00028a54;
                if (iVar3 == 0) {
                  uVar5 = 0x1356;
                }
                else {
                  iVar10 = iVar3 + iVar10 * 4;
                  if (local_4c != 0) {
                    *(int *)(iVar3 + 0xc) = local_4c;
                    local_4c = 0;
                  }
                  FUN_00018934(iVar18);
                  uVar5 = *(undefined4 *)(&UNK_00029d44 + iVar9);
                  *(int *)(iVar10 + 0xc) = iVar18;
                  FUN_00018934(uVar5);
                  *(undefined4 *)(iVar10 + 0x10) = *(undefined4 *)(&UNK_00029d44 + iVar9);
                  local_50 = FUN_00017e40(local_48,iVar3,0);
                  if (local_50 != 0) {
                    FUN_00017fec(iVar3);
                    goto LAB_00029734;
                  }
                  uVar5 = 0x1361;
                  local_50 = 0;
                }
              }
              else {
                local_34[0] = iVar18;
                local_38 = local_4c;
                local_34[1] = *(int *)(&UNK_00029cc4 + DAT_00028a50);
                local_50 = FUN_00017628(local_48,local_34 + -iVar10,iVar13);
                if (local_50 != 0) goto LAB_00029724;
                uVar5 = 0x1350;
                iVar3 = 0;
                local_50 = 0;
              }
              goto LAB_000295f4;
            }
            local_34[0] = iVar18;
            local_38 = local_4c;
            local_34[1] = *(int *)(&UNK_00029c24 + DAT_00028a48);
            local_50 = FUN_0001b728(iVar9,local_34 + -iVar10,iVar13);
            if (local_50 == 0) {
              uVar5 = 0x1348;
              iVar3 = 0;
              local_50 = 0;
              goto LAB_000295f4;
            }
LAB_00029724:
            FUN_000182bc(local_4c);
            local_4c = 0;
LAB_00029734:
            FUN_00017fec(local_48);
            iVar9 = local_50;
            local_48 = 0;
            FUN_000182bc(local_80);
            local_50 = 0;
            iVar10 = FUN_00017f5c(iVar9);
            if (iVar10 < 0) {
              uVar15 = 0x70;
              uVar5 = 0x1370;
              local_80 = iVar9;
              goto LAB_0002893c;
            }
            iVar16 = iVar14;
            local_80 = iVar9;
            if (iVar10 != 0) goto code_r0x00029768;
            goto LAB_000286ec;
          }
          uVar5 = 0x1212;
          iVar18 = iVar9;
LAB_00028d04:
          uVar15 = 0x65;
LAB_00028d08:
          FUN_000182bc(local_50);
          local_50 = 0;
          FUN_000182bc(0);
          FUN_000182bc(local_4c);
          local_4c = 0;
          FUN_000182bc(local_48);
          iVar9 = DAT_00028a0c;
          local_48 = 0;
          FUN_00017668(iVar3,&local_50,&local_48,&local_4c);
          if (*(int *)(*(int *)(iVar9 + 0x28fc0) + 0x14) == *(int *)(iVar9 + 0x293a0) &&
              *(int *)(*(int *)(iVar9 + 0x28fc0) + 0x10) == *(int *)(iVar9 + 0x2939c)) {
            if (*(int *)(iVar9 + 0x293a4) == 0) {
              iVar9 = FUN_00017f00(*(undefined4 *)(iVar9 + 0x29040));
            }
            else {
              FUN_00018934();
              iVar9 = *(int *)(iVar9 + 0x293a4);
            }
          }
          else {
            iVar9 = FUN_00018c58(*(undefined4 *)(iVar9 + 0x29040),iVar9 + 0x2939c);
          }
          iVar10 = DAT_00028a10;
          if (iVar9 == 0) {
            uVar5 = 0x1279;
            iVar16 = iVar14;
LAB_0002938c:
            iVar10 = 0;
            uVar15 = 0x6a;
            iVar2 = iVar10;
            iVar13 = iVar10;
          }
          else {
            iVar2 = FUN_00017ee8(iVar9,*(undefined4 *)(DAT_00028a10 + 0x293f0));
            if (iVar2 == 0) {
              uVar5 = 0x127b;
              iVar16 = iVar14;
              goto LAB_0002938c;
            }
            FUN_00017fec(iVar9);
            iVar9 = FUN_00019adc(local_50,*(undefined4 *)(iVar10 + 0x28da4));
            if ((iVar9 == 0) &&
               (iVar9 = FUN_00019adc(local_50,*(undefined4 *)(iVar10 + 0x28dac)), iVar9 == 0)) {
              iVar9 = FUN_00019adc(local_50,iVar2);
              uVar11 = (uint)(iVar9 != 0);
            }
            else {
              uVar11 = 1;
            }
            FUN_00017fec(iVar2);
            FUN_000182c8(iVar3,local_50,local_48,local_4c);
            local_50 = 0;
            local_48 = 0;
            local_4c = 0;
            iVar16 = iVar14;
            if (uVar11 == 0) {
LAB_00029430:
              iVar9 = 0;
              iVar10 = iVar9;
              iVar2 = iVar9;
              iVar13 = iVar9;
            }
            else {
              FUN_00019490(DAT_00028a18 + 0x28e18,uVar5,uVar15,DAT_00028a14 + 0x28e14);
              iVar10 = FUN_00018950(iVar3,&local_4c,&local_48,&local_50);
              iVar9 = DAT_00028a1c;
              if (iVar10 < 0) {
                uVar5 = 0x1284;
                uVar15 = 0x6a;
                iVar16 = iVar14;
                goto LAB_00029430;
              }
              FUN_00018934(local_48);
              iVar16 = local_48;
              FUN_000182bc(iVar14);
              if (*(int *)(*(int *)(iVar9 + 0x290b0) + 0x14) == *(int *)(iVar9 + 0x294a0) &&
                  *(int *)(*(int *)(iVar9 + 0x290b0) + 0x10) == *(int *)(iVar9 + 0x2949c)) {
                if (*(int *)(iVar9 + 0x294a4) == 0) {
                  iVar9 = FUN_00017f00(*(undefined4 *)(iVar9 + 0x29124));
                }
                else {
                  FUN_00018934();
                  iVar9 = *(int *)(iVar9 + 0x294a4);
                }
              }
              else {
                iVar9 = FUN_00018c58(*(undefined4 *)(iVar9 + 0x29124),iVar9 + 0x2949c);
              }
              iVar10 = DAT_00028a20;
              if (iVar9 == 0) {
                uVar5 = 0x1292;
                iVar10 = 0;
                iVar2 = 0;
                iVar13 = 0;
              }
              else {
                iVar2 = FUN_00017ee8(iVar9,*(undefined4 *)(DAT_00028a20 + 0x2924c));
                if (iVar2 == 0) {
                  uVar5 = 0x1294;
                  iVar10 = 0;
                  iVar13 = 0;
                  goto LAB_00028f7c;
                }
                FUN_00017fec(iVar9);
                iVar9 = FUN_00017ee8(param_1,*(undefined4 *)(iVar10 + 0x28ed4));
                if (iVar9 == 0) {
                  uVar5 = 0x129f;
                  uVar15 = 0x6c;
                  iVar10 = 0;
                  iVar13 = 0;
                  goto LAB_00029390;
                }
                iVar10 = FUN_00018840(*(undefined4 *)(iVar2 + 4),uVar6);
                iVar14 = iVar2;
                if (iVar10 == 0) {
                  iVar13 = 0;
                  uVar11 = 0;
                }
                else {
                  iVar13 = *(int *)(iVar2 + 0xc);
                  if (iVar13 == 0) {
                    uVar11 = 0;
                  }
                  else {
                    iVar14 = *(int *)(iVar2 + 8);
                    FUN_00018934(iVar13);
                    FUN_00018934(iVar14);
                    FUN_00017fec(iVar2);
                  }
                }
                iVar12 = uVar11 + 3;
                uVar15 = *(undefined4 *)(iVar14 + 4);
                uVar5 = *(undefined4 *)(iVar4 + DAT_00028a44);
                iVar10 = FUN_00018840(uVar15,uVar5);
                iVar2 = iVar14;
                if (iVar10 == 0) {
                  uVar5 = *(undefined4 *)(iVar4 + DAT_00028a4c);
                  iVar10 = FUN_00018840(uVar15,uVar5);
                  if (((iVar10 == 0) && (iVar10 = PyType_IsSubtype(uVar15,uVar5), iVar10 == 0)) ||
                     ((*(uint *)(*(int *)(iVar14 + 8) + 8) & 0xffffff8d) != 0x80)) {
                    iVar10 = PyTuple_New(iVar12);
                    if (iVar10 == 0) {
                      uVar5 = 0x12c0;
                    }
                    else {
                      iVar12 = iVar10 + uVar11 * 4;
                      if (iVar13 != 0) {
                        *(int *)(iVar10 + 0xc) = iVar13;
                      }
                      iVar13 = DAT_00028a2c;
                      FUN_00018934(*(undefined4 *)(DAT_00028a2c + 0x2977c));
                      uVar5 = *(undefined4 *)(iVar13 + 0x2977c);
                      *(int *)(iVar12 + 0x10) = iVar9;
                      *(undefined4 *)(iVar12 + 0xc) = uVar5;
                      FUN_00018934(iVar16);
                      *(int *)(iVar12 + 0x14) = iVar16;
                      iVar12 = FUN_00017e40(iVar14,iVar10,0);
                      if (iVar12 != 0) {
                        FUN_00017fec(iVar10);
                        goto LAB_0002916c;
                      }
                      uVar5 = 0x12ce;
                      iVar9 = 0;
                      iVar13 = 0;
                    }
                  }
                  else {
                    local_34[0] = *(int *)(DAT_00028a28 + 0x29710);
                    local_34[2] = iVar16;
                    local_38 = iVar13;
                    local_34[1] = iVar9;
                    iVar12 = FUN_00017628(iVar14,local_34 + -uVar11,iVar12);
                    if (iVar12 != 0) goto LAB_00029158;
                    uVar5 = 0x12b9;
                    iVar10 = 0;
                  }
                  goto LAB_00028f7c;
                }
                local_34[0] = *(int *)(DAT_00028a24 + 0x295b4);
                local_34[2] = iVar16;
                local_38 = iVar13;
                local_34[1] = iVar9;
                iVar12 = FUN_0001b728(iVar14,local_34 + -uVar11,iVar12,auStack_28,iVar18,uVar5);
                if (iVar12 != 0) {
LAB_00029158:
                  FUN_000182bc(iVar13);
                  FUN_00017fec(iVar9);
LAB_0002916c:
                  iVar13 = DAT_00028a30;
                  FUN_00017fec(iVar14);
                  FUN_00017fec(iVar12);
                  iVar2 = FUN_00017ee8(param_1,*(undefined4 *)(iVar13 + 0x291c0));
                  if (iVar2 == 0) {
                    uVar5 = 0x12dc;
                    iVar9 = 0;
                    iVar10 = 0;
                    iVar13 = 0;
                  }
                  else {
                    iVar10 = FUN_00017ee8(iVar2,*(undefined4 *)(iVar13 + 0x297e8));
                    if (iVar10 == 0) {
                      uVar5 = 0x12de;
                      iVar9 = 0;
                      iVar13 = 0;
                    }
                    else {
                      FUN_00017fec(iVar2);
                      iVar9 = FUN_00017ee8(param_1,*(undefined4 *)(iVar13 + 0x291c0));
                      if (iVar9 == 0) {
                        uVar5 = 0x12e1;
                        iVar2 = 0;
                        iVar13 = 0;
                      }
                      else {
                        iVar13 = FUN_00017ee8(iVar9,*(undefined4 *)(iVar13 + 0x29608));
                        if (iVar13 == 0) {
                          uVar5 = 0x12e3;
                          iVar2 = 0;
                        }
                        else {
                          FUN_00017fec(iVar9);
                          uVar5 = *(undefined4 *)(iVar4 + DAT_00028a40);
                          iVar9 = FUN_00018840(*(undefined4 *)(iVar13 + 4),uVar5);
                          if ((iVar9 == 0) || (iVar9 = *(int *)(iVar13 + 0xc), iVar9 == 0)) {
                            iVar9 = 0;
                            iVar2 = FUN_0001cbcc(iVar13);
                          }
                          else {
                            iVar14 = *(int *)(iVar13 + 8);
                            FUN_00018934(iVar9);
                            FUN_00018934(iVar14);
                            FUN_00017fec(iVar13);
                            iVar2 = FUN_0001ccc4(iVar14,iVar9);
                            iVar13 = iVar14;
                          }
                          FUN_000182bc(iVar9);
                          if (iVar2 == 0) {
                            uVar5 = 0x12f2;
                            iVar9 = 0;
                          }
                          else {
                            FUN_00017fec(iVar13);
                            iVar9 = FUN_000282d0(0,iVar2,*(undefined4 *)(DAT_00028a34 + 0x29500));
                            if (iVar9 == 0) {
                              uVar5 = 0x12f5;
                              iVar9 = 0;
                              iVar13 = 0;
                            }
                            else {
                              FUN_00017fec(iVar2);
                              iVar2 = FUN_00018840(*(undefined4 *)(iVar10 + 4),uVar5);
                              if ((iVar2 == 0) || (iVar2 = *(int *)(iVar10 + 0xc), iVar2 == 0)) {
                                iVar2 = 0;
                                iVar13 = FUN_0001ccc4(iVar10,iVar9);
                              }
                              else {
                                iVar14 = *(int *)(iVar10 + 8);
                                FUN_00018934(iVar2);
                                FUN_00018934(iVar14);
                                FUN_00017fec(iVar10);
                                iVar13 = FUN_0001caa0(iVar14,iVar2,iVar9);
                                iVar10 = iVar14;
                              }
                              FUN_000182bc(iVar2);
                              FUN_00017fec(iVar9);
                              if (iVar13 != 0) {
                                FUN_00017fec(iVar10);
                                FUN_00017fec(iVar13);
                                FUN_00017fec(local_4c);
                                local_4c = 0;
                                FUN_00017fec(local_48);
                                local_48 = 0;
                                FUN_00017fec(local_50);
                                local_50 = 0;
                                FUN_0001a300(*(undefined4 *)(iVar3 + 0x50),local_44,local_40,
                                             local_3c);
                                goto LAB_000286ec;
                              }
                              uVar5 = 0x1305;
                              iVar9 = 0;
                              iVar2 = 0;
                              iVar13 = 0;
                            }
                          }
                        }
                      }
                    }
                  }
                  uVar15 = 0x6d;
                  goto LAB_00029390;
                }
                uVar5 = 0x12b0;
                iVar10 = 0;
              }
LAB_00028f7c:
              uVar15 = 0x6b;
            }
          }
LAB_00029390:
          FUN_0001a300(*(undefined4 *)(iVar3 + 0x50),local_44,local_40,local_3c);
          iVar3 = 0;
          iVar14 = iVar16;
          goto LAB_000293ac;
        }
        uVar5 = 0x11a3;
      }
    }
    uVar15 = 0x60;
    iVar9 = local_80;
    iVar10 = local_80;
    iVar2 = local_80;
    iVar13 = local_80;
    iVar3 = local_80;
    iVar17 = local_80;
    iVar18 = local_80;
    iVar14 = local_80;
  }
LAB_000293ac:
  FUN_000182bc(local_50);
  FUN_000182bc(iVar9);
  FUN_000182bc(local_4c);
  FUN_000182bc(local_48);
  FUN_000182bc(iVar3);
  FUN_000182bc(iVar2);
  FUN_000182bc(iVar13);
  uVar6 = 0;
  FUN_000182bc(iVar10);
  FUN_00019490(DAT_00028a3c + 0x2940c,uVar5,uVar15,DAT_00028a38 + 0x29408);
  iVar9 = local_80;
LAB_00029784:
  FUN_000182bc(iVar17);
  FUN_000182bc(iVar18);
  FUN_000182bc(iVar14);
  FUN_000182bc(iVar9);
  return uVar6;
code_r0x00029768:
  uVar6 = *(undefined4 *)(iVar4 + DAT_00028a58);
  FUN_00018934(uVar6);
  goto LAB_00029784;
}




/* ============================================
 * Function: FUN_0002a308
 * Address:  0x2a308
 * ============================================ */

void FUN_0002a308(int param_1,undefined4 param_2,undefined4 param_3)

{
  int iVar1;
  uint uVar2;
  uint uVar3;
  int extraout_r2;
  uint uVar4;
  code *pcVar5;
  int iVar6;
  undefined4 uVar7;
  int iVar8;
  
  iVar6 = DAT_0002a524 + 0x2a324;
  uVar7 = *(undefined4 *)(param_1 + 4);
  iVar8 = *(int *)(iVar6 + DAT_0002a528);
  iVar1 = FUN_00018840(uVar7,iVar8,param_3,DAT_0002a528,param_1,param_2,param_3);
  if (iVar1 == 0) {
    iVar1 = FUN_00018840(uVar7,*(undefined4 *)(iVar6 + DAT_0002a52c));
    if (iVar1 != 0) {
      PyFloat_FromDouble(SUB84(*(double *)(param_1 + 8) - 1.0,0));
      return;
    }
    iVar1 = DAT_0002a530;
    if (extraout_r2 != 0) {
      iVar1 = DAT_0002a534;
    }
    pcVar5 = *(code **)(iVar6 + iVar1);
    goto LAB_0002a4c4;
  }
  iVar1 = *(int *)(param_1 + 8);
  if (iVar1 + 1U < 3) {
    uVar4 = 0;
    if ((iVar1 != 0) && (uVar4 = (uint)*(ushort *)(param_1 + 0xc), iVar1 == -1)) {
      uVar4 = -uVar4;
    }
    goto LAB_0002a3ac;
  }
  switch(iVar1) {
  case 0:
    break;
  case 1:
    break;
  case 2:
    uVar4 = (uint)*(ushort *)(param_1 + 0xc) | (uint)*(ushort *)(param_1 + 0xe) << 0xf;
LAB_0002a3ac:
    PyLong_FromLong(uVar4 - 1);
    return;
  case 3:
    uVar4 = (uint)*(ushort *)(param_1 + 0x10);
    goto LAB_0002a430;
  case 4:
    uVar4 = (uint)*(ushort *)(param_1 + 0x12) << 0xf | (uint)*(ushort *)(param_1 + 0x10);
LAB_0002a430:
    uVar3 = (uVar4 >> 0x11) << 0xf | (uVar4 << 0xf) >> 0x11;
    uVar4 = (uVar4 << 0xf | (uint)*(ushort *)(param_1 + 0xe)) << 0xf |
            (uint)*(ushort *)(param_1 + 0xc);
    goto LAB_0002a414;
  case -4:
    uVar3 = (uint)*(ushort *)(param_1 + 0x12) << 0xf | (uint)*(ushort *)(param_1 + 0x10);
    goto LAB_0002a3d4;
  case -3:
    uVar3 = (uint)*(ushort *)(param_1 + 0x10);
LAB_0002a3d4:
    uVar2 = (uVar3 << 0xf | (uint)*(ushort *)(param_1 + 0xe)) << 0xf |
            (uint)*(ushort *)(param_1 + 0xc);
    uVar4 = -uVar2;
    uVar3 = -(((uVar3 >> 0x11) << 0xf | (uVar3 << 0xf) >> 0x11) + (uint)(uVar2 != 0));
LAB_0002a414:
    PyLong_FromLongLong(uVar4 - 1,uVar3 - (uVar4 == 0));
    return;
  case -2:
    uVar4 = -((uint)*(ushort *)(param_1 + 0xc) | (uint)*(ushort *)(param_1 + 0xe) << 0xf);
    goto LAB_0002a3ac;
  case -1:
  }
  pcVar5 = *(code **)(*(int *)(iVar8 + 0x30) + 4);
LAB_0002a4c4:
  (*pcVar5)(param_1,param_2);
  return;
}




/* ============================================
 * Function: FUN_0002a538
 * Address:  0x2a538
 * ============================================ */

int FUN_0002a538(undefined4 param_1,undefined4 param_2,int param_3,undefined4 param_4,
                undefined4 param_5,undefined4 param_6)

{
  int iVar1;
  int iVar2;
  int iVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  undefined4 uVar9;
  int iVar10;
  undefined4 uVar11;
  undefined4 uVar12;
  undefined4 uVar13;
  int iVar14;
  int iVar15;
  int iVar16;
  int local_88;
  int local_84;
  int local_58;
  int local_54;
  int local_50;
  int local_4c;
  int local_48;
  undefined4 local_44;
  undefined4 local_40;
  int local_3c;
  int local_38;
  int local_34 [4];
  
  iVar2 = DAT_0002b32c;
  iVar6 = DAT_0002b330 + 0x2a564;
  local_58 = 0;
  local_54 = 0;
  local_50 = 0;
  local_4c = 0;
  local_48 = 0;
  local_44 = 0;
  local_40 = 0;
  local_3c = 0;
  local_84 = FUN_00018e60(*(undefined4 *)(DAT_0002b32c + 0x2a574),
                          *(undefined4 *)(DAT_0002b32c + 0x2a5a4),0);
  if (local_84 == 0) {
    uVar12 = 0x1b17;
    uVar13 = 0x9d;
    local_84 = *(int *)(iVar6 + DAT_0002b334);
    FUN_00018934(local_84);
    iVar1 = 0;
    iVar2 = 0;
    iVar5 = 0;
    iVar4 = 0;
    iVar3 = 0;
    iVar16 = 0;
    local_88 = 0;
    goto LAB_0002a5e8;
  }
  *(undefined4 *)(local_84 + 8) = param_2;
  FUN_00018934(param_2);
  local_58 = FUN_0001afd4(local_84);
  if (local_58 == 0) {
    uVar12 = 0x1b26;
    iVar1 = 0;
  }
  else {
    iVar1 = PyUnicode_Join(*(undefined4 *)(iVar2 + 0x2abc8),local_58);
    if (iVar1 != 0) {
      local_54 = iVar1;
      FUN_00017fec(local_58);
      iVar16 = local_54;
      local_58 = 0;
      local_54 = 0;
      iVar1 = FUN_00017f5c(param_6);
      if (iVar1 < 0) {
        uVar12 = 0x1b35;
        uVar13 = 0x9f;
LAB_0002bac0:
        local_88 = 0;
        iVar1 = 0;
        iVar2 = 0;
        iVar5 = 0;
        iVar4 = 0;
        iVar3 = 0;
        goto LAB_0002a5e8;
      }
      if (iVar1 == 0) {
        iVar14 = *(int *)(iVar2 + 0x2a804);
        FUN_00018934(iVar14);
LAB_0002a75c:
        iVar5 = DAT_0002b344;
        local_88 = 0;
        iVar7 = DAT_0002b344 + 0x2ae00;
        iVar8 = DAT_0002b344 + 0x2adf8;
        while (iVar3 = FUN_0002a308(iVar14,*(undefined4 *)(iVar5 + 0x2aa1c),1), iVar3 != 0) {
          local_54 = iVar3;
          FUN_00017fec(iVar14);
          local_54 = 0;
          if (*(int *)(*(int *)(iVar5 + 0x2a9dc) + 0x14) == *(int *)(iVar5 + 0x2adfc) &&
              *(int *)(*(int *)(iVar5 + 0x2a9dc) + 0x10) == *(int *)(iVar5 + 0x2adf8)) {
            if (*(int *)(iVar5 + 0x2ae00) == 0) {
              local_50 = FUN_00017f00(*(undefined4 *)(iVar5 + 0x2aa50));
            }
            else {
              FUN_00018934();
              local_50 = *(int *)(iVar5 + 0x2ae00);
            }
          }
          else {
            local_50 = FUN_00018c58(*(undefined4 *)(iVar5 + 0x2aa50),iVar8,iVar7);
          }
          iVar2 = DAT_0002b348;
          if (local_50 == 0) {
            uVar12 = 0x1b82;
LAB_0002bb50:
            iVar1 = 0;
            uVar13 = 0xa6;
            iVar2 = iVar1;
            iVar5 = iVar1;
            iVar4 = iVar1;
            goto LAB_0002a5e8;
          }
          local_58 = FUN_00017ee8(local_50,*(undefined4 *)(DAT_0002b348 + 0x2abf4));
          if (local_58 == 0) {
            uVar12 = 0x1b84;
            goto LAB_0002bb50;
          }
          FUN_00017fec(local_50);
          local_50 = 0;
          local_50 = PyTuple_New(2);
          if (local_50 == 0) {
            uVar12 = 0x1b87;
            goto LAB_0002bb50;
          }
          FUN_00018934(iVar3);
          *(int *)(local_50 + 0xc) = iVar3;
          FUN_00018934(iVar16);
          uVar12 = *(undefined4 *)(iVar2 + 0x2aea4);
          *(int *)(local_50 + 0x10) = iVar16;
          iVar2 = PyUnicode_Format(uVar12);
          if (iVar2 == 0) {
            uVar12 = 0x1b8f;
            goto LAB_0002bb50;
          }
          FUN_00017fec(local_50);
          iVar1 = local_58;
          local_50 = 0;
          uVar12 = *(undefined4 *)(iVar6 + DAT_0002b398);
          iVar4 = FUN_00018840(*(undefined4 *)(local_58 + 4),uVar12);
          if ((iVar4 != 0) && (local_50 = *(int *)(iVar1 + 0xc), local_50 != 0)) {
            iVar4 = *(int *)(iVar1 + 8);
            FUN_00018934();
            FUN_00018934(iVar4);
            iVar1 = local_58;
            local_58 = iVar4;
            FUN_00017fec(iVar1);
          }
          if (local_50 == 0) {
            local_54 = FUN_0001ccc4(local_58,iVar2);
          }
          else {
            local_54 = FUN_0001caa0(local_58,local_50,iVar2);
          }
          FUN_000182bc(local_50);
          local_50 = 0;
          FUN_00017fec(iVar2);
          if (local_54 == 0) {
            uVar12 = 0x1b9f;
            goto LAB_0002bb50;
          }
          FUN_00017fec(local_58);
          local_58 = 0;
          FUN_00017fec(local_54);
          iVar2 = DAT_0002b34c;
          local_54 = 0;
          local_58 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_0002b34c + 0x2aa3c));
          if (local_58 == 0) {
            uVar12 = 0x1bab;
            iVar2 = 0;
            iVar4 = 0;
LAB_0002aacc:
            iVar1 = 0;
            uVar13 = 0xa7;
            iVar5 = iVar1;
            goto LAB_0002a5e8;
          }
          iVar4 = PyNumber_Add(param_4,param_5);
          if (iVar4 == 0) {
            uVar12 = 0x1bad;
            iVar2 = 0;
            goto LAB_0002aacc;
          }
          if (*(int *)(*(int *)(iVar2 + 0x2abac) + 0x14) == *(int *)(iVar2 + 0x2afdc) &&
              *(int *)(*(int *)(iVar2 + 0x2abac) + 0x10) == *(int *)(iVar2 + 0x2afd8)) {
            if (*(int *)(iVar2 + 0x2afe0) == 0) {
              local_4c = FUN_00017f00(*(undefined4 *)(iVar2 + 0x2ac48));
            }
            else {
              FUN_00018934();
              local_4c = *(int *)(iVar2 + 0x2afe0);
            }
          }
          else {
            local_4c = FUN_00018c58(*(undefined4 *)(iVar2 + 0x2ac48),iVar2 + 0x2afd8);
          }
          if (local_4c == 0) {
            uVar12 = 0x1baf;
            iVar2 = 0;
            goto LAB_0002aacc;
          }
          iVar1 = 0;
          iVar2 = PyObject_RichCompare(param_3,local_4c,0);
          if (iVar2 == 0) {
            uVar12 = 0x1bb1;
            goto LAB_0002aacc;
          }
          FUN_00017fec(local_4c);
          local_4c = 0;
          iVar14 = FUN_00017f5c(iVar2);
          if (iVar14 < 0) {
            uVar12 = 0x1bb3;
            uVar13 = 0xa7;
            iVar5 = 0;
            goto LAB_0002a5e8;
          }
          FUN_00017fec(iVar2);
          if (iVar14 == 0) {
            iVar2 = *(int *)(DAT_0002b358 + 0x2ae24);
            FUN_00018934(iVar2);
            local_50 = iVar2;
          }
          else {
            FUN_00018934(param_3);
            local_50 = param_3;
          }
          iVar1 = local_58;
          iVar2 = FUN_00018840(*(undefined4 *)(local_58 + 4),uVar12);
          if (iVar2 == 0) {
            iVar2 = 0;
            iVar1 = 0;
          }
          else {
            iVar2 = *(int *)(iVar1 + 0xc);
            if (iVar2 == 0) {
              iVar1 = 0;
            }
            else {
              iVar10 = *(int *)(iVar1 + 8);
              iVar1 = 1;
              FUN_00018934(iVar2);
              FUN_00018934(iVar10);
              iVar14 = local_58;
              local_58 = iVar10;
              FUN_00017fec(iVar14);
            }
          }
          iVar14 = local_58;
          iVar15 = iVar1 + 3;
          uVar11 = *(undefined4 *)(local_58 + 4);
          uVar13 = *(undefined4 *)(iVar6 + DAT_0002b350);
          iVar10 = FUN_00018840(uVar11,uVar13);
          if (iVar10 == 0) {
            uVar9 = *(undefined4 *)(iVar6 + DAT_0002b39c);
            iVar14 = FUN_00018840(uVar11,uVar9);
            if (((iVar14 == 0) && (iVar14 = PyType_IsSubtype(uVar11,uVar9), iVar14 == 0)) ||
               ((*(uint *)(*(int *)(local_58 + 8) + 8) & 0xffffff8d) != 0x80)) {
              local_4c = PyTuple_New(iVar15);
              if (local_4c == 0) {
                uVar12 = 0x1bdd;
              }
              else {
                if (iVar2 != 0) {
                  *(int *)(local_4c + 0xc) = iVar2;
                }
                FUN_00018934(*(undefined4 *)(local_84 + 8));
                iVar2 = local_4c + iVar1 * 4;
                *(undefined4 *)(iVar2 + 0xc) = *(undefined4 *)(local_84 + 8);
                *(int *)(iVar2 + 0x10) = iVar4;
                *(int *)(iVar2 + 0x14) = local_50;
                local_50 = 0;
                local_54 = FUN_00017e40(local_58,local_4c,0);
                if (local_54 != 0) {
                  FUN_00017fec(local_4c);
                  local_4c = 0;
                  goto LAB_0002acc8;
                }
                uVar12 = 0x1beb;
                iVar2 = 0;
                iVar4 = 0;
                local_54 = 0;
              }
            }
            else {
              local_34[0] = *(int *)(local_84 + 8);
              local_34[2] = local_50;
              local_38 = iVar2;
              local_34[1] = iVar4;
              local_54 = FUN_00017628(local_58,local_34 + -iVar1,iVar15);
              if (local_54 != 0) goto LAB_0002aca8;
              uVar12 = 0x1bd5;
              local_54 = 0;
            }
            goto LAB_0002aacc;
          }
          local_34[0] = *(int *)(local_84 + 8);
          local_34[2] = local_50;
          local_38 = iVar2;
          local_34[1] = iVar4;
          local_54 = FUN_0001b728(iVar14,local_34 + -iVar1,iVar15);
          if (local_54 == 0) {
            uVar12 = 0x1bcb;
            local_54 = 0;
            goto LAB_0002aacc;
          }
LAB_0002aca8:
          FUN_000182bc(iVar2);
          FUN_00017fec(iVar4);
          FUN_00017fec(local_50);
          local_50 = 0;
LAB_0002acc8:
          FUN_00017fec(local_58);
          iVar14 = local_54;
          local_58 = 0;
          iVar1 = local_54;
          FUN_000182bc(local_88);
          iVar2 = DAT_0002b35c;
          local_54 = 0;
          if (*(int *)(*(int *)(DAT_0002b35c + 0x2af60) + 0x14) ==
              *(int *)((int)&DAT_0002b3a0 + DAT_0002b35c) &&
              *(int *)(*(int *)(DAT_0002b35c + 0x2af60) + 0x10) ==
              *(int *)((int)&DAT_0002b39c + DAT_0002b35c)) {
            if (*(int *)(DAT_0002b35c + 0x2b3a4) == 0) {
              local_58 = FUN_00017f00(*(undefined4 *)(DAT_0002b35c + 0x2afd4));
            }
            else {
              FUN_00018934();
              local_58 = *(int *)(iVar2 + 0x2b3a4);
            }
          }
          else {
            local_58 = FUN_00018c58(*(undefined4 *)(DAT_0002b35c + 0x2afd4),
                                    (int)&DAT_0002b39c + DAT_0002b35c);
          }
          iVar2 = DAT_0002b360;
          if (local_58 == 0) {
            uVar12 = 0x1bfa;
LAB_0002bc34:
            iVar1 = 0;
            local_88 = iVar14;
            uVar13 = 0xa8;
            iVar2 = iVar1;
            iVar5 = iVar1;
            iVar4 = iVar1;
            goto LAB_0002a5e8;
          }
          local_4c = FUN_00017ee8(local_58,*(undefined4 *)(DAT_0002b360 + 0x2b124));
          if (local_4c == 0) {
            uVar12 = 0x1bfc;
            goto LAB_0002bc34;
          }
          FUN_00017fec(local_58);
          local_58 = 0;
          local_58 = PyUnicode_Format(*(undefined4 *)(iVar2 + 0x2b3f4),iVar16);
          iVar2 = local_4c;
          if (local_58 == 0) {
            uVar12 = 0x1bff;
            local_58 = 0;
            goto LAB_0002bc34;
          }
          local_50 = 0;
          iVar4 = FUN_00018840(*(undefined4 *)(local_4c + 4),uVar12);
          if ((iVar4 != 0) && (local_50 = *(int *)(iVar2 + 0xc), local_50 != 0)) {
            iVar4 = *(int *)(iVar2 + 8);
            FUN_00018934();
            FUN_00018934(iVar4);
            iVar2 = local_4c;
            local_4c = iVar4;
            FUN_00017fec(iVar2);
          }
          if (local_50 == 0) {
            local_54 = FUN_0001ccc4(local_4c,local_58);
          }
          else {
            local_54 = FUN_0001caa0();
          }
          FUN_000182bc(local_50);
          local_50 = 0;
          FUN_00017fec(local_58);
          local_58 = 0;
          if (local_54 == 0) {
            uVar12 = 0x1c0e;
            goto LAB_0002bc34;
          }
          FUN_00017fec(local_4c);
          local_4c = 0;
          FUN_00017fec(local_54);
          iVar2 = DAT_0002b364;
          local_54 = 0;
          iVar4 = *(int *)(iVar6 + DAT_0002b334);
          if (iVar14 != iVar4) {
LAB_0002ae7c:
            iVar2 = DAT_0002b368;
            local_54 = 0;
            local_88 = iVar14;
            local_54 = FUN_00017ee8(param_1,*(undefined4 *)(DAT_0002b368 + 0x2b3e0));
            if (local_54 == 0) {
              uVar12 = 0x1c30;
              iVar1 = 0;
            }
            else {
              local_48 = FUN_00018f60(local_54,*(undefined4 *)(iVar2 + 0x2b300));
              if (local_48 != 0) {
                iVar2 = FUN_00018f60(local_54,*(undefined4 *)(iVar2 + 0x2b304));
                local_58 = iVar2;
                if (iVar2 == 0) {
                  uVar12 = 0x1c34;
                }
                else {
                  local_50 = 0;
                  iVar1 = FUN_00018840(*(undefined4 *)(iVar2 + 4),uVar12);
                  if ((iVar1 != 0) && (local_50 = *(int *)(iVar2 + 0xc), local_50 != 0)) {
                    iVar1 = *(int *)(iVar2 + 8);
                    FUN_00018934();
                    FUN_00018934(iVar1);
                    iVar2 = local_58;
                    local_58 = iVar1;
                    FUN_00017fec(iVar2);
                  }
                  if (local_50 == 0) {
                    local_4c = FUN_0001cbcc(local_58);
                  }
                  else {
                    local_4c = FUN_0001ccc4();
                  }
                  FUN_000182bc(local_50);
                  iVar2 = DAT_0002b36c;
                  local_50 = 0;
                  if (local_4c != 0) {
                    FUN_00017fec(local_58);
                    local_58 = 0;
                    FUN_00017fec(local_4c);
                    local_4c = 0;
                    FUN_00017fec(local_54);
                    local_54 = 0;
                    iVar5 = _PyThreadState_UncheckedGet();
                    FUN_00019f30(iVar5,&local_44,&local_40,&local_3c);
                    local_54 = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x2b444));
                    if (local_54 == 0) {
                      uVar12 = 0x1c58;
LAB_0002b164:
                      iVar1 = 0;
                      FUN_000182bc(local_58);
                      local_58 = 0;
                      FUN_000182bc(local_54);
                      local_54 = 0;
                      FUN_000182bc(local_50);
                      local_50 = 0;
                      FUN_000182bc(0);
                      FUN_000182bc(local_4c);
                      local_4c = 0;
                      FUN_000182bc(0);
                      FUN_00019490(DAT_0002b380 + 0x2b1c4,uVar12,0xac,DAT_0002b37c + 0x2b1c0);
                      iVar2 = FUN_00018950(iVar5,&local_4c,&local_58,&local_54);
                      if (iVar2 < 0) {
                        uVar12 = 0x1c7b;
                      }
                      else {
                        local_50 = PyTuple_Pack(3,local_4c,local_58,local_54);
                        if (local_50 == 0) {
                          uVar12 = 0x1c7f;
                          local_50 = 0;
                        }
                        else {
                          iVar2 = FUN_00017e40(local_48,local_50,0);
                          FUN_00017fec(local_48);
                          local_48 = 0;
                          FUN_00017fec(local_50);
                          local_50 = 0;
                          if (iVar2 == 0) {
                            uVar12 = 0x1c84;
                          }
                          else {
                            iVar4 = FUN_00017f5c(iVar2);
                            FUN_00017fec(iVar2);
                            if (iVar4 < 0) {
                              uVar12 = 0x1c88;
                            }
                            else {
                              if (iVar4 != 0) {
                                FUN_000182bc(local_4c);
                                local_4c = 0;
                                FUN_000182bc(local_58);
                                local_58 = 0;
                                FUN_000182bc(local_54);
                                local_54 = 0;
                                FUN_0001a300(*(undefined4 *)(iVar5 + 0x50),local_44,local_40,
                                             local_3c);
                                goto LAB_0002b078;
                              }
                              uVar12 = 0x1c90;
                              uVar13 = PyThreadState_Get();
                              FUN_000182c8(uVar13,local_4c,local_58,local_54);
                              local_58 = 0;
                              local_54 = 0;
                              local_4c = 0;
                            }
                          }
                        }
                      }
                      uVar13 = 0xab;
                      FUN_0001a300(*(undefined4 *)(iVar5 + 0x50),local_44,local_40,local_3c);
                      goto LAB_0002b288;
                    }
                    local_4c = PyNumber_Add(param_4,param_5);
                    if (local_4c == 0) {
                      uVar12 = 0x1c5a;
                      goto LAB_0002b164;
                    }
                    local_58 = FUN_0001b6f4(local_54,local_4c);
                    if (local_58 == 0) {
                      uVar12 = 0x1c5c;
                      goto LAB_0002b164;
                    }
                    FUN_00017fec(local_54);
                    local_54 = 0;
                    FUN_00017fec(local_4c);
                    iVar1 = local_58;
                    local_4c = 0;
                    iVar7 = FUN_00018840(*(undefined4 *)(local_58 + 4),
                                         *(undefined4 *)(iVar6 + DAT_0002b370));
                    if (iVar7 == 0) {
                      if (*(int *)(iVar2 + 0x2b21c) == iVar4) {
                        uVar12 = PyLong_FromSsize_t();
                        local_4c = FUN_0001ce44(iVar1,uVar12);
                      }
                      else {
                        local_4c = FUN_0001ce2c(iVar1);
                      }
                    }
                    else {
                      local_4c = FUN_0001ce6c(iVar1);
                    }
                    if (local_4c == 0) {
                      uVar12 = 0x1c60;
                      local_4c = 0;
                      goto LAB_0002b164;
                    }
                    FUN_00017fec(local_58);
                    iVar1 = local_4c;
                    local_58 = 0;
                    local_4c = 0;
                    FUN_000182bc(local_44);
                    local_44 = 0;
                    FUN_000182bc(local_40);
                    local_40 = 0;
                    FUN_000182bc(local_3c);
                    local_3c = 0;
LAB_0002b078:
                    if (local_48 != 0) {
                      local_3c = FUN_00017e40(local_48,*(undefined4 *)(DAT_0002b374 + 0x2b0c4),0);
                      FUN_00017fec(local_48);
                      local_48 = 0;
                      if (local_3c == 0) {
                        uVar12 = 0x1caa;
                        goto LAB_0002bcc0;
                      }
                      FUN_00017fec(local_3c);
                      local_3c = 0;
                    }
                    iVar2 = DAT_0002b378;
                    iVar7 = _PyThreadState_UncheckedGet();
                    FUN_00019f30(iVar7,&local_48,&local_3c,&local_40);
                    local_58 = FUN_00017ee8(param_1,*(undefined4 *)(iVar2 + 0x2b11c));
                    if (local_58 != 0) {
                      local_4c = FUN_00017ee8(local_58,*(undefined4 *)(iVar2 + 0x2b6d0));
                      if (local_4c == 0) {
                        uVar12 = 0x1cd2;
                        goto LAB_0002b3d8;
                      }
                      FUN_00017fec(local_58);
                      iVar2 = local_4c;
                      local_58 = 0;
                      if (iVar1 == 0) {
                        uVar12 = 0x1cd5;
                        FUN_0001aed0();
                        goto LAB_0002b3d8;
                      }
                      iVar4 = FUN_00018840(*(undefined4 *)(local_4c + 4),
                                           *(undefined4 *)(iVar6 + DAT_0002b398));
                      if ((iVar4 == 0) || (local_58 = *(int *)(iVar2 + 0xc), local_58 == 0)) {
                        iVar2 = 0;
                      }
                      else {
                        iVar4 = *(int *)(iVar2 + 8);
                        FUN_00018934();
                        FUN_00018934(iVar4);
                        iVar2 = local_4c;
                        local_4c = iVar4;
                        FUN_00017fec(iVar2);
                        iVar2 = 1;
                      }
                      iVar4 = local_4c;
                      iVar8 = iVar2 + 2;
                      uVar12 = *(undefined4 *)(local_4c + 4);
                      iVar5 = FUN_00018840(uVar12,uVar13);
                      if (iVar5 == 0) {
                        uVar13 = *(undefined4 *)(iVar6 + DAT_0002b39c);
                        iVar4 = FUN_00018840(uVar12,uVar13);
                        if (((iVar4 == 0) && (iVar4 = PyType_IsSubtype(uVar12,uVar13), iVar4 == 0))
                           || ((*(uint *)(*(int *)(local_4c + 8) + 8) & 0xffffff8d) != 0x80)) {
                          local_50 = PyTuple_New(iVar8);
                          if (local_50 == 0) {
                            uVar12 = 0x1cf3;
                          }
                          else {
                            if (local_58 != 0) {
                              *(int *)(local_50 + 0xc) = local_58;
                              local_58 = 0;
                            }
                            FUN_00018934(iVar1);
                            *(int *)(local_50 + iVar8 * 4 + 4) = iVar1;
                            FUN_00018934(iVar14);
                            *(int *)(local_50 + (iVar2 + 3) * 4 + 4) = iVar14;
                            local_54 = FUN_00017e40(local_4c,local_50,0);
                            if (local_54 != 0) {
                              FUN_00017fec(local_50);
                              local_50 = 0;
                              goto LAB_0002b650;
                            }
                            uVar12 = 0x1cfe;
                            local_54 = 0;
                          }
                        }
                        else {
                          local_38 = local_58;
                          local_34[1] = iVar14;
                          local_34[0] = iVar1;
                          local_54 = FUN_00017628(local_4c,local_34 + -iVar2,iVar8);
                          if (local_54 != 0) goto LAB_0002b640;
                          uVar12 = 0x1ced;
                          local_54 = 0;
                        }
                        goto LAB_0002b3d8;
                      }
                      local_38 = local_58;
                      local_34[1] = iVar14;
                      local_34[0] = iVar1;
                      local_54 = FUN_0001b728(iVar4,local_34 + -iVar2,iVar8);
                      if (local_54 == 0) {
                        uVar12 = 0x1ce5;
                        local_54 = 0;
                        goto LAB_0002b3d8;
                      }
LAB_0002b640:
                      FUN_000182bc(local_58);
                      local_58 = 0;
LAB_0002b650:
                      iVar5 = 0;
                      FUN_00017fec(local_4c);
                      local_4c = 0;
                      FUN_00017fec(local_54);
                      local_54 = 0;
                      FUN_000182bc(local_48);
                      local_48 = 0;
                      FUN_000182bc(local_3c);
                      local_3c = 0;
                      FUN_000182bc(local_40);
                      local_40 = 0;
LAB_0002b690:
                      FUN_000182bc(0);
                      FUN_00018934(iVar14);
                      goto LAB_0002b6a0;
                    }
                    uVar12 = 0x1cd0;
LAB_0002b3d8:
                    FUN_000182bc(local_58);
                    local_58 = 0;
                    FUN_000182bc(local_54);
                    local_54 = 0;
                    FUN_000182bc(local_50);
                    local_50 = 0;
                    FUN_000182bc(0);
                    FUN_000182bc(local_4c);
                    local_4c = 0;
                    FUN_000182bc(0);
                    iVar2 = FUN_00019fd0(*(undefined4 *)(iVar7 + 0x34),
                                         **(undefined4 **)(iVar6 + DAT_0002b384));
                    if (iVar2 == 0) {
                      uVar13 = 0xaf;
LAB_0002b874:
                      iVar2 = 0;
                      iVar5 = iVar2;
                      iVar4 = iVar2;
                    }
                    else {
                      FUN_00019490(DAT_0002b38c + 0x2b45c,uVar12,0xaf,DAT_0002b388 + 0x2b458);
                      iVar4 = FUN_00018950(iVar7,&local_54,&local_4c,&local_50);
                      iVar2 = DAT_0002b390;
                      if (iVar4 < 0) {
                        uVar12 = 0x1d23;
                        uVar13 = 0xb0;
                        goto LAB_0002b874;
                      }
                      FUN_00018934(local_4c);
                      iVar5 = local_4c;
                      if (*(int *)(*(int *)(iVar2 + 0x2b6f4) + 0x14) == *(int *)(iVar2 + 0x2bb44) &&
                          *(int *)(*(int *)(iVar2 + 0x2b6f4) + 0x10) == *(int *)(iVar2 + 0x2bb40)) {
                        if (*(int *)(iVar2 + 0x2bb48) == 0) {
                          iVar4 = FUN_00017f00(*(undefined4 *)(iVar2 + 0x2b768));
                        }
                        else {
                          FUN_00018934();
                          iVar4 = *(int *)(iVar2 + 0x2bb48);
                        }
                      }
                      else {
                        iVar4 = FUN_00018c58(*(undefined4 *)(iVar2 + 0x2b768),iVar2 + 0x2bb40,
                                             iVar2 + 0x2bb48);
                      }
                      if (iVar4 == 0) {
                        uVar12 = 0x1d31;
                        iVar2 = 0;
                      }
                      else {
                        iVar2 = FUN_00017ee8(iVar4,*(undefined4 *)(DAT_0002b394 + 0x2b970));
                        if (iVar2 == 0) {
                          uVar12 = 0x1d33;
                        }
                        else {
                          FUN_00017fec(iVar4);
                          iVar6 = FUN_00018840(*(undefined4 *)(iVar2 + 4),
                                               *(undefined4 *)(iVar6 + DAT_0002b398));
                          if ((iVar6 == 0) || (iVar6 = *(int *)(iVar2 + 0xc), iVar6 == 0)) {
                            iVar6 = 0;
                            local_58 = FUN_0001ccc4(iVar2,iVar5);
                          }
                          else {
                            iVar4 = *(int *)(iVar2 + 8);
                            FUN_00018934(iVar6);
                            FUN_00018934(iVar4);
                            FUN_00017fec(iVar2);
                            local_58 = FUN_0001caa0(iVar4,iVar6,iVar5);
                            iVar2 = iVar4;
                          }
                          FUN_000182bc(iVar6);
                          if (local_58 != 0) {
                            FUN_00017fec(iVar2);
                            FUN_00017fec(local_58);
                            local_58 = 0;
                            FUN_000182bc(local_54);
                            local_54 = 0;
                            FUN_000182bc(local_4c);
                            local_4c = 0;
                            FUN_000182bc(local_50);
                            local_50 = 0;
                            FUN_0001a300(*(undefined4 *)(iVar7 + 0x50),local_48,local_3c,local_40);
                            goto LAB_0002b690;
                          }
                          uVar12 = 0x1d42;
                          iVar4 = 0;
                        }
                      }
                      uVar13 = 0xb1;
                    }
                    FUN_0001a300(*(undefined4 *)(iVar7 + 0x50),local_48,local_3c,local_40);
                    goto LAB_0002a5e8;
                  }
                  uVar12 = 0x1c42;
                }
                uVar13 = 0xab;
                FUN_00017fec(local_48);
                local_48 = 0;
LAB_0002b288:
                local_88 = iVar14;
                iVar1 = 0;
                iVar2 = 0;
                iVar5 = 0;
                iVar4 = 0;
                goto LAB_0002a5e8;
              }
              uVar12 = 0x1c32;
              iVar1 = 0;
            }
LAB_0002bcc0:
            iVar2 = 0;
            uVar13 = 0xab;
            iVar5 = iVar2;
            iVar4 = iVar2;
            goto LAB_0002a5e8;
          }
          local_54 = PyObject_RichCompare(iVar3,*(undefined4 *)(DAT_0002b364 + 0x2b0f0),1);
          if (local_54 == 0) {
            local_88 = iVar14;
            uVar12 = 0x1c21;
            uVar13 = 0xa9;
            iVar1 = 0;
            iVar2 = 0;
            iVar5 = 0;
            iVar4 = 0;
            goto LAB_0002a5e8;
          }
          iVar10 = FUN_00017f5c();
          if (iVar10 < 0) {
            uVar12 = 0x1c22;
            uVar13 = 0xa9;
            goto LAB_0002b288;
          }
          FUN_00017fec(local_54);
          local_54 = 0;
          if (iVar10 != 0) goto LAB_0002ae7c;
          if (*(int *)(*(int *)(iVar2 + 0x2b0b4) + 0x14) == *(int *)(iVar2 + 0x2b514) &&
              *(int *)(*(int *)(iVar2 + 0x2b0b4) + 0x10) == *(int *)(iVar2 + 0x2b510)) {
            if (*(int *)(iVar2 + 0x2b518) == 0) {
              local_4c = FUN_00017f00(*(undefined4 *)(iVar2 + 0x2b128));
            }
            else {
              FUN_00018934();
              local_4c = *(int *)(iVar2 + 0x2b518);
            }
          }
          else {
            local_4c = FUN_00018c58(*(undefined4 *)(iVar2 + 0x2b128),iVar2 + 0x2b510);
          }
          iVar2 = DAT_0002b3a0;
          if (local_4c == 0) {
            uVar12 = 0x1d7e;
LAB_0002bd00:
            iVar1 = 0;
            local_88 = iVar14;
            uVar13 = 0xb4;
            iVar2 = iVar1;
            iVar5 = iVar1;
            iVar4 = iVar1;
            goto LAB_0002a5e8;
          }
          local_54 = FUN_00017ee8(local_4c,*(undefined4 *)(&UNK_0002bdb0 + DAT_0002b3a0));
          if (local_54 == 0) {
            uVar12 = 0x1d80;
            goto LAB_0002bd00;
          }
          FUN_00017fec(local_4c);
          local_4c = 0;
          local_4c = PyTuple_New(2);
          if (local_4c == 0) {
            uVar12 = 0x1d83;
            goto LAB_0002bd00;
          }
          FUN_00018934(iVar3);
          *(int *)(local_4c + 0xc) = iVar3;
          FUN_00018934(*(undefined4 *)(local_84 + 8));
          uVar13 = *(undefined4 *)(&UNK_0002bfe8 + iVar2);
          *(undefined4 *)(local_4c + 0x10) = *(undefined4 *)(local_84 + 8);
          local_58 = PyUnicode_Format(uVar13);
          if (local_58 == 0) {
            uVar12 = 0x1d8b;
            local_58 = 0;
            goto LAB_0002bd00;
          }
          FUN_00017fec(local_4c);
          iVar2 = local_54;
          local_4c = 0;
          iVar4 = FUN_00018840(*(undefined4 *)(local_54 + 4),uVar12);
          if ((iVar4 != 0) && (local_4c = *(int *)(iVar2 + 0xc), local_4c != 0)) {
            iVar4 = *(int *)(iVar2 + 8);
            FUN_00018934();
            FUN_00018934(iVar4);
            iVar2 = local_54;
            local_54 = iVar4;
            FUN_00017fec(iVar2);
          }
          if (local_4c == 0) {
            local_50 = FUN_0001ccc4(local_54,local_58);
          }
          else {
            local_50 = FUN_0001caa0();
          }
          FUN_000182bc(local_4c);
          local_4c = 0;
          FUN_00017fec(local_58);
          local_58 = 0;
          if (local_50 == 0) {
            uVar12 = 0x1d9b;
            goto LAB_0002bd00;
          }
          FUN_00017fec(local_54);
          local_54 = 0;
          FUN_00017fec(local_50);
          local_50 = 0;
          iVar14 = iVar3;
          local_88 = iVar1;
        }
        uVar12 = 0x1b76;
        uVar13 = 0xa4;
        iVar1 = 0;
        local_54 = 0;
        iVar2 = 0;
        iVar5 = 0;
        iVar4 = 0;
        iVar3 = iVar14;
      }
      else {
        if (*(int *)(*(int *)(iVar2 + 0x2a7c4) + 0x14) == *(int *)(iVar2 + 0x2abd4) &&
            *(int *)(*(int *)(iVar2 + 0x2a7c4) + 0x10) == *(int *)(iVar2 + 0x2abd0)) {
          if (*(int *)(iVar2 + 0x2abd8) == 0) {
            local_58 = FUN_00017f00(*(undefined4 *)(iVar2 + 0x2a860));
          }
          else {
            FUN_00018934();
            local_58 = *(int *)(iVar2 + 0x2abd8);
          }
        }
        else {
          local_58 = FUN_00018c58(*(undefined4 *)(iVar2 + 0x2a860),iVar2 + 0x2abd0);
        }
        if (local_58 == 0) {
          uVar12 = 0x1b3f;
        }
        else {
          local_50 = PyObject_RichCompare(param_3,local_58,5);
          if (local_50 != 0) {
            FUN_00017fec(local_58);
            local_58 = 0;
            iVar2 = FUN_00017f5c(local_50);
            if (iVar2 < 0) {
              uVar12 = 0x1b43;
              uVar13 = 0xa0;
              goto LAB_0002bac0;
            }
            FUN_00017fec(local_50);
            local_50 = 0;
            if (iVar2 == 0) {
              iVar14 = *(int *)(DAT_0002b354 + 0x2adbc);
            }
            else {
              iVar14 = *(int *)(DAT_0002b340 + 0x2a9f0);
            }
            FUN_00018934(iVar14);
            local_54 = 0;
            goto LAB_0002a75c;
          }
          uVar12 = 0x1b41;
        }
        iVar1 = 0;
        uVar13 = 0xa0;
        iVar2 = iVar1;
        iVar5 = iVar1;
        iVar4 = iVar1;
        iVar3 = iVar1;
        local_88 = iVar1;
      }
      goto LAB_0002a5e8;
    }
    uVar12 = 0x1b28;
    local_54 = 0;
  }
  uVar13 = 0x9e;
  iVar2 = iVar1;
  iVar5 = iVar1;
  iVar4 = iVar1;
  iVar3 = iVar1;
  iVar16 = iVar1;
  local_88 = iVar1;
LAB_0002a5e8:
  FUN_000182bc(local_58);
  FUN_000182bc(local_54);
  FUN_000182bc(local_50);
  FUN_000182bc(iVar4);
  FUN_000182bc(local_4c);
  FUN_000182bc(iVar2);
  iVar14 = 0;
  FUN_00019490(DAT_0002b33c + 0x2a638,uVar12,uVar13,DAT_0002b338 + 0x2a630);
LAB_0002b6a0:
  FUN_000182bc(iVar16);
  FUN_000182bc(iVar3);
  FUN_000182bc(local_88);
  FUN_000182bc(iVar1);
  FUN_000182bc(iVar5);
  FUN_00017fec(local_84);
  return iVar14;
}




/* ============================================
 * Function: _DT_FINI
 * Address:  0x2df6c
 * ============================================ */

void _DT_FINI(void)

{
  return;
}




/* ============================================
 * Function: PyUnicode_FromFormat
 * Address:  0x44000
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_FromFormat(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_SetItem
 * Address:  0x44004
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_SetItem(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyList_New
 * Address:  0x44008
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyList_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyDict_SetItemString
 * Address:  0x44010
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyDict_SetItemString(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyDict_Size
 * Address:  0x44014
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyDict_Size(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyException_SetTraceback
 * Address:  0x44018
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyException_SetTraceback(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: __cxa_finalize
 * Address:  0x4401c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void __cxa_finalize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _ITM_deregisterTMCloneTable
 * Address:  0x44024
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _ITM_deregisterTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_ClearWeakRefs
 * Address:  0x44030
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_ClearWeakRefs(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyThreadState_UncheckedGet
 * Address:  0x44034
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyThreadState_UncheckedGet(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyModuleDef_Init
 * Address:  0x44038
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyModuleDef_Init(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: Py_EnterRecursiveCall
 * Address:  0x4403c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void Py_EnterRecursiveCall(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyFrame_New
 * Address:  0x44040
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyFrame_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: memmove
 * Address:  0x44044
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */
/* WARNING: Unknown calling convention -- yet parameter storage is locked */

void * memmove(void *__dest,void *__src,size_t __n)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyNumber_Add
 * Address:  0x44048
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyNumber_Add(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GetAttrString
 * Address:  0x4404c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GetAttrString(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyUnicode_Join
 * Address:  0x44050
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_Join(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyImport_AddModule
 * Address:  0x44054
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyImport_AddModule(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyBytes_FromStringAndSize
 * Address:  0x44058
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyBytes_FromStringAndSize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_SetAttrString
 * Address:  0x4405c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_SetAttrString(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_WarnEx
 * Address:  0x44060
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_WarnEx(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _Py_Dealloc
 * Address:  0x44064
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _Py_Dealloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyModule_NewObject
 * Address:  0x44068
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyModule_NewObject(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_SetObject
 * Address:  0x4406c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_SetObject(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GC_Del
 * Address:  0x44070
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GC_Del(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_NormalizeException
 * Address:  0x44074
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_NormalizeException(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyObject_CallFunction_SizeT
 * Address:  0x44078
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyObject_CallFunction_SizeT(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_RichCompare
 * Address:  0x4407c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_RichCompare(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyCode_New
 * Address:  0x44080
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyCode_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyGen_Send
 * Address:  0x44084
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyGen_Send(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyImport_GetModuleDict
 * Address:  0x44088
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyImport_GetModuleDict(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GC_Track
 * Address:  0x4408c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GC_Track(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_SelfIter
 * Address:  0x44094
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_SelfIter(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_GivenExceptionMatches
 * Address:  0x44098
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_GivenExceptionMatches(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_SetString
 * Address:  0x4409c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_SetString(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_DelItem
 * Address:  0x440a0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_DelItem(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyMethod_New
 * Address:  0x440a4
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyMethod_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyObject_GC_New
 * Address:  0x440a8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyObject_GC_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GetItem
 * Address:  0x440ac
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GetItem(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyInterpreterState_GetID
 * Address:  0x440bc
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyInterpreterState_GetID(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyEval_EvalFrameEx
 * Address:  0x440c0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyEval_EvalFrameEx(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PySequence_Contains
 * Address:  0x440c4
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PySequence_Contains(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyTuple_GetItem
 * Address:  0x440c8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyTuple_GetItem(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyMem_Realloc
 * Address:  0x440cc
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyMem_Realloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_SetNone
 * Address:  0x440d0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_SetNone(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_ExceptionMatches
 * Address:  0x440d8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_ExceptionMatches(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyOS_snprintf
 * Address:  0x440e0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyOS_snprintf(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyTraceBack_Here
 * Address:  0x440e4
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyTraceBack_Here(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_CallFinalizerFromDealloc
 * Address:  0x440e8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_CallFinalizerFromDealloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_Not
 * Address:  0x440ec
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_Not(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_Free
 * Address:  0x440f0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_Free(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyLong_FromSsize_t
 * Address:  0x440f4
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyLong_FromSsize_t(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyFloat_FromDouble
 * Address:  0x440f8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyFloat_FromDouble(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyType_Ready
 * Address:  0x440fc
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyType_Ready(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyLong_FromLong
 * Address:  0x44100
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyLong_FromLong(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyLong_AsSsize_t
 * Address:  0x44104
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyLong_AsSsize_t(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_Clear
 * Address:  0x44108
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_Clear(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyList_Append
 * Address:  0x4410c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyList_Append(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: __gmon_start__
 * Address:  0x44118
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void __gmon_start__(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyTuple_New
 * Address:  0x4411c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyTuple_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GenericGetAttr
 * Address:  0x44120
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GenericGetAttr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyThreadState_Get
 * Address:  0x44124
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyThreadState_Get(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyNumber_Remainder
 * Address:  0x4412c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyNumber_Remainder(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyDict_SetItem_KnownHash
 * Address:  0x44134
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyDict_SetItem_KnownHash(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyArg_UnpackTuple
 * Address:  0x44138
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyArg_UnpackTuple(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_SetAttr
 * Address:  0x4413c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_SetAttr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_Occurred
 * Address:  0x44140
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_Occurred(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyImport_ImportModule
 * Address:  0x44144
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyImport_ImportModule(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyDict_GetItem_KnownHash
 * Address:  0x44148
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyDict_GetItem_KnownHash(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_CallObject
 * Address:  0x4414c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_CallObject(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: Py_LeaveRecursiveCall
 * Address:  0x44150
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void Py_LeaveRecursiveCall(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyTuple_GetSlice
 * Address:  0x44154
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyTuple_GetSlice(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyRun_StringFlags
 * Address:  0x44158
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyRun_StringFlags(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_CallFunctionObjArgs
 * Address:  0x4415c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_CallFunctionObjArgs(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyDict_GetItemString
 * Address:  0x44160
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyDict_GetItemString(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyEval_EvalCodeEx
 * Address:  0x44164
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyEval_EvalCodeEx(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_Size
 * Address:  0x44168
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_Size(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_IsTrue
 * Address:  0x44170
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_IsTrue(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyType_Lookup
 * Address:  0x44174
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyType_Lookup(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyImport_ImportModuleLevelObject
 * Address:  0x44178
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyImport_ImportModuleLevelObject(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_Hash
 * Address:  0x4417c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_Hash(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyUnicode_Compare
 * Address:  0x44180
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_Compare(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _Py_NewReference
 * Address:  0x44184
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _Py_NewReference(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyLong_AsDouble
 * Address:  0x4418c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyLong_AsDouble(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyDict_New
 * Address:  0x44194
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyDict_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyDict_Next
 * Address:  0x441a0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyDict_Next(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _PyObject_GetDictPtr
 * Address:  0x441b0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _PyObject_GetDictPtr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyUnicode_FromString
 * Address:  0x441b8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_FromString(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyType_GetFlags
 * Address:  0x441bc
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyType_GetFlags(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GetIter
 * Address:  0x441c0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GetIter(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyUnicode_InternFromString
 * Address:  0x441c4
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_InternFromString(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyDict_SetItem
 * Address:  0x441cc
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyDict_SetItem(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PySequence_Tuple
 * Address:  0x441d0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PySequence_Tuple(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_IsSubclass
 * Address:  0x441d8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_IsSubclass(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PySequence_List
 * Address:  0x441e0
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PySequence_List(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_Call
 * Address:  0x441e8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_Call(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyType_IsSubtype
 * Address:  0x441f4
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyType_IsSubtype(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyUnicode_Decode
 * Address:  0x441f8
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_Decode(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_Format
 * Address:  0x441fc
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_Format(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PySlice_New
 * Address:  0x44200
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PySlice_New(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyUnicode_FromStringAndSize
 * Address:  0x44208
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_FromStringAndSize(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyModule_GetDict
 * Address:  0x4420c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyModule_GetDict(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: _ITM_registerTMCloneTable
 * Address:  0x44210
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void _ITM_registerTMCloneTable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyLong_FromLongLong
 * Address:  0x44214
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyLong_FromLongLong(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyNumber_Index
 * Address:  0x44218
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyNumber_Index(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GetAttr
 * Address:  0x4421c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GetAttr(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyUnicode_Format
 * Address:  0x44228
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyUnicode_Format(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyMem_Malloc
 * Address:  0x4422c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyMem_Malloc(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyNumber_Subtract
 * Address:  0x44230
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyNumber_Subtract(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyTuple_Pack
 * Address:  0x44234
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyTuple_Pack(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: Py_GetVersion
 * Address:  0x44238
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void Py_GetVersion(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyNumber_InPlaceSubtract
 * Address:  0x4423c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyNumber_InPlaceSubtract(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyObject_GC_UnTrack
 * Address:  0x44240
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyObject_GC_UnTrack(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyErr_WriteUnraisable
 * Address:  0x44248
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyErr_WriteUnraisable(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




/* ============================================
 * Function: PyDict_GetItemWithError
 * Address:  0x4424c
 * ============================================ */

/* WARNING: Control flow encountered bad instruction data */

void PyDict_GetItemWithError(void)

{
                    /* WARNING: Bad instruction - Truncating control flow here */
  halt_baddata();
}




