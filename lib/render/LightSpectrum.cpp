//
// Created by Leonard on 2025-01-24.
//

#include "LightSpectrum.h"

#include <cmath>

LightSpectrum::LightSpectrum() : red(0), green(0), blue(0) {}

LightSpectrum::LightSpectrum(const double red, const double green, const double blue) : red(red), green(green), blue(blue) {}

LightSpectrum LightSpectrum::from_rgb(const double red, const double green, const double blue, const double intensity) {
    return {
        intensity * gamma(red),
        intensity * gamma(green),
        intensity * gamma(blue)
    };
}

void LightSpectrum::to_rgb(double out[3], const double reference_intensity) const {
    out[0] = inv_gamma(red / reference_intensity);
    out[1] = inv_gamma(green / reference_intensity);
    out[2] = inv_gamma(blue / reference_intensity);
}

double LightSpectrum::gamma(const double u) {
    // see https://en.wikipedia.org/wiki/SRGB
    constexpr double U = 0.04045;
    constexpr double A = 12.92;
    constexpr double C = 0.055;
    constexpr double Gamma = 2.4;
    if (u <= U) {
        return u / A;
    } else {
        return std::pow((u + C) / (1 + C), Gamma);
    }
}

double LightSpectrum::inv_gamma(const double v) {
    // see https://en.wikipedia.org/wiki/SRGB
    constexpr double V = 0.0031308;
    constexpr double A = 12.92;
    constexpr double C = 0.055;
    constexpr double Gamma = 2.4;
    if (v <= V) {
        return A * v;
    } else {
        return (1 + C) * std::pow(v, 1 / Gamma) - C;
    }
}

void LightSpectrum::add_modified(const LightSpectrum &source, const LightTransformation &modifier, const double factor) {
    red += source.red * modifier.intensity_factor * factor;
    green += source.green * modifier.intensity_factor * factor;
    blue += source.blue * modifier.intensity_factor * factor;
}

void LightSpectrum::scale(const double d) {
    red *= d;
    green *= d;
    blue *= d;
}

LightSpectrum LightSpectrum::scaled(const double d) const {
    return {red * d, green * d, blue * d};
}

