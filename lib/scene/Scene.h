//
// Created by Leonard on 2025-01-24.
//

#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include "../math/Vec3.h"
#include "scene_objects/SceneObject.h"
#include "../render/LightSpectrum.h"
#include "../util/AabbBvh.h"



class SceneObject;

/**
 * Contains a collection of objects that can be rendered as well as internal state for optimizing the rendering process.
 */
class Scene {
public:

    /**
     * Scene object operations required for implementing @c AabbBvh for scene objects.
     */
    struct SceneObjectOps {
        static Aabb get_aabb(const std::unique_ptr<SceneObject> &object);
        static Aabb wrap_aabb(std::span<std::unique_ptr<SceneObject>> objects);
        static bool possibly_intersects(const std::unique_ptr<SceneObject> &object, const Ray &ray);
        static bool ray_cast(const std::unique_ptr<SceneObject> &object, const Ray &ray, double &min_dist, Vec3 &pos,
            Vec3 &normal);
    };

private:
    using SceneObjectAabbBvh = AabbBvh<std::unique_ptr<SceneObject>, SceneObjectOps>;

    std::vector<std::unique_ptr<SceneObject>> objects;

    std::unique_ptr<SceneObjectAabbBvh> aabb_bvh;

public:
    const LightSpectrum ambient_light;

    /**
     * @param ambient_light The light emitted by the ambient surroundings.
     */
    explicit Scene(const LightSpectrum &ambient_light);

    void add_object(std::unique_ptr<SceneObject> &&object);

    /**
     * Initialize internal state after adding all desired objects to the scene.
     */
    void init();

    void iter_objects(void (*fn)(const std::unique_ptr<SceneObject>&)) const;

    /**
     * Find the nearest intersection with any object in the scene.
     * @param distance The distance from the ray origin to the intersection point.
     * @param pos The intersection position vector.
     * @param normal The intersection normal vector.
     * @param hit_object The object that was hit.
     */
    void ray_cast(const Ray &ray, double &distance, Vec3 &pos, Vec3 &normal,
        const std::unique_ptr<SceneObject>* &hit_object) const;
};



#endif //SCENE_H
