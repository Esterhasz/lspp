#include "fn/setup_config.h"
#include "fn/make_setter_map.h"
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;


static void throw_invalid_argument(const std::string& arg) {
    throw std::invalid_argument("Error: unknown argument '" + arg + "'.");
}

void fn::setup_config(int argc, char* argv[], lspp_config& config) {

    auto setterMap = fn::make_setter_map();

    for (size_t i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg.rfind("--", 0) == 0) {
            std::string_view flag = arg.substr(2);
            auto it = setterMap.find(flag);

            if (it != setterMap.end()) {
                it->second(config);
            }
            else
            {
                throw_invalid_argument(argv[i]);
            }
        }
        else if (arg.rfind("-", 0) == 0 && arg.size() > 1) {
            std::string_view flags = arg.substr(1);

            for (char ch : flags) {
                char key[2] = { ch, '\0' };
                auto it = setterMap.find(key);

                if (it != setterMap.end()) {
                    it->second(config);
                }
                else
                {
                    throw_invalid_argument(key);
                }
            }
        }
        else if (fs::exists(arg) && fs::is_directory(arg)) {
            config.set<fs::path>(fs::path(arg));
        }
        else {
            throw std::invalid_argument("Error: '" + std::string(arg) + "' is not a directory.");
        }
    }
}