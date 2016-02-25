from matasano.util.converters import *


def hex_to_base64(hex):
    base64= read_hex(hex)
    base64= bytes_to_base64(base64)
    return base64

if __name__ == "__main__":
    hex_input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"
    base64=hex_to_base64(hex_input)
    print(base64)