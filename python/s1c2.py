# this will be the python code for the next challenge
# Write a function that takes two equal-length buffers and produces their XOR combination.

import base64
import converters

# take in hex input, process as bytes, xor the bytes, process output as hex
def HexToHexXOR(inputString1, inputString2):
    length1 = len(inputString1)
    length2 = len(inputString2)
    
    if (length1 == length2):
        # safe to proceed
        
        # declare byte string to store the intermediate value
        bytestring = ''
        
        inputString1Bytes = converters.read_hex(inputString1)
        inputString2Bytes = converters.read_hex(inputString2)
        
        lengthNew = len(inputString1Bytes)
        
        # iterate over the bytes XORing as we go 
        for i in range(0,lengthNew):
            bytestring += chr(inputString1Bytes[i] ^ inputString2Bytes[i])
            
        # convert byte string into appropriate format
        output = base64.b16encode(bytestring)    

    else:
        print ("The input strings aren't the same length")
    
    return output;        

# take in hex input, process as bytes, xor the bytes, process output as base64

# take in base64 input, process as bytes, xor the bytes, process output as hex

# take in base64 input, process as bytes, xor the bytes, process output as base64


# testing the above functions: in particular, showing the challenge is solved
testVector1 = "1c0111001f010100061a024b53535009181c"
testVector2 = "686974207468652062756c6c277320657965"
testOutput = HexToHexXOR(testVector1,testVector2).lower()
print testOutput

if (testOutput == '746865206b696420646f6e277420706c6179'):
    print 'success!'