/*
 * ActorGraph.cpp
 * Author: <YOUR NAME HERE>
 * Date:   <DATE HERE>
 *
 * This file is meant to exist as a container for starter code that you can use to read the input file format
 * defined in movie_casts.tsv. Feel free to modify any/all aspects as you wish.
 */

#include <set>
#include <map>
#include <queue>
#include <unordered_set>
#include <unordered_map>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include "ActorGraph.h"
#include "Edge.h"
#include "Vertex.h"


using namespace std;

ActorGraph::~ActorGraph() {
  for (unordered_map<string, Vertex*>::iterator it=vertices.begin(); it!=vertices.end(); it++){
    //delete (it->second->getPred());
    delete (it->second);
    
  }
  vertices.clear();
 
}





bool ActorGraph::loadFromFile(const char* in_filename, bool use_weighted_edges) {
    // Initialize the file stream
   ifstream infile(in_filename);

    bool have_header = false;
    
    unordered_map<string, int> movie;
    unordered_map<string, vector<string>> ST;
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;

            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
       //cout << actor_name <<endl;
       //cout << movie_title <<endl;
       //cout << movie_year <<endl;      
        string MV;
        MV= movie_title.append(to_string(movie_year));
        Vertex* newV = new Vertex(actor_name);
        newV->setParent(newV);
        vertices.insert(pair<string,Vertex*> (newV->getName(), newV));       

        unordered_map<string, vector<string>>::iterator it = ST.find(MV);
        if(it == ST.end()) {
           vector<string> A;
           //cout <<actor_name << endl;
           A.push_back(actor_name);       
           ST.insert(pair<string, vector<string>>(MV, A));  
        }else {
           //cout <<actor_name << endl;
           (ST.find(MV)->second).push_back(actor_name);         
        }        
         
    }
    addEdge(ST, movie);     

    if (!infile.eof()) {
        cerr << "Failed to read " << in_filename << "!\n";
        return false;
    }
    infile.close();
    return true;
}


