#include "util.h"
#include "DictionaryBST.h"
#include <set>
#include <string>


/* Create a new Dictionary that uses a BST back end */
DictionaryBST::DictionaryBST(){
  DBS = new std::set<std::string>();
}

/* Insert a word into the dictionary. */
bool DictionaryBST::insert(std::string word)
{ 
  std::pair<std::set<std::string>::iterator,bool> ret;
  ret = DBS->insert(word);
  //ret = (*DBS).insert(word);
  return ret.second;
}
 
/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryBST::find(std::string word) const
{
  std::set<std::string>::iterator it = DBS->find(word);
  if (it != DBS->end()) {
    return true;
  } 
  return false;
}

/* Destructor */
DictionaryBST::~DictionaryBST(){
  delete DBS;
}
