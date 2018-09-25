#include <string>
#include <bitset>
#include <iostream>
#include <fstream>
#include <ostream>
#include "HCTree.h"
#include "HCNode.h"
#define ASCII 256

typedef unsigned char byte;
using namespace std;

int main(int argc, char** argv)
{


   ifstream inFile;
   ofstream outFile;
   vector<int> freqs(ASCII, 0);
   HCTree codeTree;

   if(argc != 3) {
      return 1;
   }
   inFile.open(argv[1], ios::binary);
   outFile.open(argv[2], ios::binary);
   inFile.seekg(0, ios::end);
   int fsize = inFile.tellg();

   inFile.close();
   inFile.open(argv[1], ios::binary);
   BitInputStream in(inFile);

   //for only one character
   if(fsize <= 10) {
      bitset<8> getC;
      for(int n=7; n>=0; n--) {
        getC[n] = in.readBit();
      }
      byte C = getC.to_ulong();
      bitset<32> TB2;
      for (int m= 31; m >= 0; m--) {
         TB2[m] = in.readBit();
      } 
      int numByte = TB2.to_ulong();
      cout <<numByte <<endl;
      for(int k= 0; k<numByte; k++) {
         outFile<<(C);
      }
      return 0;
   }
   /* this is for check point
   //read the file header 
   int numBye = 0;  
   for(int i = 0; i<freqs.size(); i++) {
     string count;
     getline(inFile, count); 
     int count2 = stoi(count);
     freqs[i] = count2;
        numByte += count2;
   }
   */

   //build Huffman coding tree 

   codeTree.readHeader(in);

   bitset<32> TB2;
   for (int j= 31; j >= 0; j--) {
      TB2[j] = in.readBit();
   }
   int numByte = TB2.to_ulong();

   for(int j=0; j<numByte; j++) {
      byte next = codeTree.decode(in);
      outFile.put(next);
   }

   outFile.close();
   inFile.close();

   return 0;
}
                                              
