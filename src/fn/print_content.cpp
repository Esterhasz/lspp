#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include "fn/print_content.h"
#include "fn/format_time.h"
#include "fn/get_human_size.h"

#include "utf8.h"

constexpr size_t NAME_LENGTH_RESERVE = 24;

// 3 less due to '...' adding
constexpr size_t NAME_LEFT_PART = 11;
constexpr size_t NAME_RIGHT_PART = 10;

constexpr size_t DATE_LENGTH_RESERVE = 10;
constexpr size_t SIZE_LENGTH_RESERVE = 3;

constexpr size_t SPACES_FIRST_COLUMN = 4;
constexpr size_t SPACES_SECOND_COLUMN = 4;


static std::string shorten_name(const std::string& str) {

    std::string result{};

    result += utf8::substring(str, 0, NAME_LEFT_PART);
    result += "...";
    result += utf8::substring(str, utf8::char_count(str) - NAME_RIGHT_PART, NAME_RIGHT_PART);

    return result;
}

static std::string get_name(const Item& item) {
    auto name = item.filename().u8string();

    size_t namelen = utf8::char_count(name);

    if (namelen > NAME_LENGTH_RESERVE)
        name = shorten_name(name);
    else
        name.append(NAME_LENGTH_RESERVE - namelen, ' ');

    name = (item.type() == ItemType::directory
        ? "] "
        : ". ")
        + name;

    return name;
}


void fn::print_content(const std::vector<Item>& content, const print_config& config) {

    std::string out;
    out.reserve(((uintmax_t)content.size()) * 
        (NAME_LENGTH_RESERVE 
        + DATE_LENGTH_RESERVE 
        + SIZE_LENGTH_RESERVE));

    uintmax_t totalSize = 0;
    
    const size_t maxNumber = content.size();
    const size_t numberWidth = std::to_string(content.size()).size();

    const auto lineLimit = config.lineLimit == 0
        ? content.size()
        : std::min(config.lineLimit, content.size());

    for (size_t i = 0; i < lineLimit; ++i) {
        auto& item = content[i];
        std::string line;

        if (Column::Number & config.columns) {
            std::string number = std::to_string(i + 1);
            number.insert(0, numberWidth - number.size(), ' ');
            line += number + ' ';
        }

        if (Column::Name & config.columns) {
            std::string name = get_name(item);
            name.append(SPACES_FIRST_COLUMN, ' ');
            line += name;
        }

        if (Column::Date & config.columns) {
            std::string date = format_time(std::filesystem::last_write_time(item.path()));
            date.append(SPACES_SECOND_COLUMN, ' ');
            line += date;
        }

        if (Column::Size & config.columns) {
            std::string size = item.size() < 1 ? "0 B" : get_human_size(item.size());
            line += size;
        }

        line += '\n';
        out += line;
    }

    std::cout << out;
}