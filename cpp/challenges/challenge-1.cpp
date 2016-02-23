#include <iostream>
#include <string>
#include "../util/MatasanoConverter.h"

int main() {
	std::string hex_input = ("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"); //Matasano Challenge 1 input
	std::string b64_output = ("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"); //Matasano Challenge 1 expected output
	std::vector<uint8_t> byte_vector;
	std::string converter_output;	
	
	byte_vector = ByteVectorFromString(hex_input, "hex");
	converter_output = StringFromByteVector(byte_vector, "b64");
	std::cout << "Challenge 1: " << std::endl << "Hex input string: " << hex_input << std::endl;
	std::cout << "Base64 output: " << converter_output << std::endl;
	
	if (converter_output.compare(b64_output) == 0) {
		std::cout << "Converter Produced correct output." << std::endl;
	} else {
		std::cout << "Converter produced incorrect output." << std::endl << "Expected Output: " << b64_output << std::endl;
	}
		
	return 0;
}

