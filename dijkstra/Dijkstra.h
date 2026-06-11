#pragma once
#include <iostream>
#include <limits>
#include "../data/AdjacencyList.h"
#include <queue>

// create an infinity value 
int INF = std::numeric_limits<int>::max();

// ---------- Heap Functions ---------- // 
std::vector<int> dijkstraHeapAdjList(AdjacencyList aList, int source) {
    // create distance vector, default INF for all but source 
    std::vector<int> dist(aList.n, INF);
    dist[source] = 0;

    // crate binary heap 
    // pair is (distance, node) - distance first so heap sorts by it
    std::priority_queue<std::pair<int,int>, 
                        std::vector<std::pair<int,int>>, 
                        std::greater<std::pair<int,int>>> pq;
    
    pq.push({0, source});

    // create visited node list 
    std::vector<bool> visited(aList.n, false);

    // main implementation 
    while (not(pq.empty())){
        // init loop 
        auto [d, u] = pq.top();     // get closest node
        pq.pop();                   // remove it
        if (visited[u]){continue;}  // check if visited 
        visited[u] = true;

        // looping over adjacent nodes 
        for (int neighbor = 0; neighbor < aList.adjList[u].size(); neighbor++) {
            int w = aList.adjList[u][neighbor].second;
            int v = aList.adjList[u][neighbor].first;
            if (d + w < dist[v]){
                dist[v] = d + w;
                pq.push({d+w, v});
            }
        }
    }
    return dist;
}

