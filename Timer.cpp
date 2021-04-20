#include "Timer.h"

#include <chrono>

double Timer::now() {
    static auto start = std::chrono::system_clock::now(); // Just say t=0 is the first time this is called
    return ((std::chrono::duration<double>)(std::chrono::system_clock::now() - start)).count();
}
