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

TestString CreateTestString(std::string input_string, uint8_t input_key);
std::vector<TestString> FilterNonPrintable(std::vector<TestString> input_strings);
std::vector<TestString> FilterExcessivePunctuation(std::vector<TestString> input_strings, uint16_t punc_threshold);

