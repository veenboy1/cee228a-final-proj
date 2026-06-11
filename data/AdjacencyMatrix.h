#pragma once
#include <iostream>
#include "../graph/networkGen.h"

struct AdjacencyMatrix {
    std::vector<std::vector<int>> matrix;
    
    void build(Graph g){
        int n = g.numNodes();
        matrix.assign(n, std::vector<int>(n, 0));
        
        for (int i = 0; i < g.edges.size(); i++) {
            // get edge info 
            int o = g.edges[i].from;
            int d = g.edges[i].to;
            int w = g.edges[i].weight;
            
            // put them into the matrix 
            matrix[o][d] = w;
            matrix[d][o] = w;
        }
    }

    void print(){
        for (int o = 0; o < matrix.size(); o++) {
            for (int d = 0; d < matrix[o].size(); d++){
                std::cout << matrix[o][d] << " " ;
            }
            std::cout << std::endl;
        }
    }
    
};