def byte_list_xor(input1, input2):
    """
    A function that takes two input byte lists and returns the bitwise xor of the two lists
    
    :param input1: a list of 8 bit integers
    :param input2: a list of 8 bit integers
    :return: a list of 8 bit integers
    """
    outputlist = []
    assert type(input1) == list
    assert type(input2) == list
    for x in input1:
        assert type(x) == int
    
    if (len(input1) != len(input2)):
        raise ValueError('byte_list_xor: input lists of unequal length')
    
    for x in range(len(input1)):
        outputlist.append(input1[x] ^ input2[x])
    
    return outputlist

