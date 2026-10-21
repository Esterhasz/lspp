#include "argument/valued_arguments.h"

static inline Column parse_column_name(std::string_view name) {
    std::string lowercase(name);
    std::transform(lowercase.begin(), lowercase.end(), lowercase.begin(), ::tolower);

    if (lowercase == "name") return Column::Name;
    if (lowercase == "date") return Column::Date;
    if (lowercase == "size") return Column::Size;
    if (lowercase == "line") return Column::Line;

    throw std::invalid_argument("Error: unknown column '" + std::string(name) + "'.");
}

void argument::set_columns(lspp_config& cfg, std::string_view value) {
    std::vector<Column> parsedColumns;

    size_t start = 0, end = 0;
    while ((end = value.find(',', start)) != std::string_view::npos) {
        std::string_view token = value.substr(start, end - start);
        token.remove_prefix(std::min(token.find_first_not_of(" \t"), token.size()));
        token.remove_suffix(std::min(token.size() - token.find_last_not_of(" \t") - 1, token.size()));

        if (!token.empty()) {
            parsedColumns.push_back(parse_column_name(token));
        }
        start = end + 1;
    }

    std::string_view last = value.substr(start);
    last.remove_prefix(std::min(last.find_first_not_of(" \t"), last.size()));
    last.remove_suffix(std::min(last.size() - last.find_last_not_of(" \t") - 1, last.size()));

    if (!last.empty()) {
        parsedColumns.push_back(parse_column_name(last));
    }

    cfg.print.columns = std::vector<Column>(parsedColumns);
}