#include <bitset>
#include <iostream>
#include <fstream>

#include "HammingTester.hpp"
#include "Hamming.hpp"
#include "Combination.hpp"

void HammingTester::test(short numToFlip){
    std::ofstream all;
    all.open("testResult.txt");
    std::ofstream passed;
    passed.open("testPassed.txt");
    std::ofstream failed;
    failed.open("testFailed.txt");

    short data = 0;

    while (true){

        short encoded = Hamming::encode(data);

        Combination error(numToFlip);
        unsigned short lastCombo = 0;
        while (true){
            unsigned short currCombo = error.getCombo();
            short adjusted = encoded ^ currCombo;
            short decoded = Hamming::decode(adjusted);

            std::bitset<16> message(data);
            std::bitset<16> adj(adjusted);
            std::bitset<16> enc(encoded);
            std::bitset<16> dec(decoded);

            all << "Message: " << message << "\n";
            all << "Encoded: " << enc << "\n";
            all << "Adjustd: " << adj << "\n";
            all << "Decoded: " << dec << "\n\n";

            short mask = 0b0011'1111'1111'1111;
            if ((decoded & mask) != (data & mask)){ // << 2 DIDNT WORK, showed 65536 ON A SHORT!!!
                failed << (decoded) << " " << (data) << "\n";
                failed << (decoded & mask) << " " << (data & mask) << "\n";
                failed << "Message: " << message << "\n";
                failed << "Encoded: " << enc << "\n";
                failed << "Adjustd: " << adj << "\n";
                failed << "Decoded: " << dec << "\n\n";
            }
            else{
                passed << "Message: " << message << "\n";
                passed << "Encoded: " << enc << "\n";
                passed << "Adjustd: " << adj << "\n";
                passed << "Decoded: " << dec << "\n\n";
            }

            if (currCombo < lastCombo){
                break;
            }

            lastCombo = error.getCombo();
            ++error;
        }

        data += 1;
        if (data == 0b0000'1000'0000'0000){
            break;
        }
    }

    all.close();
    passed.close();
    failed.close();
}
