#include "Edge.h"


Edge::~Edge() {
   from =nullptr;
   to=nullptr;
   movie = "";
   movie_year =0;
}

string Edge::getMovie() {
   return movie;
}

int Edge::getYear() {
   return movie_year; 
} 

int Edge::getCost() {
   return cost;
}
Vertex* Edge::getFrom() {
   return from;
}
Vertex* Edge::getTo(){
   return to;
}
