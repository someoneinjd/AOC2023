#include <algorithm>
#include <ranges>
#include <string>
#include <string_view>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day13_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr auto find_diff(const auto &pattern, std::size_t diff = 0) {
    for (auto i : rv::iota(ZERO, pattern.size() - 1)) {
        const auto pos_len = std::min(i + 1, pattern.size() - i - 1);
        if (util::reduce(rv::iota(ZERO, pos_len), [&](auto x) {
                return util::reduce(rv::iota(ZERO, pattern[0].size()), [&](auto y) -> std::size_t {
                    return pattern[i - x][y] != pattern[i + 1 + x][y];
                });
            }) == diff)
            return i + 1;
    }
    return ZERO;
}

constexpr auto count(const std::string_view str, std::size_t diff = 0) {
    using std::operator""sv;
    auto sum = ZERO;
    for (auto pattern_str : str | rv::split("\n\n"sv)) {
        std::vector<std::string_view> pattern{};
        for (auto line : pattern_str | rv::split('\n'))
            pattern.emplace_back(rg::begin(line), rg::end(line));
        const auto i = find_diff(pattern, diff);
        if (i != 0) {
            sum += 100 * i;
        } else {
            std::vector<std::string> transposed(pattern[0].size(),
                                                std::string(pattern.size(), '1'));
            for (auto i : rv::iota(ZERO, pattern[0].size()))
                for (auto j : rv::iota(ZERO, pattern.size())) transposed[i][j] = pattern[j][i];
            sum += find_diff(transposed, diff);
        }
    }
    return sum;
}

constexpr auto solution1(const std::string_view str) { return count(str, 0); }

constexpr auto solution2(const std::string_view str) { return count(str, 1); }

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
