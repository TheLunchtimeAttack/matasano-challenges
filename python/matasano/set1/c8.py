from matasano.util.converters import hex_to_bytestr
from Crypto.Cipher import AES

if __name__ == "__main__":

    chal_file = open("matasano/data/c8.txt", 'r');

    for line in chal_file:
        ct = hex_to_bytestr(line[:-1])
        for i in range(0, len(ct), 16):
            for j in range(i+16, len(ct), 16):
                if ct[i:i+16] == ct[j:j+16]:
                    print("Block collision found in ciphertext: {} Block {} == Block {}".format(line, i//16, j//16))
                    break
            else:
                continue
            break
        else:
            continue
        break

