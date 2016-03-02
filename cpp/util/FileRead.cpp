#include "FileRead.h"

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

std::vector<std::string> ReadFileContents(std::string file_name) {
	std::vector<std::string> output_vector;
	
	std::string line;
	std::ifstream myfile (file_name);
	if (myfile.is_open()) {
		while ( getline (myfile,line) )
		{
			output_vector.push_back(line);
		}
	myfile.close();
	} else {
		throw std::runtime_error("ReadFileContents: Unable to open file.");
	}
	
	return output_vector;
}

