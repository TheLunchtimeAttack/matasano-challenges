def xor(input1, input2):
    """
    Takes two byte strings and returns the bitwise xor
    of them.
    
    :param input1: a list of 8 bit integers
    :param input2: a list of 8 bit integers
    :return: a list of 8 bit integers
    """
    out = ''
    assert type(input1) == str
    assert type(input2) == str
    
    if (len(input1) != len(input2)):
        raise ValueError('byte_list_xor: input strings of unequal length')
    
    for c1, c2 in zip(input1, input2):
        xor = ord(c1) ^ ord(c2)
        out += chr(xor)
    
    return out
