#include <string>
#include <iostream>
#include <fstream>
#include <ostream>
#include <bitset>
#include "HCTree.h"
#include "HCNode.h"


typedef unsigned char byte;
using namespace std;

int main(int argc, char** argv)
{
   ifstream inFile;
   ofstream outFile;
   vector<int> freqs(256, 0);
   HCTree codeTree;
   int Byte;

   //wrong number of inputs
   if(argc != 3) {
      return 1;
   }

   inFile.open(argv[1]);
   outFile.open(argv[2]);

   //bulid a vector with frequencies for each characters
   while(1) {
      Byte = (int)inFile.get();
      if (inFile.eof()) {
         break;
      }
      freqs[Byte]++;
   }
   inFile.close();

   //build HCT with the frequencies   
   codeTree.build(freqs);
   BitOutputStream out(outFile);

   //wirte a Head file in the compressed file
   codeTree.writeHeader(out);

   //get the total number of characters in infile
   int totalB = 0;
   int check =0;
   for(int j= 0; j < freqs.size(); j++) {
      totalB = totalB + freqs[j];
      if(freqs[j] !=0) {
         check++;
      }
   }
   bitset<32> TB(totalB);
   for(int k =31; k>=0; k--) {
      out.writeBit(TB[k]);
   }

   if(check ==1) {
      out.writeBit((int)1);
   }

   //start encoding the characters in the infile
   inFile.open(argv[1]);
   while(1) {
     byte Byte = inFile.get();
     if (inFile.eof()) {
        break;
     }
     codeTree.encode(Byte, out);
   }

   codeTree.encode('a', out);
   codeTree.encode('a', out);
   codeTree.encode('a', out);
   inFile.close();
   outFile.close();
   return 0;
}
                          


