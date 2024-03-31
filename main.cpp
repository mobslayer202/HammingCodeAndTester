#include <iostream>
#include <bitset>

int main() {

    unsigned short data = 0b10'1010'1010;

    // Rightmost is first
    unsigned short p8Mask = 0b00000'111'1111'0000;
    unsigned short p4Mask = 0b00000'111'1000'1110;
    unsigned short p2Mask = 0b00000'110'0110'1101;
    unsigned short p1Mask = 0b00000'101'0101'1011;
    data = __builtin_parity(data); // __builtin_popcount(x)
    std::bitset<16> message(data);
    //std::cout << message << " Size: " << sizeof(data) << "\n";
    std::cout << "Parity: " << data;
    
    return 0;
}