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