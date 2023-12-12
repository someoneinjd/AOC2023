#include <algorithm>
#include <cstddef>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day11_1.txt"
};

namespace rv = std::views;
namespace rg = std::ranges;

using P = std::pair<std::size_t, std::size_t>;

constexpr auto solution(const std::string_view str) {
    std::vector<P> galaxy{};
    std::vector<std::size_t> galaxy_row(rg::count(str, '\n') + 1), galaxy_col(str.find('\n'));
    for (auto x = ZERO; auto line : str | rv::split('\n')) {
        for (auto y = ZERO; char c : line) {
            if (c == '#') {
                galaxy.emplace_back(x, y);
                galaxy_row[x] = '\1';
                galaxy_col[y] = '\1';
            }
            y++;
        }
        x++;
    }

    constexpr auto distance = [](auto count, auto row_d, auto col_d, auto expand) {
        return (row_d ? expand * (row_d - 1) + 1 : ZERO) +
               (col_d ? expand * (col_d - 1) + 1 : ZERO) - count * (expand - 1);
    };

    auto sum_0 = ZERO, sum_1 = ZERO;
    for (auto i = ZERO; auto [x0, y0] : galaxy) {
        for (auto [x1, y1] : galaxy | rv::drop(i + 1)) {
            const auto [min_row, max_row] = std::minmax(x0, x1);
            const auto [min_col, max_col] = std::minmax(y0, y1);
            const auto row_d = max_row - min_row, col_d = max_col - min_col;
            const auto count =
                (row_d > 1 ? util::reduce(galaxy_row | rv::take(max_row) | rv::drop(min_row + 1))
                           : ZERO) +
                (col_d > 1 ? util::reduce(galaxy_col | rv::take(max_col) | rv::drop(min_col + 1))
                           : ZERO);
            sum_0 += distance(count, row_d, col_d, 2);
            sum_1 += distance(count, row_d, col_d, 1000000);
        }
        i++;
    }
    return std::pair{sum_0, sum_1};
}

int main() {
    const auto [i, j] = solution(input);
    util::print(i, j);
}
