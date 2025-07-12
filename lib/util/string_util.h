//
// Created by Leonard on 2025-06-28.
//

#ifndef STRING_UTIL_H
#define STRING_UTIL_H

#include <format>

namespace string_util {
    inline std::string format_duration(const uint64_t micros) {
        if (micros > 86400000000) {
            return std::format("{} d {} h {} min {} s", micros / 86400000000, (micros % 86400000000) / 3600000000,
                (micros % 3600000000) / 60000000, (micros % 60000000) / 1000000);
        } else if (micros > 3600000000) {
            return std::format("{} h {} min {} s", micros / 3600000000, (micros % 3600000000) / 60000000,
                (micros % 60000000) / 1000000);
        } else if (micros > 60000000) {
            return std::format("{} min {} s", micros / 60000000, (micros % 60000000) / 1000000);
        } else if (micros > 1000000) {
            return std::format("{:.2f} s", static_cast<double>(micros) / 1000000);
        } else if (micros > 1000) {
            return std::format("{:.2f} ms", static_cast<double>(micros) / 1000);
        } else {
            return std::format("{} us", micros);
        }
    }

    inline std::string get_valid_path(const std::filesystem::path &path) {
        const std::string stem = path.stem().string();
        const std::string extension = path.extension().string();
        const std::string parent = path.has_parent_path()
            ? path.parent_path().string() + "/"
            : "";

        int counter = 0;
        std::string complete_path = path.string();
        while (std::filesystem::exists(complete_path)) {
            complete_path = std::format("{}{}-{}{}", parent, stem, counter, extension);
            counter++;
        }
        return complete_path;
    }
}

#endif //STRING_UTIL_H
