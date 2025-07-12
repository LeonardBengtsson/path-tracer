//
// Created by Leonard on 2025-01-24.
//

#include "Scene.h"

#include <algorithm>

#include "../config.h"
#include "../math/aabb_util.h"
#include "scene_objects/SceneObject.h"

Scene::Scene(const LightSpectrum &ambient_light) : aabb_bvh(nullptr), ambient_light(ambient_light) {}

void Scene::add_object(std::unique_ptr<SceneObject> &&object) {
    objects.push_back(std::move(object));
}

void Scene::init() {
    if constexpr (ENABLE_BVH_OPTIMIZATION) {
        uint32_t max_tree_height, min_leaf_size;
        aabb_util::get_optimal_bvh_parameters(objects.size(), max_tree_height, min_leaf_size);

        aabb_bvh = new AabbBvh(std::span(objects), max_tree_height, min_leaf_size);
    }
}

void Scene::iter_objects(void (*fn)(const std::unique_ptr<SceneObject>&)) const {
    for (auto &object : objects) {
        fn(object);
    }
}

void Scene::ray_cast(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal, const SceneObject* &hit_object) const {
    if constexpr (ENABLE_BVH_OPTIMIZATION) {
        if constexpr (DEBUG_ASSERTS)
            assert(aabb_bvh != nullptr);
        aabb_bvh->ray_cast(ray, min_dist, pos, normal, hit_object);
    } else {
        for (auto &object : objects) {
            if (!object->possibly_intersects(ray))
                continue;
            const bool outside_hit = object->ray_cast_from_outside(ray, min_dist, pos, normal);
            if (outside_hit) {
                hit_object = object.get();
            }
        }
    }
}

