def hex_to_bits(charin):
    """
    Convert an ASCII encoded hex character into it's corresponding 4 bit hex number.
    
    :param charIn: a string containing one character
    :return: a 4 bit integer
    """
    assert type(charin) == str
    char_bits =ord(charin) # converts charIn to its `integer' value (the ascii encoding value)
    if char_bits in range(ord('0'), ord('9')+1): # converts 0-9 characters to integers
        return char_bits-ord('0')
    elif char_bits in range(ord('A'), ord('Z')+1): # converts uppercase to integers
        return char_bits-ord('A') + 10
    elif char_bits in range(ord('a'), ord('z')+1): # converts lowercase to integers
        return char_bits-ord('a') + 10
    else:
        raise ValueError('Invalid hex character')

def hex_to_bytestr(hex_string):
    """
    Returns a byte string from its hexadecimal expression.
    """
    assert type(hex_string) == str
    output=""
    if len(hex_string)%2!=0:
        raise ValueError('read_hex: Odd number of hex characters input.')
    for i in range(0,len(hex_string)-1,2):
        byte_val = hex_to_bits(hex_string[i]) << 4
        byte_val += hex_to_bits(hex_string[i+1])
        output += chr(byte_val)
    return output

def to_hex(inputnum):
    """
    A function that takes a 4 bit number as input and returns a one character string of the hex character representing that number
    
    :param inputnum: an 8 bit integer
    :return: a string of length 1
    """
    assert type(inputnum) == int
    
    if 0 <= inputnum and inputnum <= 9:
        return chr(inputnum + 48)
    elif 10 <= inputnum and inputnum <= 15:
        return chr(inputnum + 87)
    else:
        raise ValueError('to_hex: Invalid hex character')

def bytestr_to_hex(byte_str):
    """
    Returns the hexadecimal representation (string)
    of a binary string.
    """
    assert type(byte_str) == str

    outputstring = ""
    
    for b in byte_str:
        outputstring += to_hex(ord(b) >> 4) #select 4 msb from eightbitnumbers[x]
        outputstring += to_hex(ord(b) & 0xF) #select 4 lsb from eightbitnumbers[x]
    
    return outputstring


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

def valid_characters(bytestr):
    """
    Returns True if the byte string provided contains only
    characters of the alphabet or newline, tab, vertical
    bar.
    Returns False otherwise.

    param bytestr: a list of bytes
    return: false if the bytes contain an invalid ASCII character, true otherwise
    """
    for b in bytestr:
        if not ord(b) in range(32,128) and not b in ['\t', '\n', '\r']:
            return False 
    return True
