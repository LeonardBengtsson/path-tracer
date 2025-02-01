//
// Created by Leonard on 2025-02-01.
//

#ifndef SCENES_H
#define SCENES_H
#include "../lib/material/Material.h"

namespace scenes {
    void init_refraction_demo(Scene &scene, Matrix4x4 &projective_matrix);

    void init_colored_grid(Scene &scene, Matrix4x4 &projective_matrix);

    void init_glass_grid(Scene &scene, Matrix4x4 &projective_matrix);
}

#endif //SCENES_H
