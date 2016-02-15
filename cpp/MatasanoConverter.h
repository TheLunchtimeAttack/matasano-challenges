#include<stdint.h>
#include<string>
#include<stdexcept>
#include<vector>
using namespace std;

class MatasanoConverter {
private:
	vector<uint8_t> converterData;
	uint8_t numberFromHexChar(char hexCharacter);
	vector<uint8_t> base64Splitter(vector<uint8_t> eightBitNumberArray);
	char base64Character(uint8_t base64Number);
	void hexStringInput(string inputString);
	uint8_t combineHex(uint8_t MSB, uint8_t LSB);
public:
	void inputBytes(vector<uint8_t> EightBitNumberArray);
	void loadString(string inputString, string inputType);
	string getBase64();
	string getHex();
};


