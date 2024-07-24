// CycleCounters.h

#ifndef __CYCLECOUNTERS_H__
#define __CYCLECOUNTERS_H__

#include <stdint.h>
#include <sys/time.h>

#if defined(__x86_64__)
#define IS_X86_64 1
#else
#define IS_X86_64 0
#endif

#if defined(__znver1)
#define IS_AMD_64 (IS_X86_64 && 1)
#define IS_INTEL_64 (IS_X86_64 && 0)
#else
#define IS_AMD_64 (IS_X86_64 && 0)
#define IS_INTEL_64 (IS_X86_64 && 1)
#endif

#if defined(__aarch64__)
#define IS_ARM_64 1
#else
#define IS_ARM_64 0
#endif

#if defined(__ARM_ARCH) && (__ARM_ARCH == 8)
#define IS_ARM8 1
#else
#define IS_ARM8 0
#endif

#define IS_ARM8_64 (IS_ARM8 && IS_ARM_64)

#if IS_X86_64
#include <x86intrin.h> // __rdtsc()
#endif

#define CPU_FREQUENCY_GHZ 4.05   // Set the frequency of your CPU here (e.g., 4.05GHz)
#define COUNTER_FREQUENCY 0.024  // The cycle counter is updated at 24MHz (CycleCounter::GetFreq()) 

#define SCALING_FACTOR (CPU_FREQUENCY_GHZ / COUNTER_FREQUENCY)

class CycleCounter {
private:
  uint64_t elapsedCycles;
  uint64_t startCycles;
  uint64_t endCycles;

public:
  CycleCounter() : elapsedCycles(0), startCycles(0), endCycles(0) {}

  uint64_t GetDurationInCycles() {
    if (endCycles && startCycles && endCycles > startCycles) {
        elapsedCycles = (endCycles - startCycles);
        return elapsedCycles;
    }
    return static_cast<uint64_t>(-1); // UINT64_MAX
  }

  double GetDurationInSeconds() const {
    return static_cast<double>(elapsedCycles) / (CPU_FREQUENCY_GHZ * 1e9);
  }

  double GetDurationInMilliSeconds() const {
    return static_cast<double>(elapsedCycles) / (CPU_FREQUENCY_GHZ * 1e6);
  }

  double GetDurationInMicroSeconds() const {
    return static_cast<double>(elapsedCycles) / (CPU_FREQUENCY_GHZ * 1e3);
  }

  double GetDurationInNanoSeconds() const {
    return static_cast<double>(elapsedCycles) / CPU_FREQUENCY_GHZ;
  }

  static double GetDurationInSeconds(const uint64_t elapsedCycles) {
    return static_cast<double>(elapsedCycles) / (CPU_FREQUENCY_GHZ * 1e9);
  }

  static double GetDurationInMilliSeconds(const uint64_t elapsedCycles) {
    return static_cast<double>(elapsedCycles) / (CPU_FREQUENCY_GHZ * 1e6);
  }

  static double GetDurationInMicroSeconds(const uint64_t elapsedCycles) {
    return static_cast<double>(elapsedCycles) / (CPU_FREQUENCY_GHZ * 1e3);
  }

  static double GetDurationInNanoSeconds(const uint64_t elapsedCycles) {
    return static_cast<double>(elapsedCycles) / CPU_FREQUENCY_GHZ;
  }

  inline void Start() {
    startCycles = GetCycles();
  }

  inline void Stop() {
    endCycles = GetCycles();
  }

  inline static uint64_t GetUsec() {
    struct timeval tv;
    gettimeofday(&tv, nullptr);
    return static_cast<uint64_t>(tv.tv_sec) * 1000000l + tv.tv_usec;
  }

  inline static uint64_t GetCycles() {
#if IS_X86_64
    return __rdtsc();
#elif IS_ARM8_64
    uint64_t counter_value;
    asm volatile("mrs %x0, cntvct_el0" : "=r"(counter_value));
    return counter_value * SCALING_FACTOR;
#else
#error Need cycle counter defines for your architecture
#endif
  }

#if IS_ARM8_64
  inline static uint64_t GetFreq() {
    uint64_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
    return freq / 1000000;
  }
#endif
};
#endif // __CYCLECOUNTERS_H__
