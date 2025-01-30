//
// Created by Leonard on 2025-01-22.
//

#include <cmath>
#include <cstdint>
#include <format>
#include <filesystem>
#include <iostream>

#include "stb_image_write.h"
#include "../lib/render/color_util.h"
#include "../lib/scene/Scene.h"
#include "../lib/scene/SphereObject.h"

#define OUTPUT_HEIGHT 2160
#define ASPECT_RATIO 16 / 9
#define OUTPUT_WIDTH (OUTPUT_HEIGHT * ASPECT_RATIO)

#define DEBUG
#define DEPTH_LIMIT 200

int main() {
    auto *buffer = new color_util::Rgba[OUTPUT_WIDTH * OUTPUT_HEIGHT];

    const auto cyan_material = Material(0, .5, LightSpectrum::from_rgb(0, 1, 1, 1));
    const auto magenta_material = Material(0, .5, LightSpectrum::from_rgb(1, 0, 1, 1));
    const auto yellow_material = Material(0, .5, LightSpectrum::from_rgb(1, 1, 0, 1));

    const auto white_emissive_material = Material(0, 0, LightSpectrum::from_rgb(1, 1, 1, 1));
    const auto transparent_reflective_material = Material(.5, .5, LightSpectrum());

    auto scene = Scene(LightSpectrum::from_rgb(0, 0, 0, 1));

    constexpr int M = 3;
    for (int i = -M; i <= M; i++) {
        for (int j = -M; j <= M; j++) {
            for (int k = -M; k <= M; k++) {
                const int mat = rand() % 3;
                const Material *material;
                if ((i + j + k) % 2 == 0) {
                    material = &transparent_reflective_material;
                } else if (mat == 0) {
                    material = &cyan_material;
                } else if (mat == 1) {
                    material = &magenta_material;
                } else {
                    material = &yellow_material;
                }
                scene.add_object(new SphereObject(Vec3(i, j, k), .35, material));
            }
        }
    }

    scene.add_object(new SphereObject(Vec3(0, 1000100, 0), 1000000, &white_emissive_material));

    auto projective_matrix = Matrix4x4(
        Matrix3x3::from_forward_down_vecs(
            Vec3(1, 2, 3).norm(),
            Vec3::Y
        ),
        Vec3(-4, -8, -12)
    );

    auto ray_stack = RayStack(projective_matrix);
    const Vec2 fov = {0.35 * std::numbers::pi, 0.35 * std::numbers::pi * OUTPUT_HEIGHT / OUTPUT_WIDTH};

    uint32_t index = 0;
    for (uint32_t j = 0; j < OUTPUT_HEIGHT; j++) {
        const double v = static_cast<double>(j) / OUTPUT_HEIGHT;
        for (uint32_t i = 0; i < OUTPUT_WIDTH; i++) {
            const double u = static_cast<double>(i) / OUTPUT_WIDTH;

            ray_stack.start(fov, {u, v});
            LightSpectrum light = ray_stack.trace(scene);

            double rgb[3];
            light.to_rgb(rgb);
            buffer[index] = color_util::pack_rgb_d(rgb);

            ray_stack.clear();
            index++;
        }
    }

    const auto directory_name = std::string("../out/");
    const auto file_name = directory_name + std::string("out");
    const auto file_extension = std::string(".png");
    int counter = 0;
    std::string complete_file_name = file_name + file_extension;

    std::filesystem::create_directory(directory_name);
    while (std::filesystem::exists(complete_file_name)) {
        complete_file_name = std::format("{}-{}{}", file_name, counter, file_extension);
        counter++;
    }
    stbi_write_png(complete_file_name.c_str(), OUTPUT_WIDTH, OUTPUT_HEIGHT, 4, buffer, 0);

    delete[] buffer;

    std::cout << "Output file to: " << complete_file_name;

    return 0;
}