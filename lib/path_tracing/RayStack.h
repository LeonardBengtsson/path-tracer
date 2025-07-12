//
// Created by Leonard on 2025-01-24.
//

#ifndef RAYSTACK_H
#define RAYSTACK_H

#include <stack>

#include "LightTransformation.h"
#include "../render/LightSpectrum.h"
#include "../math/Matrix4x4.h"
#include "../math/Vec2.h"
#include "../scene/Scene.h"

class Scene;

class RayStack {
private:
    class Node {
    public:
        const Ray ray;
        const size_t depth;
        const double distance;
        const LightTransformation light_transformation;

        Node(Ray, int, double, const LightTransformation&);
    };

    const Matrix4x4 projection_matrix;

    double solid_angle;
    std::stack<Node> stack;

    size_t current_depth;
    double current_distance;
    LightTransformation current_transformation;

public:
    explicit RayStack(const Matrix4x4& = Matrix4x4::IDENT);

    void start(double, double, Vec2);
    void push(const Ray &ray, const LightTransformation &light_transformation, double delta_dist = 0, size_t additional_depth = 0);
    void clear();
    LightSpectrum trace(const Scene&);
};



#endif //RAYSTACK_H
