#include "Hamming.hpp"

// don't put static?
short Hamming::encode(short message){
    // Calculate parities except p0
    // Rightmost is first
    bool p8 = maskNParity(0b00000'111'1111'0000, message);
    bool p4 = maskNParity(0b00000'111'1000'1110, message);
    bool p2 = maskNParity(0b00000'110'0110'1101, message);
    bool p1 = maskNParity(0b00000'101'0101'1011, message);

    // 0000 0000 b11,b10,b9,b8 b7,b6,b5,p8
    short encoded = message >> 4;
    encoded <<= 1;
    encoded += p8;


    // 0000 b11,b10,b9,b8 b7,b6,b5,p8 b4,b3,b2,p4
    encoded <<= 4;
    encoded += message & 0b0000'0000'0000'1110;
    encoded += p4;

    // 0 b11,b10,b9,b8 b7,b6,b5,p8 b4,b3,b2,p4 b1,p2,p1
    encoded <<= 1;
    encoded += message & 0b0000'0000'0000'0001;
    encoded <<= 1;
    encoded += p2;
    encoded <<= 1;
    encoded += p1;
    
    // calculate p0
    bool p0 = __builtin_parity(encoded);
    
    // b11,b10,b9,b8 b7,b6,b5,p8 b4,b3,b2,p4 b1,p2,p1,p0
    encoded <<= 1;
    encoded += p0;

    return encoded;
}

short Hamming::decode(short encoded){
    // Calculate given p0 ^ np0 : gp0 ^ np0 = rp0
    bool oddError = __builtin_parity(encoded);

    // Calculate gpx * npx
    bool rp8 = maskNParity(0b1111'1111'0000'0000, encoded);
    bool rp4 = maskNParity(0b1111'0000'1111'0000, encoded); 
    bool rp2 = maskNParity(0b1100'1100'1100'1100, encoded);
    bool rp1 = maskNParity(0b1010'1010'1010'1010, encoded);

    // Assemble error location finder
    char location = rp8;
    location <<= 1;
    location += rp4;
    location <<= 1;
    location += rp2;
    location <<= 1;
    location += rp1;

    // Initialize result
    short result = 0;


    // Handle 0, 1 or 2 bit error
    if (oddError){ // Assume 1 bit error and correct
        short flipper = 1;
        for (char i=0; i<location; i++){ // Location never 0 if Odd Num Errors
            flipper <<= 1;
        }

        encoded ^= flipper;
        result = 0b0100'0000'0000'0000;

    }
    else { 
        if (location) { // Nonzero - Assume 2 bit error, do nothing for 0 bit
            result = 0b1000'0000'0000'0000;
        }
    }

    // Assemble result
    short b11t5 = 0b1111'1110'0000'0000 & encoded;
    short b432 = 0b0000'0000'1110'0000 & encoded;
    short b1 = 0b0000'0000'0000'1000 & encoded;

    b11t5 >>= 5;
    b432 >>= 4;
    b1 >>= 3;

    result += b11t5 + b432 + b1;

    return result;
}

bool Hamming::maskNParity(short mask, short data){
    return __builtin_parity(mask & data);
}