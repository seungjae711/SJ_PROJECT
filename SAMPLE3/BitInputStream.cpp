#include "BitInputStream.h"
#include <iostream>
#include <bitset>

using namespace std;


int BitInputStream::readBit() {
   if(nBits == -1) {
      getNewBits();
      if (in.eof()) {
          return 1;
      }
   }
   if(((bits >>nBits) & 0x1) == 1) {
      nBits--;
      return 1;
   }else if(((bits>> nBits) & 0x1) == 0) {
      nBits--;
      return 0;
   }
   return 1;
}


void BitInputStream::getNewBits() {
        bits = in.get();
        nBits = 7;
}