void ActorGraph::addEdge(unordered_map<string, vector<string>> sort, unordered_map<string, int> movie) {
  
   //multimap<int, Vertex*>  
   for(unordered_map<string,vector<string>>::iterator it=sort.begin(); it!=sort.end(); it++){
      vector<string> tempVector = it->second;
      string movieName = it->first;
      string tyear;
      string tyear2;
      for(int i=0; i<4; i++) {
         char k = movieName.back();
         movieName.pop_back();
         tyear.push_back(k);      
      }

      for(int j= 0; j<4; j++) {
         char r = tyear.back();
         tyear.pop_back();      
         tyear2.push_back(r);
      }    

      int year = stoi(tyear2);  
      int cost = 1 + (2015 -year);
      for(int i=0; i<tempVector.size()-1; i++) {
         for(int j=i+1; j<tempVector.size(); j++) {
          string tempV1 = tempVector[i];
          //cout <<tempV1 <<endl;
          string tempV2 = tempVector[j];
          //cout <<tempV2 <<endl;
          Vertex* vertex1 = vertices.find(tempV1)->second;
          Vertex* vertex2 = vertices.find(tempV2)->second; 
          Edge newE1 = Edge(vertex2, vertex1, movieName, year, cost);           
          Edge newE2 = Edge(vertex1, vertex2, movieName, year, cost);
          
          vertex1->getEdges().insert(pair<string, Edge>(vertex2->getName(), newE2));
          vertex2->getEdges().insert(pair<string, Edge>(vertex1->getName(), newE1));                     
          } 
       } 
    } 
}
void ActorGraph::disjoint(string source, string dest, ofstream& out, const char* in_filename ) {
   for(unordered_map<string, Vertex*>::iterator it = vertices.begin(); it!=vertices.end(); it++) {
        (it->second)->setParent(it->second);
        (it->second)->setSize(1);
   }
   
    // Initialize the file stream
   ifstream infile(in_filename);

    bool have_header = false;
    
    unordered_map<string, int> movie;
    unordered_map<string, vector<string>> ST;
    // keep reading lines until the end of file is reached
    while (infile) {
        string s;

        // get the next line
        if (!getline( infile, s )) break;

        if (!have_header) {
            // skip the header
            have_header = true;
            continue;
        }

        istringstream ss( s );
        vector <string> record;

        while (ss) {
            string next;

            // get the next string before hitting a tab character and put it in 'next'
            if (!getline( ss, next, '\t' )) break;

            record.push_back( next );
        }

        if (record.size() != 3) {
            // we should have exactly 3 columns
            continue;
        }

        string actor_name(record[0]);
        string movie_title(record[1]);
        int movie_year = stoi(record[2]);
       //cout << actor_name <<endl;
       //cout << movie_title <<endl;
       //cout << movie_year <<endl;      
        string MV;
        MV= movie_title.append(to_string(movie_year));

        unordered_map<string, vector<string>>::iterator it = ST.find(MV);
        if(it == ST.end()) {
           vector<string> A;
           //cout <<actor_name << endl;
           A.push_back(actor_name);       
           ST.insert(pair<string, vector<string>>(MV, A));  
        }else {
           //cout <<actor_name << endl;
           (ST.find(MV)->second).push_back(actor_name);         
        }        
         
    }

  
   multimap<int, vector<string>> sortY;
   
   for(unordered_map<string, vector<string>>::iterator it3=ST.begin(); 
   it3!=ST.end(); it3++){  
      //set<string> tempSet = it3->second;
      //vector<string> V;
      //set<string>:: iterator p= tempSet.find("LAMAS, LORENZO");
      //if(p!=tempSet.end()) {
      //  cout << it3->first <<endl;
     // }
     // for(set<string>::iterator it5=tempSet.begin(); it5!=tempSet.end(); it5++) {
     //    V.push_back(*it5);
     // }  
      string movieName = it3->first;
      string tyear;
      string tyear2;
      for(int i=0; i<4; i++) {
         char k = movieName.back();
         movieName.pop_back();
         tyear.push_back(k);
      }

      for(int j= 0; j<4; j++) {
         char r = tyear.back();
         tyear.pop_back();
         tyear2.push_back(r);
      }
      int year = stoi(tyear2);
      sortY.insert(make_pair(year, it3->second));
   } 

   int connectedY;
   for(multimap<int, vector<string>>::iterator it4=sortY.begin(); it4!=sortY.end(); it4++) {
    
      vector<string> tempVector =it4->second;
 
      for(int i=0; i<tempVector.size()-1; i++) {
         //for(int j=i+1; j<tempVector.size(); j++) {
            string tempV1 = tempVector[i];
            //cout <<tempV1 <<endl;
            string tempV2 = tempVector[i+1];  
            //cout <<tempV2 <<endl;
            Vertex* actor1 = vertices.find(tempV1)->second;
            Vertex* actor2 = vertices.find(tempV2)->second;
            Union(actor1, actor2);
         //}
      }   
      string Y1 = Find(vertices.find(source)->second)->getName();
      string Y2 = Find(vertices.find(dest)->second)->getName();
      if(Y1==Y2){
          connectedY = it4->first;
          printPath4(source, dest, connectedY, out);
          return;
      } 
   }
   connectedY = 9999; 
   printPath2(source, dest, connectedY, out);
}


void ActorGraph::BST(string source, string dest, ofstream& out) {
   //cout << source <<" "<< dest << endl;
   queue<Vertex*> Q2;
   queue<Vertex*> Q;
   Vertex* start = vertices.find(source)->second;
   Q.push(start);
   Q2.push(start); 
   start->setVisited(true);

   while(!Q.empty()) {
      Vertex* curr = Q.front();
      Q.pop();
      //curr->setVisited(true);
      unordered_multimap<string, Edge> tempE = curr->getEdges();
      for(unordered_multimap<string,Edge>::iterator it=tempE.begin(); it!=tempE.end(); it++){   
         Vertex* adjV = vertices.find(it->first)->second; 
         if(adjV->wasVisited() == false) {
            adjV->setVisited(true);
            adjV->setDistance(curr->getDistance() + 1);
            adjV->setPred(curr);
            Q.push(adjV);
            Q2.push(adjV);
            
           if(adjV->getName() == dest) {
               
              printPath3(source, dest, out);
             
               while(!Q2.empty()) {
                   Q2.front()->setPred(0);
                   Q2.front()->setVisited(false);
                   Q2.pop();
               } 
               return;   
            }              
         }
      }
   }    
}


