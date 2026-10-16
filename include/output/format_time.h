#pragma once
#include <filesystem>
#include <chrono>

namespace output {
    std::string format_time(std::filesystem::file_time_type ftime) {
        auto sctp = std::chrono::time_point_cast<
            std::chrono::system_clock::duration>(
                ftime - std::filesystem::file_time_type::clock::now()
                + std::chrono::system_clock::now());

        std::time_t ctime = std::chrono::system_clock::to_time_t(sctp);

        std::tm tm = *std::localtime(&ctime);

        char buf[64];
        strftime(buf, sizeof(buf), "%d/%m/%Y", &tm);

        return buf;
    }
}