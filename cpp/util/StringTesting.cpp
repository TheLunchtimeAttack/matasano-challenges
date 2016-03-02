#include "StringTesting.h"


uint8_t TestForNonPrintable(std::string input) {
	for (uint16_t x = 0; x < input.size(); x++) {
		if (input[x] > 126 || input[x] < 32) {
			if (input[x] != 9 && input[x] != 10 && input[x] != 11 && input[x] != 13) {
				return 0;
			}
		}
	}
	
	return 1;
}

std::vector<TestString> FilterNonPrintable(std::vector<TestString> input_strings) {
	std::vector<TestString> output_strings;
	
	for (uint16_t i = 0; i < input_strings.size(); i++) {
		if (TestForNonPrintable(input_strings[i].GetCipherText()) == 1) {
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
		if (TestForExcessivePunctuation(input_strings[i].GetCipherText(), punc_threshold) == 1) {
			output_strings.push_back(input_strings[i]);
		}
	}
	
	return output_strings;
}

std::vector<TestString> AnalyseLetterFrequencies(std::vector<TestString> input_strings) {
	// The function freqanal performs frequeny analysis on the inputted vector of strings poss.
	// It does this by comparing entries of a vector of the most common characters in English text
	// with each element of the vector poss. Each element is given a value of the frequency of these
	// letters, and the element with the highest score is then returned as a string.

	std::vector<char> freq = { ' ', 'e', 't', 'a', 'o', 'i', 'n', 's' }; // most common characters, ordered by most frequent first
	std::vector<TestString> scored_strings = input_strings;

	for (int i = 0; i < input_strings.size(); i++){ //searches through each string
		int32_t n = 0; // counts freqyency of j'th entry in freq
		for (int j = 0; j < freq.size(); j++){
			n = n + ((int32_t) count(input_strings[i].GetCipherText().begin(), input_strings[i].GetCipherText().end(), freq[j])*(freq.size() - j)); // this counts, then give some
			//weight assined to each char dependent on its index in the list
		}
		scored_strings[i].SetScore(n);
		//cout << "There are " << n << " common letters in the plain text." << endl;
	}
	return scored_strings;
}

