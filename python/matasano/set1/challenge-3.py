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



#####  Greg's alternate scoring system
import re
import string

### The following empirical frequencies of normal english should be verified
# Letters: anywhere in text. u :: 0.024, b :: 0.013, e :: 0.127
# Pairs: anywhere in words in text: in :: 0.026, th :: 0.038
# Words: of :: 0.037, my :: 0.00078, not :: 0.0016, i :: 0.00078
# Not case sensitive! Assume all text in lower case.


# General scoring idea
# score text with the sum of abs(the empirical stats - the stats above)
# choose text with minimal score.


def format_text(text):
    """
    Converts a string of text into a list of lower case words with no non-alphabetic characters.
    
    param text :: a Python string
    
    return :: a list of lower-case words stripped of all punctuation or whitespace.
    """
    assert type(text) == str
    if len(text) == 0:
        return []
    text = text.lower()  # make homogenous letter case
    text = "".join(c for c in text if (c.isalpha() or c in [" ", "\n", "\t"])) # remove numbers and punctuation
    text = re.split(r"[ \t\n]", text)  # Split into a list words, including the null word ""
    text = [word for word in text if word != ""]  # Remove null words
    assert type(text) == list
    for word in text:
        assert (type(word) == str and len(word) != 0)
    return text


def letter_freq(char, text):
    assert (type(char) == str and len(char) == 1)
    count = 0
    for word in text:
        count += word.count(char)
    return count


def pair_freq(pair, text):
    assert (type(pair) == str and len(pair) == 2)
    count = 0
    for word in text:
        count += word.count(pair)
    return count


def word_freq(word, text):
    assert(type(word) == str and word.isalpha())
    count = 0
    for words in text:
        if words == word:
            count += 1
    return count


def score_english(text):
    """
    Takes a string and tests it for plausible Englishness, giving a score of 0 for non-printable characters
    
    param text :: text to test
    
    return :: score of 0 to 1 (as a float type. Perfect English should have a score of near 0.99999!
    """
    if not all([c for c in text if c not in string.printable]):  # Tests that all elements of the text are valid printables
        return 0.0
    text = format_text(text)
    
    numletters = 0
    for word in text:
        numletters += len(word)
    num_e = letter_freq("e", text)
    num_u = letter_freq("u", text)
    num_b = letter_freq("b", text)

    numpairs = 0
    for word in text:
        numpairs += len(word) - 1
    num_in = pair_freq("in", text)
    num_th = pair_freq("th", text)    

    numwords = len(text)
    num_of = word_freq("of", text)
    num_my = word_freq("my", text)
    num_not = word_freq("not", text)
    num_i = word_freq("i", text)
    variable_scores = [num_u/numletters - 0.024, num_b/numletters - 0.013, num_e/numletters, num_in/numpairs - 0.026, num_th/numpairs - 0.038,\
                       num_of/numwords - 0.037, num_my/numwords - 0.00078, num_not/numwords - 0.0016, num_i/numwords - 0.00078]
    score = sum([1/(abs(var_score) + 1) for var_score in variable_scores])/len(variable_scores)
    return score
#### Ends Greg's stuff
