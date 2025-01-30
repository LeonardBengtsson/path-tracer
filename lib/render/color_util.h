//
// Created by Leonard on 2025-01-24.
//

#ifndef COLOR_UTIL_H
#define COLOR_UTIL_H
#include <cstdint>

namespace color_util {
    typedef uint32_t Rgba;

    void unpack_rgba(Rgba, uint8_t[4]);

    Rgba pack_rgba(uint8_t, uint8_t, uint8_t, uint8_t);

    Rgba pack_rgba_d(double, double, double, double);

    Rgba pack_rgb_d(const double[3]);

    Rgba pack_rgba_d(const double[4]);
}

#endif //COLOR_UTIL_H
