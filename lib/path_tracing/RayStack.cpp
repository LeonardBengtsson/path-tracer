//
// Created by Leonard on 2025-01-24.
//

#include "RayStack.h"

#include <cassert>
#include <cmath>
#include <iostream>
#include <string>
#include <utility>

#include "../math/math_util.h"
#include "../math/Matrix4x4.h"
#include "../math/Vec2.h"
#include "../config.h"



RayStack::RayStack(const Matrix4x4 &projection_matrix)
  : projection_matrix(projection_matrix),
    solid_angle(0),
    current_depth(0),
    current_distance(0),
    current_transformation(LightTransformation::IDENTITY){}

void RayStack::init(const double v_fov, const double aspect_ratio, const Vec2 screen_pos) {
    if constexpr (DEBUG_ASSERTS) {
        assert(v_fov >= 0);
        assert(aspect_ratio > 0);
        assert(screen_pos.x >= 0 && screen_pos.x <= 1);
        assert(screen_pos.y >= 0 && screen_pos.y <= 1);
    }
    const double corner_y = std::tan(v_fov * .5);
    const Vec2 corner = {aspect_ratio * corner_y, corner_y};
    const Vec3 dir = {math_util::lerp(screen_pos, -corner, corner), 1};
    solid_angle = 1 / dir.sq();
    stack.emplace(projection_matrix.apply(Ray(Vec3::ZERO, dir.norm())), 0, 0, LightTransformation::IDENTITY);
}

void RayStack::clear() {
    while (!stack.empty())
        stack.pop();
}

void RayStack::push(const Ray &ray, const LightTransformation &light_transformation, const double delta_dist,
    const size_t additional_depth)
{
    if constexpr (DEBUG_ASSERTS)
        assert(delta_dist >= 0);
    const size_t depth = current_depth + additional_depth;
    const LightTransformation transformation = current_transformation.combine(light_transformation);
    if (depth <= DEPTH_LIMIT && transformation.get_contribution() >= MIN_RAY_CONTRIBUTION) {
        stack.emplace(ray, depth, current_distance + delta_dist, transformation);
    }
}

LightSpectrum RayStack::trace(const Scene &scene) {
    auto result = LightSpectrum();
    while (!stack.empty()) {
        const Entry &node = stack.top();

        double distance_traveled = std::numeric_limits<double>::max();
        Vec3 hit_position = Vec3::ZERO;
        Vec3 hit_normal_unnormalized = Vec3::ZERO;
        const std::unique_ptr<SceneObject> *hit_object_ptr = nullptr;

        scene.ray_cast(node.ray, distance_traveled, hit_position, hit_normal_unnormalized, hit_object_ptr);
        if (hit_object_ptr == nullptr) {
            // none hit
            result.add_modified(scene.ambient_light, node.light_transformation);
            stack.pop();
            continue;
        }
        const std::unique_ptr<SceneObject> &hit_object = *hit_object_ptr;

        if (node.depth >= DEPTH_LIMIT) {
            // reached depth limit
            stack.pop();
            continue;
        }

        // evaluate the light path from the hit location, and add any further paths to the stack through eval_path
        const Ray incident_ray = {hit_position, node.ray.dir};
        current_depth = node.depth + 1;
        current_distance = node.distance + distance_traveled;
        current_transformation = node.light_transformation;

        stack.pop();
        const LightSpectrum emitted = hit_object->eval_path(*this, incident_ray, hit_normal_unnormalized.norm());
        result.add_modified(emitted, current_transformation);
    }
    return result;
}

RayStack::Entry::Entry(Ray ray, const size_t depth, const double distance,
    const LightTransformation &light_transformation
)
  : ray(std::move(ray)), depth(depth), distance(distance), light_transformation(light_transformation)
{
    if constexpr (DEBUG_ASSERTS)
        assert(distance >= 0);
}
