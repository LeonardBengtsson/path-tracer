//
// Created by Leonard on 2025-01-25.
//

#include "LightTransformation.h"

const LightTransformation LightTransformation::IDENTITY = LightTransformation(1);

LightTransformation::LightTransformation(const double intensity_factor) : intensity_factor(intensity_factor) {}

LightTransformation LightTransformation::combine(const LightTransformation &other) const {
    return LightTransformation(intensity_factor * other.intensity_factor);
}

LightTransformation LightTransformation::of_factor(const double factor) {
    return LightTransformation(factor);
}
