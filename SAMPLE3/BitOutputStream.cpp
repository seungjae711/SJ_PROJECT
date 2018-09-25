
#include "BitOutputStream.h"
#include <iostream>
#include <bitset>

void BitOutputStream::getNewB(){
        out.put(bits);
        out.flush();
        bits = 0;
        nBits = 7;
}

void BitOutputStream::writeBit(int bit) {

        if( nBits == -1 ){
            getNewB();
        }
        unsigned char mask = bit << nBits;
        bits = bits | mask;
        nBits--;

}
