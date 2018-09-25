#include <stdio.h>
#include <string.h>


#include "util.h"
#include "SuffixArray.h"
#include <string>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <map>
/**
 *  The class for a suffix array, represented as an int array
 *  storing the indices of the sorted suffixes.
 */
SuffixArray::SuffixArray(std::string word) : 
  word(word),
  suffixIdxs(new int[word.length()+1])
{
  buildSuffixArray(word);
}

/*
 * Helper method that constructs the suffix array derived from `word`
 * preferably using an efficient algorithm, such as the DC3 algorithm
 * (if you want the 5 points for efficiency, of course.)
 */
void SuffixArray::buildSuffixArray(std::string word){
   
  //std::map<std::string, suffix> suffixes; 
  suffixes = new std::map<std::string, suffix>;
  word.push_back('$');
  int wordL = word.length();
  for(int i=0; i<wordL; i++) {
    suffix S;
    S.index = i;
    S.suffix = &word[i];
    suffixes->insert(std::pair<std::string, suffix>(S.suffix, S));   
  }
  
  int j=0;
  std::map<std::string, suffix>::iterator it;
  for(it=suffixes->begin(); it!=suffixes->end(); it++) {
    suffixIdxs[j++] = it->second.index;
  }
  /*
  for(int k=0; k<wordL; k++) {
    std::cout << suffixIdxs[k] << " ";
  }
  std::cout <<std::endl; 
  */
}

/* 
 * Return true if `pattern` exists in the word encoded by the suffix array,
 * false otherwise 
 */
bool SuffixArray::find(std::string pattern) const
{
  if(pattern.length() == 0) {
    return true;
  }
  
  pattern.push_back('$');
  int patternL = pattern.length();
  int wordL = word.length();

  
  int firstI = 0;
  int lastI = wordL;
  while(firstI <= lastI) {
    int midI = (firstI +lastI)/2;
    std::map<std::string, suffix>::iterator it = suffixes->begin();    
    for(int i=0; i<midI; i++) {
      it++;
    }
  
    int check = strncmp(pattern.c_str(), (it->first).c_str(), patternL);
    
    if(check == 0) {
      //std::cout << "found!" <<std::endl;
      return true;
    }else if( check < 0) {
      lastI = midI - 1;
    }else  {
      firstI = midI +1;
    }
  }
  //std::cout << "no found" << std::endl;
  return false;
}

/* Destructor */
SuffixArray::~SuffixArray(){
  delete [] this->suffixIdxs;
}
