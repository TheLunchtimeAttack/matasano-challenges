#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

// we read a sting of hex values, and read them 2 by 2. This means we can convert them in bytes (8 bit binary numbers).
// then to convert into base64, we must read 3 of these bytes at a time, as 3x8 = 24. This is because a base64 number
// is represented by 6 bits, and 24%6 = 0. Hence, we must buffer the string of bytes so it is divisible by 3, before
// converting to base64.

int hextodec(char charIn){
	//
	// This function takes argument charIn a hex value of datatype char. It then uses
	// an ASCII look up with calculated offset to return the corresponding decimal value
	// (byte) as an integer.
	//

	int intIn = (int)charIn;

	if (48 <= intIn & intIn <= 57){       // reads numbers hex
		intIn = intIn - 48;
	}
	else if (65 <= intIn & intIn <= 70){  // reads upper case hex
		intIn = intIn - 55;
	}
	else if (97 <= intIn & intIn <= 102){ // reads lower case hex
		intIn = intIn - 87;
	}
	return intIn;
}

int combine_hex(int first, int second){
	//
	// This function takes two agruments, both integers. The first is shifted by 4 and then
	// the two bytes are logical OR'ed together. We then return output: the byte value 
	// max 256. This thus takes 2 hex characters and makes them a byte.
	//
	first = first << 4;
	second = second & 0x0f;

	int output = first | second;
	return output;
}

vector <int> base64_splitter(vector <int> input){
	//
	// takes a list of buffered bytes and does the math so they are returned in pairs of bytes
	// to then become 2 base64 chars. the entries of input are 4 bit numbers, so we need to
	// take 3 at a time, and make them bytes. We then can turn these 3 bytes into 2 base64 bytes
	//
	int len = input.size();
	int newlen =  (len / 3)*2;// for every 3 hex numbers we need 4 base64 represenatations, i.e 2 bytes

	vector <int> arr;

	for (int i = 0; i <= len - 2; i = i + 3){ //takes 3 hex numbers and turns into 4 base64 decimals
		int output1 = input[i] >> 2;
		arr.push_back(output1);
		int temp = 0x03 & input[i];

		int output2 = temp << 4 | input[i + 1] >> 4;
		arr.push_back (output2);
		temp = 0x0f & input[i + 1];

		int output3 = temp << 2 | input[i + 2] >> 6;
		arr.push_back(output3);

		int output4 = 0x3f & input[i + 2];
		arr.push_back(output4);
		}

	return arr;
}

char to_base64(int input){
	//
	// Takes single integer and converts to a base64 char
	//
	//

	if (0 <= input & input <= 25){
		return char(input + 65);
	}
	else if (26 <= input & input <= 51){
		return char(input + 71);
	}
	else if (52 <= input & input <= 61){
		return char(input - 4);
	}
	else if (input == 62){
		return char(43);
	}
	else if (input == 63){
		return char(47);
	}

	else{
		throw invalid_argument("Invalid base64 input");
	}

	return 'e'; //this shouldnt be 'e', but this will never be reached
}

vector <char> bytes_to_base64(vector <int> arr){
	//
	// turns bytes into base64. Takes input arr: a vector of bytes of any length
	// we must first buffer the length so it is divisible by 3.

	int len = arr.size();
	int buffamount = (3 - (len % 3)) % 3; // calculates how much to buffer
	int newlen = len + buffamount;

	vector <int> arrnew(newlen); //new buffered with 0s vector

	for (int i = 0; i < newlen; i++){
		if (i < len){ //copy old vector into new
			arrnew[i] = arr[i];
		}
		else // buffer with zeros at the end of the old vector
			arrnew[i] = 0;

	}

	vector <int> arrnew2 = base64_splitter(arrnew);
	vector <char> output; //vector to store the base64 char's

	for (int i = 0; i < arrnew2.size();i++){
		output.push_back(to_base64(arrnew2[i])); // finds each char
	}

	if (len % 3 == 1){  // sort out buffering alerts
		output.pop_back(); // remove 2 elements
		output.pop_back();
		output.push_back('='); // add two =
		output.push_back('=');
	}
	else if (len % 3 == 2){
		output.pop_back(); //remove 1 element
		output.push_back('='); // add one =
	}

	return output;

}

vector <int> read_hex(string input, int len){  //was int*
	//
	// takes a string and its corresponding length and reads two at entries of the
	// string at a time and stores the decimal values in an array.
	vector <int> arr(len/2);
	int count = 0;

	for (int i = 0; i <= len - 1; i += 2){
		arr[count] = combine_hex(hextodec(input[i]), hextodec(input[i + 1]));
		count = count + 1;
	}

	return arr;
}

string hex_to_base64(string input){
	// wrapper function that turns a string input to a string of base64
	int len = input.length();

	if (len % 2 != 0){
		cout << "Even number of hex characters required" << endl;
		throw invalid_argument("Error");

	}

	vector <int> arr = read_hex(input, len); // has length len/2
	vector <char> arrnew = bytes_to_base64(arr);
	string str(arrnew.begin(), arrnew.end());

	return str;
}

int main(){
	string input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";
	string str = hex_to_base64(input);

	cout << "Hex : " << input << endl;
	cout << "Base64: " << str;

	getchar();
	return 0;
}