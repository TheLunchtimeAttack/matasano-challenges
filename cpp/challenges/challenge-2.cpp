#include <iostream>
#include <string>
#include <stdint.h>
#include "../util/MatasanoConverter.h"
#include "../util/MatasanoUtil.h"

//Write a function that takes two equal-length buffers and produces their XOR combination.
//
//If your function works properly, then when you feed it the string:
//
//1c0111001f010100061a024b53535009181c
//
//... after hex decoding, and when XOR'd against:
//
//686974207468652062756c6c277320657965
//
//... should produce:
//
//746865206b696420646f6e277420706c6179

int main() {
	std::string input_1_string = "1c0111001f010100061a024b53535009181c";
	std::string input_2_string = "686974207468652062756c6c277320657965";
	std::string expected_output_string = "746865206b696420646f6e277420706c6179";
	std::string xor_output_string;
	MatasanoConverter m;
	MatasanoUtil u;
	std::vector<uint8_t> input_1_bytes;
	std::vector<uint8_t> input_2_bytes;
	std::vector<uint8_t> xor_output_bytes;
	
	m.LoadString(input_1_string, "hex");
	input_1_bytes = m.GetBytes();
	
	m.LoadString(input_2_string, "hex");
	input_2_bytes = m.GetBytes();
	
	xor_output_bytes = u.XorByteVectors(input_1_bytes, input_2_bytes);
	m.LoadBytes(xor_output_bytes);
	xor_output_string = m.GetStringOutput("hex");
	
	std::cout << "Matasano Challenge 2:" << std::endl << "Input 1: " << input_1_string << std::endl << "Input 2: " << input_2_string << std::endl;
	std::cout << "Output:  " << xor_output_string << std::endl;
	
	if (xor_output_string.compare(expected_output_string) == 0) {
		std::cout << "Challenge Passed." << std::endl;
	} else {
		std::cout << "Challenge failed." << std::endl << "Expected Output: " << expected_output_string << std::endl;
	}
	
	return 0;
}