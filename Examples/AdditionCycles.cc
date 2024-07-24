#include <iostream>
#include <string>

#include "../CycleCounter.h"

#define NUM_ADDITIONS 100000000000llu

void benchAddition(void) {
    uint64_t sum = 0;
    volatile uint64_t incr = 15;

    // Warm up (we want to make sure that the CPU is clocked-up) 
    for (size_t i = 0; i < 200000000; i++) {
        sum += incr; 
    }
    incr = 0;

    uint64_t startCycles = CycleCounter::GetCycles();
    for (size_t i = 0; i < NUM_ADDITIONS; i += 8) {
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
    } 
    uint64_t end = CycleCounter::GetCycles();
  
    uint64_t elapsedCycles = end - startCycles;
    double elapsedNanoSeconds = CycleCounter::GetDurationInNanoSeconds(elapsedCycles);
    std::cout.setf(std::ios::fixed);  // Turn-off scientific notation
    std::cout << "Elapsed Cycles:\t\t" << elapsedCycles << " Cycles" << std::endl;
    std::cout << "Elapsed Nano Seconds:\t" << elapsedNanoSeconds << " ns\n" << std::endl;

    double cyclesPerAddition = static_cast<double>(elapsedCycles) / NUM_ADDITIONS;
    double nanoSecondsPerAddition = static_cast<double>(elapsedNanoSeconds) / NUM_ADDITIONS; 
    std::cout << "Cycles per Addition:\t\t" << cyclesPerAddition << " Cycles" << std::endl;
    std::cout << "Nano Seconds per Addition:\t"<< nanoSecondsPerAddition  << " ns" << std::endl;

    if (sum == 0)  // Make sum live without printing it
        std::cout << std::to_string(sum) << std::endl;
}

int main(int argc, char ** argv) {
    benchAddition();

    return 0;
}