#include <iostream>
#include <vector>
#include "graph.h"

using namespace std;

int Graph::insertVertex(int k) {
	Vertex* newVertex = new Vertex;
	newVertex->key = k;
	vertices.push_back(newVertex);
	return 0;
}

int Graph::insertEdge(int start, int end) {
	adjVertex* newEdge = new adjVertex;
	for (unsigned int i=0; i<vertices.size(); i++) {
		if (vertices[i]->key == start) { // find start @ index 'i'
			for (unsigned int j=0; j<vertices.size(); j++) {
				if (vertices[j]->key == end) { // find end @ index 'j'
					newEdge->v = vertices[j];
					vertices[i]->adjList.push_back(*newEdge);
					return 0;
				}
			}
			cout << "End node not found :(\n";
			return -1;
		}
	}
	cout << "Start node not found :(\n";
	return -1;
	//newEdge->v = ??; // Vertex reference containing the 'end' value;
}

Vertex* Graph::search(int k) {
	for (unsigned int i=0; i<vertices.size(); i++) {
		if (vertices[i]->key == k) {
			//cout << "Found it!\n";
			return vertices[i];
		}
	}
	cout << "Didn't find the key :(\n";
	return NULL;
}

void Graph::detectCycleHelper(Vertex *n, int k) {
	// n = NULL;
	// for (size_t i = 0; i < vertices.size(); i++) {
    //         for (size_t j = 0; j < vertices[i]->adj.size(); j++) {
    //             if (!vertices[i]->adj[j].v->visited) {
    //                 int k = vertices[i]->distance + vertices[i]->adj[j].weight;
    //                 if (distance < minDist) {
    //                     n = vertices[i]->adj[j].v;
    //                     minDist = distance;
    //                     vertices[i]->adj[j].v->pred = vertices[i];
    //                     n->pred = vertices[i];
    //                 }
    //             }
    //         }
    //     }
	// USED TO BASE HELPER CODE - Homework 9


	for(size_t i = 0; i < n->adjList.size(); i++){		
		// goes through all the adjacent vertex in the graph 
		if(n->adjList[i].v->visited == false){			
			//if the adjacent verticies are not visted then as it increments thrrough the verticies, it sets them as visted.
			detectCycleHelper(n->adjList[i].v, k);		
		}
		else{
			// if the adjacent vertices are visted, then it breaks out and moves on
			break;
		}
		n->visited = true;
		cout << n->visited << endl;
	}
}


bool Graph::detectCycle(int k) {
	Vertex* startV = search(k);
	detectCycleHelper(startV, k);
	if(startV->visited = true){		
		// once the verticies has come back to the start vertex and shows that it has been visted in the cycle, 
		// the bool returns true for the driver and main file and the test case is passsed
		return true;
	}
	else{
		//otherwise, the grpah is not a cycle and the test case fails
		return false;
	}
}