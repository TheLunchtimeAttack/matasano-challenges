// #include "chall2.h"
#include <iostream>
#include <string>
#include <sstream>

using namespace	std;

const static int BYTE_LENGTH = 16*16;

// Takes two hex characters and returns a byte
unsigned short hex_to_byte(string hex) {
	unsigned short byte = 0;
	istringstream iss(hex);
	iss >> std::hex >> byte;
	return byte;
}

// Function from challenge 2 but couldn't get it to work in different file.
static string hex_to_byte_xor_to_hex(string hex, string hex1) {
    int size = hex.length();
    int size2 = hex1.length();
    string ret_hex = "";
    if (size == size2){

        for (int i=0; i<size; i=i+2) {
            unsigned short byte = 0;
            unsigned short byte2 = 0;
            string hex2 = hex.substr(i,2);
            string hex3 = hex1.substr(i,2);
            istringstream iss2(hex2);
            istringstream iss3(hex3);
            iss2 >> std::hex >> byte;
            iss3 >> std::hex >> byte2;
            unsigned short xor_byte = byte ^ byte2;
    
            std::stringstream stream;
            stream << std::hex << xor_byte;
            string res(stream.str());
            ret_hex += res;
        }
    }
    else {
        return "0";
    }
    return ret_hex;
}

int *produce_count_array(string encrypted_hex) {
	int len = encrypted_hex.length();
	short *byte_array = new short[len/2];
	int *count = new int[BYTE_LENGTH];

	for (int i=0; i<len; i=i+2) {
		string two_byte_hex = encrypted_hex.substr(i,2);
		unsigned short byte = hex_to_byte(two_byte_hex);
		byte_array[i/2] = byte;
	}
	for (int i=1; i<16; i++) {
		for (int j=1; j<16; j++) {
			string hex; 
			stringstream ss;
			ss << std::hex << (int)i;
			ss << std::hex << (int)j << endl;
			hex = ss.str();
			unsigned short hex_byte = hex_to_byte(hex);
			for (int k=0; k<len/2; k++) {
				if (hex_byte == byte_array[k]) {
					count[((i)*16)+j]++;	
					// cout << "i= " << i << ", j= " << j << ", count= " << count[((i-1)*16)+j] << endl;
				}
			}
		}

	}

	delete [] byte_array;
	return count;
}

int main(int argc, char** argv) {
	string encrypted_hex = "1b37373331363f78151b7f2b783431333d78397828372d363c78373e783a393b3736";
	int len = encrypted_hex.length();
	int max = 0;

	int *count = produce_count_array(encrypted_hex);

	unsigned short possible_char[26] = {0};
	for (char i='A'; i<='Z'; i++) {
		unsigned short z = i - 0;
		possible_char[z-65] = z;
	}

	for (int j=0; j<26;j++) {
		unsigned short poss_byte = possible_char[j];
		unsigned short xor_byte = poss_byte ^ max;
		bool weirdness = false;
		stringstream hex_stream;
		hex_stream << std::hex << xor_byte;
		string hex_xor;
		for (int i=0;i<len/2;i++) {
			hex_xor += hex_stream.str();
		}
		
		// Does the initial decryption
		string ret_hex = hex_to_byte_xor_to_hex(encrypted_hex,hex_xor);
		if (ret_hex != "0"){
	        stringstream ss1;
	        int newlen = ret_hex.length();
	        for (int i=0; i<newlen; i=i+2) {
	        	string pair_hex = ret_hex.substr(i,2);
	        	unsigned short byte_hex = hex_to_byte(pair_hex);
	        	// Check that all the characters are either letters, spaces or apostrophes
	        	if (!((byte_hex >= 65 && byte_hex <= 90) || (byte_hex >= 97 && byte_hex <= 122) || byte_hex == 32 || byte_hex == 39)) {
	        		weirdness = true;
	        		break;
	        	}
	        	ss1 << (char)byte_hex;
	        }
	        ss1 << endl;
	        if (!weirdness) {
	            cout << "Decryption: " << ss1.str();
	            cout << "Encryption character: " << (char)possible_char[j] << endl;
	       	}
	    }
	    else {
	        cout << "The lengths of the hex strings are not equal." << endl << "Terminating..." << endl;
	        cout << encrypted_hex.length() << endl;
	        cout << hex_xor.length() << endl;
	    }
	}
}