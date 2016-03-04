#include <iostream>
#include <string>
#include <stdint.h>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <algorithm>
#include "../util/MatasanoConverter.h"
#include "../util/MatasanoUtil.h"
#include "../util/StringTesting.h"
#include "../util/FileRead.h"
#include "../util/TestString.h"

#define PUNCTUATION_THRESHOLD 5

std::vector<TestString> TestStringVectorSetup(std::string input_string) {
	std::vector<uint8_t> input_bytes = ByteVectorFromString(input_string, "hex");
	std::string xor_output_string;
	uint8_t xor_character = 0;
	std::vector<uint8_t> xor_vector;
	std::vector<uint8_t> xor_output_bytes;
	std::vector<TestString> output_strings;
	
	xor_vector = CreateSingleCharacterXorVector(xor_character, input_bytes.size());
	xor_output_bytes = XorByteVectors(input_bytes, xor_vector);
	xor_output_string = StringFromByteVector(xor_output_bytes, "ASCII");
	output_strings.push_back(TestString(input_string, xor_output_string, xor_character));
	
	for (xor_character = 1; xor_character != 0; xor_character++) {
		//test all potential i's
		xor_vector = CreateSingleCharacterXorVector(xor_character, input_bytes.size());
		xor_output_bytes = XorByteVectors(input_bytes, xor_vector);
		xor_output_string = StringFromByteVector(xor_output_bytes, "ASCII");
		output_strings.push_back(TestString(input_string, xor_output_string, xor_character));
	}
	
	return output_strings;
}

std::vector<TestString> InitialKeyAndStringPurge(std::vector<std::string> input_strings) {
	std::vector<TestString> current_key;
	std::vector<TestString> output_vector;
	
	for (int i = 0; i < input_strings.size(); i++) {
		current_key = TestStringVectorSetup(input_strings[i]);
		current_key = FilterNonPrintable(current_key);
		current_key = FilterExcessivePunctuation(current_key, PUNCTUATION_THRESHOLD);
		output_vector.reserve(output_vector.size() + current_key.size());
		output_vector.insert(output_vector.end(), current_key.begin(), current_key.end());
	}
	
	std::cout << "remaining options = " << output_vector.size() << std::endl;
	
	return output_vector;
}

int main() {
	std::vector<std::string> DataArray = ReadFileContents("datafiles/4.txt"); // read in the strings
	std::cout << "Number of inputs: " << DataArray.size() << std::endl;
	std::vector<TestString> possible_outputs = InitialKeyAndStringPurge(DataArray); // vector of possible strings
	std::cout << "Number after initial cull: " << possible_outputs.size() << std::endl;
	
	possible_outputs = AnalyseLetterFrequencies(possible_outputs);
	
	int ash_ketchum = FindHighestScore(possible_outputs);
	
	std::cout << possible_outputs[0].GetCipherText() << std::endl;

	return 0;
}