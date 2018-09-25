#include "HCTree.h"
#include <bitset>
#include <queue>
#include <vector>
#include <fstream>
#include "HCNode.h"
#include "BitInputStream.h"
#include "BitOutputStream.h"
#define ASCII 256

using namespace std;
typedef unsigned char byte;


/** Use the Huffman algorithm to build a Huffman coding trie.
 *  PRECONDITION: freqs is a vector of ints, such that freqs[i] is 
 *  the frequency of occurrence of byte i in the message.
 *  POSTCONDITION:  root points to the root of the trie,
 *  and leaves[i] points to the leaf node containing byte i.
 */

void HCTree::build(const vector<int>& freqs)
{
   int check = 0;
   int check2 = 0;
   int check3 = 0;
   priority_queue<HCNode*, vector<HCNode*>, HCNodePtrComp> forest;
   for(int i = 0; i < freqs.size(); i++) {
     HCNode* newleaf = new HCNode(freqs[i], i, 0, 0, 0);
     leaves[i] = newleaf;
     if(newleaf->count !=0) {
       check++;
       check2 = newleaf->count;
       check3 = i;
     }
     //inserts nodes into the forest    
     forest.push(leaves[i]);
   }

   //build a tree with only one node for one character 
   if(check == 1) {
      root = new HCNode(check2, check3, 0, 0, 0);
      return;
   }

   //pop nodes by two nodes untill there is only one node in the forest
   int newCount;
   HCNode* tree1 = 0;
   HCNode* tree2 = 0;
   while(forest.size() > 1) {
      tree1 = forest.top();
      //cout << tree1->count <<endl;
      forest.pop();
      tree2 = forest.top();
      //cout << tree2->count <<endl;
      forest.pop();

      //combine two nodes
      newCount = tree1->count + tree2->count;
      HCNode* newParent = new HCNode(newCount, tree1->symbol, tree1, tree2, 0);
      tree1->p = newParent;
      tree2->p = newParent;

      forest.push(newParent);
   }

   //declare root with the last node in the forest  
   root = forest.top();
   //cout << root->count <<endl;
}

/** Write to the given BitOutputStream
 *  the sequence of bits coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
void HCTree::encode(byte symbol, BitOutputStream& out) const
{
   if(root->c1 ==0) {
        return;
   }	
   vector<int> code;
   HCNode* curr = leaves[symbol];

   while( curr->p !=0 ){
      if (curr->p->c0 == curr) {
         code.push_back(0);
      }else {
         code.push_back(1);
      }
      curr = curr->p;

   }
   while (!code.empty()) {
      out.writeBit(code.back());
      code.pop_back();
   }
}


/** Write to the given ofstream
 *  the sequence of bits (as ASCII) coding the given symbol.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT 
 *  BE USED IN THE FINAL SUBMISSION.
 */
void HCTree::encode(byte symbol, ofstream& out) const
{
   HCNode* curr = leaves[symbol];
   vector<char> code;

   //encode the symbol by going up from leaf to root
   while( curr->p != 0){
      if (curr->p->c0 == curr) {
         code.push_back('0');
      }else if(curr->p->c1 == curr){
         code.push_back('1');
      }
      curr = curr->p;
   }

   //insert code in outfile
   while (!code.empty()) {
      out << code.back();
      code.pop_back();
   }
}

/** Return symbol coded in the next sequence of bits from the stream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 */
int HCTree::decode(BitInputStream& in) const
{
   HCNode* curr = root;
   char bit;
   while( curr->c0 !=0 && curr->c1 != 0) {
      // cout << in.readBit() <<endl;
      bit = in.readBit();
      //cout << bit << endl;
      if (bit == 0) {
         curr = curr->c0;
      }else if(bit == 1) {
         curr = curr->c1;
      }
   }
   return curr->symbol;

}


/** Return the symbol coded in the next sequence of bits (represented as 
 *  ASCII text) from the ifstream.
 *  PRECONDITION: build() has been called, to create the coding
 *  tree, and initialize root pointer and leaves vector.
 *  THIS METHOD IS USEFUL FOR THE CHECKPOINT BUT SHOULD NOT BE USED
 *  IN THE FINAL SUBMISSION.
 */


int HCTree::decode(ifstream& in) const 
{
   HCNode* curr = root;
   char bit;
   while( curr->c0 !=0 && curr->c1 != 0) {
      bit = in.get();
      if (bit == '0') {
         curr = curr->c0;
      }else if(bit == '1') {
         curr = curr->c1;
      }
   }
   return curr->symbol;
}


void HCTree::writeHeader(BitOutputStream & out){
   if(root->c1 == 0) {
        bitset<8> C(root->symbol);
        for(int j =7; j>= 0; j--) {
           out.writeBit((int)C[j]);
        }
        return;
   }
   Helper(root, out);
}
	

void HCTree::Helper(HCNode* curr, BitOutputStream & outS) {
   if(curr == 0) {
      return;
   }
   //label internal node with 0
   if(curr->c0 != 0 || curr->c1 != 0) {
      outS.writeBit(0);
   }

   //label external node with 1
   else {
      outS.writeBit(1);
      bitset<8> bits(curr->symbol);
      for(int i = 7; i >= 0; i--){
         outS.writeBit((int)bits[i]);
      }
   }
   Helper(curr->c0, outS);
   Helper(curr->c1, outS);
}


void HCTree::readHeader(BitInputStream& in) {
   root = new HCNode(0, 0, 0, 0, 0);
   HCNode* curr = root;
   int bit = in.readBit();
   int leavesCount= 0;

   while(leavesCount < ASCII) {
      bit = in.readBit();

      //inserts external nodes(leaves) with characters
      if(bit == 1) {
         bitset<8> symbol;
         for(int i =7; i>=0; i--) {
            symbol[i] = in.readBit();
         }
         byte SB = symbol.to_ulong();
         if(curr->c0 ==0) {
            curr->c0 = new HCNode(0, SB, 0, 0, curr);
         }else if(curr->c1 == 0) {
            curr->c1 = new HCNode(0, SB, 0, 0, curr);

            //find the node which has c0 but c1
            while( curr->c1 != 0 && curr->c0 != 0 && curr->p !=0) {
               curr = curr->p;
            }
         }
         //increases the number of leaves inserted
         leavesCount++;

      //inserts internal nodes
      }else if(bit == 0) {
         if(curr->c0 == 0) {
            curr->c0 = new HCNode(0, 0, 0, 0, curr);
            curr = curr->c0;
         }else if(curr->c1 == 0) {
            curr->c1 = new HCNode(0, 0, 0, 0, curr);
            curr = curr->c1;
         }
      }

   }
}


HCTree::~HCTree() {
   leaves.clear();
   if(root) {
      deleteAll(root);
   }

}
void HCTree::deleteAll(HCNode* node) {
   if(node) {
      if(node->c0) {
         deleteAll(node->c0);
      }
      if(node->c1) {
         deleteAll(node->c1);
      }
      delete node;
   }
}
