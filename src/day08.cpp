#include <algorithm>
#include <array>
#include <functional>
#include <numeric>
#include <ranges>
#include <string_view>
#include <utility>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day08_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

using P = std::pair<std::array<char, 3>, std::array<std::array<char, 3>, 2>>;

constexpr auto parse_map(const std::string_view str) {
    std::vector<P> map{};
    const auto first_newline = str.find('\n');
    const auto instructions = str.substr(0, first_newline);
    for (auto line :
         str.substr(first_newline) | rv::split('\n') | rv::filter(std::not_fn(rg::empty))) {
        const std::string_view line_str{line.begin(), line.end()};
        map.emplace_back(std::array{line_str[0], line_str[1], line_str[2]},
                         std::array{std::array{line_str[7], line_str[8], line_str[9]},
                                    std::array{line_str[12], line_str[13], line_str[14]}});
    }
    rg::sort(map, {}, &P::first);
    return std::pair{std::move(map), instructions};
}

constexpr auto find_z(const auto instructions, const auto &map, auto current, auto &&pred) {
    auto step = ZERO;
    for (; not pred(current); step++)
        current = rg::lower_bound(map, current, {}, &P::first)
                      ->second[instructions[step % instructions.length()] == 'R'];
    return step;
}

constexpr auto solution1(const std::string_view str) {
    const auto [map, instructions] = parse_map(str);
    return find_z(instructions, map, std::array{'A', 'A', 'A'}, [](auto a) {
        return a == std::array{'Z', 'Z', 'Z'};
    });
}

constexpr auto solution2(const std::string_view str) {
    const auto [map, instructions] = parse_map(str);
    auto lcm = ONE;
    for (auto begin : map | rv::filter([](const auto &a) { return a.first[2] == 'A'; }))
        lcm = std::lcm(lcm,
                       find_z(instructions, map, begin.first, [](auto a) { return a[2] == 'Z'; }));
    return lcm;
}

int main() {
    const auto i = solution1(input);
    const auto j = solution2(input);
    util::print(i, j);
}
