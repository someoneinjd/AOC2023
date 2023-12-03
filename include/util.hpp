#pragma once

#define FWD(r) std::forward<decltype(r)>(r)

namespace util {

constexpr bool is_digit(char ch) { return ch >= '0' && ch <= '9'; }

constexpr bool is_alpha(char ch) {
    return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z');
}
}  // namespace util
