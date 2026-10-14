#include <string>
#include <vector>
#include <iomanip>
#include <sstream>
#include <chrono>
#include <filesystem>
#include <iostream>
#include "fn/print_content.h"
#include "utf8.h"

constexpr size_t NAME_LENGTH_RESERVE = 24;

// 3 less due to '...' adding
constexpr size_t NAME_LEFT_PART = 11;
constexpr size_t NAME_RIGHT_PART = 10;

constexpr size_t DATE_LENGTH_RESERVE = 10;
constexpr size_t SIZE_LENGTH_RESERVE = 3;

constexpr size_t SPACES_FIRST_COLUMN = 4;
constexpr size_t SPACES_SECOND_COLUMN = 4;

static std::string get_human_size(uintmax_t size) {
    const std::vector<std::string> units =
    { "B", "KB", "MB", "GB", "TB", "PB" };

    double step = 1024.0;

    double value = size;
    size_t unit = 0;

    while (value >= step && unit < units.size() - 1) {
        value /= step;
        unit++;
    }

    char buffer[64];

    if (value >= 100)
        snprintf(buffer, sizeof(buffer), "%.0f %s", value, units[unit].c_str());
    else if (value >= 10)
        snprintf(buffer, sizeof(buffer), "%.1f %s", value, units[unit].c_str());
    else
        snprintf(buffer, sizeof(buffer), "%.2f %s", value, units[unit].c_str());

    return buffer;
}

static std::string shorten_name(const std::string& str) {

    std::string result{};

    result += utf8::substring(str, 0, NAME_LEFT_PART);
    result += "...";
    result += utf8::substring(str, utf8::char_count(str) - NAME_RIGHT_PART, NAME_RIGHT_PART);

    return result;
}

static std::string format_time(std::filesystem::file_time_type ftime) {
    auto sctp = std::chrono::time_point_cast<
        std::chrono::system_clock::duration>(
            ftime - std::filesystem::file_time_type::clock::now()
            + std::chrono::system_clock::now());

    std::time_t ctime = std::chrono::system_clock::to_time_t(sctp);

    std::tm tm = *std::localtime(&ctime);

    char buf[64];
    strftime(buf, sizeof(buf), "%d/%m/%Y", &tm);

    return buf;
}

void fn::print_content(std::vector<Item> content) {

    std::string out;
    out.reserve(((uintmax_t)content.size()) * 
        (NAME_LENGTH_RESERVE 
        + DATE_LENGTH_RESERVE 
        + SIZE_LENGTH_RESERVE));

    uintmax_t totalSize = 0;
    
    const size_t maxNumber = content.size();
    const size_t numberWidth = std::to_string(content.size()).size();

    for (size_t i = 0; i < content.size(); ++i) {
        auto& item = content[i];
        
        std::string name = item.filename().u8string();
        std::string number = std::to_string(i + 1);
        number.insert(0, numberWidth - number.size(), ' ');

        size_t namelen = utf8_char_count(name);

        if (namelen > NAME_LENGTH_RESERVE)
            name = shorten_name(name);
        else
            name.append(NAME_LENGTH_RESERVE - namelen, ' ');

        name = (item.type() == ItemType::directory
            ? "] "
            : ". ")
            + name;

        std::string date = format_time(
            std::filesystem::last_write_time(item.path())
        );

        std::string size = item.size() < 1
            ? "0 B"
            : get_human_size(item.size());


        date.append(SPACES_SECOND_COLUMN, ' ');
        name.append(SPACES_FIRST_COLUMN, ' ');

        std::string line{
            number + ' ' +
            name +
            date +
            size + '\n'
        };

        totalSize += item.size();
        out += line;
    }

    std::cout << out;
}