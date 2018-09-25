#ifndef EDGE_HPP
#define EDGE_HPP
#include <string>

using namespace	std;

class Vertex;


class Edge{
private:
   Vertex* from;
   Vertex* to;
   string movie;
   int movie_year;
   int cost;


public:
   Edge(Vertex* from, Vertex* to, string movie, int movie_year, int cost): 
        from(from), to(to), movie(movie), movie_year(movie_year), cost(cost){};
  
   ~Edge();

  string getMovie();
  
  int getYear();
  
  int getCost();
  
  Vertex* getFrom();
 
  Vertex* getTo();
};
#endif

