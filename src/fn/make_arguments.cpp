#include <algorithm>
#include <stdexcept>
#include <vector>
#include <string_view>

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

static inline Column parse_column_name(std::string_view name) {
    std::string lowercase(name);
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);

    if (lowercase == "name") return Column::Name;
    if (lowercase == "date") return Column::Date;
    if (lowercase == "size") return Column::Size;
    if (lowercase == "line") return Column::Line;

    throw std::invalid_argument("Error: unknown column '" + std::string(name) + "'.");
}

static void set_line_limit(lspp_config& cfg, std::string_view value) {
    cfg.print.lineLimit = fn::parse_size(value);
}

static void set_columns(lspp_config& cfg, std::string_view value_str) {
    std::vector<Column> parsedColumns;

    size_t start = 0, end = 0;
    while ((end = value_str.find(',', start)) != std::string_view::npos) {
        std::string_view token = value_str.substr(start, end - start);
        token.remove_prefix(std::min(token.find_first_not_of(" \t"), token.size()));
        token.remove_suffix(std::min(token.size() - token.find_last_not_of(" \t") - 1, token.size()));

        if (!token.empty()) {
            parsedColumns.push_back(parse_column_name(token));
        }
        start = end + 1;
    }

    std::string_view last = value_str.substr(start);
    last.remove_prefix(std::min(last.find_first_not_of(" \t"), last.size()));
    last.remove_suffix(std::min(last.size() - last.find_last_not_of(" \t") - 1, last.size()));

    if (!last.empty()) {
        parsedColumns.push_back(parse_column_name(last));
    }

    cfg.print.columns = std::vector<Column>(parsedColumns);
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

            { "lines",          "l", set_line_limit },
            { "columns",        "C", set_columns },
        };
    }
}