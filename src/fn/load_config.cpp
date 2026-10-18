#include <filesystem>
#include <fstream>
#include <string>
#include <cctype>

#include "fn/load_config.h"

void fn::load_config(std::filesystem::path& path, std::string& buffer) {

    std::ifstream file(path, std::ios::binary);

    if (!file) {
        return;
    }

    bool quoted = false;
    bool started = false;
    char ch;

    while (file.get(ch)) {
        if (ch == '"') {
            quoted = !quoted;
            started = true;
        }
        else if (std::isspace(static_cast<unsigned char>(ch)) && !quoted) {
            if (started) {
                buffer.push_back('\0');
                started = false;
            }
        }
        else {
            buffer.push_back(ch);
            started = true;
        }
    }

    if (started)
        buffer.push_back('\0');
}