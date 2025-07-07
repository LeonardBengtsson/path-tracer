//
// Created by Leonard on 2025-02-06.
//

#ifndef AABB_BVH_H
#define AABB_BVH_H

#include <memory>
#include <span>
#include <variant>
#include <stack>

#include "Axis.h"
#include "../math/Aabb.h"
#include "../math/Ray.h"
#include "../math/Vec3.h"


class SceneObject;

class AabbBvh {
public:
    struct Node {
        using Leaf = std::span<std::unique_ptr<SceneObject>>;
        struct Branch {
            Axis axis;
            std::array<std::unique_ptr<Node>, 2> children;
        };

        using Child = std::variant<Leaf, Branch>;
        Child child;

        Aabb aabb;

        Node(Child child, Aabb aabb);

        void split(Axis axis);
    };

private:
    struct TraversalRecord {
        const Node &node;
        bool second_pass;

        explicit TraversalRecord(const Node &node);
    };

    const std::span<std::unique_ptr<SceneObject>> objects;

    std::unique_ptr<Node> root_node;

    std::stack<TraversalRecord> traversal_stack;

public:
    AabbBvh(std::span<std::unique_ptr<SceneObject>> objects, uint32_t max_tree_height, uint32_t min_leaf_size);

    void ray_cast(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal, const SceneObject* &hit_object);
};



#endif //AABB_BVH_H
