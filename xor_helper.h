#ifndef XOR_HELPER_H
#define XOR_HELPER_H

#include <string>

class xor_helper {
	public:
		static void print_candidates(unsigned short possible_char[], std::string encrypted_hex, int hexlen);
		static int *produce_count_array(std::string encrypted_hex);
	private:
		const static int BYTE_LENGTH;
		unsigned short hex_to_byte(std::string hex);
		unsigned short *hex_xor_to_byte_arr(std::string hex, std::string hex1);
		std::string byte_arr_to_hex_str(std::string hex, std::string hex1);
};

#endif