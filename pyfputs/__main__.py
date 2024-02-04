import pyfputs

if __name__ == "__main__":
  print(pyfputs.__doc__)
  pyfputs.fputs("hello.txt", "Hello, World!")
  print("Wrote to hello.txt")