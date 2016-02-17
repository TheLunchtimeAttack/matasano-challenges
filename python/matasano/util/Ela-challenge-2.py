import converters 

input_1='1c0111001f010100061a024b53535009181c'
input_2='686974207468652062756c6c277320657965'

def hex_string_to_decimal(hex_string):
    dec_array=int(hex_string,16) # takes the integer value, parsing 16 bits
    return dec_array             # of hex_string at a time

def decimal_array_to_hex(dec_array): # does the opposite of the above
    hex_string = hex(dec_array)[2:]         # reads after '0x'
    return hex_string

def xor_hex_strings_to_string(hex_1, hex_2): # takes two hex strings, xors and returns
    dec_1=hex_string_to_decimal(hex_1)        # the resulting string in hex format
    dec_2=hex_string_to_decimal(hex_2)
    result=dec_1^dec_2
    return decimal_array_to_hex(result)



print (xor_hex_strings_to_string(input_1, input_2))
