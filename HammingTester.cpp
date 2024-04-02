#include <bitset>
#include <iostream>

#include "HammingTester.hpp"
#include "Hamming.hpp"

void HammingTester::test(short numToFlip){
    short data = 0;
    bool start = data;
    while (true){

        short encoded = Hamming::encode(data);
        short error = 0b0000'0000'0000'0001;
        short adjusted = encoded ^ error;
        short decoded = Hamming::decode(adjusted);

        std::bitset<16> message(data);
        std::bitset<16> adj(adjusted);
        std::bitset<16> enc(encoded);
        std::bitset<16> dec(decoded);
        std::cout << "Message: " << message << "\n";
        std::cout << "Encoded: " << enc << "\n";
        std::cout << "Adjustd: " << adj << "\n";
        std::cout << "Decoded: " << dec << "\n\n";
        if (data == start){
            break;
        }
    }
}
