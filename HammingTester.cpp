#include <bitset>
#include <iostream>
#include <fstream>

#include "HammingTester.hpp"
#include "Hamming.hpp"
#include "Combination.hpp"

void HammingTester::test(short numToFlip){
    // Open File streams
    std::ofstream all("testResult.txt");
    std::ofstream failed("testFailed.txt");
    std::ofstream passed("testPassed.txt");

    // Initialize message to be encoded
    short data = 0;

    while (true){

        // Encode message
        short encoded = Hamming::encode(data);

        // Initialize bit flipper to introduce error
        Combination error(numToFlip);
        unsigned short lastCombo = 0; 
        while (true){
            unsigned short currCombo = error.getCombo();
            // Introduce error
            short adjusted = encoded ^ currCombo;

            // Decode
            short decoded = Hamming::decode(adjusted);
            
            // Log results: all results, failed, passed
            log(all, data, encoded, adjusted, decoded);
            short mask = 0b0011'1111'1111'1111;
            if ((decoded & mask) != (data & mask)){ // << 2 DIDNT WORK, showed 65536 ON A SHORT!!!
                log(failed, data, encoded, adjusted, decoded);
            }
            else{
                log(passed, data, encoded, adjusted, decoded);
            }

            // currCombo < lastCombo when one of the bits fall off the left side
            if (currCombo < lastCombo){
                break;
            }

            lastCombo = error.getCombo();

            // Increment to next combo
            ++error;
        }

        // Increment to next data
        data += 1;
        
        // This hamming encoding only supports 11 bit messages
        if (data == 0b0000'1000'0000'0000){
            break;
        }
    }

    all.close();
    failed.close();
    passed.close();
}

void HammingTester::log(std::ofstream& output, short data, short encoded, short adjusted, short decoded){

    std::bitset<16> message(data);
    std::bitset<16> adj(adjusted);
    std::bitset<16> enc(encoded);
    std::bitset<16> dec(decoded);

    output << "Message: " << message << "\n"; // output red squiggly if const reference instead of reference
    output << "Encoded: " << enc << "\n";
    output << "Adjustd: " << adj << "\n";
    output << "Decoded: " << dec << "\n\n";
}
