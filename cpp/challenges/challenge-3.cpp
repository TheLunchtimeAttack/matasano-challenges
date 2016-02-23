#include <iostream>
#include <string>
#include <stdint.h>
#include "../util/MatasanoConverter.h"
#include "../util/MatasanoUtil.h"

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

struct TestString {
	std::string s;
	uint8_t key;
	uint32_t score;
};

std::vector<uint8_t> CreateXorVector(uint8_t xor_character, uint32_t size) {
	std::vector<uint8_t> out;
	
	for (uint32_t i = 0; i < size; i++) {
		out.push_back(xor_character);
	}
	
	return out;
}

std::string StringFromVector(std::vector<uint8_t> input_vector) {
	std::string out = "";
	
	for (uint32_t i = 0; i < input_vector.size(); i++) {
		out += (char) input_vector[i];
	}
	
	return out;
}

uint8_t TestForNonText(std::string input) {
	for (uint16_t x = 0; x < input.size(); x++) {
		if (input[x] > 126 || input[x] < 32) {
			return 0;
		}
	}
	
	return 1;
}

TestString CreateTestString(std::string input_string, uint8_t input_key) {
	TestString t;
	t.s = input_string;
	t.key = input_key;
	return t;
}

std::vector<TestString> InitialFilterNonText(std::vector<uint8_t> input_bytes) {
	std::string xor_output_string;
	uint8_t xor_character;
	std::vector<uint8_t> xor_vector;
	std::vector<uint8_t> xor_output_bytes;
	std::vector<TestString> output_strings;
	
	xor_vector = CreateXorVector(0, input_bytes.size());
	xor_output_bytes = XorByteVectors(input_bytes, xor_vector);
	xor_output_string = StringFromVector(xor_output_bytes);
	if (TestForNonText(xor_output_string) == 1) {
		output_strings.push_back(CreateTestString(xor_output_string, xor_character));
	}
	
	for (xor_character = 1; xor_character != 0; xor_character++) {
		//test all potential i's
		xor_vector = CreateXorVector(xor_character, input_bytes.size());
		xor_output_bytes = XorByteVectors(input_bytes, xor_vector);
		xor_output_string = StringFromVector(xor_output_bytes);
		if (TestForNonText(xor_output_string) == 1) {
			output_strings.push_back(CreateTestString(xor_output_string, xor_character));
		}
	}
	
	return output_strings;
}

uint8_t TestForExcessivePunctuation(std::string test_string) {
	uint8_t punctuation_count = 0;
	
	for (uint16_t x = 0; x < test_string.size(); x++) {
		if ((32 < test_string[x] && test_string[x] < 48) || (57 < test_string[x] && test_string[x] < 65) || (90 < test_string[x] && test_string[x] < 97) || (122 < test_string[x] && test_string[x] < 127)) {
			punctuation_count++;
		}
		if (punctuation_count == PUNCTUATION_THRESHOLD) {
			return 0;
		}
	}
	
	return 1;
}

std::vector<TestString> FilterExcessivePunctuation(std::vector<TestString> input_strings) {
	std::vector<TestString> output_strings;
	
	for (uint8_t i = 0; i < input_strings.size(); i++) {
		if (TestForExcessivePunctuation(input_strings[i].s) == 1) {
			output_strings.push_back(input_strings[i]);
		}
	}
	
	return output_strings;
}

int main() {
	std::string input_string = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	std::vector<uint8_t> input_byte_vector;
	std::vector<TestString> potential_strings;
	
	input_byte_vector = ByteVectorFromString(input_string, "hex");;
	
	potential_strings = InitialFilterNonText(input_byte_vector);
	std::cout << "Remaining Keys (initial filter): " << potential_strings.size() << std::endl;
	
	potential_strings = FilterExcessivePunctuation(potential_strings);
	std::cout << "Remaining Keys (initial filter): " << potential_strings.size() << std::endl;
	
	for (uint16_t i = 0; i < potential_strings.size(); i++) {
		std::cout << "Key used: " << (unsigned) potential_strings[i].key << std::endl << potential_strings[i].s << std::endl;
	}
	
	std::cout << "Remaining Keys: " << potential_strings.size() << std::endl;
	
	return 0;
}