import ctypes


a = [(f'Data{i}', ctypes.c_int16) for i in range(1, 33)].extend()

print(a)
