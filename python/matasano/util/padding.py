def pkcs7(input_str, block_size):
    padding_bytes = block_size - (len(input_str) % block_size)
    return input_str + chr(padding_bytes)*padding_bytes
