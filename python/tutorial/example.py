from matasano.util.byte_xor import byte_list_xor
import sys

if __name__ == "__main__":
    if len(sys.argv) != 2:
        print("Usage:\n\t python -m example.py <string to encrypt>")
        quit()

    input_str = sys.argv[1]

    # Convert string to list of bytes
    byte_list_input = [ord(c) for c in input_str]

    # XOR the string with the byte 1 (flips last bit)
    output_list = byte_list_xor(byte_list_input, [1]*len(input_str))

    # Convert list back to string
    output_str = "".join(chr(b) for b in output_list)

    print("The encrypted string is: {}".format(output_str))