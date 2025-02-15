#pragma once

#include <string_view>

namespace alog {

consteval size_t placeholders_count(const std::string_view view, const std::string_view pattern)
{
    size_t res { 0 }, pos { 0 };
    while (pos = view.find(pattern, pos), pos != std::string_view::npos) {
        ++res;
        pos += pattern.size();
    }
    return res;
}

template <typename... Args>
consteval size_t args_count(Args&&... args) { return sizeof...(args); }

} // namespace alog
