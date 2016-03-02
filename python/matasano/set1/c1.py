from matasano.util.converters import *

hex_input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"

def hex_to_base64(hexstr):
	bstr = hex_to_bytestr(hexstr)
	base64 = bytes_to_base64(bstr)

	return base64

base64 = hex_to_base64(hex_input)
print(base64)
