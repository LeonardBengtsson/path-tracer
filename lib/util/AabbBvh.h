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


class SceneObject;

// nightmare ahead
// why didn't i just use rust and traits :|

struct wrap_aabb_cpo_t {
    template<typename T>
    constexpr auto operator()(const std::span<T>&& span) const
        noexcept(noexcept(wrap_aabb(std::forward<const std::span<T>>(span))))
        -> decltype(wrap_aabb(std::forward<const std::span<T>>(span)))
    {
        return wrap_aabb(std::forward<const std::span<T>>(span));
    }
};

struct possibly_intersects_cpo_t {
    template<typename T>
    constexpr auto operator()(T&& t, const Ray &ray) const
        noexcept(noexcept(possibly_intersects(std::forward<T>(t), std::forward<const Ray&>(ray))))
        -> decltype(possibly_intersects(std::forward<T>(t), std::forward<const Ray&>(ray)))
    {
        return possibly_intersects(std::forward<T>(t), std::forward<const Ray&>(ray));
    }
};

struct ray_cast_cpo_t {
    template<typename T>
    constexpr auto operator()(T&& t, const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal) const
        noexcept(noexcept(ray_cast(std::forward<T>(t), std::forward<const Ray&>(ray), std::forward<double&>(min_dist), std::forward<Vec3&>(pos), std::forward<Vec3&>(normal))))
        -> decltype(ray_cast(std::forward<T>(t), std::forward<const Ray&>(ray), std::forward<double&>(min_dist), std::forward<Vec3&>(pos), std::forward<Vec3&>(normal)))
    {
        return ray_cast(std::forward<T>(t), std::forward<const Ray&>(ray), std::forward<double&>(min_dist), std::forward<Vec3&>(pos), std::forward<Vec3&>(normal));
    }
};

inline constexpr wrap_aabb_cpo_t wrap_aabb_cpo{};
inline constexpr possibly_intersects_cpo_t possibly_intersects_cpo{};
inline constexpr ray_cast_cpo_t ray_cast_cpo{};

template<typename T>
concept SceneObjectLike = requires(T t, std::span<T> span, Ray ray, double &min_dist, Vec3 &pos, Vec3 &normal) {
    { wrap_aabb(span) } -> std::same_as<Aabb>;
    { possibly_intersects(t, ray) } -> std::same_as<bool>;
    { ray_cast(t, ray, min_dist, pos, normal) } -> std::same_as<bool>;
};

template<SceneObjectLike T>
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
