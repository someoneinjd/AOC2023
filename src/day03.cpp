#include <algorithm>
#include <iterator>
#include <ranges>
#include <string_view>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day03_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr auto line_length = input.find('\n');

constexpr auto to_map(const std::string_view str) {
    std::vector<std::string> vec(line_length + 2, std::string(line_length + 2, '.'));
    auto i = ONE;
    for (auto line : str | rv::split('\n')) rg::copy(line, rg::next(vec[i++].begin()));
    return vec;
}

constexpr auto solution1(const std::string_view str) {
    const auto map = to_map(str);

    constexpr auto check_neigh = [](std::size_t line, std::size_t begin, std::size_t end,
                                    const auto &map) {
        return rg::any_of(std::array{line - 1, line + 1},
                          [&](auto x) {
                              return rg::any_of(rv::iota(begin - 1, end + 1),
                                                [&](auto column) { return map[x][column] != '.'; });
                          }) ||
               map[line][begin - 1] != '.' || map[line][end] != '.';
    };

    auto sum = ZERO;
    for (auto line : rv::iota(ONE, line_length + 1)) {
        const auto begin = map[line].begin();
        const auto end = map[line].end();
        for (auto iter = rg::find_if(map[line], util::is_digit); iter != end;
             iter = rg::find_if(iter, end, util::is_digit)) {
            auto num_end = rg::find_if_not(iter, end, util::is_digit);
            if (check_neigh(line, rg::distance(begin, iter), rg::distance(begin, num_end), map))
                sum += util::parse_digits(iter, num_end);
            iter = num_end;
        }
    }
    return sum;
}

constexpr auto solution2(const std::string_view str) {
    const auto map = to_map(str);

    constexpr auto check_neigh = [](std::size_t line, std::size_t begin, std::size_t end,
                                    const auto &map) {
        std::vector<std::size_t> vec{};
        for (auto x : rv::iota(line - 1, line + 2))
            for (auto y : rv::iota(begin - 1, end + 1))
                if (map[x][y] == '*') vec.push_back(y + x * map.size());
        return vec;
    };

    using T = std::pair<std::size_t, std::vector<size_t>>;
    std::vector<T> vec{};
    for (auto line : rv::iota(ONE, line_length + 1)) {
        const auto begin = map[line].begin();
        const auto end = map[line].end();
        for (auto iter = rg::find_if(map[line], util::is_digit); iter != end;
             iter = rg::find_if(iter, end, util::is_digit)) {
            auto num_end = rg::find_if_not(iter, end, util::is_digit);
            auto num = util::parse_digits(iter, num_end);
            for (auto index :
                 check_neigh(line, rg::distance(begin, iter), rg::distance(begin, num_end), map)) {
                if (auto ret = rg::find(vec, index, &T::first); ret != vec.end())
                    ret->second.push_back(num);
                else
                    vec.emplace_back(index, std::vector{num});
            }
            iter = num_end;
        }
    }

    return util::reduce(vec, [](auto &&i) {
        const auto &[_, nums] = i;
        if (nums.size() == 2) return nums[0] * nums[1];
        return ZERO;
    });
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
