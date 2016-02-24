#include "MatasanoUtil.h"

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

std::vector<uint8_t> XorByteVectors(std::vector<uint8_t> first_input, std::vector<uint8_t> second_input) {
	std::vector<uint8_t> output_vector;
		
	if (first_input.size() != second_input.size()) {
		throw std::invalid_argument("XorByteVectors: inputs of uneven length.");
	}
	
	for (int i = 0; i < first_input.size(); i++) {
		output_vector.push_back(first_input[i] ^ second_input[i]);
	}
	
	return output_vector;
}

std::vector<uint8_t> CreateSingleCharacterXorVector(uint8_t xor_character, uint32_t size) {
	std::vector<uint8_t> out;
	
	for (uint32_t i = 0; i < size; i++) {
		out.push_back(xor_character);
	}
	
	return out;
}

