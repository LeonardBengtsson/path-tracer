//
// Created by Leonard on 2025-01-24.
//

#ifndef LIGHTSPECTRUM_H
#define LIGHTSPECTRUM_H
#include "../path_tracing/LightTransformation.h"



class LightSpectrum {
private:
    double red, green, blue;

    LightSpectrum(double, double, double);

    static double gamma(double u);
    static double inv_gamma(double u);

public:
    explicit LightSpectrum();

    static LightSpectrum from_rgb(double, double, double, double);

    void to_rgb(double[3], double = 1) const;

    void add_modified(const LightSpectrum&, const LightTransformation&, double = 1);
    void scale(double);

    LightSpectrum scaled(double) const;
};



#endif //LIGHTSPECTRUM_H
