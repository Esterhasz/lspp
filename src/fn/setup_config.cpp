#include <filesystem>
#include <stdexcept>
#include <string>
#include <algorithm>
#include "fn/setup_config.h"
#include "fn/make_arguments.h"

namespace fs = std::filesystem;

static void throw_invalid_argument(const std::string& arg) {
    throw std::invalid_argument("Error: unknown argument '" + arg + "'.");
}

void fn::setup_config(std::string_view buffer, lspp_config& config) {

    auto arguments = fn::make_arguments();

    constexpr uint8_t vcap = lspp_config::VALUED_ARGS_CAP;
    uint8_t paramIndex = 0;
    uint8_t setterIndex = 0;

    std::string_view parameters[vcap];
    ValuedSetter* setters[vcap];

    size_t pos = 0;

    while (pos < buffer.size()) {
        size_t end = buffer.find('\0', pos);

        if (end == std::string_view::npos)
            end = buffer.size();

        std::string_view arg = buffer.substr(pos, end - pos);
        pos = end + 1;

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
                    setters[setterIndex++] = fn;
                }
                else if (auto fn = std::get_if<UnvaluedSetter>(&it->setter)) {
                    (*fn)(config);
                }
            }
            else {
                throw_invalid_argument(std::string(arg));
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
                        if (setterIndex > vcap)
                            throw std::invalid_argument("Error: maximum amount of valued arguments is " + std::to_string(vcap) + ". ");

                        setters[setterIndex++] = fn;
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
            if (paramIndex > vcap)
                throw std::invalid_argument("Error: maximum amount of valued arguments is " + std::to_string(vcap) + ". ");

            parameters[paramIndex++] = arg;
        }
    }

    for (size_t i = 0; i < setterIndex; i++) {

        if (vcap <= i)
            throw std::invalid_argument("Error: not enough parameters.");

        auto setter = (*setters[i]);

        auto value = parameters[i];
        setter(config, value);
    }
}