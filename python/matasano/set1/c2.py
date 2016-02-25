from matasano.util.converters import *
from matasano.util.byte_xor import *


def hex_string_xor(hex1string, hex2string):
    """
    A complete function for reading in two hex strings and outputting a string of the xor of the two inputs
    
    :param hex1_string: a string of ASCII encoded hex characters
    :param hex2_string: a string of ASCII encoded hex characters
    :return: a string of ASCII encoded hex characters
    """
    assert type(hex1string) == str
    assert type(hex2string) == str
    
    hex1bytes = read_hex(hex1string)
    hex2bytes = read_hex(hex2string)
    
    outputbytes = byte_list_xor(hex1bytes, hex2bytes)
    outputstring = bytes_to_hex_string(outputbytes)
    
    return outputstring
    
if __name__ == "__main__":
    hexinput1 = "1c0111001f010100061a024b53535009181c"
    hexinput2 = "686974207468652062756c6c277320657965"
    xor = hex_string_xor(hexinput1, hexinput2)
    print(xor)
