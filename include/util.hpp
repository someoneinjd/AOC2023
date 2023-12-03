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

template <std::ranges::input_range Range1, std::ranges::input_range Range2,
          class Pred = std::ranges::equal_to, class Proj1 = std::identity,
          class Proj2 = std::identity>
    requires std::indirectly_comparable<std::ranges::iterator_t<Range1>,
                                        std::ranges::iterator_t<Range2>, Pred, Proj1, Proj2>
constexpr bool starts_with(Range1 &&range1, Range2 &&range2, Pred pred = {}, Proj1 proj1 = {},
                           Proj2 proj2 = {}) {
    return std::ranges::mismatch(std::ranges::begin(range1), std::ranges::end(range1),
                                 std::ranges::begin(range2), std::ranges::end(range2), pred, proj1,
                                 proj2)
               .in2 == std::ranges::end(range2);
}

void print(auto &&...args) {
#if __has_include(<print>)
    (std::println("{}", FWD(args)), ...);
#else
    ((std::cout << FWD(args) << "\n"), ...);
#endif
}

}  // namespace util
