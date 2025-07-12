//
// Created by Leonard on 2025-01-22.
//

#include <format>
#include <filesystem>
#include <iostream>

#include "scenes.h"
#include "../lib/render/RenderBuffer.h"
#include "../lib/scene/Scene.h"
#include "../lib/config.h"
#include "../lib/util/time_util.h"

int main() {
    auto scene = Scene(LightSpectrum());
    auto projective_matrix = Matrix4x4::IDENT;
    scenes::init_glass_grid(scene, projective_matrix);

    if constexpr (ENABLE_BVH_OPTIMIZATION) {
        time_util::start_stopwatch();
        scene.init();
        std::string init_time_string = time_util::format_stopwatch();
        std::cout << std::format("Initialized BVH in {}", init_time_string) << std::endl;
    }

    const auto buffer = std::make_unique<RenderBuffer>(OUTPUT_WIDTH, OUTPUT_HEIGHT, SAMPLE_GRID_SIZE);

    time_util::start_stopwatch();
    buffer->render(scene, projective_matrix, (V_FOV_DEGREES) / 180.0 * std::numbers::pi);
    std::string render_time_string = time_util::format_stopwatch();
    std::cout << std::format("Rendered scene in {}", render_time_string) << std::endl;

    const std::string output_path = buffer->write_png("../out/out.png");
    std::cout << std::format("Output file to [{}]", output_path) << std::endl;
}