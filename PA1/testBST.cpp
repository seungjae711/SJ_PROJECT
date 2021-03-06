#include "BSTInt.h"
#include "BST.hpp"
#include "BSTIterator.hpp"

#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
#include <set>

using namespace std;

/**
 * A test driver for the BST int class and class template.
 * PA1 CSE 100 2016
 * Author: Christine Alvarado and Sungjae Choi
 * TODO: Add more tests
 */
int main() {

    /* Create an STL vector of some ints */
    /*test*/
    vector<int> v;
    for(int i = 0; i <=100; i++) {
	v.push_back(i);	
    }
     
//v.push_back(60);
// v.push_back(70);
// v.push_back(80);
// v.push_back(90);
    /* Create an instance of BST holding int */
    BSTInt b;

    // Could use: for(auto item : v) { instead of the line below
    for(int item : v) {
        bool pr = b.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item 
                 << endl;
            return -1;
        }
    }
    
    /* Test size. */
    cout << "Size is: " << b.size() << endl;
    if(b.size() != v.size()) {
        cout << "... which is incorrect." << endl;
        return -1;
    }

    /* Test find return value. */
    // Test the items that are already in the tree
    for(int item : v) {
        if(!b.find(item)) {
            cout << "Incorrect return value when finding " << item << endl;
            return -1;
        }
    }
    
	
   
    /* UNCOMMENT THE LINES BELOW TO TEST THE TEMPLATE-BASED ITERATOR */

    
    // Test the template version of the BST  with ints 
    BST<int> btemp;
    for (int item : v) {
        // The auto type here is the pair of BSTIterator<int>, bool
        cout << "Inserting " << item << " into the int template-based BST...";
        auto p = btemp.insert(item);
        if (*(p.first) != item) {
            cout << "Wrong iterator returned.  "
                 << "Expected " << item << " but got " << *(p.first) << endl;
            return -1;
        }
        if (!p.second) {
            cout << "Wrong boolean returned.  Expected true but got " 
                 << p.second << endl;
            return -1;
        }
        cout << "success!" << endl;
              
    }

    // Now test finding the elements we just put in
    for (int item: v) {
        cout << "Finding " << item << "...." << endl;
        BSTIterator<int> foundIt = btemp.find(item);
        if (*(foundIt) != item) {
            cout << "incorrect value returned.  Expected iterator pointing to "
                 << item << " but found iterator pointing to " << *(foundIt) 
                 << endl;
            return -1;
        }
        cout << "success!" << endl;
    }



    // Test the iterator: The iterator should give an in-order traversal
  
    // Sort the vector, to compare with inorder iteration on the BST
    sort(v.begin(),v.end());

    cout << "traversal using iterator..." << endl;
    auto vit = v.begin();
    auto ven = v.end();

    // This is equivalent to BSTIterator<int> en = btemp.end();
    auto en = btemp.end();

    //This is equivalent to BST<int>::iterator it = btemp.begin();
    auto it = btemp.begin();
    for(; vit != ven; ++vit) {
        if(! (it != en) ) {
            cout << *it << "," << *vit 
                 << ": Early termination of BST iteration." << endl;
            return -1;

        }
        cout << *it << endl;
        if(*it != *vit) {
            cout << *it << "," << *vit 
                 << ": Incorrect inorder iteration of BST." << endl;
            return -1;
        }
        ++it;
    }

    cout << "success!" << endl;

    

    // ADD MORE TESTS HERE.  You might also want to change what is input
    // into the vector v
    
      
   
    /** check if insert function return false if there is already 
      * element which is equal to an item we want to insert in
      */ 
    if(b.insert(3)) {
        cout << "wrong! because the item is already in it" <<endl;
    	return -1;
    }  
    
    /** builds tree c which has just one element
      */
    BSTInt c;
    vector<int> v2;
    v2.push_back(2);
    for(int item : v2) {
        bool pr = c.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item
                 << endl;
            return -1;
        }
    }
        
    /** builds an empty tree d
      */
    BSTInt d;
    vector<int> v3;
    for(int item : v3) {
        bool pr = d.insert(item);
        if(! pr ) {
            cout << "Incorrect bool return value when inserting " << item
                 << endl;
            return -1;
        }
    }
   
   /** test deleteAll function
     */ 
 
   /** check if the find function properly
    */
    if(!b.find(3)) {
	cout << "the item should be in BST" <<endl;	
        return -1;    
    }
    if(b.find(-1)) {
     	cout << "the item should not be found" <<endl;
        return -1;               
    }
    if(d.find(7)) {
        cout <<"this is an empty BST" <<endl;
        return -1;
    } 
     
   /** check if empty function works properly
    */ 
   if(b.empty()) {
        cout <<"this is not an empty BST!" <<endl;
        return -1;
   }  
   if(!d.empty()) {
	cout <<"this is an empty BST!" <<endl;
        return -1;
    } 
    
    /** check if height function works properly 
     */
    //case that hegiht is 4 
    cout << "b tree hegiht: "<< b.height() <<endl;
    //case that hegiht is 0(only root)
    cout << "c tree hegiht: "<< c.height() <<endl;
    //case that height is -1(empty tree)
    cout << "d tree hegiht: "<< d.height() <<endl;
    
    cout << "All tests passed!" << endl;
    return 0;
}



