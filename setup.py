from distutils.core import setup, Extension

def main():
    setup(
      name="pyfputs",
      version="1.0.0",
      description="Python interface for the fputs C library function",
      author="Diogo Andre",
      author_email="your_email@gmail.com",
      ext_modules=[Extension("pyfputs", [
        "lib/init.c",
        "lib/src/pyfputs.c",
      ])]
    )

if __name__ == "__main__":
    main()