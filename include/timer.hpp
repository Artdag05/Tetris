#pragma once
#include <chrono>

class Timer
{
public:
    Timer();
    ~Timer();
    void start();
    void reset();
    double elapsed(); // returns time from start point
    
private:
    using clock_t = std::chrono::high_resolution_clock;
    using duration_t = std::chrono::duration<double>;
    clock_t::time_point mStart; 
};