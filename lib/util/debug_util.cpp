//
// Created by Leonard on 2025-07-16.
//

#include "debug_util.h"

#include <cassert>

#include "../math/math_util.h"



void debug_util::assert_unit(const Vec3 &v) {
    // Let |v| = 1 + x
    // Then, abs(|v|² - 1) = abs(x² + 2x) ≈ abs(2x)
    assert(math_util::almost_zero(std::abs(v.sq() - 1) * .5));
}
