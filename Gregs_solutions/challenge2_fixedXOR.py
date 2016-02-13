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


def xorit(no1, no2):
    """
    :param no1: int type
    :param no2: int type
    :return: no1 XOR no2
    """
    return no1 ^ no2


def int_number_to_hex_string(intnumber):
    """
    :param intnumber: a integer number
    :return: the hex equivalent as a string
    """
    assert type(intnumber) == int
    return hex(intnumber)[2:]  # Ignore the '0x' chars


if __name__ == "__main__":
    from sys import argv
    if len(argv) != 3:
        print("Add 2 hexstrings to xor!!\n\n\t\tTRY AGAIN")
        quit()
    n1 = make_hexstring_a_decimal(argv[1])
    n2 = make_hexstring_a_decimal(argv[2])
    xor = xorit(n1, n2)
    print("The XOR of", argv[1], "and", argv[2], "is:", int_number_to_hex_string(xor))
    print("Have a lovely day :)\n\t~love Greg")
    quit()
