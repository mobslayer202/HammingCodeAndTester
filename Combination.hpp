#include "vector"

class Combination{
    public:
        Combination(short num1s);
        void reset(short num1s);
        void operator++(); // Prefix only

        short getCombo(){
            return combo;
        }

    private:
        short combo;
        std::vector<short> find1s();
};