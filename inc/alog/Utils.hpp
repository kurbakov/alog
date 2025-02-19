#pragma once

#include <cxxabi.h>
#include <execinfo.h>
#include <stacktrace>
#include <string_view>
#include <unistd.h>

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

std::string get_stacktrace(const int max_frames = 100)
{
    void* array[max_frames];
    int size;

    // Get the stack frames
    size = backtrace(array, max_frames);

    // Convert the stack frames to strings
    char** strings = backtrace_symbols(array, size);
    if (strings == nullptr) {
        return "Error: backtrace_symbols failed";
    }

    // Create a string stream to hold the stack trace
    std::ostringstream stacktrace;
    for (int i = 0; i < size; ++i) {
        stacktrace << strings[i] << "\n";
    }

    // Free the strings array
    free(strings);

    return stacktrace.str();
}

} // namespace alog
