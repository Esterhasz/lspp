#include "fn/executable_path.h"
#include "whereami/whereami.h"
#include <string>

bool fn::executable_path(std::filesystem::path& path) {
    int length = wai_getExecutablePath(nullptr, 0, nullptr);

    if (length <= 0) {
        return false;
    }

    std::string path_buffer(length, '\0');
    int dirLength = 0;

    wai_getExecutablePath(path_buffer.data(), length, &dirLength);

    path.assign(std::move(path_buffer));
    path.remove_filename();

    return true;
}