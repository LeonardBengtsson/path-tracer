//
// Created by Leonard on 2025-01-22.
//

#include <cmath>
#include <cstdint>
#include <iostream>
#include <fstream>
#include "stb_image_write.h"

#define WIDTH 1920
#define HEIGHT 1080

typedef uint32_t Rgba;

void fill_buffer(Rgba *rgb, const uint32_t size_x, const uint32_t size_y, Rgba(*frag_shader)(double, double)) {
    uint32_t index = 0;
    for (uint32_t j = 0; j < size_y; j++) {
        const double y = static_cast<double>(j) / size_y;
        for (uint32_t i = 0; i < size_x; i++) {
            const double x = static_cast<double>(i) / size_x;
            rgb[index] = frag_shader(x, y);
            index++;
        }
    }
}

void unpack_argb(const Rgba rgb, uint8_t out[4]) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    out[0] = static_cast<uint8_t>(rgb & 0xff);
    out[1] = static_cast<uint8_t>((rgb >> 8) & 0xff);
    out[2] = static_cast<uint8_t>((rgb >> 16) & 0xff);
    out[3] = static_cast<uint8_t>((rgb >> 24) & 0xff);
#else
    out[0] = static_cast<uint8_t>((rgb >> 24) & 0xff);
    out[1] = static_cast<uint8_t>((rgb >> 16) & 0xff);
    out[2] = static_cast<uint8_t>((rgb >> 8) & 0xff);
    out[3] = static_cast<uint8_t>(rgb & 0xff);
#endif
}

Rgba pack_rgba(const uint8_t r, const uint8_t g, const uint8_t b, const uint8_t a) {
#if __BYTE_ORDER__ == __ORDER_LITTLE_ENDIAN__
    return r | (g << 8) | (b << 16) | (a << 24);
#else
    return (r << 24) | (g << 16) | (b << 8) | a;
#endif
}

Rgba pack_rgba_d(const double r, const double g, const double b, const double a) {
    return pack_rgba(
        static_cast<uint8_t>(255 * r),
        static_cast<uint8_t>(255 * g),
        static_cast<uint8_t>(255 * b),
        static_cast<uint8_t>(255 * a)
    );
}

void write_ppm(const char *path, const Rgba *pixels, const uint32_t size_x, const uint32_t size_y) {
    std::ofstream out;
    std::remove(path);
    out.open(path);
    out << "P3\n" + std::to_string(size_x) + " " + std::to_string(size_y) + "\n255\n";

    uint32_t index = 0;
    for (uint32_t j = 0; j < size_y; j++) {
        for (uint32_t i = 0; i < size_x; i++) {
            uint8_t rgb[4];
            unpack_argb(pixels[index], rgb);
            out << std::to_string(rgb[1]) + " " + std::to_string(rgb[2]) + " " + std::to_string(rgb[3]) + " ";
            index++;
        }
        out << "\n";
    }
    out.close();
}

int main() {
    Rgba *buffer = new Rgba[WIDTH * HEIGHT];
    fill_buffer(buffer, WIDTH, HEIGHT, [](const double u, const double v) -> Rgba {
        double y = std::fmod(100 * u, 1) < 0.5 ^ std::fmod(100 * v, 1) < 0.5 ? 1 : 0;
        return pack_rgba_d(y, y, y, 1);
    });

    const char *OUTPUT = "out.png";

    std::remove(OUTPUT);
    stbi_write_png(OUTPUT, WIDTH, HEIGHT, 4, buffer, 0);

    delete buffer;

    return 0;
}