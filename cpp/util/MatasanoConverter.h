#include<stdint.h>
#include<string>
#include<stdexcept>
#include<vector>
#include<algorithm>

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

#ifndef MATASANOCONVERTER_H
#define MATASANOCONVERTER_H

std::vector<uint8_t> ByteVectorFromString(std::string input_string, std::string input_type);
std::string StringFromByteVector(std::vector<uint8_t> input_vector, std::string output_type);

#endif /* MATASANOCONVERTER */
