//
// Created by Leonard on 2025-02-01.
//

#ifndef SCENES_H
#define SCENES_H

#include "../lib/material/Material.h"



namespace scenes {
    void init_refraction_demo(Scene &scene, Matrix4x4 &projective_matrix);

    void init_translucency_demo(Scene &scene, Matrix4x4 &projective_matrix);

    void init_colored_sphere_grid(Scene &scene, Matrix4x4 &projective_matrix);

    void init_glass_grid(Scene &scene, Matrix4x4 &projective_matrix);

    void init_box_grid(Scene &scene, Matrix4x4 &projective_matrix);

    void init_glass_boxes(Scene &scene, Matrix4x4 &projective_matrix);

    void init_pyramid_mesh(Scene &scene, Matrix4x4 &projective_matrix);

    bool init_single_obj(Scene &scene, Matrix4x4 &projective_matrix, const std::string &obj_path);
}

#endif //SCENES_H
