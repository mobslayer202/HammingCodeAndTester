#include <fstream>

class HammingTester{
    // testOnce(data, numToFlip)

    // testfor(startData, endData)

    public:
        static void test(short numToFlip);
    
    private:
        static void log(std::ofstream& output, short data, short encoded, short adjusted, short decoded); // output red squiggly if not passed by reference
};