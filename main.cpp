#include <iostream>
#include <bitset>

#include "Hamming.hpp"

int main() {

    // Input data
    short data = 0b00000'010'1010'1010;

    short encoded = Hamming::encode(data);
    short error = 0b0000'0000'0000'0001;
    short adjusted = encoded ^ error;
    short decoded = Hamming::decode(adjusted);


    std::bitset<16> message(data);
    std::bitset<16> adj(adjusted);
    std::bitset<16> enc(encoded);
    std::bitset<16> dec(decoded);
    //std::cout << message << " Size: " << sizeof(data) << "\n";
    //std::cout << "Parity: " << message << " Size: " << sizeof(message) << "\n";
    std::cout << "Message: " << message << "\n";
    std::cout << "Encoded: " << enc << "\n";
    std::cout << "Adjustd: " << adj << "\n";
    std::cout << "Decoded: " << dec << "\n";
    
    return 0;
}

void hammingTester(int numToFlip){
    
}