#include "timer.hpp"

Timer::Timer()
{
}

Timer::~Timer()
{
}

void Timer::start()
{
    mStart = clock_t::now();
}

void Timer::reset()
{
    mStart = clock_t::now();
}

double Timer::elapsed()
{
    return std::chrono::duration_cast<duration_t>(clock_t::now() - mStart).count();
}