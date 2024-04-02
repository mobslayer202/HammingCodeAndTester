#include <iostream>
#include <bitset>

//#include "Hamming.hpp"
#include "Combination.hpp"

int main() {

    Combination combo(7);

    for (short i=0; i<1000; i++){
        unsigned short c = combo.getCombo();
        std::bitset<16> cb(c);
        std::cout << cb << "\n";
        ++combo;
    }

    return 0;
}

