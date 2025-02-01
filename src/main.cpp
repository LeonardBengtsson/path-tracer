//
// Created by Leonard on 2025-01-22.
//

#include <cstdint>
#include <format>
#include <filesystem>
#include <iostream>

#define DEBUG

#include "scenes.h"
#include "../lib/render/RenderBuffer.h"
#include "../lib/scene/Scene.h"

#define OUTPUT_WIDTH 1920
#define OUTPUT_HEIGHT 1080

#define DEPTH_LIMIT 20
#define SAMPLE_GRID_SIZE 2

int main() {
    auto scene = Scene(LightSpectrum());
    auto projective_matrix = Matrix4x4::IDENT;
    scenes::init_glass_grid(scene, projective_matrix);

    const auto buffer = new RenderBuffer(OUTPUT_WIDTH, OUTPUT_HEIGHT, SAMPLE_GRID_SIZE);
    buffer->render(scene, projective_matrix, 0.35 * std::numbers::pi);

    const std::string output_path = buffer->write_png("../out/out.png");
    std::cout << "Output file to: " << output_path;

    delete buffer;

    return 0;
}