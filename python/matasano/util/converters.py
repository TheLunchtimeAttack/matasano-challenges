import binascii

def hex_to_bytestr(hex_string):
    """
    Returns a byte string from its hexadecimal expression.
    """
    return binascii.unhexlify(hex_string)

def bytestr_to_hex(byte_string):
    """
    Returns the hexadecimal representation (string)
    of a binary string.
    """
    return binascii.hexlify(byte_string)

def base64_splitter(eightbitnumbers): 
    """
    Splits hex bytes into base 64 bytes
    
    :param eight_bit_numbers: a list of 8 bit integers
    :return: a list of 6 bit integers
    """
    assert type(eightbitnumbers) == list
    for x in eightbitnumbers:
        assert type(x) == int
    output=[]
    for i in range(0, len(eightbitnumbers)-2,3): # 3 hex bytes to 4 base64 bytes
        output1=eightbitnumbers[i]>>2 # 00123456
        output.append(output1)
        temp= 0b00000011 & eightbitnumbers[i] # temp is 00000078
        output2=temp<<4 | eightbitnumbers[i+1]>>4 # 00781234
        output.append(output2)
        temp= 0b00001111 & eightbitnumbers[i+1] # 00005678
        output3=temp<<2 | eightbitnumbers[i+2]>>6 # 00567812
        output.append(output3)
        output4=eightbitnumbers[i+2] & 0b00111111
        output.append(output4)
    return output

def to_base64(inputnum): # returns the base64 byte characters
    """
    Returns the base64 character the input value corresponds to
    
    :param inputNum: a 6 bit integer
    :return: a string containing one character
    """
    assert type(inputnum) == int
    if 0<= inputnum and inputnum<=25: # uppercase to ascii
        return chr(inputnum+65)
    elif 26<= inputnum and inputnum<=51: # lowercase to ascii
        return chr(inputnum+71)
    elif 52<= inputnum and inputnum<=61: # integers to ascii
        return chr(inputnum-4)
    elif inputnum==62: # +
        return chr(43)
    elif inputnum==63: # /
        return chr(47)
    else:
        raise ValueError('Invalid base64 input')

def bytes_to_base64(bytestr):
    """
    Convert a string of bytes into the corresponding base64 encoded string
    
    :param eight_bit_numbers: a list of 8 bit integer values
    :return: a string of ASCII characters
    """
    assert type(bytestr) == str

    length = len(bytestr)
    # Pad the length to the next multiple of 3.
    while len(bytestr) % 3 != 0:
        bytestr += '\x00'

    # Convert byte string to string of 8-bit integers.
    intstr = [ord(b) for b in bytestr]

    tmp = base64_splitter(intstr)

    outputstring = ""
    for i in range(0,len(tmp)):
        outputstring += to_base64(tmp[i])
    if length % 3 == 1:
        outputstring = outputstring[:len(outputstring) - 2] + '=='
    elif length % 3 == 2:
        outputstring = outputstring[:len(outputstring) - 1] + '='

    return outputstring

def valid_character(byteinput):
    """
    Checks an list of bytes for valid English characters

    param byteinput: a list of bytes
    return: false if the bytes contain an invalid ASCII character, true otherwise
    """
    for x in byteinput:
        c = ord(x)
        if c<=31 or c>=127:
            if c!=9 and c!=10 and c!=11: # 9 is hotizontal tab, 10 is newline, 11 is vertical tab
                return False
    else:
        return True

