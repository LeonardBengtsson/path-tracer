//
// Created by Leonard on 2025-07-05.
//

#ifndef MESH_UTIL_H
#define MESH_UTIL_H

#include <fstream>
#include <iostream>
#include <limits>
#include <optional>

#include "MeshObject.h"



namespace mesh_util {
    inline void stream_ignore_line(std::istream &stream) {
        stream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    inline std::optional<std::unique_ptr<MeshObject>> from_obj(const std::string &path, const Material *material) {
        std::ifstream stream(path);

        std::vector<Vec3> obj_vertices;
        std::vector<Vec3> tri_vertices;

        double x, y, z, w;
        int i1, i2, i3;
        for (std::string line; std::getline(stream, line, ' ');) {
            if (line == "#") {
                stream_ignore_line(stream);
            } else if (line == "v") {
                if (stream >> x >> y >> z) {
                    if (stream >> w) {
                        x *= w;
                        y *= w;
                        z *= w;
                        stream_ignore_line(stream);
                    } else {
                        stream.clear();
                    }
                    obj_vertices.emplace_back(x, y, z);
                } else {
                    stream.close();
                    return {};
                }
            } else if (line == "f") {
                if (stream >> i1 >> i2 >> i3) {
                    i1--; i2--; i3--;
                    if (i1 >= obj_vertices.size() || i2 >= obj_vertices.size() || i3 >= obj_vertices.size()) {
                        stream.close();
                        return {};
                    }
                    stream_ignore_line(stream);
                    tri_vertices.push_back(obj_vertices[i1]);
                    tri_vertices.push_back(obj_vertices[i2]);
                    tri_vertices.push_back(obj_vertices[i3]);
                } else {
                    stream.close();
                    return {};
                }
            } else {
                stream.close();
                return {};
            }
        }

        stream.close();
        return {std::make_unique<MeshObject>(std::move(tri_vertices), material)};
    }
}



#endif //MESH_UTIL_H
