#ifndef PYFPUTS_H
#define PYFPUTS_H

#include <stdio.h>
#include <Python.h>

PyObject *method_fputs(PyObject *self, PyObject *args);

typedef struct {
  PyObject_HEAD
  char *filename;
} ExampleClass;

void ExampleClass_dealloc(ExampleClass *self);

PyObject *ExampleClass_new(PyTypeObject *type, PyObject *args, PyObject *kwargs);

int ExampleClass_init(ExampleClass *self, PyObject *args, PyObject *kwargs);

PyObject *ExampleClass_set_filename(ExampleClass *self, PyObject *args);

PyObject *ExampleClass_get_filename(ExampleClass *self, void *closure);

PyObject *ExampleClass_fputs(ExampleClass *self, PyObject *args);

#endif // PYFPUTS_H