#include <algorithm>
#include <array>
#include <numeric>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day08_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

using P = std::pair<std::size_t, std::array<std::size_t, 3>>;
using R = std::pair<std::size_t, std::size_t>;

constexpr auto indexes = []() constexpr {
    std::array<R, rg::count(input, '=')> indexes{};
    const auto first_newline = input.find('\n');
    const auto left = input.substr(first_newline + 2);
    auto count = ZERO;
    for (auto line : left | rv::split('\n')) {
        const std::string_view line_str{line.begin(), line.end()};
        indexes[count] = std::pair{(line_str[0] << 16) + (line_str[1] << 8) + line_str[2], count};
        count++;
    }
    rg::sort(indexes, {}, &R::first);
    return indexes;
}();

constexpr auto get_index(std::size_t i) {
    return rg::lower_bound(indexes, i, {}, &R::first)->second;
}

constexpr auto parse_map(const std::string_view str) {
    constexpr auto to_integer = [](char a, char b, char c) -> std::size_t {
        return (a << 16) + (b << 8) + c;
    };
    std::vector<P> map{};
    const auto first_newline = str.find('\n');
    const auto left = str.substr(first_newline + 2);
    for (auto line : left | rv::split('\n')) {
        const std::string_view line_str{line.begin(), line.end()};
        map.emplace_back(get_index(to_integer(line_str[0], line_str[1], line_str[2])),
                         std::array{get_index(to_integer(line_str[7], line_str[8], line_str[9])),
                                    get_index(to_integer(line_str[12], line_str[13], line_str[14])),
                                    to_integer(line_str[0], line_str[1], line_str[2])});
    }
    rg::sort(map, {}, &P::first);
    return std::pair{std::move(map), str.substr(0, first_newline)};
}

constexpr auto find_z(const auto instructions, const auto &map, auto current, auto &&pred) {
    auto step = ZERO;
    for (; not pred(map[current].second[2]); step++)
        current = map[current].second[instructions[step % instructions.length()] == 'R'];
    return step;
}

constexpr auto solution1(const std::string_view str) {
    const auto [map, instructions] = parse_map(str);
    return find_z(instructions, map, get_index(0x00414141), [](auto a) { return a == 0x005a5a5a; });
}

constexpr auto solution2(const std::string_view str) {
    const auto [map, instructions] = parse_map(str);
    auto lcm = ONE;
    for (auto begin : map | rv::filter([](const auto &a) { return (a.second[2] & 0xff) == 0x41; }))
        lcm = std::lcm(
            lcm, find_z(instructions, map, begin.first, [](auto a) { return (a & 0xff) == 0x5a; }));
    return lcm;
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
