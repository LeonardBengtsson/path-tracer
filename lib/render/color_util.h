//
// Created by Leonard on 2025-01-24.
//

#ifndef COLOR_UTIL_H
#define COLOR_UTIL_H

#include <cstdint>



namespace color_util {
    typedef uint32_t Rgba;

    inline void unpack_rgba(const Rgba rgb, uint8_t out[4]) {
        if constexpr (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) {
            out[0] = static_cast<uint8_t>(rgb & 0xff);
            out[1] = static_cast<uint8_t>((rgb >> 8) & 0xff);
            out[2] = static_cast<uint8_t>((rgb >> 16) & 0xff);
            out[3] = static_cast<uint8_t>((rgb >> 24) & 0xff);
        } else {
            out[0] = static_cast<uint8_t>((rgb >> 24) & 0xff);
            out[1] = static_cast<uint8_t>((rgb >> 16) & 0xff);
            out[2] = static_cast<uint8_t>((rgb >> 8) & 0xff);
            out[3] = static_cast<uint8_t>(rgb & 0xff);
        }
    }

    inline Rgba pack_rgba_i(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
        if constexpr (__BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__) {
            return r | (g << 8) | (b << 16) | (a << 24);
        } else {
            return (r << 24) | (g << 16) | (b << 8) | a;
        }
    }

    inline Rgba pack_rgba_d(const double r, const double g, const double b, const double a) {
        return pack_rgba_i(
            static_cast<uint8_t>(255 * r),
            static_cast<uint8_t>(255 * g),
            static_cast<uint8_t>(255 * b),
            static_cast<uint8_t>(255 * a)
        );
    }

    inline Rgba pack_rgb_d(const double rgb[3]) {
        return pack_rgba_d(rgb[0], rgb[1], rgb[2], 1);
    }

    inline Rgba pack_rgba_d(const double rgba[4]) {
        return pack_rgba_d(rgba[0], rgba[1], rgba[2], rgba[3]);
    }
}



#endif //COLOR_UTIL_H
