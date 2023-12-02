#include <algorithm>
#include <array>
#include <cstddef>
#include <print>
#include <ranges>
#include <string_view>

#include "util.hpp"

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr std::string_view input{
#include "../dataset/day02_1.txt"
};

consteval auto parse_num(auto &&r) {
    auto begin = rg::find_if(r, util::is_digit);
    auto end = rg::find_if_not(begin, rg::end(r), util::is_digit);
    std::size_t val{};
    for (char ch : rg::subrange(begin, end)) {
        val += ch - '0';
        val *= 10;
    }
    return std::pair{rg::subrange(end, rg::end(r)), val / 10};
}

consteval auto parse_color(auto &&r) {
    char ch = *rg::find_if(r, util::is_alpha);
    return (ch <= 'g') + (ch == 'b');
}

consteval auto solution1(const std::string_view input) {
    constexpr auto check_set = [](auto &&r) {
        for (auto cube : r | rv::split(',')) {
            const auto [left, num] = parse_num(cube);
            if (num > 12 + parse_color(left)) return false;
        }
        return true;
    };

    std::size_t sum{};
    for (auto line : input | rv::split('\n')) {
        const auto [left, id] = parse_num(line);
        if (rg::all_of(left | rv::split(';'), check_set)) sum += id;
    }

    return sum;
}

consteval auto solution2(const std::string_view input) {
    constexpr auto check_set = [](auto &&r) {
        std::array<std::size_t, 3> nums{};
        for (auto cube : r | rv::split(',')) {
            const auto [left, num] = parse_num(cube);
            nums[parse_color(left)] = num;
        }
        return nums;
    };

    std::size_t sum{};
    for (auto line : input | rv::split('\n')) {
        size_t max_red = 0, max_green = 0, max_blue = 0;
        const auto [left, _] = parse_num(line);
        for (auto set : left | rv::split(';')) {
            const auto [r, g, b] = check_set(set);
            max_red = std::max(max_red, r);
            max_green = std::max(max_green, g);
            max_blue = std::max(max_blue, b);
        }
        sum += max_red * max_green * max_blue;
    }
    return sum;
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    std::println("{}\n{}", i, j);
}
