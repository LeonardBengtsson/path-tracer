//
// Created by Leonard on 2025-01-24.
//

#include "RenderBuffer.h"

#include <filesystem>
#include <format>
#include <fstream>

#include "../stb_image_write.h"
#include "../render/color_util.h"

RenderBuffer::RenderBuffer(const size_t size_x, const size_t size_y)
  : size_x(size_x), size_y(size_y), buffer(new uint32_t[size_x * size_y]) {}

RenderBuffer::~RenderBuffer() {
    delete buffer;
}

void RenderBuffer::render(const Scene &scene, const Matrix4x4 &projective_matrix, const double v_fov) const {
    auto ray_stack = RayStack(projective_matrix);

    uint32_t index = 0;
    for (uint32_t j = 0; j < size_y; j++) {
        const double v = static_cast<double>(j) / size_y;
        for (uint32_t i = 0; i < size_x; i++) {
            const double u = static_cast<double>(i) / size_x;

            ray_stack.start(v_fov, static_cast<double>(size_x) / static_cast<double>(size_y), {u, v});
            LightSpectrum light = ray_stack.trace(scene);

            double rgb[3];
            light.to_rgb(rgb);
            buffer[index] = color_util::pack_rgb_d(rgb);

            ray_stack.clear();
            index++;
        }
    }
}

std::string get_valid_path(const std::filesystem::path &path) {
    const std::string stem = path.stem().string();
    const std::string extension = path.extension().string();
    const std::string parent = path.has_parent_path()
        ? path.parent_path().string() + "/"
        : "";

    int counter = 0;
    std::string complete_path = path.string();
    while (std::filesystem::exists(complete_path)) {
        complete_path = std::format("{}{}-{}{}", parent, stem, counter, extension);
        counter++;
    }
    return complete_path;
}

std::string RenderBuffer::write_png(const std::string &output_path) const {
    const std::filesystem::path path(output_path);
    if (path.has_parent_path())
        create_directories(path.parent_path());
    const std::string valid_path = get_valid_path(path);

    stbi_write_png(valid_path.c_str(), size_x, size_y, 4, buffer, 0);
    return valid_path;
}

std::string RenderBuffer::write_ppm(const std::string &output_path) const {
    const std::filesystem::path path(output_path);
    if (path.has_parent_path())
        create_directories(path.parent_path());
    const std::string valid_path = get_valid_path(path);

    std::ofstream out;
    out.open(valid_path);
    out << "P3\n" + std::to_string(size_x) + " " + std::to_string(size_y) + "\n255\n";

    size_t index = 0;
    for (size_t j = 0; j < size_y; j++) {
        for (size_t i = 0; i < size_x; i++) {
            uint8_t rgba[4];
            color_util::unpack_rgba(buffer[index], rgba);
            out << std::to_string(rgba[0]) + " " + std::to_string(rgba[1]) + " " + std::to_string(rgba[2]) + " ";
            index++;
        }
        out << "\n";
    }
    out.close();

    return valid_path;
}
