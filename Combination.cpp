#include "Combination.hpp"

#include <iostream> // Can include twice?

Combination::Combination(short num1s){
    reset(num1s);
}

void Combination::reset(short num1s){
    this->combo = 1;
    for (short i=0; i<num1s; i++){
        this->combo *= 2;
    }
    this->combo -= 1;
}

void Combination::operator++(){
    std::vector<short> all1s = find1s(); // move elsewhere?, will disappear if use iterator only?
    short newCombo = 0;

    /*std::vector<short>::iterator all1sIt = all1s.begin();
    while (all1sIt != all1s.end()){
        if (*all1sIt << 1 != *std::next(all1sIt)){
            
        }
    }*/

    for (short i=0; i<all1s.size(); i++){
        if (i+1 == all1s.size() or all1s[i] << 1 != all1s[i+1]){
            all1s[i] <<= 1;

            short original = 0b0000'0000'0000'0001;
            for (short j=0; j<i; j++){
                all1s[j] = original;
                original <<= 1;
            }
            break;
        }

    }

    for (auto bit:all1s){
        //std::cout << bit << ",";
        newCombo += bit;
    }
    //std::cout << "\n";

    this->combo = newCombo;
}

// Return vector | : For each set bit of combo, returns a short with only that bit set. LSB->MSB
std::vector<short> Combination::find1s(){
    std::vector<short> all1s;
    short numBits = sizeof(this->combo)*8;
    short finder = 0b0000'0000'0000'0001; // Need to change if variable combo size
    for (short i=0; i<numBits; i++){
        if ((finder & this->combo) != 0){ // PARENTHESIS AROUND (finder & this->combo) FIXED BUG!!!
            all1s.push_back(finder);
        }
        finder <<= 1;
    }
    return all1s;
}

