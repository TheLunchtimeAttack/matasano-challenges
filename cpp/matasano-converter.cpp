#include"matasano-converter.h"
#include<iostream>
#include<iomanip>
using namespace std;
//class MatasanoConverter {
//private:
//	vector<uint8_t> converterData;
//	uint8_t numberFromHexChar(char hexCharacter);
//	vector<uint8_t> base64Splitter(vector<uint8_t> eightBitNumberArray);
//	char base64Character(uint8_t base64Number);
//	void hexStringInput(string inputString);
//	uint8_t combineHex(uint8_t MSB, uint8_t LSB);
//public:
//	void inputBytes(vector<uint8_t> eightBitNumberArray);
//	void loadString(string inputString, string inputType);
//	string getBase64();
//	string getHex();
//}

uint8_t MatasanoConverter::numberFromHexChar(char hexCharacter) {
	//cout << hexCharacter << endl;
	if (48 <= hexCharacter && hexCharacter <= 57) { //0-9
		return (uint8_t) hexCharacter - 48;
	} else if (65 <= hexCharacter && hexCharacter <= 70) { //A-F
		return (uint8_t) hexCharacter - 55;
	} else if (97 <= hexCharacter && hexCharacter <= 102) { //a-f
		return (uint8_t) hexCharacter - 87;
	} else { //other - error!
		throw invalid_argument("numberFromHexChar: hexCharacter not valid.");
	}
}

uint8_t MatasanoConverter::combineHex(uint8_t MSB, uint8_t LSB) {
	return (MSB << 4) | LSB;
}

void MatasanoConverter::hexStringInput(string inputString) {
	//need to loop over each character and add two characters at a time to the uint8_t array
	uint32_t max = inputString.length();
	uint8_t a = 0, b = 0;
	
	if (max % 2 != 0) {
		throw invalid_argument("hexStringInput: inputString not valid hex - uneven length.");
	}
	
	converterData.clear();
	
	for(uint32_t i = 0; i < max; i+=2) {
		//loop over array
		a = numberFromHexChar(inputString[i]);
		b = numberFromHexChar(inputString[i + 1]);
		converterData.push_back( combineHex( a , b ) );
	}
}

void MatasanoConverter::loadString(string inputString, string inputType) {
	if (inputType.compare("hex") == 0) {
		hexStringInput(inputString);
	} else {
		throw invalid_argument("inputString: unknown inputType.");
	}
}

char MatasanoConverter::base64Character(uint8_t base64Number) {
	char out;
	if (0 <= base64Number && base64Number <= 25) { //upper case characters
		return (char) base64Number + 65;
	} else if (26 <= base64Number && base64Number <= 51) { //lower case characters
		return (char) base64Number + 71;
	} else if (52 <= base64Number && base64Number <= 61) { //numbers
		return (char) base64Number - 4;
	} else if (62 == base64Number) { //+
		return '+';
	} else if (63 == base64Number) { // /
		return '/';
	} else {
		throw invalid_argument("base64Character: invalid base64 number (not a number 0-63)");
	}
}

string MatasanoConverter::getBase64() {
	return "blah";
}

void MatasanoConverter::test() {
	int temp;
	cout << "vector contains " << converterData.size() << " elements:" << endl;
	cout << "testing base64Character 10=" << base64Character(10) << " 26=" << base64Character(26) << " 63=" << base64Character(63) << endl;
	
}