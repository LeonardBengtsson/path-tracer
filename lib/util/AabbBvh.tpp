//
// Created by Leonard on 2025-02-06.
//

#ifndef AABBBVH_TPP
#define AABBBVH_TPP

#include "AabbBvh.h"

#include <algorithm>
#include <cassert>
#include <format>
#include <utility>

#include "../math/aabb_util.h"
#include "../config.h"
#include "../scene/scene_objects/BoxObject.h"

template<typename T, AabbBvhOps<T> Ops>
AabbBvh<T, Ops>::Node::Node(Child child, Aabb aabb)
  : child(std::move(child)), aabb(std::move(aabb)) {}

template<typename T, AabbBvhOps<T> Ops>
void AabbBvh<T, Ops>::Node::split(Axis axis) {
    // splits a leaf node into two leaf nodes, converting the current node to a branch node and assigning the new
    // leaves as children.
    if constexpr (DEBUG_ASSERTS)
        assert(std::holds_alternative<Leaf>(child));

    const auto objects = std::get<Leaf>(child);
    std::ranges::sort(
        objects,
        [this, axis](const T &a, const T &b) {
            const Aabb a_aabb = Ops::get_aabb(a);
            const Aabb b_aabb = Ops::get_aabb(b);
            // sort by aabb centerpoint coordinate
            return a_aabb.min.component(axis) + a_aabb.max.component(axis)
                 < b_aabb.min.component(axis) + b_aabb.max.component(axis);
        }
    );
    const size_t object_count = objects.size();

    if constexpr (DEBUG_ASSERTS)
        assert(object_count >= 2);

    const auto min_objects = objects.subspan(0, object_count / 2);
    const auto max_objects = objects.subspan(object_count / 2, object_count - object_count / 2);

    auto min_child = std::make_unique<Node>(Leaf(min_objects), Ops::wrap_aabb(min_objects));
    auto max_child = std::make_unique<Node>(Leaf(max_objects), Ops::wrap_aabb(max_objects));

    std::array<std::unique_ptr<Node>, 2> children = {std::move(min_child), std::move(max_child)};
    child.template emplace<Branch>(axis, std::move(children));
}

template<typename T, AabbBvhOps<T> Ops>
void split_recursively(typename AabbBvh<T, Ops>::Node &node, const uint32_t subtree_max_height, const uint32_t min_leaf_size) {
    using Leaf = typename AabbBvh<T, Ops>::Node::Leaf;
    using Branch = typename AabbBvh<T, Ops>::Node::Branch;

    if constexpr (DEBUG_ASSERTS)
        assert(std::holds_alternative<Leaf>(node.child));

    if (subtree_max_height == 0)
        return;
    if (std::get<Leaf>(node.child).size() <= min_leaf_size)
        return;

    // TODO more efficient axis selection
    Axis axis;
    switch (subtree_max_height % 3) {
    case 0:
        axis = X;
        break;
    case 1:
        axis = Y;
        break;
    default:
        axis = Z;
        break;
    }
    node.split(axis);

    if constexpr (DEBUG_ASSERTS)
        assert(std::holds_alternative<Branch>(node.child));

    auto &[_, children] = std::get<Branch>(node.child);
    split_recursively<T, Ops>(*children[0], subtree_max_height - 1, min_leaf_size);
    split_recursively<T, Ops>(*children[1], subtree_max_height - 1, min_leaf_size);
}

template<typename T, AabbBvhOps<T> Ops>
AabbBvh<T, Ops>::AabbBvh(const std::span<T> objects, const uint32_t max_tree_height, const uint32_t min_leaf_size)
  : objects(objects),
    root_node(std::make_unique<Node>(typename Node::Leaf(objects), Ops::wrap_aabb(objects))),
    traversal_stack(std::stack<TraversalRecord>())
{
    // TODO consider using a vec with pre-allocated memory for all the nodes
    // std::vector<Node> vec = new std::vector<Node>();
    split_recursively<T, Ops>(*root_node, max_tree_height, min_leaf_size);
}

template<typename T, AabbBvhOps<T> Ops>
AabbBvh<T, Ops>::TraversalRecord::TraversalRecord(const Node &node) : node(node), second_pass(false) {}

template<typename T, AabbBvhOps<T> Ops>
void AabbBvh<T, Ops>::ray_cast(const Ray &ray, double &min_dist, Vec3 &pos, Vec3 &normal, const T *&hit_object) {
    while (!traversal_stack.empty())
        traversal_stack.pop();

    traversal_stack.emplace(*root_node);

    const size_t dir_indices[3] = {
        std::signbit(ray.dir.x),
        std::signbit(ray.dir.y),
        std::signbit(ray.dir.z),
    };

    while (!traversal_stack.empty()) {
        TraversalRecord &current_record = traversal_stack.top();
        const Node &current_node = current_record.node;
        if (std::holds_alternative<typename Node::Leaf>(current_node.child)) {
            const auto objects = std::get<typename Node::Leaf>(current_node.child);
            for (auto &object : objects) {
                if (!Ops::possibly_intersects(object, ray))
                    continue;
                const bool outside_hit = Ops::ray_cast(object, ray, min_dist, pos, normal);
                if (outside_hit) {
                    hit_object = &object;
                }
            }
            traversal_stack.pop();
        } else {
            const auto &[axis, children] = std::get<typename Node::Branch>(current_node.child);
            size_t next_node_index = dir_indices[axis];

            if (current_record.second_pass)
                next_node_index ^= 0x1;

            const auto &next_node = children[next_node_index];

            if (current_record.second_pass)
                traversal_stack.pop();
            else
                current_record.second_pass = true;

            const Aabb aabb = next_node->aabb;

            const double intersect_dist = aabb.ray_dist(ray);

            if (intersect_dist <= min_dist && intersect_dist != -1)
                traversal_stack.emplace(*next_node);
        }
    }
}



#endif //AABBBVH_TPP
