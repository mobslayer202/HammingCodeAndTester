#include "Combination.hpp"

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

// Increments to the next combo bigger than current one
void Combination::operator++(){
    // Get vector | each value has only one of the 1s in the combo
    std::vector<short> all1s = find1s(); // move elsewhere?, will disappear if use iterator only?
    short newCombo = 0;

    // Go through each of the slices of combo
    for (short i=0; i<all1s.size(); i++){
        // If the current 1 bit is at the end or if its not going to overlap the 1 bit ahead of it
        // Move it left
        // Also move everything behind it back to smallest position.
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

    // Add the changed slices back together to form the new combo
    for (auto bit:all1s){
        newCombo += bit;
    }

    this->combo = newCombo;
}

// Return vector | : For each set bit of combo, returns a short with only that bit set. LSB->MSB
std::vector<short> Combination::find1s(){
    std::vector<short> all1s;
    // Calculate number of bits
    short numBits = sizeof(this->combo)*8;
    
    // Search whole bit string, if you see a 1: 
    //      make a bit string with only that 1 and add to vector
    short finder = 0b0000'0000'0000'0001; // Need to change if variable combo size
    for (short i=0; i<numBits; i++){
        if ((finder & this->combo) != 0){ // PARENTHESIS AROUND (finder & this->combo) FIXED BUG!!!
            all1s.push_back(finder);
        }
        finder <<= 1;
    }
    return all1s;
}

