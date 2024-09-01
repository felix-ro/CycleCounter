# CycleCounter
This header-only library enables high-precision benchmarking using the `CNTVCT_EL0` register on ARM CPUs (for more information, see [here](https://developer.arm.com/documentation/ddi0601/2024-06/AArch64-Registers/CNTVCT-EL0--Counter-timer-Virtual-Count-Register)). The frequency with which this register is updated depends on the implementation; on an Apple M3 CPU, the frequency is 24 MHz. Together, they allow simple but high-resolution measurements. 

The header file also includes some time conversation functions; see the `Examples` directory for usage examples.

## Installation:
1. Clone the repository
2. Move it into your include directory (e.g., `/usr/local/include/`)
3. Get your counter frequency (you can use `CycleCounter::GetFreq()`)
4. Set `COUNTER_FREQUENCY` in the header file

## Usage
Below is an example of how to measure the number of cycles an addition of two `uint64_t` integers takes. We need to avoid compiler optimizations such as constant folding and dead code elimination to get an accurate measurement, which we did below.

```CXX
#include <iostream>
#include <string>
#include "CycleCounter.h"

#define NUM_ADDITIONS 100000000000llu

void benchAddition(void) {
    uint64_t sum = 0;
    volatile uint64_t incr = 15; // set volatile to avoid constant folding

    // warm up
    for (size_t i = 0; i < 200000000; i++) {
        sum += incr; 
    }
    incr = 0;

    uint64_t startCycles = CycleCounter::GetCycles();
    for (size_t i = 0; i < NUM_ADDITIONS; i += 8) {
        // unroll loop to reduce loop-overhead
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
        sum += incr;
    } 
    uint64_t endCycles = CycleCounter::GetCycles();

    double elapsedNanoSeconds = CycleCounter::GetDurationInNanoSeconds(endCycles - startCycles);
    double cyclesPerAddition = static_cast<double>(endCycles - startCycles) / NUM_ADDITIONS;
    double nanoSecondsPerAddition = static_cast<double>(elapsedNanoSeconds) / NUM_ADDITIONS; 
    std::cout << "Cycles per Addition:\t\t" << cyclesPerAddition << " Cycles" << std::endl;
    std::cout << "Nano Seconds per Addition:\t"<< nanoSecondsPerAddition  << " ns" << std::endl;

    if (sum == 0)  // make sum live to avoid dead code elimination
        std::cout << std::to_string(sum) << std::endl;
}
```

Running the benchmarking function gives us:
```
Cycles per Addition:            1.02334 Cycles
Nano Seconds per Addition:      0.252677 ns
```
As expected an addition takes 1 cycle. 

## Acknowledgments
This header file incorporates some ideas introduced in 'Understanding Software Dynamics' by Richard L. Sites, which is an excellent book on performance and tracing.