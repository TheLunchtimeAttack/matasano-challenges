#!/usr/bin/python

# This code encypts a string by XORing with a repeated key. Inputs: The string to encrypt and the key. Outputs: the ciphertext in hex. Plaintext and key currently hardcoded (should be able to easily refactor).

from matasano.util.converters import *

ptxt = "Burning 'em, if you ain't quick and nimble I go crazy when I hear a cymbal"

key = "ICE"
klength = len(key)

ctext = ""

for index,c in enumerate(ptxt):
  byte_ptext = ord(c)
  byte_key = ord(key[(index % klength)])
  byte_ctext = byte_ptext ^ byte_key
  ctext = ctext + hex(byte_ctext)[2:] + " "

print ctext



