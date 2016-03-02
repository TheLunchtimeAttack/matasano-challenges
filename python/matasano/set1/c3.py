import matasano.util.converters as converters
input1='1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736'

Bytes=converters.read_hex(input1)
print ('Bytes:',Bytes)

potential_keys=[]

# looks for repeated characters
def repeated(bytestring):
    repeated=[]
    for i in range(0, len(bytestring)-1):
        if bytestring[i]==bytestring[i+1]:
            repeated.append(bytestring[i])
    return repeated
# if a repeated character exists, the potential keys are reduced to keys which
# will decrypt to a repeated character found in the English language, namely s,e,t,m,o
if len(repeated(Bytes))>0:
    for item in repeated(Bytes):
        potential_keys.extend((item^ord('s'),item^ord('e'),item^ord('t'),item^ord('l'),item^ord('m'),item^ord('o')))
    print('Repeated letters found.  Only relevant keys added.')
    print ('Current potential keys:', potential_keys)
    print ('Current number of potential keys:', len(potential_keys))
    # removes potential keys which are not printable characters
    for k in potential_keys:
        if k not in range(32,127):
            potential_keys.remove(k)
    print ('Current number of potential keys:', len(potential_keys))
else:
    for k in range (32,127):
        potential_keys.append(k)
    print('No repeated letters found.  All relevant keys added.')
    print ('Current potential keys:', potential_keys)
    print ('Current number of potential keys:', len(potential_keys))

def decrypt(k,c):
    """
    xors the ciphertext bytestring with key k and returns as bytestring

    param k: key
    param c: ciphertext bytes
    return a string of bytes
    """
    decrypted_bytes=[]
    for byte in c:
        decrypted_bytes.append(byte^k)
    return decrypted_bytes
# this checks the potential keys and removes any which result in invalid decryptions
for k in potential_keys:
    decrypted=decrypt(k,Bytes)
    if not converters.valid_character(decrypted):
        potential_keys.remove(k)
print('\n Keys which return invalid decryptions filtered out.')
print ('Current potential keys:', potential_keys)
print ('Current number of potential keys:', len(potential_keys))

def plaintext(k,bytes):
    """
    xors the ciphertext bytestring with key k and returns as ascii

    param k: key
    param c: ciphertext bytes
    return a string of ascii characters
    """
    decrypted=decrypt(k,bytes)
    plaintext=converters.bytes_to_char(decrypted)
    return plaintext

candidate_plaintext={}
for k in potential_keys:
    candidate_plaintext[k]=plaintext(k,Bytes)

def most(charstring): # returns an ordered array of the most common bytes
    occurrences={} # creates a lookup so that occourances[byte] will return the number of
# times that byte appeats in the string
    for i in range(32, 127):
        occurrences[chr(i)]=0 # initialises the dictionary
    for char in charstring:
        occurrences[char]=0 # +1 for every time a character is found
    for char in charstring:
        occurrences[char]+=1 # +1 for every time a character is found
    most=[] # an ordered list of the most frequent bytes
    while len(occurrences)>0:
        most.append(max(occurrences, key=occurrences.get))
        del occurrences[max(occurrences, key=occurrences.get)]
    return most

def score(charstring):
    score=0
    scoring={' ':13, 'e':12, 't':11, 'a':10, 'o':9, 'i':8, 'n':7, 's':6, 'h':5, 'r':4, 'd':3, 'l':2, 'u':1}
    Most=most(charstring)
    for i in range (0,len(Most)):
        if Most[i] in scoring:
            score+=scoring[Most[i]]-i
    return score

Score={}
for k in potential_keys:
    Score[k]=score(candidate_plaintext[k])

key=max(Score, key=Score.get)
print(candidate_plaintext[key])
print('key: ', chr(key))
