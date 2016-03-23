from matasano.util.byte_xor import xor

def hamming_distance(x, y):
    assert len(x) == len(y)
    sum = 0
    for b in xor(x, y):
        sum += bin(ord(b)).count('1')

    return sum
