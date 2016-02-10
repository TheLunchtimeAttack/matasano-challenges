def hex2byte(charIn):
	charIn=ord(charIn) # converts charIn to its integer value (ascii)
	if 48<= charIn and charIn <=57: # converts integers to dec values
		charIn=charIn-48
	elif 65<= charIn and charIn <=70: # converts uppercase to dec
		charIn=charIn-55
	elif 97<= charIn and charIn<=102: # converts lowercase to dec
		charIn=charIn-87
	else:
		raise ValueError('Invalid hex character')
	return charIn

def combine_hex(first, second): # puts 4 9 into one byte value 48
	first=first<<4 # puts the significant bits on the left
	output=first | second # or of first and second
	return output

def read_hex(input): # puts together byte values of the combined characters
	byteVals=[]
	if len(input)%2!=0:
		print "Woah, odd number of hex characters duuuuuuuuude."
	for i in xrange(0,len(input)-1,2):
		byteVals.append(combine_hex(hex2byte(input[i]),hex2byte(input[i+1])))
	return byteVals

def base64_splitter(input): # splits hex bytes into base 64 bytes
	#while len(input)%3!=0: # pads input to multiple of 3
		#input.append(0)
	output=[]
	for i in xrange(0, len(input)-2,3): # 3 hex bytes to 4 base64 bytes
		output1=input[i]>>2 # 00123456
		output.append(output1)
		temp= 0b00000011 & input[i] # temp is 00000078
		output2=temp<<4 | input[i+1]>>4 # 00781234
		output.append(output2)
		temp= 0b00001111 & input[i+1] # 00005678
		output3=temp<<2 | input[i+2]>>6 # 00567812
		output.append(output3)
		output4=input[i+2] & 0b00111111
		output.append(output4)
	return output

def to_base64(inputNum): # returns the base64 byte characters
	if 0<= inputNum and inputNum<=25: # uppercase to ascii
		return chr(inputNum+65)
	elif 26<= inputNum and inputNum<=51: # lowercase to ascii
		return chr(inputNum+71)
	elif 52<= inputNum and inputNum<=61: # integers to ascii
		return chr(inputNum-4)
	elif inputNum==62: # +
		return chr(43)
	elif inputNum==63: # /
		return chr(47)
	else:
		raise ValueError('Invalid base64 input')

def byte_to_base64(input):
	length=len(input)
	print length
	while len(input)%3!=0: # pads input to multiple of 3
		input.append(0)
 	temp=base64_splitter(input)
 	outputString = ""
 	for i in range(0,len(temp)):
		outputString+=to_base64(temp[i])
	if length%3==1:
		outputString = outputString[:len(outputString) - 2] + '=='
	elif length%3==2:
		outputString = outputString[:len(outputString) - 1] + '='
	return outputString
