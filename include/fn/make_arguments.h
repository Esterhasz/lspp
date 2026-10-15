#pragma once
#include <unordered_map>
#include <variant>
#include <string_view>
#include "lspp_config.h"

namespace fn {
    using UnvaluedSetter = void(*)(lspp_config&);
    using ValuedSetter = void(*)(lspp_config&, std::string_view);

    struct Argument {
        std::string_view name;
        std::string_view shortName;

        std::variant<ValuedSetter, UnvaluedSetter> setter;

        bool takes_value() const {
            return std::holds_alternative<ValuedSetter>(setter);
        }
    };

	std::vector<Argument> make_arguments();
}