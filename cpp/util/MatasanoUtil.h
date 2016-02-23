#include<stdint.h>
#include<string>
#include<stdexcept>
#include<vector>

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

struct TestString {
	std::string s;
	uint8_t key;
	uint32_t score;
};

std::vector<uint8_t> XorByteVectors(std::vector<uint8_t> first_input, std::vector<uint8_t> second_input);
std::vector<TestString> FilterNonPrintable(std::vector<TestString> input_strings);
std::vector<TestString> FilterExcessivePunctuation(std::vector<TestString> input_strings, uint16_t punc_threshold);

