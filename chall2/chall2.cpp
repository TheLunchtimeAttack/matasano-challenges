#include <iostream>
#include <sstream>
#include <string>
#include <assert.h> 

using namespace std;

string hex_to_byte_xor_to_hex(string hex, string hex1) {
    int size = hex.length();
    int size2 = hex1.length();
    string ret_hex = "";
    if (size == size2){

        for (int i=0; i<size; i=i+2) {
            unsigned short byte = 0;
            unsigned short byte2 = 0;
            string hex2 = hex.substr(i,2);
            string hex3 = hex1.substr(i,2);
            istringstream iss2(hex2);
            istringstream iss3(hex3);
            iss2 >> std::hex >> byte;
            iss3 >> std::hex >> byte2;
            unsigned short xor_byte = byte ^ byte2;
    
            std::stringstream stream;
            stream << std::hex << xor_byte;
            string res(stream.str());
            ret_hex += res;
        }
    }
    else {
        return "0";
    }
    return ret_hex;
}

int main(int argc, char** argv) {
    string hex = "1c0111001f010100061a024b53535009181c";
    string hex1 = "686974207468652062756c6c277320657965";
    string ret_hex = hex_to_byte_xor_to_hex(hex,hex1);

    if (ret_hex != "0"){
        
        string true_res = "746865206b696420646f6e277420706c6179";
        bool correct = ret_hex == true_res;
        if (correct == true){
            cout << "Correct!" << endl;
        }
        else {
            cout << "Wrong..." << endl;
        }
    }
    else {
        cout << "The lengths of the hex strings are not equal." << endl << "Terminating..." << endl;
    }
}