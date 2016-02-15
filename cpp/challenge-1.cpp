#include <iostream>
#include <string>
#include "MatasanoConverter.h"
using namespace std;

int main() {
	string hexInput("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
	string testString = ("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
	string result;
	MatasanoConverter m;
	
	m.loadString(hexInput, "hex");
	result = m.getStringOutput("b64");
	
	cout << "Challenge 1: ";
	if (result.compare(testString) == 0) {
		cout << "PASSED" << endl << "Input: " << hexInput << endl << "Output: " << result << endl << "As Required." << endl;
	} else {
		cout << "FAILED" << endl << "Input: " << hexInput << endl << "Expected: " << testString << endl << "Observed: " << result << endl;
	}
}