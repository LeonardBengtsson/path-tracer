//
// Created by Leonard on 2025-01-22.
//

#include <format>
#include <filesystem>
#include <iostream>

#define DEBUG

#include "../lib/render/RenderBuffer.h"
#include "../lib/scene/Scene.h"
#include "../lib/scene/SphereObject.h"

#define OUTPUT_WIDTH 1920
#define OUTPUT_HEIGHT 1080

#define DEPTH_LIMIT 20
#define SAMPLE_GRID_SIZE 2

int main() {
    const auto white_emissive_material = Material(0, 0, 1, LightSpectrum::from_rgb(1, 1, 1, 1));

    const auto cyan_material = Material(.5, 0, 1, LightSpectrum::from_rgb(0, 1, 1, 1));
    const auto magenta_material = Material(.5, 0, 1, LightSpectrum::from_rgb(1, 0, 1, 1));

    const auto transparent_reflective_material = Material(.5, .4, 1.2, LightSpectrum::from_rgb(1, 1, 1, 1));

    auto scene = Scene(LightSpectrum());

    scene.add_object(new SphereObject(Vec3(0, 1000020, 0), 1000000, &white_emissive_material));
    scene.add_object(new SphereObject(Vec3(-5, 0, 0), 4, &magenta_material));
    scene.add_object(new SphereObject(Vec3(5, 0, 0), 4, &cyan_material));
    scene.add_object(new SphereObject(Vec3(-2, -3, -7), 1.5, &transparent_reflective_material));
    const auto projective_matrix = Matrix4x4(
        Matrix3x3::from_forward_down_vecs(
            Vec3(1, 2, 3).norm(),
            Vec3::Y
        ),
        Vec3(-3, -6, -9)
    );

    auto buffer = new RenderBuffer(OUTPUT_WIDTH, OUTPUT_HEIGHT, SAMPLE_GRID_SIZE);
    buffer->render(scene, projective_matrix, 0.35 * std::numbers::pi);
    const std::string output_path = buffer->write_png("../out/out.png");
    std::cout << "Output file to: " << output_path;
    delete buffer;

    return 0;
}