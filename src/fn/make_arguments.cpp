#include "fn/make_arguments.h"
#include "fn/parse_size.h"

#include "compare/all.h"
#include "measure/all.h"
#include "priority/all.h"
#include "predicate/all.h"

using StringKeys = std::initializer_list<std::string_view>;

template<auto obj> 
void set(lspp_config& cfg) {
	cfg.set(obj);
}

static void set_line_limit(lspp_config& cfg, std::string_view value) {
    cfg.print.lineLimit = fn::parse_size(value);
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

            { "lines",          "l", set_line_limit }
        };
    }
}