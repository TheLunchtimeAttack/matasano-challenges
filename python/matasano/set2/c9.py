from matasano.util.padding import pkcs7

if __name__ == '__main__':
    input_str = "YELLOW SUBMARINE"
    padded_str = pkcs7(input_str, 20)
    print("String: {} padded to {} bytes is {}".format(input_str, 20, padded_str))
    assert padded_str == "YELLOW SUBMARINE\x04\x04\x04\x04"