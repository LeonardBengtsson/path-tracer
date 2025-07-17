//
// Created by Leonard on 2025-01-24.
//

#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include "../../material/Material.h"
#include "../../path_tracing/RayStack.h"
#include "../../math/Aabb.h"



class Material;
class RayStack;

/**
 * Abstract type that represents an object that can be rendered in a scene by determining ray intersections.
 */
class SceneObject {
public:
    const Aabb aabb;

    const Material *const material;

    /**
     * @param aabb The smallest bounding box that fits the entire object.
     * @param material The material to be used when evaluating rays hitting this object.
     */
    SceneObject(Aabb aabb, const Material *material);

    /**
     * @return @c false if the ray definitely does not intersect the object, otherwise @c true.
     */
    bool possibly_intersects(const Ray &ray) const;

    /**
     * Evaluates a light path by determining possible light paths from the point of incidence, and pushing them to the
     * ray stack to be evaluated at a later point.
     * @param ray_stack A ray stack to which evaluated light rays are pushed to.
     * @param incident_ray A ray with its @c from vector set to the point of incidence, and its @c dir vector set to the
     * incident light ray direction.
     * @param surface_normal The normalized surface normal vector at the point of incidence.
     * @return The light emitted by the object in the incident ray direction.
     */
    LightSpectrum eval_path(RayStack &ray_stack, const Ray &incident_ray, const Vec3 &surface_normal) const;

    virtual ~SceneObject() = default;

    /**
     * @param min_dist The minimal distance for which a ray intersection has yet been found. All intersections that lie
     * further can be disregarded.
     * @param pos The position vector of the nearest intersection yet.
     * @param normal The normal vector of the nearest intersection yet.
     * @return
     * If the ray does not hit object, return @c false.
     * If the ray does hit an object, and the distance is higher than @c min_dist, return @c false.
     * If the ray does hit an object, and the distance is lower than @c min_dist, return @c true and update @c min_dist,
     * @c pos and @c normal.
     */
    virtual bool ray_cast_from_outside(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) const = 0;

    /**
     * Assumed to always hit the object.
     * @param dist The distance to the intersection.
     * @param pos The intersection position vector.
     * @param normal The intersection normal vector.
     */
    virtual void ray_cast_from_inside(const Ray &ray, double &dist, Vec3 &pos, Vec3 &normal) const = 0;
};



#endif //SCENEOBJECT_H
