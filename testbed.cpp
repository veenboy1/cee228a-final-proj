#include <iostream>
#include <chrono>
#include <cstdlib>
#include "./benchmark/Timer.h"
#include "./graph/networkGen.h"
#include "./data/AdjacencyList.h"
#include "./data/AdjacencyMatrix.h"
#include "./data/ForwardStar.h"
#include "./dijkstra/Dijkstra.h"

int main() {
    // timer testing 
    Timer t;
    t.start();

    // something to measure -- count to a million
    int sum = 0;
    for (int i = 0; i < 1000000; i++) {
        sum += i;
    }

    t.stop();
    
    // graph builder testing 
    srand(420); // i don't actually want it to be different each time
    Graph tiny;
    tiny.generateGrid(3, 3, 10);
    tiny.printEdges();
    std::cout << "\nNumber of edges in graph: " << tiny.edges.size() << std::endl;
    std::cout << std::endl;
    
    // testing the adjacency list 
    AdjacencyList aList; 
    aList.build(tiny);
    aList.print(); 
    std::cout << std::endl;

    // testing the edge list (built into the graph)
    tiny.print();
    std::cout << std::endl;


    // testing the adjacency matrix 
    AdjacencyMatrix adjMatrix; 
    adjMatrix.build(tiny);
    adjMatrix.print();
    std::cout << std::endl;


    // testing the forward star 
    ForwardStar fs; 
    fs.build(tiny);
    fs.print();
    std::cout << std::endl;

    // dijkstraHeap check with adjecency list 
    auto distancesHAL = dijkstraHeapAdjList(aList, 0);
    for (int i = 0; i < distancesHAL.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesHAL[i] << std::endl;
    }
    std::cout << std::endl;


    // dijkstraBucket check with adjecency list 
    auto distancesBAL = dijkstraBucketAdjList(aList, 0);
    for (int i = 0; i < distancesBAL.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesBAL[i] << std::endl;
    }
    std::cout << std::endl;

    // compare results from bucket and adjecency list 
    bool match = true;
    for (int i = 0; i < distancesBAL.size(); i++) {
        if (distancesBAL[i] != distancesHAL[i]) {
            std::cout << "Mismatch at node " << i << std::endl;
            match = false;
        }
    }
    if (match) { std::cout << "All distances match!" << std::endl; }
    std::cout << std::endl;


    // dijkstraHeapAdjMatrix check 
    auto distancesHAM = dijkstraHeapAdjMatrix(adjMatrix, 0);
    for (int i = 0; i < distancesHAM.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesHAM[i] << std::endl;
    }
    
    // compare results from adjacency matrix and adjecency list 
    match = true;
    for (int i = 0; i < distancesHAL.size(); i++) {
        if (distancesHAL[i] != distancesHAM[i]) {
            std::cout << "Mismatch at node " << i << std::endl;
            match = false;
        }
    }
    if (match) { std::cout << "All distances match! Pt. 2" << std::endl; }
    std::cout << std::endl;

    // dijkstraHeapEdgeList check 
    auto distancesHEL = dijkstraHeapEdgeList(tiny, 0);
    for (int i = 0; i < distancesHEL.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesHEL[i] << std::endl;
    }
    
    // compare results from edge list and adjacency list 
    match = true;
    for (int i = 0; i < distancesHAL.size(); i++) {
        if (distancesHAL[i] != distancesHEL[i]) {
            std::cout << "Mismatch at node " << i << std::endl;
            match = false;
        }
    }
    if (match) { std::cout << "All distances match! Pt. 3" << std::endl; }
    std::cout << std::endl;

    // dijkstraHeapForwardStar check 
    auto distancesHFS = dijkstraHeapForwardStar(fs, 0);
    for (int i = 0; i < distancesHFS.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesHFS[i] << std::endl;
    }
    
    // compare results from forward star and adjacency list 
    match = true;
    for (int i = 0; i < distancesHAL.size(); i++) {
        if (distancesHAL[i] != distancesHFS[i]) {
            std::cout << "Mismatch at node " << i << std::endl;
            match = false;
        }
    }
    if (match) { std::cout << "All distances match! Pt. 4" << std::endl; }
    std::cout << std::endl;
    // dijkstraBucketAdjMatrix check
    auto distancesBAM = dijkstraBucketAdjMatrix(adjMatrix, 0);
    for (int i = 0; i < distancesBAM.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesBAM[i] << std::endl;
    }
    match = true;
    for (int i = 0; i < distancesHAL.size(); i++) {
        if (distancesHAL[i] != distancesBAM[i]) {
            std::cout << "Mismatch at node " << i << std::endl;
            match = false;
        }
    }
    if (match) { std::cout << "All distances match! Pt. 5" << std::endl; }
    std::cout << std::endl;

    // dijkstraBucketEdgeList check
    auto distancesBEL = dijkstraBucketEdgeList(tiny, 0);
    for (int i = 0; i < distancesBEL.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesBEL[i] << std::endl;
    }
    match = true;
    for (int i = 0; i < distancesHAL.size(); i++) {
        if (distancesHAL[i] != distancesBEL[i]) {
            std::cout << "Mismatch at node " << i << std::endl;
            match = false;
        }
    }
    if (match) { std::cout << "All distances match! Pt. 6" << std::endl; }
    std::cout << std::endl;

    // dijkstraBucketForwardStar check
    auto distancesBFS = dijkstraBucketForwardStar(fs, 0);
    for (int i = 0; i < distancesBFS.size(); i++) {
        std::cout << "Node 0 to Node " << i << ": " << distancesBFS[i] << std::endl;
    }
    match = true;
    for (int i = 0; i < distancesHAL.size(); i++) {
        if (distancesHAL[i] != distancesBFS[i]) {
            std::cout << "Mismatch at node " << i << std::endl;
            match = false;
        }
    }
    if (match) { std::cout << "All distances match! Pt. 7" << std::endl; }
    std::cout << std::endl;

    // dummy return 
    return 0;
}