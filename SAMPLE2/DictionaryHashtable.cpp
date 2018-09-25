#include "util.h"
#include "DictionaryHashtable.h"
#include <string>
#include <unordered_set>

/* Create a new Dictionary that uses a Hashset back end */
DictionaryHashtable::DictionaryHashtable(){
  HTS = new std::unordered_set<std::string>();
}

/* Insert a word into the dictionary. */
bool DictionaryHashtable::insert(std::string word)
{
   std::pair<std::unordered_set<std::string>::iterator,bool> ret;
   std::unordered_set<std::string>::iterator it;
   ret = HTS->insert(word);
   return ret.second;
}

/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryHashtable::find(std::string word) const
{
  std::unordered_set<std::string>::const_iterator found = HTS->find(word); 
  if( found != HTS->end()) { 
    return true;
  }
  return false;
}

/* Destructor */
DictionaryHashtable::~DictionaryHashtable(){
  delete HTS;
}