void ActorGraph::Dijkstra(string source, string dest, ofstream& out) {  
   multimap<int, Vertex*> minHeap;
   for(unordered_map<string, Vertex*>::iterator it = vertices.begin(); it!=vertices.end(); it++) {
        (it->second)->setDistance(10000);
        (it->second)->setPred(0);
        (it->second)->setVisited(false);
   }
    
   //insert the source vertex in the heap
   vertices.find(source)->second->setDistance(0);
   Vertex* source_V = vertices.find(source)->second;
   int source_D =vertices.find(source)->second->getDistance();
   minHeap.insert(pair<int, Vertex*>(source_D, source_V ));
   unordered_set<string> tempM;
   
   while(!minHeap.empty()) {
      multimap<int, Vertex*>::iterator it =minHeap.begin();
      Vertex* cVertex = it->second; 
      minHeap.erase(it);

      if(cVertex->wasVisited()) {
 	 continue;
      }else {
         cVertex->setVisited(true);
      }
      
      //cout <<cVertex->getDistance() <<endl;
      //cout <<cVertex->getName() <<endl;
      //tempM.insert(pair<string, Vertex*>(cVertex->getName(), cVertex));
         
      //searching adjacent vertices     
      unordered_multimap<string, Edge> tempE = cVertex->getEdges();
      //cout <<tempE.size() <<endl;
      for( unordered_multimap<string, Edge>::iterator it = tempE.begin(); it !=tempE.end(); it++) {
         Vertex* adjV = vertices.find(it->first)->second;
         int D = cVertex->getDistance() + (it->second).getCost();
         //unordered_map<string, Vertex*>::iterator got = tempM.find(it->first);
         if(adjV->wasVisited()==false && D < adjV->getDistance()) {
            adjV->setDistance(D);
            adjV->setPred(cVertex);
            adjV->setPredM((it->second).getMovie());
            adjV->setPredY((it->second).getYear());
            pair<int, Vertex*> nVertex(D, adjV);
            //cout <<adjV->getName() <<endl;
            minHeap.insert(nVertex);
            //minHeap.push(adjV);
         } 
      }
   } 
   printPath(source, dest, out);
   return;
}


void ActorGraph::widestPath(string source, string dest, ofstream& out) {
   priority_queue<pair<Vertex*,unsigned int> , vector<pair<Vertex*,unsigned int>>, 
   VertexCompare2> minHeap;
   //reset vertices
   for(unordered_map<string, Vertex*>::iterator it = vertices.begin(); it!=vertices.end();
   it++) {
        (it->second)->setDistance(0);
        (it->second)->setPred(0);
        (it->second)->setVisited(false);
   }
    
   //insert the source vertex in the heap
   int source_D = vertices.find(source)->second->getDistance();
   Vertex* source_V =vertices.find(source)->second;
   vertices.find(source)->second->setDistance(100000);
   minHeap.push(make_pair(source_V, source_D));
   
   //start poping vertices in the minheap
   while(!minHeap.empty()) {
      pair <Vertex*, int> p = minHeap.top();
      Vertex* cVertex = p.first;
      minHeap.pop();

      if(cVertex->wasVisited()) {
 	 continue;
      }else {
         cVertex->setVisited(true);
      }
         
      //traveling adjacent vertices     
      unordered_multimap<string, Edge> tempE = cVertex->getEdges();
      for( unordered_multimap<string, Edge>::iterator it = tempE.begin(); it !=tempE.end();
       it++) {
         Vertex* adjV = vertices.find(it->first)->second;
         int M = min(cVertex->getDistance(), (it->second).getCost());
         //unordered_map<string, Vertex*>::iterator got = tempM.find(it->first);
         
        if(adjV->wasVisited()==false && M > adjV->getDistance()) {
            adjV->setDistance(M);
            adjV->setPred(cVertex);
            //cout <<adjV->getName() <<endl;
            minHeap.push(make_pair(adjV, M));
         } 
      }
   }  
   printPath4(source, dest, (2016-vertices.find(dest)->second->getDistance()), out);
   return;

}
void ActorGraph::printPath4(string source,string dest,int connetedY,ofstream& out) {
   string year = to_string(connetedY);
    string str;
    str.append(source);
    str.append("	");
    str.append(dest);
    str.append("	");
    str.append(year);
    out << str;
    out << '\n';

}

