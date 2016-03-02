import unittest
from matasano.util.converters import *

class ParsingTest(unittest.TestCase):
    def test_hex_to_base64_standard(self):
        # Regular hex string
        hex_string = "deadbeef1234"
        b64_string = "3q2+7xI0"
        self.assertEqual(bytes_to_base64(hex_to_bytestr(hex_string)), b64_string)

    def test_hex_to_base64_padding(self):
        # Hex string needing padding
        hex_string = "1a"
        b64_string = "Gg=="
        self.assertEqual(bytes_to_base64(hex_to_bytestr(hex_string)), b64_string)

        hex_string2 = "c0de"
        b64_string2 = "wN4="
        self.assertEqual(bytes_to_base64(hex_to_bytestr(hex_string2)), b64_string2)

    def test_hex_to_base64_null(self):
        # Test null strings
        self.assertEqual(bytes_to_base64(hex_to_bytestr("")), "")

    def test_hex_to_base64_upper(self):
        # Test upper case hex
        hex_string = "BA5EBA11"
        b64_string = "ul66EQ=="
        self.assertEqual(bytes_to_base64(hex_to_bytestr(hex_string)), b64_string)

if __name__ == '__main__':
    unittest.main()
