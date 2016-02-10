#include<matasano-converter.h>

//class MatasanoConverter {
//private:
//	vector<uint8_t> converterData;
//	uint8_t numberFromHexChar(char hexCharacter);
//	vector<uint8_t> base64Splitter(vector<uint8_t> 8bitNumberArray);
//	char base64Character(uint8_t base64Number);
//	void hexStringInput(string inputString);
//	uint8_t combineHex(uint8_t MSB, uint8_t LSB);
//public:
//	void inputBytes(vector<uint8_t> 8bitNumberArray);
//	void inputString(string inputString, string inputType);
//	string getBase64();
//	string getHex();
//}

uint8_t MatasanoConverter::numberFromHexChar(char hexCharacter) {
	if 48 <= hexCharacter && hexCharacter <= 57 { //0-9
		return (uint8_t) hexCharacter - 48;
	} else if (65 <= hexCharacter && hexCharacter <= 70) { //A-F
		return (uint8_t) hexCharacter - 55;
	} else if (97 <= hexCharacter && hexCharacter <= 102) { //a-f
		return (uint8_t) hexCharacter - 87;
	} else { //other - error!
		throw invalid_argument("numberFromHexChar: hexCharacter not valid.")
	}
}

uint8_t combineHex(uint8_t MSB, uint8_t LSB) {
	return (MSB << 4) || LSB;
}

void MatasanoConverter::hexStringInput(string inputString) {
	//need to loop over each character and add two characters at a time to the uint8_t array
	uint32_t max = inputString.length();
	
	if max % 2 != 0 {
		throw invalid_argument("hexStringInput: inputString not valid hex - uneven length.")
	}
	
	converterData = new vector<uint8_t>
	
	for(uint32_t i = 0; i < max; i+=2) {
		//loop over array
	}
}

void MatasanoConverter::inputString(string inputString, string inputType) {
	if inputType.compare("hex") {
		hexStringInput(inputString);
	} else {
		throw invalid_argument("inputString: unknown inputType.")
	}
}

string MatasanoConverter::getBase64() {
	return "blah";
}