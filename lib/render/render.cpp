//
// Created by Leonard on 2025-01-25.
//

#include "render.h"

#include "color_util.h"

namespace render {
    void render(const Scene &scene, const RenderBuffer &buffer, const Matrix4x4 &projectionMatrix, const double h_fov) {
        RayStack stack = RayStack(projectionMatrix);
        const Vec2 fov = {h_fov, static_cast<double>(buffer.size_y) / buffer.size_x * h_fov};

        uint32_t buffer_index = 0;
        for (uint32_t y = 0; y < buffer.size_y; y++) {
            double v = static_cast<double>(y) / buffer.size_y;
            for (uint32_t x = 0; x < buffer.size_x; x++) {
                double u = static_cast<double>(x) / buffer.size_x;

                stack.start(fov, {u, v});
                const LightSpectrum light = stack.trace(scene);

                double rgba[3];
                light.to_rgb(rgba);
                buffer.buffer[buffer_index] = color_util::pack_rgba_d(rgba);

                stack.clear();
                buffer_index++;
            }
        }
    }
}
