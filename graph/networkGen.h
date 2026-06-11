#pragma once
#include <iostream>
#include <cstdlib>   // for rand()
#include <ctime>     // for time()
#include <vector>

struct Edge {
    int from, to, weight;
};

struct Graph{
    std::vector<Edge> edges;
    int nRows, nCols;

    void generateGrid(int numRows, int numCols, int maxWeight){
        // store the size of the graph
        nRows = numRows;
        nCols = numCols;
        
        // create all the edges in the graph 
        for (int row = 0; row < numRows; row++) {
            for (int col = 0; col < numCols; col++) {
                int nodeID = row * numCols + col;

                // connect to right neighbor if it exists
                if (col + 1 < numCols) {
                    int weight = (rand() % maxWeight) + 1;
                    // create edge from nodeID to (nodeID + 1)
                    edges.push_back(Edge {nodeID, (nodeID+1), weight});
                }

                // connect to bottom neighbor if it exists
                if (row + 1 < numRows) {
                    // create edge from nodeID to (nodeID + numCols)
                    int weight = (rand() % maxWeight) + 1;
                    edges.push_back(Edge {nodeID, (nodeID+numCols), weight});
                }
            }
        }
    }

    int numNodes() {
        return nRows * nCols;
    }

    void printEdges() {
        // This one is for printing the edges from an edge view 
        for (int i = 0; i < edges.size(); i++) {
            std::cout << "from: " << edges[i].from << " to: " << edges[i].to << " with wieght: " << edges[i].weight << std::endl;
        }
    }

    void print() { 
        // This prints edges from a node view 
        int n = nRows * nCols;
        for (int i = 0; i < n; i++) {
            std::cout << "Node " << i << ": ";
            for (int j = 0; j < edges.size(); j++) {
                if (edges[j].from == i || edges[j].to == i) {
                    // print the neighbor and weight
                    std::cout << "(" << edges[j].to << ", " << edges[j].weight  << ") ";
                }
            }
            std::cout << std::endl;
        }
    }

};