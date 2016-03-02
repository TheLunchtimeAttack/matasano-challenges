#include "TestString.h"

TestString::TestString(std::string plain_input, std::string cipher_input, uint8_t key_input) {
	plain_text = plain_input;
	cipher_text = cipher_input;
	key = key_input;
	score = 0;
}

TestString::TestString(std::string cipher_input, uint8_t key_input) {
	plain_text = "";
	cipher_text = cipher_input;
	key = key_input;
	score = 0;
}

std::string TestString::GetPlainText() {
	return plain_text;
}

std::string TestString::GetCipherText() {
	return cipher_text;
}

uint8_t TestString::GetKey() {
	return key;
}

int32_t TestString::GetScore() {
	return score;
}

void TestString::SetScore(int32_t score_input) {
	score = score_input;
}

