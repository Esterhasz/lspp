#include "fn/setup_config.h"
#include "fn/make_arguments.h"
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;


static void throw_invalid_argument(const std::string& arg) {
    throw std::invalid_argument("Error: unknown argument '" + arg + "'.");
}

void fn::setup_config(int argc, char* argv[], lspp_config& config) {

    auto arguments = fn::make_arguments();

    std::vector<ValuedSetter*> valuedSetters{};
    std::vector<std::string_view> values{};

    config.executablePath = argv[0];

    for (size_t i = 1; i < argc; ++i) {
        std::string_view arg = argv[i];

        if (arg.rfind("--", 0) == 0) {
            std::string_view flag = arg.substr(2);
            
            auto it = std::find_if(
                arguments.begin(),
                arguments.end(),
                [flag](const Argument& arg) {
                    return arg.name == flag;
                }
            );

            if (it != arguments.end()) {
                auto& setter = it->setter;

                if (auto fn = std::get_if<ValuedSetter>(&it->setter)) {
                    valuedSetters.push_back(fn);
                }
                else if (auto fn = std::get_if<UnvaluedSetter>(&it->setter)) {
                    (*fn)(config);
                }
            }
            else {
                throw_invalid_argument(argv[i]);
            }
        }
        else if (arg.rfind("-", 0) == 0 && arg.size() > 1) {
            std::string_view flags = arg.substr(1);

            for (char ch : flags) {
                char key[2] = { ch, '\0' };
                
                auto it = std::find_if(
                    arguments.begin(),
                    arguments.end(),
                    [key](const Argument& arg) {
                        return arg.shortName == key;
                    }
                );

                if (it != arguments.end()) {
                    auto& setter = it->setter;

                    if (auto fn = std::get_if<ValuedSetter>(&it->setter)) {
                        valuedSetters.push_back(fn);
                    }
                    else if (auto fn = std::get_if<UnvaluedSetter>(&it->setter)) {
                        (*fn)(config);
                    }
                }
                else
                {
                    throw_invalid_argument(key);
                }
            }
        }
        else if (fs::exists(arg)) {
            if (!fs::is_directory(arg))
                throw std::invalid_argument("Error: '" + std::string(arg) + "' is not a directory.");

            config.set(fs::path(arg));
        }
        else {
            values.push_back(arg);
        }
    }

    for (size_t i = 0; i < valuedSetters.size(); i++) {
        auto setter = (*valuedSetters[i]);

        if (values.size() <= i)
            throw std::invalid_argument("Error: not enough parameters.");

        auto value = values[i];
        setter(config, value);
    }
}