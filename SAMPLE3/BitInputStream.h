#ifndef BITINPUTSTREAM_HPP
#define BITINPUTSTREAM_HPP

#include <iostream>
#include <bitset>


class BitInputStream{
private:
        char bits;
        int nBits;
        std::istream & in;


public:
        BitInputStream(std::istream & s): in(s), bits(s.get()), nBits(7) {}
        int readBit();
        void getNewBits();
};

#endif
