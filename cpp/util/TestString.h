#include <string>
#include <vector>
#include <stdint.h>

#ifndef TESTSTRING_H
#define TESTSTRING_H
class TestString {
private:
	std::string plain_text;
	std::string cipher_text;
	uint8_t key;
	int32_t score;
public:
	TestString(std::string plain_input, std::string cipher_input, uint8_t key_input);
	TestString(std::string cipher_input, uint8_t key_input);
	std::string GetPlainText();
	std::string GetCipherText();
	uint8_t GetKey();
	int32_t GetScore();
	void SetScore(int32_t score_input);
};

#endif /* TESTSTRING_H  */ 
