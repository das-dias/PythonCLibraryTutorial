
#include <stdio.h>
#include <Python.h>
#include <string.h>
#include "../include/pyfputs.h"

// Write the core function
PyObject *method_fputs(PyObject *self, PyObject *args) {
  char *str, *filename = NULL;
  int bytes_copied = -1;
  // Parse the input tuple
  if (!PyArg_ParseTuple(args, "ss", &str, &filename)) {
      return NULL;
  }
  // Open the file, write to it and close it
  FILE *fp = fopen(filename, "w");
  if (fp != NULL) {
      bytes_copied = fputs(str, fp);
      fclose(fp);
  }
  return PyLong_FromLong(bytes_copied);
}

// Define the ExampleClass's methods
/* dealloc */
void ExampleClass_dealloc(ExampleClass *self) {
  Py_TYPE(self)->tp_free((PyObject*)self);
}
/* new = alloc */
PyObject* ExampleClass_new(PyTypeObject *type, PyObject *args, PyObject *kwargs) {
  ExampleClass *self;
  self = (ExampleClass *)type->tp_alloc(type, 0);
  if (self != NULL) {
    // Initialize the object's attributes
    self->filename = NULL;
  }
  return (PyObject *)self;
}

/* init */
int ExampleClass_init(ExampleClass *self, PyObject *args, PyObject *kwargs) {
  static char *kwlist[] = {"filename", NULL};
  /* but initialization can also be done using kwargs */
  if (!PyArg_ParseTupleAndKeywords(
    args, kwargs, "s", kwlist, &self->filename
  )) {
    return -1;
  }
  return 0;
}

PyObject *ExampleClass_get_filename(ExampleClass *self, void *closure) {
  return PyUnicode_FromString(self->filename);
}

PyObject *ExampleClass_set_filename(ExampleClass *self, PyObject *args) {
  char *new_filename = "none";
  if (!PyArg_ParseTuple(args, "s", &new_filename)) {
    Py_RETURN_NONE;
  }
  if (!PyUnicode_Check(PyUnicode_FromString(new_filename))) {
    PyErr_SetString(PyExc_TypeError, "The filename attribute value must be a string");
    return NULL;
  }
  Py_XDECREF(self->filename);
  self->filename = strdup(new_filename);
  Py_XINCREF(self->filename);
  Py_RETURN_NONE;
}

/* fputs method */
PyObject *ExampleClass_fputs(ExampleClass *self, PyObject *args) {
  char *str;
  int bytes_copied = -1;
  if (!strcmp(self->filename, "none")) {
    PyErr_SetString(PyExc_ValueError, "The filename attribute must be set");
    return PyLong_FromLong(bytes_copied);
  }
  // Parse the input tuple
  if (!PyArg_ParseTuple(args, "s", &str)) {
    return NULL;
  }
  // Write to the file
  if (self->filename != NULL) {
    FILE *fp = fopen(self->filename, "w");
    if (fp != NULL) {
      bytes_copied = fputs(str, fp);
      fclose(fp);
    }
  }
  return PyLong_FromLong(bytes_copied);
}