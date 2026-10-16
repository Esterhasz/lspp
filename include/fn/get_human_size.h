#pragma once

namespace fn {
    static std::string get_human_size(uintmax_t size) {
        const char* units[] = { " B", "KB", "MB", "GB", "TB", "PB" };

        double value = static_cast<double>(size);
        size_t unit = 0;

        while (value >= 1024.0 && unit < 5) {
            value /= 1024.0;
            unit++;
        }

        char number[16];
        if (unit == 0 || value >= 100)
            snprintf(number, sizeof(number), "%.0f", value);
        else if (value >= 10)
            snprintf(number, sizeof(number), "%.1f", value);
        else
            snprintf(number, sizeof(number), "%.2f", value);

        char result[64];
        snprintf(result, sizeof(result), "%-4s %s", number, units[unit]);

        return result;
    }
}