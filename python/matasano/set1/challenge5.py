input1="Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal"

def repeating_key_xor(plaintext,key):
    key_length=len(key)
    working=[]
    output=''
    for i in range(0, len(plaintext)): # xors values and puts the resulting integer into the list 'working'
        xored = ord(key[i%key_length])^ord(plaintext[i])
        working.append(xored)
    for num in working: # reads through the numbrers and converts them into hex characters
        hex_value=hex(num)
        output+=str(hex_value)[2:]
    if len(output)%2==1: # pads 0 to the start if the output is an odd number of hex characters
        new='0'
        new+=output[2:]
        output=new
    return output

answer=repeating_key_xor(input1, "ICE")

print (answer)
