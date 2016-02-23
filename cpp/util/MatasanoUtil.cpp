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

uint8_t TestForNonPrintable(std::string input) {
	for (uint16_t x = 0; x < input.size(); x++) {
		if (input[x] > 126 || input[x] < 32) {
			return 0;
		}
	}
	
	return 1;
}

std::vector<TestString> FilterNonPrintable(std::vector<TestString> input_strings) {
	std::vector<TestString> output_strings;
	
	for (uint16_t i = 0; i < input_strings.size(); i++) {
		if (TestForNonPrintable(input_strings[i].s) == 1) {
			output_strings.push_back(input_strings[i]);
		}
	}
	
	return output_strings;
}

uint8_t TestForExcessivePunctuation(std::string test_string, uint16_t punc_threshold) {
	uint8_t punctuation_count = 0;
	
	for (uint16_t x = 0; x < test_string.size(); x++) {
		if ((32 < test_string[x] && test_string[x] < 48) || (57 < test_string[x] && test_string[x] < 65) || (90 < test_string[x] && test_string[x] < 97) || (122 < test_string[x] && test_string[x] < 127)) {
			punctuation_count++;
		}
		if (punctuation_count == punc_threshold) {
			return 0;
		}
	}
	
	return 1;
}

std::vector<TestString> FilterExcessivePunctuation(std::vector<TestString> input_strings, uint16_t punc_threshold) {
	std::vector<TestString> output_strings;
	
	for (uint8_t i = 0; i < input_strings.size(); i++) {
		if (TestForExcessivePunctuation(input_strings[i].s, punc_threshold) == 1) {
			output_strings.push_back(input_strings[i]);
		}
	}
	
	return output_strings;
}


