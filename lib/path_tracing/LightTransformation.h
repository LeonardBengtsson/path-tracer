//
// Created by Leonard on 2025-01-25.
//

#ifndef LIGHTTRANSFORMATION_H
#define LIGHTTRANSFORMATION_H

#include "../render/LightSpectrum.h"



class LightSpectrum;

/**
 * Represents how a light ray will be transformed when passing through one or more optical elements.
 */
class LightTransformation {
private:
    friend LightSpectrum;

    explicit LightTransformation(double intensity_factor);

    double intensity_factor;

public:
    static const LightTransformation IDENTITY;

    /**
     * @return The light transformation that has the same effect as applying @c other, and then @c this.
     */
    LightTransformation combine(const LightTransformation &other) const;

    /**
     * @return A measure of how much light that is transformed by this object will contribute to the final sample.
     */
    double get_contribution() const;

    /**
     * @return A light transformation that corresponds to attenuating light by the given factor.
     */
    static LightTransformation of_factor(double factor);
};



#endif //LIGHTTRANSFORMATION_H
