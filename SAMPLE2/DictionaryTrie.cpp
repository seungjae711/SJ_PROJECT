#include "util.h"
#include "DictionaryTrie.h"
#include <string>
#include <vector>
#include <iostream>
#include <cctype>
#include <algorithm>
#include <queue>
#include <map>
#include <stack>
TSTNode::TSTNode(char s) {
  
  left= NULL; 
  equal= NULL;
  right = NULL;
  parent = NULL;
  W = "";
  character = s;
  frequency = 0;
  checkEnd =false;

}

TSTNode::TSTNode() {
  
  left= NULL;
  equal= NULL;
  right = NULL;
  parent = NULL;
  W = "";
  character =' ';
  frequency = 0;
  checkEnd =false;
}

/* Create a new Dictionary that uses a Trie back end */
DictionaryTrie::DictionaryTrie(){
  //root = new TSTNode();
}


/* Insert a word with its frequency into the dictionary.
 * Return true if the word was inserted, and false if it
 * was not (i.e. it was already in the dictionary or it was
 * invalid (empty string) */
bool DictionaryTrie::insert(std::string word, unsigned int freq)
{ 
   if(word.empty()) {
     return false;
   }
   for(unsigned int i=0; i<word.length(); i++) {
     char letter = word.at(i);
     if(!(('A' <= letter && letter <='Z')||('a' <=letter && letter <='z') || letter == ' ')) {
       return false;
     }
     if(!root) {
       root = new TSTNode(letter);
     }
     while(root->character != letter) {
       if(root->character < letter) {     
         if(!root->right) {
           root->right = new TSTNode(letter);
           root->right->parent = root;
           root = root->right;
           
         }else {
           root = root->right; 
         }
       }else if(letter < root->character) {
         if(!root->left) {
           root->left = new TSTNode(letter);
           root->left->parent = root;
           root = root->left;
         }else {
           root = root->left;
         } 
       }
      }
    if(i != word.length() -1) {
      if(!root->equal) {
        root->equal = new TSTNode(word.at(i+1));
        root->equal->parent = root;
        root = root->equal;
      }else {
        root = root->equal;
      }
    }
   }
   if(root->checkEnd) {
     if(root->frequency < freq) {
       root->frequency = freq; 
     }
     while(root->parent) {
       root = root->parent;
     }
     return false;
   }else {
     root->checkEnd = true;
     root->frequency = freq;
     while(root->parent) {
       root = root->parent;
     } 
     return true;
   }
}



/* Return true if word is in the dictionary, and false otherwise */
bool DictionaryTrie::find(std::string word) const
{
  TSTNode* curr = root;
  if(word.empty()) {
    return false;
  } 
  for(unsigned int i=0; i<word.length(); i++) { 
    char letter = word.at(i);
    if(!curr) {
      return false;
    }
    while(curr->character != letter) {
      if(curr->character < letter) {
        curr = curr->right;
        if(!curr) {
          return false;
        }
      }else if(letter < curr->character) {
        curr = curr->left;
        if(!curr) {
          return false;
        }
      }
    }
    if(i !=word.length()-1) {
      curr = curr->equal;    
    }
  }
  if(curr->frequency != 0) {
    return true;    
  }
  return false;
}


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
std::vector<std::string> DictionaryTrie::predictCompletions(std::string prefix, unsigned int num_completions)
{
  std::vector<std::string> words;
  std::multimap<unsigned int, TSTNode*> temp1;
  std::multimap<unsigned int, TSTNode*>* temp = &temp1;
  std::vector<std::string> words1;
  
  if (prefix.length() == 0){
    std::cout << "Invalid Input. Please retry with correct input" << std::endl;
    return words;
  }
  
  if(!find(prefix)) {
    std::cout << "Invalid Input. Please retry with correct input" <<std::endl;
    return words;
  }
  
  TSTNode* curr = root; 
  for(unsigned int i=0; i<prefix.length(); i++) {
    char letter = prefix.at(i);
    while(curr->character != letter) {
      if(curr->character < letter) {
        curr = curr->right;
      }else if(letter < curr->character) {
        curr = curr->left;
      }
    }
    if(i !=prefix.length()-1) {
      curr = curr->equal;
    }
  }
  
  curr->W =prefix;
  temp->insert(std::pair<unsigned int, TSTNode*>(curr->frequency, curr));
  curr = curr->equal;
  HpredictCompletions(curr, temp, prefix);
  
  std::map<unsigned int, TSTNode*>::reverse_iterator rit;
  for(rit=temp->rbegin(); rit!=temp->rend(); ++rit) {
    std::string word= rit->second->W;
    words.push_back(word);
  }
  unsigned int Difference = words.size()-num_completions;
  if(words.size()>num_completions) {
    for(unsigned int i=0; i<Difference; i++) {
      words.pop_back();
    }
  }
            
  return words;
}


void DictionaryTrie::HpredictCompletions(TSTNode* node, std::multimap<unsigned int, TSTNode*>* words, std::string word)
{
  if(node) {
    HpredictCompletions(node->left, words, word);
    word.push_back(node->character);
    if(node->checkEnd) {
      node->W = word;
      words->insert(std::pair<unsigned int, TSTNode*>(node->frequency, node));
    }
    HpredictCompletions(node->equal, words, word);
    word.pop_back();
    HpredictCompletions(node->right, words, word);
  }
}



/*
 * Return the most similar word of equal length to the query, based
 * on their Hamming distance. 
 * p
 * In case of ties, return the word with the highest frequency (you may
 * assume there will always be one should a tie happen.)
 * In case there isn't any word of equal length to the query in the
 * trie, return an empty string.
 */
std::string DictionaryTrie::checkSpelling(std::string query)
{
  if(query =="") {
    return "";
  }
  std::stack<TSTNode*> mystack1;
  std::stack<TSTNode*>* mystack =&mystack1;
  TSTNode* curr = root;
  std::string word ="";
  HcheckSpelling(curr, mystack,query, word);
  if(mystack->empty()) {
    return "";
  }else {
    return mystack->top()->W; 
  }
  return "";
}

void DictionaryTrie::HcheckSpelling(TSTNode* node, std::stack<TSTNode*>* mystack, std::string query, std::string word)

{
  if(node) {
    HcheckSpelling(node->left, mystack,query, word);
    word.push_back(node->character);
    if(node->checkEnd) {
      node->W = word;
      if(word.length() == query.length()) {
        int Hdistance = 0;
        for(unsigned int i=0; i<query.length(); i++) {
          if(word.at(i) == query.at(i)) {
            Hdistance++;
          }
        }
        node->HD = Hdistance;
        if(mystack->empty()) {
          mystack->push(node);
        }else {
          
          if(mystack->top()->HD < node->HD) {
            mystack->push(node);
          }else if(mystack->top()->HD == node->HD) {
            if( mystack->top()->frequency < node->frequency) {
              mystack->push(node);
            }
          }
        }
      }
    }
    HcheckSpelling(node->equal, mystack, query, word);
    word.pop_back(); 
    HcheckSpelling(node->right, mystack, query, word);
  }
}





/* Destructor */
DictionaryTrie::~DictionaryTrie(){
  deleteAll(root);
}

void DictionaryTrie::deleteAll(TSTNode* n) {
  if(n == 0) {
    return;
  }
  deleteAll(n->left);
  deleteAll(n->equal);
  deleteAll(n->right);
  delete n;
}





