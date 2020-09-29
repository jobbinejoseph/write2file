from cffi import FFI
import importlib
from uuid import uuid4

def load(filename):
    name = filename + '_' + uuid.uuid4().hex
    
    source = open(filename + '.c').read()
    includes = open(filename + '.h').read()

    ffibuilder = FFI()
    ffibuilder.cdef(includes)
    ffibuilder.set_source(name, source)
    ffibuilder.compile()
    
    module = importlib.import_module(name)
    return module.lib
