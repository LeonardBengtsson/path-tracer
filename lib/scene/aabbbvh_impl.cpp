//
// Created by Leonard on 2025-07-15.
//

#include "../util/AabbBvh.tpp"



// Required for compiler to generate template.
template class AabbBvh<std::unique_ptr<SceneObject>, Scene::SceneObjectOps>;
