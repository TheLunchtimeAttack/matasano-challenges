#include <fstream>
#include <string>
#include <vector>

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

#ifndef FILEREAD_H
#define FILEREAD_H

std::vector<std::string> ReadFileContents(std::string file_name);

#endif /* FILEREAD_H */
