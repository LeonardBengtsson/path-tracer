//
// Created by Leonard on 2025-01-24.
//

#include "RenderBuffer.h"

#include <filesystem>
#include <format>
#include <fstream>

#include "../stb_image_write.h"
#include "../render/color_util.h"
#include "../util/string_util.h"



RenderBuffer::RenderBuffer(const size_t size_x, const size_t size_y, const size_t sample_grid_size)
  : size_x(size_x), size_y(size_y), sample_grid_size(sample_grid_size),
    buffer(std::make_unique<color_util::Rgba[]>(size_x * size_y)) {}

void RenderBuffer::render(const Scene &scene, const Matrix4x4 &projective_matrix, const double v_fov) const {
    auto ray_stack = RayStack(projective_matrix);

    const double sample_factor = 1.0 / (sample_grid_size * sample_grid_size);
    const double sample_u_offset = 1.0 / (size_x * sample_grid_size);
    const double sample_v_offset = 1.0 / (size_y * sample_grid_size);

    size_t index = 0;
    for (size_t j = 0; j < size_y; j++) {
        const double pixel_v = static_cast<double>(j) / size_y;
        for (size_t i = 0; i < size_x; i++) {
            const double pixel_u = static_cast<double>(i) / size_x;

            auto incoming_light = LightSpectrum();
            for (size_t m = 0; m < sample_grid_size; m++) {
                for (size_t n = 0; n < sample_grid_size; n++) {
                    const double u = pixel_u + m * sample_u_offset;
                    const double v = pixel_v + n * sample_v_offset;
                    ray_stack.init(v_fov, static_cast<double>(size_x) / static_cast<double>(size_y), {u, v});
                    LightSpectrum light = ray_stack.trace(scene);
                    incoming_light.add_modified(light, LightTransformation::IDENTITY, sample_factor);
                }
            }

            double rgb[3];
            incoming_light.to_rgb(rgb);
            buffer[index] = color_util::pack_rgb_d(rgb);

            ray_stack.clear();
            index++;
        }
    }
}

std::string RenderBuffer::write_png(const std::string &output_path) const {
    const std::filesystem::path path(output_path);
    if (path.has_parent_path())
        create_directories(path.parent_path());
    const std::string valid_path = string_util::get_valid_path(path);

    // use external library
    stbi_write_png(valid_path.c_str(), size_x, size_y, 4, buffer.get(), 0);
    return valid_path;
}

std::string RenderBuffer::write_ppm(const std::string &output_path) const {
    const std::filesystem::path path(output_path);
    if (path.has_parent_path())
        create_directories(path.parent_path());
    const std::string valid_path = string_util::get_valid_path(path);

    std::ofstream out;
    out.open(valid_path);
    out << std::format("P3\n{} {}\n255\n", size_x, size_y);

    size_t index = 0;
    uint8_t rgba[4];
    for (size_t j = 0; j < size_y; j++) {
        for (size_t i = 0; i < size_x; i++) {
            color_util::unpack_rgba(buffer[index], rgba);
            out << std::format("{} {} {} ", rgba[0], rgba[1], rgba[2]);
            index++;
        }
        out << "\n";
    }
    out.close();

    return valid_path;
}
