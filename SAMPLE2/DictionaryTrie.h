/**
 *  CSE 100 PA3 C++ Autocomplete
 *  Authors: Jor-el Briones, Christine Alvarado, Carlos Mattoso
 */

#ifndef DICTIONARY_TRIE_H
#define DICTIONARY_TRIE_H

#include <vector>
#include <string>
#include <map>
#include <stack>
/**
 *  The class for a dictionary ADT, implemented as a trie
 *  You may implement this class as either a mulit-way trie
 *  or a ternary search trie, but you must use one or the other.
 *
 */


class TSTNode
{
public:
  TSTNode* left;
  TSTNode* equal;
  TSTNode* right;
  TSTNode* parent;
  char character;
  unsigned int frequency; 
  bool checkEnd; 
  int HD; 
  TSTNode();
  TSTNode(char s);
  std::string W;
};



class DictionaryTrie
{
public:

  /* Create a new Dictionary that uses a Trie back end */
  DictionaryTrie();

  /* Insert a word with its frequency into the dictionary.
   * Return true if the word was inserted, and false if it
   * was not (i.e. it was already in the dictionary or it was
   * invalid (empty string) */
  bool insert(std::string word, unsigned int freq);
 // int Hinsert(TSTNode* node, const char* Ch, unsigned int f);
  /* Return true if word is in the dictionary, and false otherwise */
  bool find(std::string word) const;
 // bool Hfind(TSTNode* node, const char* Ch2) const;

  /* Return up to num_completions of the most frequent completions
   * of the prefix, such that the completions are words in the dictionary.
   * These completions should be listed from most frequent to least.
   * If there are fewer than num_completions legal completions, this
   * function returns a vector with as many completions as possible.
   * If no completions exist, then the function returns a vector of size 0.
   * The prefix itself might be included in the returned words if the prefix
   * is a word (and is among the num_completions most frequent completions
   * of the prefix)
   */
  std::vector<std::string>
  predictCompletions(std::string prefix, unsigned int num_completions);
 // void HpredictCompletions(TSTNode* node, int index, std::map<unsigned int, TSTNode*> words, std::string word);
  /* Return the most similar word of equal length to the query, based
   * on their Hamming distance. 
   * In case of ties, return the word with the highest frequency (you may
   * assume there will always be one should a tie happen.)
   * In case there isn't any word of equal length to the query in the
   * trie, return an empty string.
   */
  std::string
  checkSpelling(std::string query);
 // void HcheckSpelling(TSTNode* node, TSTNode* target, int index, std::string query, std::string word);

  /* Destructor */
  ~DictionaryTrie();

  

private:
  // Add your own data members and methods here 
  TSTNode* root = NULL; 
 
  //std::map<unsigned int, TSTNode*> temp;
  //std::string getW;
  static void deleteAll(TSTNode* n);
  static void HpredictCompletions(TSTNode* node, std::multimap<unsigned int,   TSTNode*>* words, std::string word);
  static void HcheckSpelling(TSTNode* node, std::stack<TSTNode*>* mystack, std::string  query, std::string word);


};

#endif // DICTIONARY_TRIE_H
