#pragma once
#include <iostream>
#include <chrono>

struct Timer {
    // variables to store the two timestamps
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;

    void start() {
    startTime = std::chrono::high_resolution_clock::now(); 
    }

    int stop(bool printTime = false) {
    endTime = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(endTime - startTime);
    if (printTime) {
        std::cout << duration.count() << " microseconds" << std::endl;
    }
    
    return duration.count();

    }
};