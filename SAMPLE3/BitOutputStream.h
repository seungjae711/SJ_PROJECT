#ifndef BITOUTPUTSTREAM_HPP
#define BITOUTPUTSTREAM_HPP

#include <iostream>
#include <bitset>


using namespace std;


class BitOutputStream{
private:
        char bits;
        int nBits;
        ostream & out;
public:
        BitOutputStream(ostream & o) : out(o), bits(0), nBits(7) {;}

        void writeBit(int bit);
        void getNewB();
};

#endif

