#include <iostream>
#include <string>
#include <stdint.h>
#include "../util/MatasanoConverter.h"
#include "../util/MatasanoUtil.h"
#include "../util/StringTesting.h"

#define PUNCTUATION_THRESHOLD 5

//The hex encoded string:
//
//1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736
//... has been XOR'd against a single character. Find the key, decrypt the message.
//
//You can do this by hand. But don't: write code to do it for you.
//
//How? Devise some method for "scoring" a piece of English plaintext. 
//Character frequency is a good metric. Evaluate each output and choose the one with the best score.

std::vector<uint8_t> CreateXorVector(uint8_t xor_character, uint32_t size) {
	std::vector<uint8_t> out;
	
	for (uint32_t i = 0; i < size; i++) {
		out.push_back(xor_character);
	}
	
	return out;
}

TestString CreateTestString(std::string input_string, uint8_t input_key) {
	TestString t;
	t.s = input_string;
	t.key = input_key;
	return t;
}

std::vector<TestString> TestStringVectorSetup(std::vector<uint8_t> input_bytes) {
	std::string xor_output_string;
	uint8_t xor_character;
	std::vector<uint8_t> xor_vector;
	std::vector<uint8_t> xor_output_bytes;
	std::vector<TestString> output_strings;
	
	xor_vector = CreateXorVector(0, input_bytes.size());
	xor_output_bytes = XorByteVectors(input_bytes, xor_vector);
	xor_output_string = StringFromByteVector(xor_output_bytes, "ASCII");
	output_strings.push_back(CreateTestString(xor_output_string, xor_character));
	
	for (xor_character = 1; xor_character != 0; xor_character++) {
		//test all potential i's
		xor_vector = CreateXorVector(xor_character, input_bytes.size());
		xor_output_bytes = XorByteVectors(input_bytes, xor_vector);
		xor_output_string = StringFromByteVector(xor_output_bytes, "ASCII");
		output_strings.push_back(CreateTestString(xor_output_string, xor_character));
	}
	
	return output_strings;
}

int main() {
	std::string input_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	std::vector<uint8_t> input_byte_vector;
	std::vector<TestString> potential_strings;
	
	input_byte_vector = ByteVectorFromString(input_string, "hex");;
	
	potential_strings = TestStringVectorSetup(input_byte_vector);
	
	potential_strings = FilterNonPrintable(potential_strings);
	std::cout << "Remaining Keys (initial filter): " << potential_strings.size() << std::endl;
	
	potential_strings = FilterExcessivePunctuation(potential_strings, PUNCTUATION_THRESHOLD);
	std::cout << "Remaining Keys (excessive punctuation filter): " << potential_strings.size() << std::endl;
	
	for (uint16_t i = 0; i < potential_strings.size(); i++) {
		std::cout << "Key used: " << (unsigned) potential_strings[i].key << std::endl << potential_strings[i].s << std::endl;
	}
	
	std::cout << "Remaining Keys: " << potential_strings.size() << std::endl;
	
	return 0;
}