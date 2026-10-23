#include <string>
#include <vector>
#include <filesystem>
#include <iostream>
#include "output/print_content.h"
#include "output/format_time.h"
#include "output/get_human_size.h"
#include "lspp_config.h"
#include "utf8.h"

namespace output {
    static std::string shorten_name(const std::string& str, size_t reserve, const std::string& splitter) {
        const auto splitSize = splitter.size();

        const size_t left = (reserve - splitSize + 1) / 2;
        const size_t right = (reserve - splitSize) / 2;
        const size_t length = utf8::char_count(str);

        std::string result;
        result += utf8::substring(str, 0, left);
        result += splitter;
        result += utf8::substring(str, length - right, right);

        return result;
    }

    static std::string get_name(const Item& item, size_t reserve, const std::string& splitter) {
        auto name = item.filename().u8string();
        const size_t length = utf8::char_count(name);

        if (length > reserve)
            name = shorten_name(name, reserve, splitter);
        else if (length < reserve)
            name.append(reserve - length, ' ');
            
        name = (item.type() == ItemType::directory
            ? "] "
            : ". ")
            + name;

        return name;
    }

    void print_content(const std::vector<Item>& content, const print_config& config) {

        size_t nameReserve = config.nameLengthReserve;

        if (nameReserve == 0) {
            for (const auto& item : content) {
                const auto name = item.filename().u8string();
                nameReserve = std::max(
                    nameReserve,
                    utf8::char_count(name)
                );
            }
        }
        else {
            nameReserve = std::max<size_t>(config.nameLengthReserve, lspp_config::NAME_WIDTH_MIN);
        }

        std::string out;
        out.reserve(
            static_cast<uintmax_t>(content.size()) *
            (nameReserve + config.dateLengthReserve)
        );

        const auto spacing = config.spacing;
        uintmax_t totalSize = 0;

        const size_t maxNumber = content.size();
        const size_t numberWidth = std::to_string(content.size()).size();

        const auto lineLimit = config.lineLimit == 0
            ? content.size()
            : std::min(config.lineLimit, content.size());

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
                        std::string name = get_name(item, nameReserve, config.splitter);
                        name.append(spacing, ' ');
                        line += name;
                        break;
                    }
                    case Column::Date: {
                        std::string date = format_time(item.last_write());
                        date.append(spacing, ' ');
                        line += date;
                        break;
                    }
                    case Column::Size: {

                        auto size = item.size();

                        if (size.has_value())
                            line += get_human_size(size.value());
                        else
                            line.append(config.sizeLengthReserve, ' ');

                        line.append(spacing, ' ');

                        break;
                    }
                }
            }

            line += '\n';
            out += line;
        }

        std::cout << out;
    }
}