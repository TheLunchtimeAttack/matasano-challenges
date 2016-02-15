#include <iostream>
#include <string>
#include "MatasanoConverter.h"

void MatasanoConverterTest(MatasanoConverter m, std::string input, std::string inputType, std::string expectedOutput, std::string outputType) {
	std::string result;
	
	m.LoadString(input, inputType);
	result = m.GetStringOutput(outputType);
	
	if (result.compare(expectedOutput) == 0) {
		std::cout << "PASSED" << std::endl << "Input: " << input << std::endl << "Output: " << result << std::endl << "As Required." << std::endl << std::endl;
	} else {
		std::cout << "FAILED" << std::endl << "Input: " << input << std::endl << "Expected: " << expectedOutput << std::endl << "Observed: " << result << std::endl;
	}
}


int main() {
	std::string test_input = ("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d"); //Matasano Challenge 1 input
	std::string test_output = ("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t"); //Matasano Challenge 1 expected output
	MatasanoConverter m;
		
	std::cout << "Challenge 1: ";
	MatasanoConverterTest(m, test_input, "hex", test_output, "b64");
	
	//Sam Standard case
	std::cout << "Sam tests: " << std::endl << "Test 1: ";
	test_input = "deadbeef1234";
	test_output = "3q2+7xI0";
	MatasanoConverterTest(m, test_input, "hex", test_output, "b64");
	
	//Sam padding test
	std::cout << "Test 2: ";
    test_input = "1a";
    test_output = "Gg==";
	MatasanoConverterTest(m, test_input, "hex", test_output, "b64");
	
	std::cout << "Test 3: ";
    test_input = "c0de";
    test_output = "wN4=";
	MatasanoConverterTest(m, test_input, "hex", test_output, "b64");
	
	//Sam null test
	std::cout << "Test 4: ";
    test_input = "";
    test_output = "";
	MatasanoConverterTest(m, test_input, "hex", test_output, "b64");
	
	std::cout << "Test 5: ";
    test_input = "BA5EBA11";
    test_output = "ul66EQ==";
	MatasanoConverterTest(m, test_input, "hex", test_output, "b64");
}