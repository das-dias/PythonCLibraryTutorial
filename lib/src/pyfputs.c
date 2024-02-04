
#include <stdio.h>
#include <Python.h>
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