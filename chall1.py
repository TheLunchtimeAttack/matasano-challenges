import base64
import binascii

def h_to_b64(hex_string):
	# h_size = len(hex_string) * 4
	## hex_string = hex_string[::-1]
	## h = (bin(int(hex_string, 16))[2:])
	# h = (bin(int(hex_string, 16))[2:]).zfill(h_size)
	# bin_size = len(h)
	# r = bin_size % 6
	## for j in range(0,r):
	## 	h = h.zfill(h_size+r)
	# print h
	# out = ''
	# i=0
	# while (i < bin_size):
	# 	new_h = h[i:i+6]
	# 	bin_h = bin(int(new_h,2))[2:]
	# 	print bin_h
	# 	base_64_h = binascii.b2a_base64(bin_h)
	# 	print base_64_h
	# 	out += base_64_h
	# 	i += 6
	## print out
	check = 'SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t'
	output = base64.b64encode(binascii.unhexlify(hex_string))
	if output == check:
		print output
		print 'yay'
	else:
		print output
		print check
		print ':('