std::vector<int> dijkstraHeapAdjMatrix(AdjacencyMatrix aMat, int source){
    // create distance vector, default INF for all but source 
    std::vector<int> dist(aMat.matrix.size(), INF);
    dist[source] = 0;

    // create binary heap
    std::priority_queue<std::pair<int,int>, 
                        std::vector<std::pair<int,int>>, 
                        std::greater<std::pair<int,int>>> pq;
    pq.push({0, source});

    // create visited node list 
    std::vector<bool> visited(aMat.matrix.size(), false);

    // main implementation 
    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) { continue; }
        visited[u] = true;

        // key difference from adjacency list:
        // instead of looping over a neighbor list,
        // we scan the entire row of the matrix
        // a non-zero value means an edge exists
        for (int v = 0; v < aMat.matrix[u].size(); v++) {
            int w = aMat.matrix[u][v];  // weight, 0 means no edge
            if (w != 0 && d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

std::vector<int> dijkstraHeapEdgeList(Graph g, int source){
    int n = g.numNodes();
    std::vector<int> dist(n, INF);
    dist[source] = 0;

    std::priority_queue<std::pair<int,int>, 
                        std::vector<std::pair<int,int>>, 
                        std::greater<std::pair<int,int>>> pq;
    pq.push({0, source});

    std::vector<bool> visited(n, false);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) { continue; }
        visited[u] = true;

        // key difference: scan ALL edges looking for ones that leave node u
        // this is O(E) per node — the slow part of edge lists
        for (int i = 0; i < g.edges.size(); i++) {
            if (g.edges[i].from == u) {
                int v = g.edges[i].to;
                int w = g.edges[i].weight;
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
            // since undirected, also check the reverse direction
            if (g.edges[i].to == u) {
                int v = g.edges[i].from;
                int w = g.edges[i].weight;
                if (d + w < dist[v]) {
                    dist[v] = d + w;
                    pq.push({dist[v], v});
                }
            }
        }
    }

    return dist;
}

std::vector<int> dijkstraHeapForwardStar(ForwardStar fs, int source){
    std::vector<int> dist(fs.n, INF);
    dist[source] = 0;

    std::priority_queue<std::pair<int,int>, 
                        std::vector<std::pair<int,int>>, 
                        std::greater<std::pair<int,int>>> pq;
    pq.push({0, source});

    std::vector<bool> visited(fs.n, false);

    while (!pq.empty()) {
        auto [d, u] = pq.top();
        pq.pop();

        if (visited[u]) { continue; }
        visited[u] = true;

        // key difference: use start[u] to start[u+1] to find neighbors
        // this is the cache-friendly part that makes forward star fast
        for (int i = fs.start[u]; i < fs.start[u+1]; i++) {
            int v = fs.to[i];
            int w = fs.weight[i];
            if (d + w < dist[v]) {
                dist[v] = d + w;
                pq.push({dist[v], v});
            }
        }
    }

    return dist;
}

// ---------- Bucket Functions ---------- // 
std::vector<int> dijkstraBucketAdjList(AdjacencyList aList, int source){
    // create distance vector, default INF for all but source 
    std::vector<int> dist(aList.n, INF);
    dist[source] = 0;
    
    int maxDist = aList.n * 20;  // n nodes, max edge weight 20
    // std::cout << "Maximum Distance value: " << maxDist << std::endl;

    // create the buckets 
    std::vector<std::vector<int>> buckets(maxDist, std::vector<int>());
    buckets[0].push_back(source);  // source goes in bucket 0

    // create visited node list 
    std::vector<bool> visited(aList.n, false);

    // main implementation 
    int curr = 0; 

    while (curr < maxDist) {
        // find next non-empty bucket
        while (curr < maxDist && buckets[curr].empty()) { curr++; }
        if (curr >= maxDist) { break; }

        // get next node
        int u = buckets[curr].back();
        buckets[curr].pop_back();

        // skip if already visited (no continue needed, just wrap in if/else)
        if (!visited[u]) {
            visited[u] = true;

            // loop over neighbors
            for (int neighbor = 0; neighbor < aList.adjList[u].size(); neighbor++) {
                int w = aList.adjList[u][neighbor].second;
                int v = aList.adjList[u][neighbor].first;
                
                // only update if shorter path found AND within bounds
                if (curr + w < dist[v] && curr + w < maxDist) {
                    dist[v] = curr + w;
                    buckets[dist[v]].push_back(v);
                }
            }
        }
    }

    return dist;
}

std::vector<int> dijkstraBucketAdjMatrix(AdjacencyMatrix aMat, int source){
    int n = aMat.matrix.size();
    std::vector<int> dist(n, INF);
    dist[source] = 0;

    int maxDist = n * 20;
    std::vector<std::vector<int>> buckets(maxDist, std::vector<int>());
    buckets[0].push_back(source);

    std::vector<bool> visited(n, false);
    int curr = 0;

    while (curr < maxDist) {
        while (curr < maxDist && buckets[curr].empty()) { curr++; }
        if (curr >= maxDist) { break; }

        int u = buckets[curr].back();
        buckets[curr].pop_back();

        if (!visited[u]) {
            visited[u] = true;
            for (int v = 0; v < aMat.matrix[u].size(); v++) {
                int w = aMat.matrix[u][v];
                if (w != 0 && curr + w < dist[v] && curr + w < maxDist) {
                    dist[v] = curr + w;
                    buckets[dist[v]].push_back(v);
                }
            }
        }
    }
    return dist;
}

std::vector<int> dijkstraBucketEdgeList(Graph g, int source){
    int n = g.numNodes();
    std::vector<int> dist(n, INF);
    dist[source] = 0;

    int maxDist = n * 20;
    std::vector<std::vector<int>> buckets(maxDist, std::vector<int>());
    buckets[0].push_back(source);

    std::vector<bool> visited(n, false);
    int curr = 0;

    while (curr < maxDist) {
        while (curr < maxDist && buckets[curr].empty()) { curr++; }
        if (curr >= maxDist) { break; }

        int u = buckets[curr].back();
        buckets[curr].pop_back();

        if (!visited[u]) {
            visited[u] = true;
            for (int i = 0; i < g.edges.size(); i++) {
                if (g.edges[i].from == u) {
                    int v = g.edges[i].to;
                    int w = g.edges[i].weight;
                    if (curr + w < dist[v] && curr + w < maxDist) {
                        dist[v] = curr + w;
                        buckets[dist[v]].push_back(v);
                    }
                }
                if (g.edges[i].to == u) {
                    int v = g.edges[i].from;
                    int w = g.edges[i].weight;
                    if (curr + w < dist[v] && curr + w < maxDist) {
                        dist[v] = curr + w;
                        buckets[dist[v]].push_back(v);
                    }
                }
            }
        }
    }
    return dist;
}

std::vector<int> dijkstraBucketForwardStar(ForwardStar fs, int source){
    std::vector<int> dist(fs.n, INF);
    dist[source] = 0;

    int maxDist = fs.n * 20;
    std::vector<std::vector<int>> buckets(maxDist, std::vector<int>());
    buckets[0].push_back(source);

    std::vector<bool> visited(fs.n, false);
    int curr = 0;

    while (curr < maxDist) {
        while (curr < maxDist && buckets[curr].empty()) { curr++; }
        if (curr >= maxDist) { break; }

        int u = buckets[curr].back();
        buckets[curr].pop_back();

        if (!visited[u]) {
            visited[u] = true;
            for (int i = fs.start[u]; i < fs.start[u+1]; i++) {
                int v = fs.to[i];
                int w = fs.weight[i];
                if (curr + w < dist[v] && curr + w < maxDist) {
                    dist[v] = curr + w;
                    buckets[dist[v]].push_back(v);
                }
            }
        }
    }
    return dist;
}