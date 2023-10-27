from NVXDevice import NVX36
import ctypes


nvx = NVX36()
nvx.begin()
nvx.open()

print(nvx.get_information())
print(nvx.get_property())
print(nvx.get_possibility())

print(nvx.get_data_mode())
print(nvx.get_sample_rate_count())
print(nvx.get_frequency_bandwidth())


