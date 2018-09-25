/*
 * ActorGraph.h
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#ifndef ACTORGRAPH_H
#define ACTORGRAPH_H

#include <iostream>
#include <unordered_map>
#include "Vertex.h"
#include "Edge.h"

// Maybe include some data structures here

using namespace std;


class VertexCompare {
public:
   bool operator()(Vertex* lhs, Vertex* rhs) const {
      return lhs->getDistance() > rhs->getDistance();
   }
};

class VertexCompare2 {
public:
   bool operator()(pair<Vertex*,unsigned int> &L, pair<Vertex*,unsigned int> &R){
      return L.second < R.second; 
   }
};



class ActorGraph {
    protected:
  	unordered_map<string, Vertex*> vertices;	    		
        // Maybe add class data structure(s) here

    public:
        ActorGraph(void) {
           vertices = unordered_map<string, Vertex*>();
        };
         
        ~ActorGraph();
        
        // Maybe add some more methods here

        /** You can modify this method definition as you wish
         *
         * Load the graph from a tab-delimited file of actor->movie relationships.
         *
         * in_filename - input filename
         * use_weighted_edges - if true, compute edge weights as 1 + (2015 - movie_year), otherwise all edge weights will be 1
         *
         * return true if file was loaded sucessfully, false otherwise
         */
        
	bool loadFromFile(const char* in_filename, bool use_weighted_edges);
	
	void addEdge(unordered_map<string, vector<string>> sort, unordered_map<string, int>
         movie);
            
        void BST(string source, string dest, ofstream& out);

        void Dijkstra(string source, string dest, ofstream& out);

        void widestPath(string source, string dest, ofstream& out);
  
        void disjoint(string source, string dest, ofstream& out, const char* in_filename);
 	
        void printPath(string source, string dest, ofstream& out);
    
     	void printPath2(string source, string dest,int connectedY, ofstream& out);
    
        void printPath3(string source, string dest, ofstream& out);
 
        void printPath4(string source,string dest,int connetedY,ofstream& out);
  
        void Union(Vertex* N1, Vertex* N2);
  
        Vertex* Find(Vertex* N);
    
};


#endif // ACTORGRAPH_H
