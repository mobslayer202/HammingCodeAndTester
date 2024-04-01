class Hamming{
    public:
        static short encode (short message);
        static short decode (short encoded);

    private:
        static bool maskNParity(short mask, short data);
};