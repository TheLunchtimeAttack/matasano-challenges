// #include "chall2.h"
#include <string>
#include "xor_helper.h"

int main(int argc, char** argv) {
	std::string encrypted_hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	int len = encrypted_hex.length();

	int *count = xor_helper::produce_count_array(encrypted_hex);

	unsigned short possible_char[26] = {0};
	for (char i='A'; i<='Z'; i++) {
		unsigned short z = i - 0;
		possible_char[z-65] = z;
	}

	xor_helper::print_candidates(possible_char, encrypted_hex, len);

	delete [] count;
}