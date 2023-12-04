#include <algorithm>
#include <array>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <string_view>
#include <vector>

#include "util.hpp"

constexpr std::string_view input{
#include "../dataset/day04_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr auto match(auto first1, auto last1, auto first2, auto last2) {
    constexpr auto parse_nums = [](auto &&r) {
        std::vector<std::size_t> nums{};
        for (auto num : r | rv::split(' ') | rv::filter([](auto &&r) { return not rg::empty(r); }))
            nums.push_back(util::parse_digits(num));
        return nums;
    };
    const auto winning = parse_nums(rg::subrange(first1, last1));
    const auto we_have = parse_nums(rg::subrange(first2, last2));

    std::size_t sum{};
    for (auto num : we_have) sum += rg::find(winning, num) != rg::end(winning);
    return sum;
};

constexpr auto solution1(const std::string_view str) {
    std::size_t sum{};
    for (auto line : str | rv::split('\n')) {
        auto winning_num_begin = rg::next(rg::find(line, ':'));
        auto winning_num_end = rg::find(line, '|');
        auto num =
            match(winning_num_begin, winning_num_end, rg::next(winning_num_end), rg::end(line));
        if (num > 0) sum += 1 << (num - 1);
    }
    return sum;
}

constexpr auto solution2(const std::string_view str) {
    constexpr auto length = rg::count(input, '\n') + 1;
    std::array<std::size_t, length> card_nums{};
    std::size_t i = 0, sum = 0;
    for (auto line : str | rv::split('\n')) {
        card_nums[i] += 1;
        auto winning_num_begin = rg::next(rg::find(line, ':'));
        auto winning_num_end = rg::find(line, '|');
        auto num =
            match(winning_num_begin, winning_num_end, rg::next(winning_num_end), rg::end(line));
        for (auto j : rv::iota(i + 1, i + 1 + num)) card_nums[j] += card_nums[i];
        sum += card_nums[i++];
    }
    return sum;
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
