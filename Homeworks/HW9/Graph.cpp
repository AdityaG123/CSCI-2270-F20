#include "Graph.hpp"
#include <vector>
#include <queue>
#include <iostream>
#include <climits>

using namespace std;

void Graph::createEdge(string v1, string v2, int num) {
  for(int i = 0; i < vertices.size(); i++) {
    if(vertices[i]->name == v1) {
      for(int j = 0; j < vertices.size(); j++) {
        if(vertices[j]->name == v2 && i != j) {
          adjVertex av;
          av.v = vertices[j];
          av.weight = num;
          vertices[i]->adj.push_back(av);
          adjVertex av2;
          av2.v = vertices[i];
          av2.weight = num;
          vertices[j]->adj.push_back(av2);
        }
      }
    }
  }
}

void Graph::insertVertex(string n){

}

void Graph::displayEdges(){
    //loop through all vertices and adjacent vertices
    // cout<<"here"<<vertices.size()<<endl;
    for(unsigned int i = 0; i < vertices.size(); i++){
        cout<<vertices[i]->name<<":"<<endl;
        for(unsigned int j = 0; j < vertices[i]->adj.size(); j++){
            cout<<" --> "<< vertices[i]->adj[j].v->name << " "<<vertices[i]->adj[j].weight<<endl;
        }
        cout<<endl;
    }
}

void Graph::traverseWithDijkstra(string start){
    vertex * vStart = NULL;
    for(int i = 0; i < vertices.size(); i++){
        if(start == vertices[i]->name){
            vStart = vertices[i];
        }
    }

    vStart->visited = true;
    vStart->distance = 0;
    vector<vertex*> solvedList;
    solvedList.push_back(vStart);
    bool allSolved = false;
    int dist = 0;
    int minDist = INT_MAX;
    vertex * solv;

    while(!allSolved){
        solv = NULL;
        minDist = INT_MAX;
        allSolved = true;

        for(int i = 0; i < solvedList.size(); i++){
            vertex * temp = solvedList[i];
            for(int j = 0; j < temp->adj.size(); j++){
                if(!temp->adj[j].v->visited){
                    dist = temp->distance + temp->adj[j].weight;
                    if(dist < minDist){
                        solv = temp->adj[j].v;
                        minDist = dist;
                    }
                    allSolved = false;
                }
            }
        }

        if(!allSolved){
            solv->distance = minDist;
            solv->visited = true;
            solvedList.push_back(solv);
        }
    }
}



void depthFirstTraversalHelper(vertex *n) {
  n->visited = true;
  for(size_t x = 0; x < n->adj.size(); x++) {
    if (!n->adj[x].v->visited) {
      cout << n->adj[x].v->name << " -> ";
      depthFirstTraversalHelper(n->adj[x].v);
    }
  }
}

void Graph::depthFirstTraversal(string sourceVertex) {
  for (size_t i = 0; i < vertices.size(); i++) {
    if (vertices[i]->name == sourceVertex) {
      cout << vertices[i]->name << " -> ";
      depthFirstTraversalHelper(vertices[i]);
      cout << "DONE" << endl;
    }
  }
}

void Graph::minDistPath(string start, string end) {
    traverseWithDijkstra(start);
    for(int i=0; i<vertices.size(); i++) {
        vertices[i]->visited = false;
    }
    vector<vertex*> solved;
    vertex* sv;
    vertex* ev;
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == start) {
            sv = vertices[i];
            sv->visited = true;
            solved.push_back(sv);
        }
        if (vertices[i]->name == end) {
            ev = vertices[i];
        }
    }
    vertex* n = NULL;
    while (!ev->visited) {
        int minDist = 9999999;
        n = NULL;
        for (size_t i = 0; i < solved.size(); i++) {
            for (size_t j = 0; j < solved[i]->adj.size(); j++) {
                if (!solved[i]->adj[j].v->visited) {
                    int dist = solved[i]->distance + solved[i]->adj[j].weight;
                    if (dist < minDist) {
                        n = solved[i]->adj[j].v;
                        minDist = dist;
                        solved[i]->adj[j].v->pred = solved[i];
                        n->pred = solved[i];
                    }
                }
            }
        }
        n->distance = minDist;
        n->visited = true;
        solved.push_back(n);
        //cout << end << " -> ";
    }
    ev->distance = n->distance;
    //cout << "DONE [" << ev->distance << "]" << endl;
    vector<string> path;
    vertex* endv = NULL;
    for (size_t i = 0; i < vertices.size(); i++) {
        if (vertices[i]->name == end) {
            endv = vertices[i];
        }
    }
    path.push_back(endv->name);
    while (endv->name != start) {
        path.push_back(endv->pred->name);
        endv = endv->pred;
    }
    for (size_t i = path.size(); i > 0; i--) {
        cout << path[i-1] << " -> ";
    }
    cout << "DONE [" << ev->distance << "]" << endl;
}