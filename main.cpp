#include <iostream>
#include <chrono>
#include <cstdlib>
#include "./benchmark/Timer.h"
#include "./graph/networkGen.h"
#include "./data/AdjacencyList.h"
#include "./data/AdjacencyMatrix.h"
#include "./data/ForwardStar.h"
#include "./dijkstra/Dijkstra.h"

int basicTest(int numRows, int numCols, int maxWeight) {
    // ---------- Build Graph ---------- // 
    srand(420);  // random edge weights 
    Graph G;
    G.generateGrid(numRows, numCols, maxWeight);
    int numNodes = G.numNodes();

    std::cout << "\nNumber of edges in graph: " << numNodes << std::endl;
    std::cout << std::endl;

    // ---------- Build all data structures ---------- // 
    // Note that the edge list is built into G 

    // Adjacency List
    AdjacencyList aList; 
    aList.build(G); 

    // Adjacency Matrix 
    AdjacencyMatrix adjMatrix;
    adjMatrix.build(G);
    
    // Forward Star 
    ForwardStar fs;
    fs.build(G);

    // ---------- Heap Testing ---------- // 
    std::vector<int> times; 

    // Adjacency List
    Timer timer1;
    
    timer1.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraHeapAdjList(aList, i);
    }
    times.push_back(timer1.stop());

    // Adjacency Matrix 
    Timer timer2;

    timer2.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraHeapAdjMatrix(adjMatrix, i);
    }
    times.push_back(timer2.stop());

    // Edge List 
    Timer timer3; 

    timer3.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraHeapEdgeList(G, i);
    }
    times.push_back(timer3.stop());

    // Forward Star
    Timer timer4;

    timer4.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraHeapForwardStar(fs, i);
    }
    times.push_back(timer4.stop());

    // Print out all the times 
    std::cout << "All heap times in seconds:" << std::endl;
    for (int i = 0; i < times.size(); i++) {
        std::cout << "Run #" << i+1 << ": " << times[i]/1000000.0 << " seconds" << std::endl;
    }

    // ---------- Bucket Testing ---------- // 
    std::vector<int> bucketTimes; 

    // Adjacency List
    Timer bucketTimer1;
    
    bucketTimer1.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraBucketAdjList(aList, i);
    }
    bucketTimes.push_back(bucketTimer1.stop());

    // Adjacency Matrix 
    Timer bucketTimer2;

    bucketTimer2.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraBucketAdjMatrix(adjMatrix, i);
    }
    bucketTimes.push_back(bucketTimer2.stop());

    // Edge List 
    Timer bucketTimer3; 

    bucketTimer3.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraBucketEdgeList(G, i);
    }
    bucketTimes.push_back(bucketTimer3.stop());

    // Forward Star
    Timer bucketTimer4;

    bucketTimer4.start();
    for (int i = 0; i < numNodes; i++) {
        dijkstraBucketForwardStar(fs, i);
    }
    bucketTimes.push_back(bucketTimer4.stop());

    // Print out all the times 
    std::cout << "\nAll bucket times in seconds:" << std::endl;
    for (int i = 0; i < bucketTimes.size(); i++) {
        std::cout << "Run #" << i+1 << ": " << bucketTimes[i]/1000000.0 << " seconds" << std::endl;
    }

    return 0;
}

void scalingTest(int lowerBound, int upperBound, int maxWeight) {
    // CSV header
    std::cout << "size,nodes,heap_adjlist,heap_adjmatrix,heap_edgelist,heap_forwardstar,bucket_adjlist,bucket_adjmatrix,bucket_edgelist,bucket_forwardstar" << std::endl;

    for (int size = lowerBound; size <= upperBound; size++) {
        // ---------- Build Graph ---------- // 
        srand(420);
        Graph G;
        G.generateGrid(size, size, maxWeight);
        int numNodes = G.numNodes();

        // ---------- Build all data structures ---------- // 
        AdjacencyList aList;
        aList.build(G);

        AdjacencyMatrix adjMatrix;
        adjMatrix.build(G);

        ForwardStar fs;
        fs.build(G);

        // ---------- Heap Testing ---------- // 
        Timer t;

        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraHeapAdjList(aList, i); }
        int heapAL = t.stop();

        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraHeapAdjMatrix(adjMatrix, i); }
        int heapAM = t.stop();

        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraHeapEdgeList(G, i); }
        int heapEL = t.stop();

        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraHeapForwardStar(fs, i); }
        int heapFS = t.stop();

        // ---------- Bucket Testing ---------- // 
        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraBucketAdjList(aList, i); }
        int bucketAL = t.stop();

        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraBucketAdjMatrix(adjMatrix, i); }
        int bucketAM = t.stop();

        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraBucketEdgeList(G, i); }
        int bucketEL = t.stop();

        t.start();
        for (int i = 0; i < numNodes; i++) { dijkstraBucketForwardStar(fs, i); }
        int bucketFS = t.stop();

        // ---------- Print CSV row ---------- // 
        std::cout << size << ","
                  << numNodes << ","
                  << heapAL << ","
                  << heapAM << ","
                  << heapEL << ","
                  << heapFS << ","
                  << bucketAL << ","
                  << bucketAM << ","
                  << bucketEL << ","
                  << bucketFS << std::endl;
    }
}

int main() {
    scalingTest(3, 30, 10);
    return 0;
}

/*
gvv@Mac cee228a-final-proj % c++ -std=c++17 main.cpp -o main
gvv@Mac cee228a-final-proj % ./main                         

Number of edges in graph: 2500

3094996 microseconds
85521766 microseconds
75389085 microseconds
2402776 microseconds
Run #1: 3.095seconds
Run #2: 85.5218seconds
Run #3: 75.3891seconds
Run #4: 2.40278seconds
gvv@Mac cee228a-final-proj % 

All heap times in seconds:
Run #1: 3.07624seconds
Run #2: 85.527seconds
Run #3: 72.1293seconds
Run #4: 2.41874seconds

All bucket times in seconds:
Run #1: 4.01007seconds
Run #2: 84.338seconds
Run #3: 72.0248seconds
Run #4: 3.4321seconds
*/