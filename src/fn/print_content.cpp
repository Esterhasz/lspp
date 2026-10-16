#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include "fn/print_content.h"
#include "fn/format_time.h"
#include "fn/get_human_size.h"

#include "utf8.h"

static std::string shorten_name(const std::string& str) {

    std::string result{};

    result += utf8::substring(str, 0, print_config::NAME_LEFT_PART);
    result += "...";
    result += utf8::substring(str, utf8::char_count(str) - print_config::NAME_RIGHT_PART, print_config::NAME_RIGHT_PART);

    return result;
}

static std::string get_name(const Item& item) {
    auto name = item.filename().u8string();

    size_t namelen = utf8::char_count(name);

    if (namelen > print_config::NAME_LENGTH_RESERVE)
        name = shorten_name(name);
    else
        name.append(print_config::NAME_LENGTH_RESERVE - namelen, ' ');

    name = (item.type() == ItemType::directory
        ? "] "
        : ". ")
        + name;

    return name;
}


void fn::print_content(const std::vector<Item>& content, const print_config& config) {

    std::string out;
    out.reserve(((uintmax_t)content.size()) * 
        (print_config::NAME_LENGTH_RESERVE
        + print_config::DATE_LENGTH_RESERVE));

    uintmax_t totalSize = 0;
    
    const size_t maxNumber = content.size();
    const size_t numberWidth = std::to_string(content.size()).size();

    const auto lineLimit = config.lineLimit == 0
        ? content.size()
        : std::min(config.lineLimit, content.size());

    const auto spaces = print_config::SPACES;
    
    for (size_t i = 0; i < lineLimit; ++i) {
        auto& item = content[i];
        std::string line;

        for (size_t j = 0; j < config.columns.size(); j++)
        {
            switch (config.columns[j])
            {
                case Column::Line: {
                    std::string number = std::to_string(i + 1);
                    number.insert(0, numberWidth - number.size(), ' ');
                    line += number + ' ';
                    break;
                }
                case Column::Name: {
                    std::string name = get_name(item);
                    name.append(spaces, ' ');
                    line += name;
                    break;
                }
                case Column::Date: {
                    std::string date = format_time(std::filesystem::last_write_time(item.path()));
                    date.append(spaces, ' ');
                    line += date;
                    break;
                }
                case Column::Size: {
                    
                    auto size = item.size();

                    if (size.has_value())
                        line += get_human_size(size.value());
                    else
                        line.append(print_config::SIZE_LENGTH_BLANK, ' ');

                    line.append(spaces, ' ');
                    
                    break;
                }
            }
        }

        line += '\n';
        out += line;
    }

    std::cout << out;
}