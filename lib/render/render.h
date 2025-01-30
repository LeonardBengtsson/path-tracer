//
// Created by Leonard on 2025-01-25.
//

#ifndef RENDER_H
#define RENDER_H
#include "RenderBuffer.h"
#include "../math/Matrix4x4.h"
#include "../path_tracing/RayStack.h"

namespace render {
    void render(const Scene* scene, const RenderBuffer&, const Matrix4x4&, double);
}

#endif //RENDER_H
