#include <algorithm>
#include <cstddef>
#include <iterator>
#include <ranges>
#include <string_view>
#include <utility>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day01_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr std::size_t solution1(const std::string_view str) {
    constexpr auto find_first = [](auto &&r) { return *rg::find_if(FWD(r), util::is_digit) - '0'; };
    return util::reduce(str | rv::split('\n'), [find_first](auto &&r) {
        return 10 * find_first(r) + find_first(r | rv::reverse);
    });
}

template <bool Reverse, std::size_t... I>
constexpr std::size_t match(auto &&r, std::index_sequence<I...>) {
    constexpr std::string_view nums[] = {"one", "two",   "three", "four", "five",
                                         "six", "seven", "eight", "nine"};
    auto ret = ZERO;
    if constexpr (Reverse)
        ((util::starts_with(FWD(r), nums[I] | rv::reverse) && (ret = I + 1)) || ...);
    else
        ((util::starts_with(FWD(r), nums[I]) && (ret = I + 1)) || ...);
    return ret;
}

template <bool Reverse>
constexpr std::size_t match(auto &&r) {
    return match<Reverse>(FWD(r), std::make_index_sequence<9>{});
}

constexpr std::size_t solution2(const std::string_view str) {
    constexpr auto find_first = []<bool Reverse = false>(auto &&r) {
        auto begin = rg::begin(r);
        auto end = rg::end(r);
        std::size_t first;
        for (; begin != end; begin = rg::next(begin)) {
            if (util::is_digit(*begin)) {
                first = *begin - '0';
                break;
            };
            if ((first = match<Reverse>(rg::subrange(begin, end)))) break;
        }
        return first;
    };
    return util::reduce(str | rv::split('\n'), [find_first](auto &&r) {
        return 10 * find_first(r) + find_first.operator()<true>(r | rv::reverse);
    });
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
