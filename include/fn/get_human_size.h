#pragma once

namespace fn {
    static std::string get_human_size(uintmax_t size) {
        const std::vector<std::string> units =
        { "B", "KB", "MB", "GB", "TB", "PB" };

        double step = 1024.0;

        double value = size;
        size_t unit = 0;

        while (value >= step && unit < units.size() - 1) {
            value /= step;
            unit++;
        }

        char buffer[64];

        if (value >= 100)
            snprintf(buffer, sizeof(buffer), "%.0f %s", value, units[unit].c_str());
        else if (value >= 10)
            snprintf(buffer, sizeof(buffer), "%.1f %s", value, units[unit].c_str());
        else
            snprintf(buffer, sizeof(buffer), "%.2f %s", value, units[unit].c_str());

        return buffer;
    }

}