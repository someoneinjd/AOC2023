#include <algorithm>
#include <array>
#include <cstddef>
#include <ranges>
#include <string_view>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day02_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr auto parse_num(auto &&r) {
    auto begin = rg::find_if(FWD(r), util::is_digit);
    auto end = rg::find_if_not(begin, rg::end(r), util::is_digit);
    return std::pair{rg::subrange(end, rg::end(r)), util::parse_digits(begin, end)};
}

constexpr auto parse_color(auto &&r) {
    char ch = *rg::find_if(FWD(r), util::is_alpha);
    return (ch <= 'g') + (ch == 'b');
}

constexpr auto solution1(const std::string_view str) {
    constexpr auto check_set = [](auto &&r) {
        for (auto cube : r | rv::split(',')) {
            const auto [left, num] = parse_num(cube);
            if (num > 12u + parse_color(left)) return false;
        }
        return true;
    };

    return util::reduce(str | rv::split('\n'), [check_set](auto &&r) {
        const auto [left, id] = parse_num(FWD(r));
        if (rg::all_of(left | rv::split(';'), check_set)) return id;
        return ZERO;
    });
}

constexpr auto solution2(const std::string_view str) {
    constexpr auto check_set = [](auto &&r, auto &&max_nums) {
        for (auto cube : r | rv::split(',')) {
            const auto [left, num] = parse_num(cube);
            auto color = parse_color(left);
            max_nums[color] = std::max(max_nums[color], num);
        }
    };

    return util::reduce(str | rv::split('\n'), [check_set](auto &&r) {
        std::array<std::size_t, 3> max_nums{};
        const auto [left, _] = parse_num(FWD(r));
        for (auto set : left | rv::split(';')) check_set(set, max_nums);
        return max_nums[0] * max_nums[1] * max_nums[2];
    });
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
