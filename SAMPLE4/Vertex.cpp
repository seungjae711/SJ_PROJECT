#include "Vertex.h"

#include <unordered_map>
#include <map>
using namespace std;

unordered_multimap<string, Edge>& Vertex::getEdges() {
   return edges;
} 

string Vertex::getName() {
   return name;
}

int Vertex::getDistance() {
   return distance;
}

void Vertex::setDistance(int distance) {
   this->distance = distance;
}

bool Vertex::wasVisited() {
   return visited;
}

void Vertex::setVisited(bool visited) {
   this->visited = visited;
}

Vertex* Vertex::getPred() {
   return pred;
}

void Vertex::setPred(Vertex* V) {
   this->pred = V;
}

string Vertex::getPredM() {
   return predM;
}

int Vertex::getPredY() {
   return predY;
}

void Vertex::setPredM(string M) {
   this->predM = M;
}

void Vertex::setPredY(int Y) {
   this->predY =Y;
}


int Vertex::getSize() {
   return size;
}

void Vertex::setSize(int S) {
   this->size =S;
}

Vertex* Vertex::getParent(){
   return parent;
}

void Vertex::setParent(Vertex* P) {
   this->parent = P;
} 

bool Vertex::isRoot() {
   return root;
}

void Vertex::setRoot(bool R){
   this->root = R;
}

bool Vertex::operator<(const Vertex& other) {
  //if(distance != other.distance){
    return distance > other.distance;
  //}else {
  //  return name < other.name;
  //}

}

bool Vertex::operator>(const Vertex& other) {
  //if(distance != other.distance){
    return distance < other.distance;
  //}else {
  //  return name < other.name;
  //} 

}


