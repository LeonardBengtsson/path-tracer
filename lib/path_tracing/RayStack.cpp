//
// Created by Leonard on 2025-01-24.
//

#include "RayStack.h"

#include <cmath>
#include <iostream>
#include <string>
#include <utility>

#include "../math/math_util.h"
#include "../math/Matrix4x4.h"
#include "../math/Vec2.h"
#include "../config.h"

#ifndef DEPTH_LIMIT
#define DEPTH_LIMIT 5
#endif

RayStack::RayStack(const Matrix4x4 &projection_matrix)
  : projection_matrix(projection_matrix),
    solid_angle(0),
    current_depth(0),
    current_distance(0),
    current_transformation(LightTransformation::IDENTITY){}

void RayStack::start(const double v_fov, const double aspect_ratio, const Vec2 uv) {
    const double corner_y = std::tan(v_fov * .5);
    const Vec2 corner = {aspect_ratio * corner_y, corner_y};
    const Vec3 dir = {math_util::lerp(uv, -corner, corner), 1};
    solid_angle = 1 / dir.sq();
    stack.emplace_back(projection_matrix.apply(Ray(Vec3::ZERO, dir.norm())), 0, 0, LightTransformation::IDENTITY);
}

void RayStack::clear() {
    stack.clear();
}

void RayStack::push(const Ray &ray, const LightTransformation &light_transformation, const double delta_dist) {
    stack.emplace_back(ray, current_depth, current_distance + delta_dist, current_transformation.combine(light_transformation));
}

LightSpectrum RayStack::trace(const Scene &scene) {
    auto result = LightSpectrum();
    while (!stack.empty()) {
        const Node &node = stack.back();

        double distance_traveled = std::numeric_limits<double>::max();
        Vec3 hit_position = Vec3::ZERO;
        Vec3 hit_normal_unnormalized = Vec3::ZERO;
        const SceneObject *hit_object = nullptr;

        scene.ray_cast(node.ray, distance_traveled, hit_position, hit_normal_unnormalized, hit_object);
        if (hit_object == nullptr) {
            result.add_modified(scene.ambient_light, node.light_transformation);
            stack.pop_back();
            continue;
        }

        if (node.depth == DEPTH_LIMIT) {
            result.add_modified(scene.ambient_light, node.light_transformation);
            stack.pop_back();
            continue;
        }

        const Ray incident_ray = {hit_position, node.ray.dir};
        current_depth = node.depth + 1;
        current_distance = node.distance + distance_traveled;
        current_transformation = node.light_transformation;

        stack.pop_back();
        const LightSpectrum emitted = hit_object->eval_path(this, incident_ray, hit_normal_unnormalized.norm());
        result.add_modified(emitted, current_transformation);
    }
    return result;
}

RayStack::Node::Node(Ray ray, const int depth, const double distance, const LightTransformation &light_modifier)
  : ray(std::move(ray)), depth(depth), distance(distance), light_transformation(light_modifier) {}
