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