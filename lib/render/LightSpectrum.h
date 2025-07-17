//
// Created by Leonard on 2025-01-24.
//

#ifndef LIGHTSPECTRUM_H
#define LIGHTSPECTRUM_H

#include "../path_tracing/LightTransformation.h"



class LightTransformation;

/**
 * Abstractly represents a light distribution.
 */
class LightSpectrum {
private:
    double red, green, blue;

    LightSpectrum(double red, double green, double blue);

    /**
     * @return Gamma correction applied to the intensity value @c u.
     */
    static double gamma(double u);

    /**
     * @return Inverse gamma correction applied to the intensity value @c u.
     */
    static double inv_gamma(double u);

public:
    static const LightSpectrum BLACK;

    explicit LightSpectrum();

    static LightSpectrum from_rgb(double red, double green, double blue, double intensity);

    void to_rgb(double out[3], double reference_intensity = 1) const;

    void add_modified(const LightSpectrum &source, const LightTransformation &transformation, double factor = 1);

    void scale(double d);

    LightSpectrum scaled(double d) const;
};



#endif //LIGHTSPECTRUM_H
