#pragma once
#include <iostream>
#include "../graph/networkGen.h"

struct ForwardStar {
    std::vector<int> to;      // destination of each edge
    std::vector<int> weight;  // weight of each edge
    std::vector<int> start;   // where each node's edges begin
    int n;                    // number of nodes

    void build(Graph g){
        n = g.numNodes();
        
        // a vector to keep track of number of links hitting each node
        std::vector<int> count(n, 0);

        for (int i = 0; i < g.edges.size(); i++) {
            int o = g.edges[i].from;
            int d = g.edges[i].to;
            count[o]++;
            count[d]++;
        }
        
        // build the start vector 
        start.resize(n + 1, 0);  // n+1 so the last node has a sentinel
        for (int i = 0; i < n; i++) {
            start[i + 1] = start[i] + count[i];
        }
        
        // temporary position vector (keep start intact)
        std::vector<int> pos(n);
        for (int i = 0; i < n; i++) pos[i] = start[i];
        
        // build the edges vector 
        int totalEdges = g.edges.size() * 2; // note: only works if all links are bidirectional 
        to.resize(totalEdges);
        weight.resize(totalEdges);
        
        for (int i = 0; i < g.edges.size(); i++) {
            int o = g.edges[i].from;
            int d = g.edges[i].to;
            int w = g.edges[i].weight;
            
            to[pos[o]] = d;
            weight[pos[o]] = w;
            pos[o]++;
            
            to[pos[d]] = o;
            weight[pos[d]] = w;
            pos[d]++;
        }
    }

    void print(){
        for (int i = 0; i < n; i++) {
        std::cout << "Node " << i << ": ";
            for (int j = start[i]; j < start[i+1]; j++) {
                // to[j] and weight[j] are the neighbor and weight
                std::cout << "(" << to[j]  << ", " << weight[j] << ") ";
            }
        std::cout << std::endl;
        }
    }
};

// std::cout << "(" << adjList[i][j].first << ", " << adjList[i][j].second << ") ";
