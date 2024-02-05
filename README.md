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
│   ├── init.c # defines the cpyfputs C Python Library extension module
│   ├── Makefile
│   ├── src/
│   │   └── pyfputs.c
│   └── include/
│       └── pyfputs.h
│
├── pyfputs/
│   ├── __init__.py
│   ├── __main__.py
│   └── example_class.py
│
├── setup.py
└── README.md
```

## API Flow

A call to the ```fputs``` C library is made through the ```lib/init.c::PyInit_cpyfputs``` function. This function is called by the Python interpreter when the Python module is imported, creating the C library module linkage to the Python interpreter. The ```PyInit_cpyfputs``` function is declared in the [```lib/init.c```](./lib/init.c) file.

After the ```PyInit_cpyfputs``` function creates the link to the module's symbols, the declared C methods and datastructures within the ```lib/init.c::PyFputs_methods``` and  ```lib/init.c::ExampleClass_methods``` structs are made available to the Python interpreter. The [```ExampleClass```](./lib/include/pyfputs.h) is also instantiated as a Python Object of the module in the initialization function. The methods and datastructures are declared source of the C library and are now ready to be used within the Python module.

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
      name="PyFputs",
      version="1.0.0",
      description="Python interface for the fputs C library function",
      author="Diogo Andre",
      author_email="your_email@gmail.com",
      ext_modules=[Extension(
        "cpyfputs", 
        [ "lib/init.c", "lib/src/pyfputs.c"],
        swig_opts=["-modern", "-I./venv/include/python3.11"],
      )],
      packages=["pyfputs"],
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

The [```__main__.py```](./pyfputs/__main__.py) file in the [```pyfputs```](./pyfputs) directory will be executed, creating three new files in the root directory of the repository: ```hello.txt```, ```hello_from_exampleclass.txt``` and ```hello_from_exampleclass2.txt```.

```python
from pyfputs import fputs, ExampleClassWrapper

if __name__ == "__main__":
  fputs("Hello, World!", "hello.txt")
  print("Wrote to hello.txt")
  obj = ExampleClassWrapper("hello_from_exampleclass.txt")
  obj.fputs("Hello, World! From the ExampleClass!")
  print("Wrote to hello_from_exampleclass.txt")
  obj2 = ExampleClassWrapper()
  print("Current filename: ", obj2.filename)
  obj2.filename = "hello_from_exampleclass2.txt"
  obj2.fputs("Hello, World! From the ExampleClass! Again!")
  print("Wrote to hello_from_exampleclass2.txt")
```