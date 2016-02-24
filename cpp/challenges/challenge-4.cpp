#include <iostream>
#include <string>
#include <stdint.h>
#include "../util/MatasanoConverter.h"
#include "../util/MatasanoUtil.h"
#include "../util/StringTesting.h"
#include "../util/FileRead.h"

int main() {
	std::string file_name = "4.txt";
	std::vector<std::string> input_file = ReadFileContents(file_name);
	
	for (uint16_t i = 0; i < input_file.size(); i++) {
		std::cout << input_file[i] << std::endl;
	}
	
	std::cout << "File contains " << input_file.size() << " lines." << std::endl;
	
	return 0;
}

