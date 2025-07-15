//
// Created by Leonard on 2025-02-06.
//

#ifndef AABBBVH_H
#define AABBBVH_H

#include <memory>
#include <span>
#include <variant>
#include <stack>

#include "Axis.h"
#include "../math/Aabb.h"
#include "../math/Ray.h"
#include "../math/Vec3.h"


template<typename Ops, typename T>
concept AabbBvhOps = requires(const std::span<T> span, const T &object, const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) {
    { Ops::get_aabb(object) } -> std::same_as<Aabb>;
    { Ops::wrap_aabb(span) } -> std::same_as<Aabb>;
    { Ops::possibly_intersects(object, ray) } -> std::same_as<bool>;
    { Ops::ray_cast(object, ray, min_dist, pos, normal) } -> std::same_as<bool>;
};

template<typename T, AabbBvhOps<T> Ops>
class AabbBvh {
public:
    struct Node {
        using Leaf = std::span<T>;
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

    const std::span<T> objects;

    std::unique_ptr<Node> root_node;

    std::stack<TraversalRecord> traversal_stack;

public:
    AabbBvh(std::span<T> objects, uint32_t max_tree_height, uint32_t min_leaf_size);

    void ray_cast(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal, const T *&hit_object);
};



#endif //AABBBVH_H
