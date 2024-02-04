#include <stdio.h>
#include <Python.h>
#include "include/pyfputs.h"

static PyMethodDef PyFputsMethods[] = {
  {"fputs", method_fputs, METH_VARARGS, "Python interface for fputs C library function"},
  {NULL, NULL, 0, NULL}
};

static struct PyModuleDef pyfputsmodule = {
  PyModuleDef_HEAD_INIT,
  "pyfputs",
  "Python interface for the fputs C library function",
  -1,
  PyFputsMethods
};

PyMODINIT_FUNC PyInit_pyfputs(void) {
    return PyModule_Create(&pyfputsmodule);
}