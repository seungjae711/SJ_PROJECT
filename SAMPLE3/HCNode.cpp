
#include "HCNode.h"
#include <iostream>


/** Less-than comparison, so HCNodes will work in std::priority_queue
 *  We want small counts to have high priority.
 *  And we want to break ties deterministically.
 */
bool HCNode::operator<(const HCNode& other) 
{
   if(count != other.count) {
      return count > other.count;
   //if counter are tie, breaking the tie by comparing symbols
   }else  { 
      return symbol < other.symbol;     
   }
}