void ActorGraph::printPath2(string source, string dest, int connectedY, ofstream& out) {
    string year = to_string(connectedY); 
    string str;
    str.append(source);
    str.append("	");
    str.append(dest);
    str.append("	");
    str.append(year);
    out << str;
    out << '\n';
       
}



void ActorGraph::printPath(string source, string dest, ofstream& out) {
   vector<string> path;
   string tempV = dest;

   //gets path by traverse the prep nodes
   while(vertices.find(tempV)->second->getPred() != 0){
      path.push_back(tempV);
      tempV = vertices.find(tempV)->second->getPred()->getName();
   } 
   path.push_back(source);  
   string str; 
   for(int j = path.size() -1; j>=0; j--){
     if(j == path.size()-1) {
        str.append("(");
        str.append(vertices.find(path[j])->second->getName());
        str.append(")");
     }else {
        str.append("--[");
        string Movie = vertices.find(path[j])->second->getPredM();
        str.append(Movie);
        str.append("#@");
        string Year = to_string(vertices.find(path[j])->second->getPredY());
        str.append(Year);
        str.append("]-->"); 
        str.append("(");
        str.append(vertices.find(path[j])->second->getName());
        str.append(")");
     }
   }           
   //str.append(to_string(vertices.find(dest)->second->getDistance()));
   out <<str;
   out <<('\n');
   return;
     
}

void ActorGraph::printPath3(string source, string dest, ofstream& out) {
   vector<string> path;
   string tempV = dest;

   //gets path by traverse the prep nodes
   while(vertices.find(tempV)->second->getPred() != 0){ 
      path.push_back(tempV);
      tempV = vertices.find(tempV)->second->getPred()->getName();
   }   
   path.push_back(source);  
   string str; 
   for(int j = path.size() -1; j>=0; j--){
     if(j == 0) {
        str.append("(");
        str.append(vertices.find(path[j])->second->getName());
        str.append(")");
     }else {
        str.append("(");
        string name  = vertices.find(path[j])->second->getName();
        str.append(name);
        str.append(")--[");
        string Movie = vertices.find(path[j])->second->getEdges().find(path[j-1])->second.getMovie();     
        str.append(Movie);
        str.append("#@");
        string Year = to_string(vertices.find(path[j])->second->getEdges().find(path[j-1])->second.getYear());
        str.append(Year);
        str.append("]-->"); 
     }   
   }    
   //str.append(to_string(vertices.find(dest)->second->getDistance()));
   //cout << str <<endl;
   out <<str;
   out <<('\n');
   return;
        
}


void ActorGraph::Union(Vertex* N1, Vertex* N2) {
   Vertex* P1 = Find(N1);
   Vertex* P2 = Find(N2);
   if(P1->getName() == P2->getName()) {
     return;
   }
   if(P1->getSize() > P2->getSize()) {
      P2->setParent(P1);
      P1->setSize(P1->getSize() + P2->getSize());
      //cout <<"big"<<endl;
   }else {
      P1->setParent(P2);
      P2->setSize(P2->getSize() + P1->getSize());
      //cout <<"samll"<<endl;
   }
}

Vertex* ActorGraph::Find(Vertex* N) {
    
   if(N->getParent() == N) {
     return N;
   }else {
      //cout <<"find" <<endl;
      return Find(N->getParent());
   }

}

