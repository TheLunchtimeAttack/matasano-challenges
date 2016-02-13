"""Simple functions to XOR together strings of hexadecimal (base 16) numbers"""

HexChars = ["0", "1", "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f"]


def make_hexstring_a_decimal(string):
    """
    :param string: a hexnumber given as a python string type
    :return: the hexnumber as a decimal int
    """
    assert type(string) == str     # Check formatting part 1
    for char in string.lower():
        assert char in HexChars    # Check formatting part 2
    return int(string, 16)


def int_number_to_hex_string(intnumber):
    """
    :param intnumber: an integer-type number
    :return: the hex equivalent as a string
    """
    assert type(intnumber) == int  # Sanity check
    return hex(intnumber)[2:]  # Ignore the '0x' chars


def xor_of_two_hexstrings(hexs1, hexs2):
    """
    A lightweight function to xor two hexadecimal strings

    :param hexs1: a python string type of hexadecimal characters only
    :param hexs2: a python string type of hexadecimal characters only
    :return: the bitwise XOR of the two hexnumbers, given as a hexadecimal python string
    """
    lhs = make_hexstring_a_decimal(hexs1)
    rhs = make_hexstring_a_decimal(hexs2)
    xored_num = lhs ^ rhs
    return int_number_to_hex_string(xored_num)


def xor_of_n_hexstrings(*hexs):
    """
    A slightly heavier function to xor a list of hexadecimal strings

    :param hexs: python strings type of hexadecimal characters only
    :return: the bitwise XOR of the hexnumbers, given as a hexadecimal python string
    """
    for obj in hexs:
        assert type(obj) == str     # sanity checks
        for char in obj.lower():
            assert char in HexChars
    length = len(hexs)  # I will use this a lot
    if length == 0:
        return 0        # Nothing XORed together gives 0 (warning, this is an int type, not a str type)
    elif length == 1:
        return hexs[0]  # hexs[0] is the ONLY element in the tuple
    else:
        init_lhs = make_hexstring_a_decimal(hexs[0])
        init_rhs = make_hexstring_a_decimal(hexs[1])
        init = init_lhs ^ init_rhs
        del init_lhs, init_rhs  # Free up redundant space by deleting these two auxillary variables
        for i in range(2, length):  # iterate over i = 2, 3, 4, ...., length - 1  [not length]
            init ^= make_hexstring_a_decimal(hexs[i])  # In python, "a ^= b" is shorthand for "a = a ^ b"
        return int_number_to_hex_string(init)           # ... the same trick works for +, -, *, /, //, ** and % too


def xor_of_n_hexstrings__alternate(hexs):
    """
    Function works as xor_of_n_hexstrings, but with a tuple (or list) AS input, rather than a tuple OF inputs

    :param hexs: iterable object (e.g. list or tuple) of python strings type of hexadecimal characters only
    :return: the bitwise XOR of the hexnumbers, given as a hexadecimal python string
    """
    for obj in hexs:
        assert type(obj) == str     # sanity checks
        for char in obj.lower():
            assert char in HexChars
    length = len(hexs)  # I will use this a lot
    if length == 0:
        return 0        # Nothing XORed together gives 0 (warning, this is an int type, not a str type)
    elif length == 1:
        return hexs[0]  # hexs[0] is the ONLY element in the tuple
    else:
        init_lhs = make_hexstring_a_decimal(hexs[0])
        init_rhs = make_hexstring_a_decimal(hexs[1])
        init = init_lhs ^ init_rhs
        del init_lhs, init_rhs  # Free up redundant space by deleting these two auxillary variables
        for i in range(2, length):  # iterate over i = 2, 3, 4, ...., length - 1  [not length]
            init ^= make_hexstring_a_decimal(hexs[i])  # In python, "a ^= b" is shorthand for "a = a ^ b"
        return int_number_to_hex_string(init)           # ... the same trick works for +, -, *, /, //, ** and % too


if __name__ == "__main__":
    from sys import argv
    if len(argv) == 1:
        print("Error. Add some hexadecimal numbers to xor together!!\n\n\t\tTRY AGAIN")
        quit()
    arguments = argv[1:]  # This is a list type, the args to XOR are all the inputs expect the script name itself.
    print(xor_of_n_hexstrings__alternate(arguments))
    quit()
