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

    const auto start = std::chrono::high_resolution_clock::now();
    buffer->render(scene, projective_matrix, 0.35 * std::numbers::pi);
    const auto duration = std::chrono::high_resolution_clock::now() - start;

    const auto micros = std::chrono::duration_cast<std::chrono::microseconds>(duration).count();
    std::string time_string;
    if (micros > 60000000) {
        time_string = std::format("{} min {} s", micros / 60000000, (micros % 60000000) / 1000000);
    } else if (micros > 1000000) {
        time_string = std::format("{:.2f} s", static_cast<double>(micros) / 1000000);
    } else if (micros > 1000) {
        time_string = std::format("{:.2f} ms", static_cast<double>(micros) / 1000);
    } else {
        time_string = std::format("{} μs", micros);
    }

    const std::string output_path = buffer->write_png("../out/out.png");
    std::cout << std::format("Rendered scene and output file to [{}]. Time taken: {}", output_path, time_string);

    delete buffer;

    return 0;
}