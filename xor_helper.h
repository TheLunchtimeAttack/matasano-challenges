#ifndef XOR_HELPER_H
#define XOR_HELPER_H

#include <string>

class xor_helper {
	public:
		void print_candidates(unsigned short possible_char[], std::string encrypted_hex, int hexlen);
		int *produce_count_array(std::string encrypted_hex);
	private:
		const int BYTE_LENGTH = 16*16;
		unsigned short hex_to_byte(std::string hex);
		unsigned short *hex_xor_to_byte_arr(std::string hex, std::string hex1);
		std::string byte_arr_to_hex_str(std::string hex, std::string hex1);
};

#endif