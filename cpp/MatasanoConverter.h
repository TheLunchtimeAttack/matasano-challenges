#include<stdint.h>
#include<string>
#include<stdexcept>
#include<vector>
#include<algorithm>
using namespace std;

class MatasanoConverter {
private:
	vector<uint8_t> converterData;
	uint8_t numberFromHexChar(char hexCharacter);
	vector<uint8_t> base64Splitter(vector<uint8_t> eightBitNumberArray);
	vector<uint8_t> hexSplitter(vector<uint8_t> eightBitNumberAray);
	char base64Character(uint8_t base64Number);
	char hexCharacter(uint8_t hexNumber);
	uint8_t combineHex(uint8_t MSB, uint8_t LSB);
	void hexStringInput(string inputString);
	string getBase64();
	string getHex();
public:
	void inputBytes(vector<uint8_t> EightBitNumberArray);
	void loadString(string inputString, string inputType);
	string getStringOutput(string outputType);
};


