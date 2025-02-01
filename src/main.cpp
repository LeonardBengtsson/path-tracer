//
// Created by Leonard on 2025-01-22.
//

#include <cstdint>
#include <format>
#include <filesystem>
#include <iostream>

#include "../lib/render/RenderBuffer.h"
#include "../lib/scene/Scene.h"
#include "../lib/scene/SphereObject.h"

#define OUTPUT_WIDTH 1920
#define OUTPUT_HEIGHT 1080

#define DEBUG
#define DEPTH_LIMIT 20

int main() {
    const auto cyan_material = Material(0, .5, LightSpectrum::from_rgb(0, 1, 1, 1));
    const auto magenta_material = Material(0, .5, LightSpectrum::from_rgb(1, 0, 1, 1));
    const auto yellow_material = Material(0, .5, LightSpectrum::from_rgb(1, 1, 0, 1));

    const auto transparent_reflective_material = Material(.5, .5, LightSpectrum());

    auto scene = Scene(LightSpectrum());

    constexpr int M = 2;
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

    auto projective_matrix = Matrix4x4(
        Matrix3x3::from_forward_down_vecs(
            Vec3(1, 2, 3).norm(),
            Vec3::Y
        ),
        Vec3(-3, -6, -9)
    );

    auto buffer = new RenderBuffer(OUTPUT_WIDTH, OUTPUT_HEIGHT);
    buffer->render(scene, projective_matrix, 0.35 * std::numbers::pi);
    const std::string output_path = buffer->write_png("../out/out.png");
    std::cout << "Output file to: " << output_path;
    delete buffer;

    return 0;
}