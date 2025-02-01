//
// Created by Leonard on 2025-01-24.
//

#ifndef RENDERBUFFER_H
#define RENDERBUFFER_H

#include "color_util.h"
#include "../math/Matrix4x4.h"
#include "../scene/Scene.h"


class RenderBuffer {
private:
    const size_t size_x, size_y;
    color_util::Rgba * const buffer;

public:
    RenderBuffer(size_t size_x, size_t size_y);

    ~RenderBuffer();

    void render(const Scene &scene, const Matrix4x4 &projective_matrix, double v_fov) const;

    std::string write_png(const std::string &output_path) const;

    std::string write_ppm(const std::string &output_path) const;
};



#endif //RENDERBUFFER_H
