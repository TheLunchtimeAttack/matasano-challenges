#include <iostream>
#include <string>
#include <vector>

using namespace std;

int hextobyte(char charIn){
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

char bytetohex(int dec){
	// takes an integer byte and turns it into its hexidecimal value. The hex number is returned as
	// a char, and uses lowercase alphabetical characters when needed.
	char charIn;

	if (dec <= 9 & dec >= 0){ //numbers
		dec = dec + 48;
	}
	else if (dec <= 15 & dec >= 10){
		dec = dec + 87;
	}
	return (char)dec;
}


vector <int> xor(vector <int> a, vector <int> b){
	//
	// XOR's a and b. for a,b two svectors of equal length. Returns vector of integers
	//
	int len = a.size();
	int len2 = b.size();

	vector <int> xordec;

	if (len != len2){ // check equal length
		cout << "Strings must be of equal length";
		throw invalid_argument("Strings must be of equal length");
	}

	for (int i = 0; i < len; i++){ //bitwise XOR
		int xor = (a[i] ^ b[i]);
		xordec.push_back(xor);
	}
	return xordec;
}

vector <int> hexdecode(string a){
	//
	// takes a string of hex characters and converts to a vector of decimal values (binary)
	//

	int len = a.length();
	vector <int> intstr;

	for (int i = 0; i < len; i++){
		intstr.push_back(hextobyte(a[i]));
	}
	return intstr;
}

string hexencode(vector <int> xordec){
	// takes vector of integers and returns the corresponding string of hex characters
	vector <char> xorhex;

	for (int i = 0; i < xordec.size(); i++){
		xorhex.push_back(bytetohex(xordec[i]));
	}

	 string str(xorhex.begin(), xorhex.end());
	 return str;
}

int main(){
	string a =  "1c0111001f010100061a024b53535009181c";
	string b = "686974207468652062756c6c277320657965";

	string str = hexencode(xor(hexdecode(a), hexdecode(b))); //hex encoding the xor of the decoded hex strings
	cout << str;

	getchar();
	return 0;
}