#pragma once

#if __has_include(<print>)
#include <print>
#else
#include <iostream>
#endif

#include <cstddef>
#include <ranges>

#define FWD(r) std::forward<decltype(r)>(r)

namespace util {

constexpr bool is_digit(char ch) { return ch >= '0' && ch <= '9'; }

constexpr bool is_alpha(char ch) { return (ch >= 'A' && ch <= 'Z') || (ch >= 'a' && ch <= 'z'); }

constexpr std::size_t parse_digits(const auto &r) {
    std::size_t val = 0;
    for (char ch : r) {
        val += ch - '0';
        val *= 10;
    }
    return val / 10;
}

constexpr std::size_t parse_digits(const auto &begin, const auto &end) {
    return parse_digits(std::ranges::subrange(begin, end));
}

void print(auto &&...args) {
#if __has_include(<print>)
    (std::println("{}", FWD(args)), ...);
#else
    ((std::cout << FWD(args) << "\n"), ...);
#endif
}

}  // namespace util
