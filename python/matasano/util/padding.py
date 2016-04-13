def pkcs7(input_str, block_size):
    if block_size < 2 or block_size > 255:
        raise ValueError("Block size must be between 2 and 255")
    padding_bytes = block_size - (len(input_str) % block_size)
    return input_str + chr(padding_bytes)*padding_bytes
