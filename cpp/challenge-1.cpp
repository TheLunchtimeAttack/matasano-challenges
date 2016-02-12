#include <iostream>
#include <string>
#include "matasano-converter.h"
using namespace std;

int main() {
	string hexInput("49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d");
	string testString = ("SSdtIGtpbGxpbmcgeW91ciBicmFpbiBsaWtlIGEgcG9pc29ub3VzIG11c2hyb29t");
	MatasanoConverter m;
	
	m.loadString(hexInput, "hex");
	m.test();
	//cout << m.getBase64();
}