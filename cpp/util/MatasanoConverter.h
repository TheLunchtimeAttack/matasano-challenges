#include<stdint.h>
#include<string>
#include<stdexcept>
#include<vector>
#include<algorithm>

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

class MatasanoConverter {
private:
	std::vector<uint8_t> converter_data;
	uint8_t NumberFromHexChar(char hex_character);
	std::vector<uint8_t> Base64Splitter(std::vector<uint8_t> eight_bit_number_array);
	std::vector<uint8_t> HexSplitter(std::vector<uint8_t> eight_bit_number_array);
	char Base64Character(uint8_t base_64_number);
	char HexCharacter(uint8_t hex_number);
	uint8_t CombineHex(uint8_t msb, uint8_t lsb);
	void HexStringInput(std::string input_string);
	std::string GetBase64String();
	std::string GetHexString();
public:
	std::vector<uint8_t> GetBytes();
	void LoadBytes(std::vector<uint8_t> eight_bit_number_array);
	void LoadString(std::string input_string, std::string input_type);
	std::string GetStringOutput(std::string output_type);
};


