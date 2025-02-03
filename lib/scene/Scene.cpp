//
// Created by Leonard on 2025-01-24.
//

#include "Scene.h"

#include "SceneObject.h"

Scene::Scene(const LightSpectrum &ambient_light) : ambient_light(ambient_light) {}

void Scene::add_object(const SceneObject *obj) {
    objects.push_back(obj);
}


void Scene::iter_objects(void (*fn)(const SceneObject*)) const {
    for (const SceneObject *obj : objects) {
        fn(obj);
    }
}

void Scene::ray_cast(const Ray &ray, double &min_dist, Vec3 &hit_position, Vec3 &hit_normal_unnormalized, const SceneObject* &hit_object) const {
    for (const SceneObject *obj : objects) {
        if (!obj->intersects(ray))
            continue;
        const bool outside_hit = obj->ray_cast_from_outside(ray, min_dist, hit_position, hit_normal_unnormalized);
        if (outside_hit) {
            hit_object = obj;
        }
    }
}

