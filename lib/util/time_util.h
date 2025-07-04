//
// Created by Leonard on 2025-06-29.
//

#ifndef TIMER_UTIL_H
#define TIMER_UTIL_H

#include <chrono>

#include "string_util.h"

using TimePoint = std::chrono::time_point<std::chrono::system_clock>;
using Duration = std::chrono::duration<long long, std::ratio<1, 1000000000>>;

inline TimePoint start;

inline void start_stopwatch() {
    start = std::chrono::high_resolution_clock::now();
}

inline Duration end_stopwatch() {
    return std::chrono::high_resolution_clock::now() - start;
}

inline std::string format_stopwatch() {
    const auto duration = end_stopwatch();
    const auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    return format_duration(micros);
}

#endif //TIMER_UTIL_H
