#pragma once
#include <iostream>
#include "../graph/networkGen.h"

struct AdjacencyList {
    std::vector<std::vector<std::pair<int,int>>> adjList;
    int n;

    void build(Graph g){
        n = g.nCols * g.nRows;  // number of nodes 
        adjList.resize(n);          // make the list as long as there are nodes 

        for (int i = 0; i < g.edges.size(); i++) {
            int o = g.edges[i].from;
            int d = g.edges[i].to;
            int w = g.edges[i].weight;
            adjList[o].push_back({d, w});
            adjList[d].push_back({o, w});
        }
    }

    void print(){
        for (int i = 0; i < n; i++) {
            std::cout << "Node " << i << ": ";
            for (int j = 0; j < adjList[i].size(); j++) {
                // adjList[i][j] is a pair
                // .first is the neighbor, .second is the weight
                 std::cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ") ";
            }
            
            std::cout << std::endl;
        }
    }

};