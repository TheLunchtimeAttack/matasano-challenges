#include<stdint.h>
#include<string>
#include<stdexcept>
#include<vector>

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

std::vector<uint8_t> XorByteVectors(std::vector<uint8_t> first_input, std::vector<uint8_t> second_input);
std::vector<uint8_t> CreateSingleCharacterXorVector(uint8_t xor_character, uint32_t size);
	
