#include"MatasanoConverter.h"

// styled according to the Google C++ Style guide
// https://google.github.io/styleguide/cppguide.html

uint8_t NumberFromHexChar(char hex_character) {
	if (48 <= hex_character && hex_character <= 57) { //0-9
		return (uint8_t) hex_character - 48;
	} else if (65 <= hex_character && hex_character <= 70) { //A-F
		return (uint8_t) hex_character - 55;
	} else if (97 <= hex_character && hex_character <= 102) { //a-f
		return (uint8_t) hex_character - 87;
	} else { //other - error!
		throw std::invalid_argument("numberFromHexChar: hex_character not valid.");
	}
}


std::vector<uint8_t> Base64Splitter(std::vector<uint8_t> eight_bit_number_array) {
	uint8_t temp;
	std::vector<uint8_t> base_64_output;
	base_64_output.clear(); //may be redundant
	
	for (int i = 0; i < eight_bit_number_array.size(); i+=3) { //three 8 bit numbers are taken at once and converted into four 6 bit numbers
		temp = eight_bit_number_array[i] >> 2;
		base_64_output.push_back(temp);
		temp = (eight_bit_number_array[ i ] & 0x3) << 4 | eight_bit_number_array[i+1] >> 4;
		base_64_output.push_back(temp);
		temp = (eight_bit_number_array[i+1] & 0xF) << 2 | eight_bit_number_array[i+2] >> 6;
		base_64_output.push_back(temp);
		temp = eight_bit_number_array[i+2] & 0x3F;
		base_64_output.push_back(temp);
	}
	
	return base_64_output;
}


std::vector<uint8_t> HexSplitter(std::vector<uint8_t> eight_bit_number_array) {
	uint8_t temp;
	std::vector<uint8_t> hex_output;
	hex_output.clear(); //may be redundant
	
	for (int i = 0; i < eight_bit_number_array.size(); i++) {
		temp = eight_bit_number_array[i] >> 4;
		hex_output.push_back(temp);
		temp = eight_bit_number_array[i] & 0xF;
		hex_output.push_back(temp);
	}
	
	return hex_output;
}


char Base64Character(uint8_t base_64_number) {
	if (0 <= base_64_number && base_64_number <= 25) { //upper case characters
		return (char) base_64_number + 65;
	} else if (26 <= base_64_number && base_64_number <= 51) { //lower case characters
		return (char) base_64_number + 71;
	} else if (52 <= base_64_number && base_64_number <= 61) { //numbers
		return (char) base_64_number - 4;
	} else if (62 == base_64_number) { //+
		return '+';
	} else if (63 == base_64_number) { // /
		return '/';
	} else {
		throw std::invalid_argument("Base64Character: invalid base64 number (not a number 0-63)");
	}
}


char HexCharacter(uint8_t hex_number) {
	if (0 <= hex_number && hex_number <= 9) {
		return (char) hex_number + 48;
	} else if (10 <= hex_number && hex_number <= 15) {
		return (char) hex_number + 87;
	} else {
		throw std::invalid_argument("HexCharacter: invalid hex number (not a number 0-15)");
	}
}


uint8_t CombineHex(uint8_t msb, uint8_t lsb) {
	return (msb << 4) | lsb;
}


std::string GetBase64String(std::vector<uint8_t> input_vector) {
	std::vector<uint8_t> data_copy = input_vector; //create copy that can be safely modified if needed
	char padding_bytes; //counter to record number of bytes added - value will be 0, 1 or 2
	std::string base_64_string = "";

	if (data_copy.size() % 3 == 1) {
		//add two pad bytes
		data_copy.push_back(0);
		data_copy.push_back(0);
		padding_bytes = 2;
	} else if (data_copy.size() % 3 == 2) {
		//add one pad byte
		data_copy.push_back(0);
		padding_bytes = 1;
	} else {
		//no padding required
		padding_bytes = 0;
	}
	
	data_copy = Base64Splitter(data_copy);
	
	for (int i = 0; i < data_copy.size(); i++) {
		base_64_string += Base64Character(data_copy[i]);
	}
	
	if (padding_bytes == 1) {
		base_64_string.replace(base_64_string.length() - 1, 1, "=", 0, 1);
	} else if (padding_bytes == 2) {
		base_64_string.replace(base_64_string.length() - 2, 2, "==", 0, 2);
	}
	
	data_copy.clear(); //destroy the vector as the copy is no longer needed - maybe redundant
	
	return base_64_string;
}

std::string GetHexString(std::vector<uint8_t> input_vector) {
	std::vector<uint8_t> data_copy = input_vector; //create copy that can be safely modified if needed
	std::string hex_string = "";
	
	data_copy = HexSplitter(data_copy);
	
	for (int i = 0; i < data_copy.size(); i++) {
		hex_string += HexCharacter(data_copy[i]);
	}
	
	return hex_string;
}

std::vector<uint8_t> HexStringConvert(std::string input_string) {
	//need to loop over each character and add two characters at a time to the uint8_t array
	std::vector<uint8_t> output_vector;
	uint32_t max = input_string.length();
	uint8_t a = 0, b = 0;
	
	output_vector.clear(); //may be redundant
	
	if (max % 2 != 0) {
		throw std::invalid_argument("HexStringInput: inputString not valid hex - uneven length.");
	}
	
	for(uint32_t i = 0; i < max; i+=2) {
		a = NumberFromHexChar(input_string[i]);
		b = NumberFromHexChar(input_string[i + 1]);
		output_vector.push_back( CombineHex( a , b ) );
	}
	
	return output_vector;
}

std::string StringFromByteVector(std::vector<uint8_t> input_vector, std::string output_type) {
	std::string temp; //needed for upper case hex output
	if (output_type.compare("base64") == 0 || output_type.compare("b64") == 0 || output_type.compare("Base64") == 0 || output_type.compare("B64") == 0) {
		return GetBase64String(input_vector);	
	} else if (output_type.compare("hex") == 0 || output_type.compare("h") == 0) { //returns lower case hex output
		return GetHexString(input_vector);
	} else if (output_type.compare("H") == 0 || output_type.compare("Hex") == 0 || output_type.compare("HEX") == 0) { //returns upper case hex output
		temp = GetHexString(input_vector);
		transform(temp.begin(), temp.end(), temp.begin(), ::toupper);
		return temp;
	} else {
		throw std::invalid_argument("GetStringOutput: unknown output_type.");
	}
}

std::vector<uint8_t> ByteVectorFromString(std::string input_string, std::string input_type) {
	//this function uses an if statement and the hexStringInput function to allow for easy expansion of the MatasanoConverter class
	//e.g. for base64 input
	if (input_type.compare("hex") == 0 || input_type.compare("Hex") == 0 || input_type.compare("h") == 0) { 
		return HexStringConvert(input_string);
	} else {
		throw std::invalid_argument("inputString: unknown inputType.");
	}
}

