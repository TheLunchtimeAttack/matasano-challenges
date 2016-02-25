#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <fstream>
#include <iterator>
#include <algorithm>
#include <iostream>

using namespace std;

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
	else {
		cout << "no good" << endl;
		return 0;
	}
	return intIn;
}

vector <int> read_hex(string input, int len){  //was int*
	//
	// takes a string and its corresponding length and reads two at entries of the
	// string at a time and stores the decimal values in an array.
	vector <int> arr(len / 2);
	int count = 0;

	for (int i = 0; i <= len - 1; i += 2){
		arr[count] = combine_hex(hextobyte(input[i]), hextobyte(input[i + 1]));
		count = count + 1;
	}

	return arr;
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


vector <char> keytest(vector <int> bytes, int key){
	// This function takes arguement bytes, a vector of hex decoded base64 bytes and a key.
	// We know that this byte string has been XOR'd by a string of the key repeated suffiently.
	// This function uses the xor function to XOR the bytes with a vector of the repeteated key.
	// This effectively decrypts the cipher text we were given. A sanity check is performed, in
	// which the ascii characters the resulting XOR'd string contains are checked to see if they
	// are printable. If the string contains unprintable characters, the key is dropped. If there
	// are no such unprintable characters the vector of ascii characters is returned.

	vector <int> keyvector(bytes.size());
	vector <char> plaintext;

	fill(keyvector.begin(), keyvector.end(), key); // fills a vector of keys
	vector <int> plainbytes = xor(bytes, keyvector); // XORs the bytes with the keyvector

	for (int i = 0; i < plainbytes.size(); i++){ // look at each element in the vector and check the byte is printable
		if ((plainbytes[i] > 126 | plainbytes[i] < 32) & (plainbytes[i] != 9) & (plainbytes[i] != 10)&(plainbytes[i] != 11)&(plainbytes[i] != 13)){ //in the range of readable ascii characters // add 9 , 10 , 11, 13 ascii characters
			//cout << endl << "invalid char";
			vector <char> empty;
			return  empty; // unprintable char, so return empty vector
		}
		else {
			plaintext.push_back((char)plainbytes[i]); //vector of ascii chars
		}
	}
	return plaintext;
}

string freqanal(vector <string> poss){
	// The function freqanal performs frequeny analysis on the inputted vector of strings poss.
	// It does this by comparing entries of a vector of the most common characters in English text
	// with each element of the vector poss. Each element is given a value of the frequency of these
	// letters, and the element with the highest score is then returned as a string.

	vector <char> freq = { ' ', 'e', 't', 'a', 'o', 'i', 'n', 's' }; // most common characters, ordered by most frequent first
	vector <int> freqnum; //stores total number of occourenes of those letters, for each string

	for (int i = 0; i < poss.size(); i++){ //searches through each string
		int n = 0; // counts freqyency of j'th entry in freq
		for (int j = 0; j < freq.size(); j++){
			n = n + count(poss[i].begin(), poss[i].end(), freq[j])*(freq.size() - j); // this counts, then give some
			//wieght assined to each char dependent on its index in the list
		}
		freqnum.push_back(n);
		//cout << "There are " << n << " common letters in the plain text." << endl;
	}

	int maxindex = distance(freqnum.begin(), max_element(freqnum.begin(), freqnum.end())); // this finds the maximum element
	// and uses distance to calculate the index of the maximum element
	string str(poss[maxindex].begin(), poss[maxindex].end()); // the corresponding element of poss, is returned as a string
	return str;
}

vector <string> readfile(string str){
	// This function reads the file name stored as a string in the variable str. It then
	// creates a vector of strings and stores each string in the file strings.txt as an
	// element in the vector

	vector<string> DataArray;

	// Create two input streams, opening the named files in the process.
	// You only need to check for failure if you want to distinguish
	// between "no file" and "empty file". In this example, the two
	// situations are equivalent.
	ifstream myfile(str);

	// std::copy(InputIt first, InputIt last, OutputIt out) copies all
	//   of the data in the range [first, last) to the output iterator "out"
	// istream_iterator() is an input iterator that reads items from the
	//   named file stream
	// back_inserter() returns an interator that performs "push_back"
	//   on the named vector.
	copy(istream_iterator<string>(myfile),
		istream_iterator<string>(),
		back_inserter(DataArray));

	cout << DataArray.size();
	for (int j = 0; j < DataArray.size(); j++){ // print all possibilities
		cout << DataArray[j] << endl;
	}
	return DataArray;
}

vector <string> keyatt(vector <string> Array){
	// keyatt takes a vector of hex encoded strings in a variable called Array.It then looks at each element
	// of this array, and decodes the hex characters into bytes. We know these bytes have been XOR'd with some
	// ASCII character (the key) so we XOR this byte string with every possible key (128 of them) to retrive the
	// possible plaintexts. We do this by calling the keytest function on each element of byte strings and the 
	// key we are using to decrypt. If the dectrypted string has no unprintable characters, it is added to a vector
	// of possible plaintext strings. This vector is then returned by the function.


	vector <string> poss; //possible strings
	for (int x = 0; x < Array.size(); x++){ //loop through all elements in array
		vector <int> bytes = read_hex(Array[x], Array[x].length()); //gets bytes

		for (int i = 0; i < 128; i++){ //we run through all 128 possible keys here
			vector <char> plaintext = keytest(bytes, i); // calls keytest to try key i on the decoded bytes
			if (plaintext.size() > 0){ // if the size is not empty, the key wasn't rejected, so we add it to the vector
				string str2(plaintext.begin(), plaintext.end());
				poss.push_back(str2);
			}
		}
	}
	return poss;

}

int main() {
	vector <string> DataArray = readfile("strings.txt"); // read in the strings
	vector <string> poss = keyatt(DataArray); // vector of possible strings

	for (int j = 0; j < DataArray.size(); j++){ // print all possibilities
		cout << DataArray[j] << endl;
	}
	cout << "done";
	//string plaintext = freqanal(poss); // perform freq.anal. to find most likely solution

	//cout << endl << "Frequency analysis results esitmate plaintext to be:" << endl << '"' << plaintext << '"';

	getchar();
	return 0;
}