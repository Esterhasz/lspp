#pragma once
#include <string_view>
#include "lspp_config.h"
#include "fn/parse_size.h"

namespace argument {
    
    void set_columns(lspp_config&, std::string_view);

    inline void set_line_limit(lspp_config& cfg, std::string_view value) {
        cfg.print.lineLimit = fn::parse_size(value);
    }
    inline void set_spacing(lspp_config& cfg, std::string_view value) {
        cfg.print.spacing = fn::parse_size(value);
    }
    inline void set_name_width(lspp_config& cfg, std::string_view value) {
        cfg.print.nameLengthReserve = fn::parse_size(value);
    }
}