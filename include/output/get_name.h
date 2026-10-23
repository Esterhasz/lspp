#pragma once
#include <string>
#include "Item.h"
#include "utf8.h"
#include "shorten_name.h"

inline std::string get_name(const Item& item, size_t reserve, const std::string& splitter) {
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