# PythonCLibraryTutorial

A tutorial on how to create a Python C library using the Python C API, 
and how to use it in a Python program.

## TOC:
- [PythonCLibraryTutorial](#pythonclibrarytutorial)
  - [TOC:](#toc)
  - [Introduction](#introduction)
  - [Repository Structure](#repository-structure)
  - [API Flow](#api-flow)
  - [Makefile](#makefile)
  - [Building the C Library](#building-the-c-library)
  - [Running the Python Program](#running-the-python-program)

## Introduction
This tutorial is based on the [RealPython.com](https://realpython.com/build-python-c-extension-module/) tutorial for packaging a C Library in a Python module.
This tutorial extends the previous by using a Python virtual environment together with a 
[```Makefile```](./lib/Makefile) to tell the ```clang``` compiler where the Python header files are located.

## Repository Structure

The repository is structured as follows:
  
```
PythonCLibraryTutorial/
│
├── lib/
│   ├── init.c
│   ├── Makefile
│   ├── src/
│   │   └── pyfputs.c
│   └── include/
│       └── pyfputs.h
│
├── pyfputs/
│   ├── __init__.py
│   └── __main__.py
│
├── setup.py
└── README.md
```

## API Flow

A call to the ```fputs``` C library is made through the ```lib/init.c::PyInit_pyfputs``` function. This function is called by the Python interpreter when the Python module is imported, creating the C library module linkage to the Python interpreter. The ```PyInit_pyfputs``` function is declared in the [```lib/init.c```](./lib/init.c) file.

After the ```PyInit_pyfputs``` function creates the link to the module's symbols, the declared C methods and datastructures within the ```lib/init.c::PyFputsMethods``` struct are made available to the Python interpreter. The methods and datastructures are declared source of the C library, and are now ready to be used within the Python module.

## Makefile

The [```Makefile```](./lib/Makefile) is used to build the C library. In this example, its sole purpose is to tell the ```clang``` compiler where the Python header files are located. The ```Makefile``` is located in the [```lib```](./lib) directory.

```make
# Makefile
CFLAGS = -I venv/include/python3.11/
```

Because I am using a Python virtual environment, the Python header files are located in the ```venv/include/python3.11/``` directory. The ```-I``` flag tells the compiler (```clang``` in my case, but it also works for ```gcc```) where to find the header files.

## Building the C Library

Building the library is quite straightfoward. This tutorial takes use of a (deprecated!) ```setup.py``` file to build the Python C library. The ```setup.py``` file is located in the root directory of the repository.

```python
from distutils.core import setup, Extension

def main():
    setup(
      name="pyfputs", # name of the Python module
      version="1.0.0",
      description="Python interface for the fputs C library function",
      author="Diogo Andre",
      author_email="your_email@gmail.com",
      ext_modules=[Extension("pyfputs", [ # the name of the declared Python module in the C library
        "lib/init.c", # the C Python initialization source file
        # the C source code files
        "lib/src/pyfputs.c",
      ])]
    )

if __name__ == "__main__":
    main()
```

A different approach is being researched to build the library using Python-native (non-deprecated) tools. If you have any suggestions, please let me know by creating an issue or a pull request.

## Running the Python Program

To run the Python program, simply run the following command in the root directory of the repository:

```bash
$ python pyfputs
```

The [```__main__.py```](./pyfputs/__main__.py) file in the [```pyfputs```](./pyfputs) directory will be executed, creating a new ```Hello, World!.txt``` file in the root directory of the repository.