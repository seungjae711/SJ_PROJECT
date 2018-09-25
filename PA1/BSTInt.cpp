
#include "BSTInt.h"

/* Function definitions for a int-based BST class */


/** Default destructor.
    Delete every node in this BST.
*/
BSTInt::~BSTInt() {
  deleteAll(root);
}

/** Given a reference to a Data item, insert a copy of it in this BST.
 *  Return  true if the item was added to this BST
 *  as a result of this call to insert,
 *  false if an item equal to this one was already in this BST.
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=)  For the reasoning
 *  behind this, see the assignment writeup.
 */

bool BSTInt::insert(int item)
{
  //If there is no root, inserts the time as a root
  BSTNodeInt* curr = root;
  BSTNodeInt* newNode = new BSTNodeInt(item);  
  if (!root) {
    root = newNode;
    ++isize;
    return true;
  } else {
    while (curr) {
      if (item < curr->data) {        
	//if current node's left child is empty, insert the time there
	if(!curr->left) {
	  curr->left = newNode;
	  newNode->parent = curr;
          ++isize;
	  return true;
	}else { 
          //otherwise, current node is changed into its left child
	  curr = curr->left;		  	
        }

      }else if (curr->data < item) {
        //if current node's right child is empty, insert the item there 
	if(!curr->right) {    
	  curr->right = newNode;
	  newNode->parent = curr;
  	  ++isize;
	  return true;	
	}else {
	  //otherwise, current node is changed into its right child	
	  curr = curr->right;
        }
      }else {
        return false;   //if there is a node euqual to item
      }
    } 
  }
  return true;
}


/** Find a Data item in the BST.
 *  Return true if the item is in the BST or false otherwise
 *  Note: This function should use only the '<' operator when comparing
 *  Data items. (should not use ==, >, <=, >=).  For the reasoning
 *  behind this, see the assignment writeup.
 */
bool BSTInt::find(int item) const
{
  if(!root) {
    return false;
  }
  BSTNodeInt* curr = root;
  while (curr) {
    if (curr->data < item) {
      curr = curr->right;
    }
    else if (item < curr->data) {
      curr = curr->left;
    }
    else {
      return true;
    }
  }
  return false;
}

  
/** Return the number of items currently in the BST.
 */
unsigned int BSTInt::size() const 
{
  return isize;
}

  
/** Return the height of the BST.
    Height of tree with just root node is 0
    height of an empty tree is -1
 */
int BSTInt::height() const
{
  if(!root) {
    return -1;  
  }else { 
    return getHeight(root);           	
  }
}

int BSTInt::getHeight(BSTNodeInt* node) const{
  if (!node) {
    return -1;
  }else {
    int left = getHeight(node->left);
    int right = getHeight(node->right);
    if (left > right) {
      return 1 + left;
    }else {
      return 1 + right;
    }
  }
} 



/** Return true if the BST is empty, else false. 
 */
bool BSTInt::empty() const 
{
  //if root is null, then it's empty
  if(!root) {
    return true;	
  }  
  //if root is not null, then it's not empty
  return false;
}


/** do a postorder traversal, deleting nodes
 * This is a helper for the destructor
 * This method is static because it acts on BSTNodeInts
 *   and not on the BSTInt object directly.
 */
void BSTInt::deleteAll(BSTNodeInt* n)
{
  if(n == 0) {
    return;	
  } 
  deleteAll(n->left);
  deleteAll(n->right);
  delete n;
}
