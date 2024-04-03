//#include <iostream>
//#include <bitset>
//#include <fstream>

//#include "Hamming.hpp"
//#include "Combination.hpp"
#include "HammingTester.hpp"

int main() {

    /*std::ofstream output;
    output.open("output.txt");

    Combination combo(7);

    int counter = 0;
    unsigned short last = 0;
    while(true){
        unsigned short c = combo.getCombo();
        std::bitset<16> cb(c);
        std::cout << cb << "\n";
        output << cb << "\n";
        ++combo;

        /*if (counter == 750){
            combo.reset(2);
        }

        std::cout << c << "\n" << last << "\n";
        output << c << " <? " << last << "\n";
        if (c < last){
            break;
        }

        last = c;
        counter++;
    }

    std::cout << counter << "\n";*/

    HammingTester::test(1);

    return 0;
}

