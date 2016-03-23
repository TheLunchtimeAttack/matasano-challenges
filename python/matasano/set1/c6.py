# -*- coding: utf-8 -*-
"""
Created on Wed Mar  9 12:21:15 2016

@author: pbva152
"""

import convert
import numpy as np
import matasanochallenge3


datas = np.genfromtxt("mt6.txt", dtype = str) 
data = "".join(datas)

def HammDist( string1, string2):
    assert(len(string1) == len(string2))
    hammweight = 0
    for i in range(0, len(string1)):
        tempbin = bin(string1[i] ^ string2[i])
        hammweight = tempbin.count("1") + hammweight
    return hammweight
    

bytedata = convert.base642byte(data)
metricvec = []
finalmetric = 100000    
for keysize in range(2, 41):
    bytes1 =[]
    bytes2 = []
    bytes3 = []
    bytes4 = []
    for i in range(0, keysize):
        bytes1.append(bytedata[i])
        bytes2.append(bytedata[i + keysize])
        bytes3.append(bytedata[i + (2 * keysize)])
        bytes4.append(bytedata[i + (3 * keysize)])
    metric1 = HammDist(bytes1, bytes2) / keysize
    metric2 = HammDist(bytes1, bytes3) / keysize
    metric3 = HammDist(bytes1, bytes4) / keysize
    metric4 = HammDist(bytes2, bytes3) / keysize
    metric5 = HammDist(bytes2, bytes4) / keysize
    metric6 = HammDist(bytes3, bytes4) / keysize
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
    plain = matasanochallenge3.DecryptCaesarCipher(convert.byte2hex(ciph))
    for j in range(0, (len(bytedata) // finalkeysize)+1):
        if (j* finalkeysize + i) < len(bytedata):
            plaintext[j* finalkeysize + i] = plain[j]   
finalplaintext = "".join(plaintext)
print(finalplaintext)








