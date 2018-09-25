#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <ostream>
#include <sstream>
#include "Edge.h"
#include "Vertex.h"
#include "ActorGraph.h"


using namespace std;


int main(int argc, char** argv)
{

   if(argc != 5) {
      return 1;
   }
   const char* movie_casts = argv[1];
   const char w = *argv[2];    
   
   bool use_weighted_edges;
   if(w == 'w') {
      use_weighted_edges = true;  
   }else if(w  == 'u') {
      use_weighted_edges = false;
   }

   ifstream test_pairs; 
   test_pairs.open(argv[3]);
    
   ofstream out_paths;
   out_paths.open(argv[4]);

   ActorGraph G;
   G.loadFromFile(movie_casts, use_weighted_edges);

   bool have_header = false;
   out_paths << "(actor)--[movie#@year]-->(actor)--...\n";
   while(test_pairs) {
      string s;
      if(!getline( test_pairs, s)) break;
          
      if(!have_header) {
         have_header = true;
         continue;
      }
      
      istringstream ss(s);
      vector <string> record;

      while (ss) {
         string next;
         if (!getline(ss, next, '\t')) break;
         record.push_back( next );         
        
      }
      if (record.size() !=2) {
         continue;
      } 
      string source(record[0]);
      string dest(record[1]); 
      if(w == 'u' ) {
         G.BST(source, dest, out_paths); 
      }else if(w == 'w') {
         G.Dijkstra(source, dest, out_paths);
      }
   } 
   test_pairs.close();
   out_paths.close();
}
