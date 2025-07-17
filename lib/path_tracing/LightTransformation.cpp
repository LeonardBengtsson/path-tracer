//
// Created by Leonard on 2025-01-25.
//

#include "LightTransformation.h"

#include <cassert>

#include "../config.h"



const LightTransformation LightTransformation::IDENTITY = LightTransformation(1);

LightTransformation::LightTransformation(const double intensity_factor)
  : intensity_factor(intensity_factor)
{
    if constexpr (DEBUG_ASSERTS)
        assert(intensity_factor >= 0);
}

LightTransformation LightTransformation::combine(const LightTransformation &other) const {
    return LightTransformation(intensity_factor * other.intensity_factor);
}

double LightTransformation::get_contribution() const {
    return intensity_factor;
}

LightTransformation LightTransformation::of_factor(const double factor) {
    if constexpr (DEBUG_ASSERTS)
        assert(factor >= 0);
    return LightTransformation(factor);
}
