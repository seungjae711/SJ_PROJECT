
#include <stdio.h>
#include <string.h>
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
   const char* w = argv[4];    
   string widestp ="widestp"; 
   bool option;
   if(strcmp(w, widestp.c_str())==0) {
      option = true;  
   }else {
      option = false;
   }   

   ifstream test_pairs; 
   test_pairs.open(argv[2]);
    
   ofstream out_paths;
   out_paths.open(argv[3]);

   ActorGraph G;

   G.loadFromFile(movie_casts, option);
   

   bool have_header = false;
   out_paths << "Actor1	Actor2	Year\n";
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
      string widestp ="widestp";
      if(strcmp(w, widestp.c_str())==0) {
         G.widestPath(source, dest, out_paths);
      }else {
         G.disjoint(source, dest, out_paths, movie_casts );
      }
   }
   test_pairs.close();
   out_paths.close();
}


