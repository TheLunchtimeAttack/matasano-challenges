import converters

hex_input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d1"
#print hex_input

def hex2base64(hex):
	base64= converters.read_hex(hex)
	base64= converters.byte_to_base64(base64)
	return base64

base64=hex2base64(hex_input)
print base64