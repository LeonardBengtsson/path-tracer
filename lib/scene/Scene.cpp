//
// Created by Leonard on 2025-01-24.
//

#include "Scene.h"

#include "scene_objects/SceneObject.h"

Scene::Scene(const LightSpectrum &ambient_light) : aabb_bvh(nullptr), ambient_light(ambient_light) {}

void Scene::add_object(const SceneObject *obj) {
    objects.push_back(obj);
}

void Scene::init() {
#if ENABLE_BVH_OPTIMIZATION
    uint32_t max_tree_height, min_leaf_size;
    get_optimal_bvh_parameters(objects.size(), max_tree_height, min_leaf_size);

    aabb_bvh = new AabbBvh(std::span(objects), max_tree_height, min_leaf_size);
#endif
}

void Scene::iter_objects(void (*fn)(const SceneObject*)) const {
    for (const SceneObject *obj : objects) {
        fn(obj);
    }
}

void Scene::ray_cast(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal, const SceneObject* &hit_object) const {
#if ENABLE_BVH_OPTIMIZATION
    #if DEBUG_ASSERTS
        assert(aabb_bvh != nullptr);
    #endif

    aabb_bvh->ray_cast(ray, min_dist, pos, normal, hit_object);
#else
    for (const SceneObject *obj : objects) {
        if (!obj->intersects(ray))
            continue;
        const bool outside_hit = obj->ray_cast_from_outside(ray, min_dist, pos, normal);
        if (outside_hit) {
            hit_object = obj;
        }
    }
#endif
}

