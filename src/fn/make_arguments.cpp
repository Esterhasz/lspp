#include <algorithm>
#include <stdexcept>
#include <vector>

#include "fn/make_arguments.h"

#include "strategy/compare/all.h"
#include "strategy/measure/all.h"
#include "strategy/priority/all.h"
#include "strategy/predicate/all.h"

#include "argument/valued_arguments.h"

using StringKeys = std::initializer_list<std::string_view>;

template<auto obj> 
void set(lspp_config& cfg) {
	cfg.set(obj);
}

static std::size_t parse_size(std::string_view str) {
    std::size_t value{};

    auto [ptr, ec] = std::from_chars(
        str.data(),
        str.data() + str.size(),
        value
    );

    if (ec != std::errc{} || ptr != str.data() + str.size()) {
        throw std::invalid_argument("Invalid number: " + std::string(str));
    }

    return value;
}

namespace fn {
    std::vector<Argument> make_arguments() {
        
        return {
            { "reversed",       "r", set<compare::reversed> },

            { "recursive",      "R", set<measure::recursive> },
            { "no-measure",     "m", set<measure::none> },

            { "by-name-cs",     "c", set<predicate::by_name_cs> },
            { "by-name-ci",     "i", set<predicate::by_name_ci> },
            { "by-size",        "s", set<predicate::by_size> },
            { "by-time",        "t", set<predicate::by_time> },

            { "file-first",     "f", set<priority::files> },
            { "dir-first",      "d", set<priority::directories> },
            { "no-priority",    "p", set<priority::none> },

            { "lines",          "l", argument::set_line_limit },
            { "columns",        "C", argument::set_columns },

            { "name-width",     "w", argument::set_name_width },
            { "spacing",        "g", argument::set_spacing },
        };
    }
}