//
// Created by Leonard on 2025-07-16.
//

#ifndef DEBUG_UTIL_H
#define DEBUG_UTIL_H

#include "../math/Vec3.h"



namespace debug_util {
    /**
     * Assert that @c v is roughly unit length.
     */
    void assert_unit(const Vec3 &v);
}



#endif //DEBUG_UTIL_H
