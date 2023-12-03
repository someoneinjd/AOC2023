#pragma once

#if __has_include(<print>)
#include <print>
#else
#include <iostream>
#endif

#define FWD(r) std::forward<decltype(r)>(r)

namespace util {

constexpr bool is_digit(char ch) { return ch >= '0' && ch <= '9'; }

constexpr bool is_alpha(char ch) { return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'); }

void print(auto &&...args) {
#if __has_include(<print>)
    (std::println("{}", FWD(args)), ...);
#else
    ((std::cout << FWD(args) << "\n"), ...);
#endif
}

}  // namespace util
