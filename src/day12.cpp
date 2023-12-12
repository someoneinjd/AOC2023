#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string_view>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day12_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr auto arrangement(const auto &cond_str, const auto &nums) {
    const std::string_view cond_view{rg::begin(cond_str), rg::end(cond_str)};
    const auto len_i = nums.size(), len_j = cond_view.size();
    auto a = std::vector(len_i + 1, std::vector(len_j + 1, ZERO));
    a[0][0] = 1;
    for (auto j : rv::iota(ONE, len_j + 1)) a[0][j] = a[0][j - 1] && cond_view[len_j - j] != '#';
    for (auto i : rv::iota(ONE, len_i + 1)) {
        for (auto j : rv::iota(ONE, len_j + 1)) {
            const auto n = nums[len_i - i];
            if (cond_str[len_j - j] == '.') {
                a[i][j] = a[i][j - 1];
            } else {
                if (j == n &&
                    !rg::any_of(cond_str | rv::drop(len_j - j), [](char x) { return x == '.'; }))
                    a[i][j] = i == 1;
                else if (j > n &&
                         !rg::any_of(cond_str | rv::drop(len_j - j) | rv::take(n),
                                     [](char x) { return x == '.'; }) &&
                         cond_str[len_j - j + n] != '#')
                    a[i][j] = a[i - 1][j - n - 1];
                if (cond_str[len_j - j] == '?') a[i][j] += a[i][j - 1];
            }
        }
    }
    return a.back().back();
}

constexpr auto solution1(const std::string_view str) {
    return util::reduce(str | rv::split('\n'), [](auto line) {
        const std::string_view line_str{rg::begin(line), rg::end(line)};
        const auto delim = line_str.find(' ');
        const auto cond_str = line_str.substr(0, delim);
        std::vector<std::size_t> nums{};
        for (auto num : line_str.substr(delim + 1) | rv::split(','))
            nums.push_back(util::parse_digits(num));
        return arrangement(cond_str, nums);
    });
}

constexpr auto solution2(const std::string_view str) {
    return util::reduce(str | rv::split('\n'), [](auto line) {
        const std::string_view line_str{rg::begin(line), rg::end(line)};
        const auto delim = line_str.find(' ');
        const auto cond_str = line_str.substr(0, delim);
        std::vector<std::size_t> tmp{};
        for (auto num : line_str.substr(delim + 1) | rv::split(','))
            tmp.push_back(util::parse_digits(num));
        auto nums = tmp;
        std::string str(cond_str.data(), cond_str.size());
        str.reserve(str.size() * 5 + 4);
        nums.reserve(nums.size() * 5);
        for (auto _ : rv::iota(ZERO, ZERO + 4)) {
            nums.insert(nums.end(), tmp.begin(), tmp.end());
            str += "?";
            str += cond_str;
        }
        return arrangement(str, nums);
    });
}

int main() {
    const auto i = solution1(input);
    const auto j = solution2(input);
    util::print(i, j);
}
