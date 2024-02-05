from typing import Optional
from cpyfputs import ExampleClass

class ExampleClassWrapper(ExampleClass):
  """
  Python wrapper class 
  for C's ExampleClass
  """
  
  def __init__(
    self, 
    filename: Optional[None] = None, 
    *args,
    **kwargs
  ):
    if filename is not None:
      super().__init__(filename)
    elif "filename" in kwargs:
      super().__init__(kwargs["filename"])
    elif len(args) > 0:
      super().__init__(args[0])
    else:
      super().__init__("none")
    
  @property
  def filename(self) -> str:
    ret = self.get_filename()
    return ret if ret != "none" else None
    

  @filename.setter
  def filename(self, filename: Optional[str] = None):
    fn = str(filename) if filename is not None else "none"
    self.set_filename(fn)
  
  def fputs(self, text: str):
    if self.filename is None:
      raise ValueError("filename must be set")
    super().fputs(text)