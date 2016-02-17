#include <iostream>
#include <string>
#include "../util/MatasanoConverter.h"

void MatasanoConverterTest(std::string input, std::string inputType, std::string expectedOutput, std::string outputType) {
	std::string result;
	std::vector<uint8_t> bytes;
	
	bytes = ByteVectorFromString(input, inputType);
	result = StringFromByteVector(bytes, outputType);
	
	if (result.compare(expectedOutput) == 0) {
		std::cout << "PASSED" << std::endl << "Input: " << input << std::endl << "Output: " << result << std::endl << "As Required." << std::endl << std::endl;
	} else {
		std::cout << "FAILED" << std::endl << "Input: " << input << std::endl << "Expected: " << expectedOutput << std::endl << "Observed: " << result << std::endl;
	}
}

int main() {
	std::string test_input;
	std::string test_output;
		
	//Sam Standard case
	std::cout << "Sam tests: " << std::endl << "Test 1: ";
	test_input = "deadbeef1234";
	test_output = "3q2+7xI0";
	MatasanoConverterTest(test_input, "hex", test_output, "b64");
	
	//Sam padding test
	std::cout << "Test 2: ";
    test_input = "1a";
    test_output = "Gg==";
	MatasanoConverterTest(test_input, "hex", test_output, "b64");
	
	std::cout << "Test 3: ";
    test_input = "c0de";
    test_output = "wN4=";
	MatasanoConverterTest(test_input, "hex", test_output, "b64");
	
	//Sam null test
	std::cout << "Test 4: ";
    test_input = "";
    test_output = "";
	MatasanoConverterTest(test_input, "hex", test_output, "b64");
	
	std::cout << "Test 5: ";
    test_input = "BA5EBA11";
    test_output = "ul66EQ==";
	MatasanoConverterTest(test_input, "hex", test_output, "b64");
	
	return 0;
}