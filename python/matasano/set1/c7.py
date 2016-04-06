from matasano.util.converters import base64_to_bytes
from Crypto.Cipher import AES
import base64

if __name__ == "__main__":

    chal_file = open("matasano/data/c7.txt", 'r');

    key = "YELLOW SUBMARINE"

    # Instantiate the cipher
    cipher = AES.new(key, AES.MODE_ECB)

    # Covert from base64 to bytes and encode
    ct = base64.b64decode(chal_file.read())

    # Perform the decryption
    pt = cipher.decrypt(ct)
    print(pt.decode())


