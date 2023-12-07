#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string_view>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day06_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr auto count_win(auto time, auto distance) {
    auto search_space = rv::iota(ONE, time / 2 + 1);
    auto first_match = *rg::lower_bound(search_space, distance,
                                        [&](auto i, auto j) { return i * (time - i) < j; });
    return time - first_match - first_match + 1;
}

constexpr auto solution1(const std::string_view str) {
    std::vector<std::size_t> nums{};
    for (auto line : str | rv::split('\n'))
        for (auto num : line | rv::split(' ') | rv::filter([](auto &&r) {
                            return (not rg::empty(r)) && util::is_digit(*r.begin());
                        }))
            nums.push_back(util::parse_digits(num));

    auto product = ONE;
    for (std::size_t i : rv::iota(ZERO, nums.size() / 2))
        product *= count_win(nums[i], nums[i + nums.size() / 2]);
    return product;
}

constexpr auto solution2(const std::string_view str) {
    std::vector<std::size_t> nums{};
    for (auto line : str | rv::split('\n')) {
        std::vector<std::string_view> num_strs{};
        for (auto num : line | rv::split(' ') | rv::filter([](auto &&r) {
                            return (not rg::empty(r)) && util::is_digit(*r.begin());
                        }))
            num_strs.emplace_back(rg::begin(num), rg::end(num));
        nums.push_back(util::parse_digits(num_strs | rv::join));
    }
    return count_win(nums[0], nums[1]);
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
