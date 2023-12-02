#include <algorithm>
#include <cstddef>
#include <print>
#include <ranges>
#include <string_view>

#include "util.hpp"

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr std::string_view input1{
#include "../dataset/day02_1.txt"
};

constexpr std::size_t RED_NUM = 12;
constexpr std::size_t GREEN_NUM = 13;
constexpr std::size_t BLUE_NUM = 14;

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

consteval auto parse_and_check_color(auto &&r, std::size_t num) {
    auto begin = rg::find_if(r, util::is_alpha);
    auto end = rg::find_if_not(begin, rg::end(r), util::is_alpha);
    const std::string_view str{begin, end};

    if (str == "red") return num <= RED_NUM;
    if (str == "green") return num <= GREEN_NUM;
    if (str == "blue") return num <= BLUE_NUM;
    return false;
}

consteval auto solution1(const std::string_view input) {
    std::size_t sum{};

    constexpr auto check_set = [](auto &&r) {
        for (auto cube : r | rv::split(',')) {
            const auto [left, num] = parse_num(cube);
            if (!parse_and_check_color(left, num)) return false;
        }
        return true;
    };

    for (auto line : input | rv::split('\n')) {
        const auto [left, id] = parse_num(line);
        bool possible = true;
        for (auto set : left | rv::split(';'))
            possible = possible && check_set(set);
        if (possible) sum += id;
    }

    return sum;
}

int main() {
    constexpr auto i = solution1(input1);
    std::println("{}\n{}", i, 0);
}
