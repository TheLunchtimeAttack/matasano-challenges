#!/usr/bin/python
# This programme takes as input a number of string hex strings, trys all 256 keys for a single key
# XOR on each input string and returns the most likely plaintext out of all inputs and keys.

from matasano.util.converters import *
from matasano.set1.c3 import *

# Takes the file and converts it into a list
text_file = open("matasano/set1/strings.txt");
inputlist = text_file.read().splitlines();


# Takes a byte string and returns the most likely plaintext and key.
def decryptsinglexor(input1):

    byte_input = hex_to_bytestr(input1) #Changes input to bytes
    potential_keys = []

    for k in range (0,256):
        potential_keys.append(chr(k))

    for k in potential_keys:
        decrypted = decrypt(k,byte_input)
        if not valid_characters(decrypted):
            potential_keys.remove(k)

    #print('\n Keys which return invalid decryptions filtered out.')
    #print ('Current potential keys:', potential_keys)
    #print ('Current number of potential keys:', len(potential_keys))

    candidate_plaintext={}

    for k in potential_keys:
        candidate_plaintext[k]=decrypt(k,byte_input)

    Score={}

    for k in potential_keys:
        Score[k]=score_string(candidate_plaintext[k])

    key=max(Score, key=Score.get)

    #print(candidate_plaintext[key])
    #print('Key: ', chr(key))
    #return candidate_plaintext
    return(key, candidate_plaintext[key])


plaintextscores = {}
# A dictionary keeping track of the keys and the plaintexts

#For each value in the input list, this enters into the dictionary the most likely plaintext
# along with the plaintext score.
for input in inputlist:
    (working_key, working_plaintext) = decryptsinglexor(input)
    working_score = score_string(working_plaintext)
    #print("Working key:", working_key)
    #print ("Working plaintext:", working_plaintext)
    #print ("Working score:", working_score)
    plaintextscores[working_plaintext] = working_score

# To pring the dictionary listing all the plaintexts and their scores
# print ("This is the dictionary:", plaintextscores)

# This searches the dictionary for the highest plaintext score and sets it equal to maxscore
maxscore = max(plaintextscores.values())
# print ("Max score:", maxscore)

# This defines the winning plaintext to be the plaintext corresponding to the
# highest plaintext score (maxscore) in the dictionary
winning_plaintext = [x for x,y in plaintextscores.items() if y ==maxscore]


print ("And the winning plaintext is...", winning_plaintext[0])
