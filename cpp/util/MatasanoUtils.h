#include<stdint.h>
#include<string>
#include<stdexcept>
#include<vector>

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

class MatasanoUtils {
private:
	
public:
	std::vector<uint8_t> XorByteVectors(std::vector<uint8_t> first_input, std::vector<uint8_t> second_input);
};