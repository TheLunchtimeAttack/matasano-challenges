#include <iostream>
#include "../util/MatasanoConverter.h"
#include "../util/MatasanoUtil.h"

int main() {
	std::string s = "Burning 'em, if you ain't quick and nimble\nI go crazy when I hear a cymbal";
	std::string key = "ICE";
	std::string expected_output = "0b3637272a2b2e63622c2e69692a23693a2a3c6324202d623d63343c2a26226324272765272a282b2f20430a652e2c652a3124333a653e2b2027630c692b20283165286326302e27282f";
	std::vector<uint8_t> s_byte_vector = ByteVectorFromString(s, "ASCII");
	std::vector<uint8_t> key_byte_vector = ByteVectorFromString(key, "ASCII");	
	std::vector<uint8_t> result_vector = RepeatingKeyXor(s_byte_vector, key_byte_vector);
	std::string result = StringFromByteVector(result_vector, "hex");
	
	std::cout << result << std::endl;
	
	if (expected_output.compare(result) == 0) {
		std::cout << "As expected." << std::endl;
	}
	return 0;
}
