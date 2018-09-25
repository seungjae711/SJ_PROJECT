#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <string>
#include <unordered_map>
#include "Edge.h"


using namespace std;

class Vertex {

private:
   string name;
   int distance;
   bool visited;
   Vertex* pred;
   string predM;
   int predY;
   Vertex* parent;
   int size;
   bool root;
   unordered_multimap<string, Edge> edges;


public:
   
   Vertex(string &name): name(name), distance(0), visited(false), pred(0), predM(""), predY(0), parent(0), size(1), root(true) {
      edges = unordered_multimap<string, Edge>();
   }

   
   unordered_multimap<string, Edge>& getEdges(); 

   string getName();

   int getDistance();
  
   Vertex* getPred();

   void setDistance(int distance);

   bool wasVisited();

   void setVisited(bool visited);
  
   void setPred(Vertex* V);

   bool operator<(const Vertex& other);
 
   bool operator>(const Vertex& other);

   string getPredM();
   
   void setPredM(string M);

   int getPredY();

   void setPredY(int Y);
   
   int getSize();

   void setSize(int S);

   Vertex* getParent();

   void setParent(Vertex* P);

   bool isRoot();
 
   void setRoot(bool root);


};
#endif

