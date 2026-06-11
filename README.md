# CEE 228A Final Project — Graph Data Structure Benchmarking

A C++ benchmarking suite comparing the performance of four graph data structures and two shortest path algorithms on urban transportation networks.

## Overview

Implements and benchmarks Dijkstra's algorithm (heap and bucket variants) across four data structures:
- Edge List
- Adjacency List
- Adjacency Matrix
- Forward Star

Networks are generated as grid graphs (proxy for urban street layouts) with random integer edge weights representing travel times.

## Project Structure

```
cee228a-final-proj/
├── main.cpp                  # benchmarking entry point
├── benchmark/
│   └── Timer.h               # microsecond timer utility
├── graph/
│   └── networkGen.h          # grid graph generator
├── data/                     # all data strucutres
│   ├── AdjacencyList.h
│   ├── AdjacencyMatrix.h
│   └── ForwardStar.h
└── dijkstra/
└── Dijkstra.h            # all Dijkstra implementations
```

## Building and Running

```bash
c++ -std=c++17 -O2 main.cpp -o main
./main > results.csv
```

## Results

Benchmarks run all-pairs Dijkstra's on grid sizes 3×3 to 30×30. Forward star consistently outperforms other structures due to cache-friendly memory layout. Full analysis in the course report.

## Requirements

- macOS with Xcode Command Line Tools
- otherwise, any system capable of running C++