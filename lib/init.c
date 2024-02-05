#include <stdio.h>
#include <Python.h>
#include "include/pyfputs.h"

static PyMethodDef ExampleClass_methods[] = {
  {"get_filename", (PyCFunction)ExampleClass_get_filename, METH_NOARGS, "Return the value of the filename attribute"},
  {"set_filename", (PyCFunction)(void(*)(void))ExampleClass_set_filename, METH_VARARGS, "Set the value of the filename attribute"},
  {"fputs", (PyCFunction)ExampleClass_fputs, METH_VARARGS, "Write the filename attribute to a file"},
  {NULL, NULL, 0, NULL}
};


static PyTypeObject ExampleClassType = {
  PyVarObject_HEAD_INIT(NULL, 0)
  "pyfputs.ExampleClass", /* tp_name */
  sizeof(ExampleClass), /* tp_basicsize */
  0, /* tp_itemsize */
  (destructor)ExampleClass_dealloc, /* tp_dealloc */
  0, /* tp_print */
  0, /* tp_getattr */
  0, /* tp_setattr */
  0, /* tp_reserved */
  0, /* tp_repr */
  0, /* tp_as_number */
  0, /* tp_as_sequence */
  0, /* tp_as_mapping */
  0, /* tp_hash  */
  0, /* tp_call */
  0, /* tp_str */
  0, /* tp_getattro */
  0, /* tp_setattro */
  0, /* tp_as_buffer */
  Py_TPFLAGS_DEFAULT | Py_TPFLAGS_BASETYPE, /* tp_flags */
  "ExampleClass object", /* tp_doc */
  0, /* tp_traverse */
  0, /* tp_clear */
  0, /* tp_richcompare */
  0, /* tp_weaklistoffset */
  0, /* tp_iter */
  0, /* tp_iternext */
  ExampleClass_methods, /* tp_methods */
  0, /* tp_members */
  0, /* tp_getset */
  0, /* tp_base */
  0, /* tp_dict */
  0, /* tp_descr_get */
  0, /* tp_descr_set */
  0, /* tp_dictoffset */
  (initproc)ExampleClass_init, /* tp_init */
  0, /* tp_alloc */
  ExampleClass_new, /* tp_new */
};


static PyMethodDef PyFputs_methods[] = {
  {"fputs", method_fputs, METH_VARARGS, "Python interface for fputs C library function"},
  /* Add the ExampleClass methods */
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyfputsmodule = {
  PyModuleDef_HEAD_INIT,
  "cpyfputs",
  "Python interface for the fputs C library function",
  -1,
  PyFputs_methods
};

PyMODINIT_FUNC PyInit_cpyfputs(void) {
    /*return PyModule_Create(&pyfputsmodule); */
    PyObject *m;
    if (PyType_Ready(&ExampleClassType) < 0)
        return NULL;
    m = PyModule_Create(&pyfputsmodule);
    if (m == NULL)
        return NULL;
    Py_INCREF(&ExampleClassType);
    if (PyModule_AddObject(m, "ExampleClass", (PyObject *)&ExampleClassType) < 0) {
        Py_DECREF(&ExampleClassType);
        Py_DECREF(m);
        return NULL;
    }
    return m;
}