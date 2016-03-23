from matasano.util.converters import *
from matasano.util.misc import hamming_distance
from matasano.set1.c4 import decryptsinglexor


datas = open("matasano/data/c6.txt") 
data = "".join(d for d in datas)

bytedata = base64_to_bytes(data)
metricvec = []
finalmetric = 100000    
for keysize in range(2, 41):
    bytes1 =""
    bytes2 = ""
    bytes3 = ""
    bytes4 = ""
    for i in range(0, keysize):
        bytes1 += (bytedata[i])
        bytes2 += (bytedata[i + keysize])
        bytes3 += (bytedata[i + (2 * keysize)])
        bytes4 += (bytedata[i + (3 * keysize)])
    metric1 = hamming_distance(bytes1, bytes2) / keysize
    metric2 = hamming_distance(bytes1, bytes3) / keysize
    metric3 = hamming_distance(bytes1, bytes4) / keysize
    metric4 = hamming_distance(bytes2, bytes3) / keysize
    metric5 = hamming_distance(bytes2, bytes4) / keysize
    metric6 = hamming_distance(bytes3, bytes4) / keysize
    metric = (metric1 + metric2 + metric3 + metric4 + metric5 + metric6) / 6
    metricvec.append(metric)
    if (metric < finalmetric):
        finalmetric = metric
        finalkeysize = keysize
        
plaintext = [''] * len(bytedata)

for i in range(0,finalkeysize):
    ciph = []
    
    for j in range(0, (len(bytedata) // finalkeysize) +1):
        if (j* finalkeysize + i) < len(bytedata):
            ciph.append(bytedata[j* finalkeysize + i])
    plain = decryptsinglexor(bytestr_to_hex("".join(ciph)))[1]
    for j in range(0, (len(bytedata) // finalkeysize)+1):
        if (j* finalkeysize + i) < len(bytedata):
            plaintext[j* finalkeysize + i] = plain[j]   
finalplaintext = "".join(plaintext)
print(finalplaintext)








