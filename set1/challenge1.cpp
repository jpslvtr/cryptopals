#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Converts a single hex character to integer (0-15)
int hexCharToValue(char hex) {
    if ('0' <= hex && hex <= '9') {
        return hex - '0';
    }
    if ('a' <= hex && hex <= 'f') {
        return hex - 'a' + 10;
    }
    if ('A' <= hex && hex <= 'F') {
        return hex - 'A' + 10;
    }

    cout << "Error: Invalid hex character '" << hex << endl;
}

// Convert a hex string to bytes
vector<int> hexToBytes(const string &hex) {
    vector<int> bytes;

    if (hex.size() % 2 != 0) {
        cout << "Error: Hex string length must be even." << endl;
        exit(1);
    }

    for (int i = 0; i < hex.size(); i += 2) {
        int byte = (hexCharToValue(hex[i]) << 4) | hexCharToValue(hex[i + 1]);
        bytes.push_back(byte);
    }

    return bytes;
}

// Convert bytes to base64
string bytesToBase64(const vector<int> &bytes) {
    const string base64_chars =
        "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
        "abcdefghijklmnopqrstuvwxyz"
        "0123456789+/";

    string base64;
    int val = 0;
    int valb = -6;

    for (int byte : bytes) {
        val = (val << 8) | (byte & 0xFF);
        valb += 8;
        while (valb >= 0) {
            base64.push_back(base64_chars[(val >> valb) & 0x3F]);
            valb -= 6;
        }
    }

    if (valb > -6) {
        base64.push_back(base64_chars[((val << 8) >> (valb + 8)) & 0x3F]);
    }

    while (base64.size() % 4) {
        base64.push_back('=');
    }

    return base64;
}

int main() {
    string hex_input = "49276d206b696c6c696e6720796f757220627261696e206c696b65206120706f69736f6e6f7573206d757368726f6f6d";

    vector<int> bytes = hexToBytes(hex_input);
    string base64_output = bytesToBase64(bytes);

    cout << "Base64 Output: " << base64_output << endl;

    return 0;
}
