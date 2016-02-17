#include <iostream>
#include <string>
#include <stdint.h>
#include "../util/MatasanoConverter.h"
#include "../util/MatasanoUtil.h"

//The hex encoded string:
//
//1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
//... has been XOR'd against a single character. Find the key, decrypt the message.
//
//You can do this by hand. But don't: write code to do it for you.
//
//How? Devise some method for "scoring" a piece of English plaintext. 
//Character frequency is a good metric. Evaluate each output and choose the one with the best score.

std::vector<uint8_t> create_xor_vector(uint8_t xor_character, uint32_t size) {
	std::vector<uint8_t> out;
	
	for (uint32_t i = 0; i < size; i++) {
		out.push_back(xor_character);
	}
	
	return out;
}

std::string string_from_vector(std::vector<uint8_t> input_vector) {
	std::string out = "";
	
	for (uint32_t i = 0; i < input_vector.size(); i++) {
		out += (char) input_vector[i];
	}
	
	return out;
}

void TestOutputString(uint8_t xor_char, std::string input) {
	for (uint16_t x = 0; x < input.size(); x++) {
		if (input[x] > 127 || input[x] < 32) {
			return;
		}
	}
	
	std::cout << "xor_character: " << unsigned(xor_char) << std::endl << input << std::endl;
}

int main() {
	std::string input_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	std::string xor_output_string;
	uint8_t xor_character;
	MatasanoConverter m;
	MatasanoUtil u;
	std::vector<uint8_t> input_bytes;
	std::vector<uint8_t> xor_vector;
	std::vector<uint8_t> xor_output_bytes;
	
	m.LoadString(input_string, "hex");
	input_bytes = m.GetBytes();
	
	for (xor_character = 1; xor_character != 0; xor_character++) {
		//test all potential i's
		xor_vector = create_xor_vector(xor_character, input_bytes.size());
		xor_output_bytes = u.XorByteVectors(input_bytes, xor_vector);
		xor_output_string = string_from_vector(xor_output_bytes);
		TestOutputString(xor_character, xor_output_string);
	}
	
	return 0;
}