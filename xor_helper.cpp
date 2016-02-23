// #include "chall2.h"
#include <iostream>
#include <string>
#include <sstream>
#include <stdlib.h>
#include "xor_helper.h"

//const int xor_helper::BYTE_LENGTH = 16*16;

// Takes two hex characters and returns a byte
unsigned short xor_helper::hex_to_byte(std::string hex) {
	unsigned short byte = 0;
	std::istringstream iss(hex);
	iss >> std::hex >> byte;
	return byte;
}

unsigned short* xor_helper::hex_xor_to_byte_arr(std::string hex, std::string hex1) { 
    int size = hex.length();
    int size2 = hex1.length();
    unsigned short *byte_arr = new unsigned short[size/2];
    if (size == size2){

        for (int i=0; i<size; i=i+2) {
            unsigned short byte = 0;
            unsigned short byte2 = 0;
            std::string hex2 = hex.substr(i,2);
            std::string hex3 = hex1.substr(i,2);
            std::istringstream iss2(hex2);
            std::istringstream iss3(hex3);
            iss2 >> std::hex >> byte;
            iss3 >> std::hex >> byte2;
            unsigned short xor_byte = byte ^ byte2;
            byte_arr[i/2] = xor_byte;
        }
    }
    else {
    	std::cout << "The lengths of strings are inequal." << std::endl << "Exiting..." << std::endl;
        exit(EXIT_FAILURE);
    }
    return byte_arr;
}

// Function from challenge 2 but couldn't get it to work in different file.
std::string xor_helper::byte_arr_to_hex_str(std::string hex, std::string hex1) {
    unsigned short *byte_arr = hex_xor_to_byte_arr(hex,hex1);
    std::stringstream ss;
    for (int i=0; i<(hex.size())/2; i++)
    {
    	unsigned short byte = byte_arr[i];
    	ss << std::hex << byte;
    }
    std::string ret_hex = ss.str();
    return ret_hex;
}

int* xor_helper::produce_count_array(std::string encrypted_hex) {
	int len = encrypted_hex.length();
	short *byte_array = new short[len/2];
	int *count = new int[BYTE_LENGTH];

	for (int i=0; i<len; i=i+2) {
		std::string two_byte_hex = encrypted_hex.substr(i,2);
		unsigned short byte = hex_to_byte(two_byte_hex);
		byte_array[i/2] = byte;
	}
	for (int i=1; i<16; i++) {
		for (int j=1; j<16; j++) {
			std::string hex; 
			std::stringstream ss;
			ss << std::hex << (int)i;
			ss << std::hex << (int)j << std::endl;
			hex = ss.str();
			unsigned short hex_byte = hex_to_byte(hex);
			for (int k=0; k<len/2; k++) {
				if (hex_byte == byte_array[k]) {
					count[((i)*16)+j]++;	
					// std::cout << "i= " << i << ", j= " << j << ", count= " << count[((i-1)*16)+j] << std::endl;
				}
			}
		}

	}

	delete [] byte_array;
	return count;
}

void xor_helper::print_candidates(unsigned short possible_char[], std::string encrypted_hex, int hexlen) {
	for (int j=0; j<26;j++) {
		unsigned short poss_byte = possible_char[j];
		int weirdness = 0;
		std::stringstream hex_stream;
		hex_stream << std::hex << poss_byte;
		std::string hex_xor;
		for (int i=0;i<hexlen/2;i++) {
			hex_xor += hex_stream.str();
		}
		
		// Does the initial decryption
		std::string ret_hex = byte_arr_to_hex_str(encrypted_hex,hex_xor);
        std::stringstream ss1;
        int newlen = ret_hex.length();
        for (int i=0; i<newlen; i=i+2) {
        	std::string pair_hex = ret_hex.substr(i,2);
        	unsigned short byte_hex = hex_to_byte(pair_hex);

        	// Check that all the characters are either letters, spaces, question/exclamation marks, numbers or apostrophes
        	if (!((byte_hex >= 65 && byte_hex <= 90) || (byte_hex >= 97 && byte_hex <= 122) || byte_hex == 32 
                    || (byte_hex < 58 && byte_hex > 47)) && !(byte_hex < 32) && !(byte_hex > 126)) {
        		weirdness++;
        	}

            if (byte_hex < 32 || byte_hex > 126) {
                weirdness += 5;
            }
        	ss1 << (char)byte_hex;
        }
        ss1 << std::endl;
        // Edit this weirdness value based on results
        if (weirdness<2) {
            std::cout << "encrypted_hex: " << encrypted_hex << std::endl;
            std::cout << "Decryption: " << ss1.str();
            std::cout << "Encryption character: " << (char)possible_char[j] << std::endl;
            std::cout << "weirdness: " << weirdness << std::endl;
       	}
	}
}