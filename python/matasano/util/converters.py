def hex_to_byte(charin):
    """
    Convert an ASCII encoded hex character into it's corresponding 4 bit hex number.
    
    :param charIn: a string containing one character
    :return: a 4 bit integer
    """
    assert type(charin) == str
    assert len(charin) == 1
    charin=ord(charin) # converts charIn to its `integer' value (the ascii encoding value)
    if 48<= charin and charin <=57: # converts 0-9 characters to integers
        charin=charin-48
    elif 65<= charin and charin <=70: # converts uppercase to integers
        charin=charin-55
    elif 97<= charin and charin<=102: # converts lowercase to integers
        charin=charin-87
    else:
        raise ValueError('Invalid hex character')
    return charin

def combine_hex(msb, lsb):
    """
    Combines two 4 bit numbers into one 8 bit number
    e.g. combine_hex(4,8) would return 0x48
    
    :param msb: a 4 bit integer
    :param lsb: a 4 bit integer
    :return: an 8 bit integer
    """
    assert type(msb) == int
    assert type(lsb) == int
    msb=msb<<4 # puts the significant bits on the left
    output=msb | lsb # or of first and second
    return output

def read_hex(hexstring):
    """
    Creates a list of 8 bit numbers from a hex string
    
    :param hexstring: a string of ASCII encoded characters
    :return: a list of 8 bit numbers
    """
    assert type(hexstring) == str
    byteVals=[]
    if len(hexstring)%2!=0:
        raise ValueError('read_hex: Odd number of hex characters input.')
    for i in range(0,len(hexstring)-1,2):
        byteVals.append(combine_hex(hex_to_byte(hexstring[i]),hex_to_byte(hexstring[i+1])))
    return byteVals

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

def bytes_to_base64(eightbitnumbers):
    """
    Convert a list of eight bit numbers into the corresponding base64 encoded string
    
    :param eight_bit_numbers: a list of 8 bit integer values
    :return: a string of ASCII characters
    """
    assert type(eightbitnumbers) == list
    for x in eightbitnumbers:
        assert type(x) == int
    length=len(eightbitnumbers)
    while len(eightbitnumbers)%3!=0: # pads input to multiple of 3
        eightbitnumbers.append(0)
    temp=base64_splitter(eightbitnumbers)
    outputstring = ""
    for i in range(0,len(temp)):
        outputstring+=to_base64(temp[i])
    if length%3==1:
        outputstring = outputstring[:len(outputstring) - 2] + '=='
    elif length%3==2:
        outputstring = outputstring[:len(outputstring) - 1] + '='
    return outputstring

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

def bytes_to_hex_string(eightbitnumbers):
    """
    Converts a list of 8 bit numbers into an ASCII encoded hex string
    
    :param eightbitnumbers: a list of integers
    :return: a string of ASCII characters
    """
    assert type(eightbitnumbers) == list
    for x in eightbitnumbers:
        assert type(x) == int
    
    outputstring = ""
    
    for x in range(len(eightbitnumbers)):
        outputstring += to_hex(eightbitnumbers[x] >> 4) #select 4 msb from eightbitnumbers[x]
        outputstring += to_hex(eightbitnumbers[x] & 0xF) #select 4 lsb from eightbitnumbers[x]
    
    return outputstring

def bytes_to_char(byteinput):
    """
    Converts a list of bytes into a list of ASCII characters

    param byteinput: a list of bytes
    return a string of ASCII characters
    """
    chars=''
    for x in byteinput:
        chars+=chr(x)
    return chars

def valid_character(byteinput):
    """
    Checks an list of bytes for valid English characters

    param byteinput: a list of bytes
    return: false if the bytes contain an invalid ASCII character, true otherwise
    """
    for x in byteinput:
        if x<=31 or x>=127:
            if x!=9 and x!=10 and x!=11: # 9 is hotizontal tab, 10 is newline, 11 is vertical tab
                return False
    else:
        return True

def base64_to_hex(Base64_chars):
    """
    Converts an ASCII string representing a Base64 encoding into
    an ASCII string representing a hex encoding
    
    :param Base64_chars: A base64 encoded string in ASCII
    :return: A hex encoded string in ASCII
    """
    assert type(Base64_chars)==str
    assert len(Base64_chars)%2==0

# Converts the base64 values into their decimal representations
# each byte ends up in format 00xxxxxx where 'x' is a significant bit
    bytes=[]
    for charin in Base64_chars:
        charin=ord(charin)
        if ord('A')<= charin and charin <=ord('Z'):
            Byte=charin-ord('A') # 'A' = 0 in base64
        elif ord('a')<= charin and charin <=ord('z'):
            Byte=charin-ord('a')+26 # 'a' = 26 in base64
        elif ord('0')<= charin and charin<=ord('9'):
            Byte=charin-ord('0')+52 # '0' = 52 in base64
        elif charin==ord('+'):
            Byte=62 # '+'=62 in base64
        elif charin==ord('/'):
            Byte==63 # 
        elif charin==ord('='): # padding
            break
        else:
            raise ValueError('Invalid Base64 character')
        bytes.append(Byte)
# parses the bytestring and changes it to a hex bytestring:
# 00123456 00123456 -> 00001234 00005612 00003456
    hex_bytes=[]
    for i in range(0,len(bytes)-1,2):
        # 0b00123456 -> 0b00001234:
        first=bytes[i]>>2
        hex_bytes.append(first)
        # 0b00123456, 0b00123456 -> 0b00005612
        second=((bytes[i] & 0b00000011)<<2) | ((bytes[i+1] & 0b00110000)>>4)
        hex_bytes.append(second)
        # 0b00123456 -> 0b00003456
        third = bytes[i+1] & 0b00001111
        hex_bytes.append(third)

# converts the single hex bytes into ASCII encoded characters
# eg 00000001 -> '1', 00001010 -> 'a'
    hex_str=''
    for byte in hex_bytes:
        if 0<= byte and byte <=9:
            hex_char=chr(byte+ord('0'))
        elif 10<= byte and byte <=15:
            hex_char=chr(byte-10+ord('a'))
        else:
            raise ValueError(byte, 'not in range')
        hex_str = hex_str + hex_char

    return hex_str
