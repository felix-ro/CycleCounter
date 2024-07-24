#include <iostream>
#include <unistd.h>

#include "../CycleCounter.h"

void useCounterObject(void) {
    // Usage Method 1
    CycleCounter counter;
    counter.Start();
    sleep(2);
    counter.Stop();

    std::cout << "Cycles Elapsed:\t\t\t" << counter.GetDurationInCycles() <<  " Cycles" << std::endl;
    std::cout << "Duration in Seconds:\t\t" << counter.GetDurationInSeconds() << " s" << std::endl;
    std::cout << "Duration in Milli Seconds:\t" << counter.GetDurationInMilliSeconds() << " ms" << std::endl;
    std::cout << "Duration in Micro Seconds:\t" << counter.GetDurationInMicroSeconds() << " us" << std::endl;
    std::cout << "Duration in Nano Seconds:\t" << counter.GetDurationInNanoSeconds() << " ns\n" << std::endl;
}

void staticCounter(void) {
    uint64_t start = CycleCounter::GetCycles();
    sleep(2); 
    uint64_t end = CycleCounter::GetCycles();
    uint64_t elapsedCycles = end - start;

    std::cout << "Cycles Elapsed:\t\t\t" << elapsedCycles <<  " Cycles" << std::endl;
    std::cout << "Duration in Seconds:\t\t" << CycleCounter::GetDurationInSeconds(elapsedCycles) << " s" << std::endl;
    std::cout << "Duration in Milli Seconds:\t" << CycleCounter::GetDurationInMilliSeconds(elapsedCycles) << " ms" << std::endl;
    std::cout << "Duration in Micro Seconds:\t" << CycleCounter::GetDurationInMicroSeconds(elapsedCycles) << " us" << std::endl;
    std::cout << "Duration in Nano Seconds:\t" << CycleCounter::GetDurationInNanoSeconds(elapsedCycles) << " ns" << std::endl;
}

int main(int argc, char **argv) {    
    // Usage Method 1
    useCounterObject();

    // Usage Method 2
    staticCounter();
    return 0;
}