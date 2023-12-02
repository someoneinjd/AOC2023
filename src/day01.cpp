#include <algorithm>
#include <cstddef>
#include <iterator>
#include <print>
#include <ranges>
#include <string_view>
#include <utility>

constexpr std::string_view input{
#include "../dataset/day01_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

consteval std::size_t solution1(const std::string_view input) {
    std::size_t sum{};
    constexpr auto find_first = [](auto &&r) consteval {
        return *rg::find_if(r, [](char ch) { return ch >= '0' && ch <= '9'; }) -
               '0';
    };
    for (auto line : input | rv::split('\n'))
        sum += 10 * find_first(line) + find_first(line | rv::reverse);
    return sum;
}

template <bool Reverse, std::size_t... I>
consteval std::size_t match(auto &&r, std::index_sequence<I...>) {
    constexpr std::string_view nums[] = {
        "one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};
    std::size_t ret = 10;
    if constexpr (Reverse)
        ([&] {
            return rg::starts_with(r, nums[I] | rv::reverse) && (ret = I + 1);
        }() ||
         ...);
    else
        ([&] { return rg::starts_with(r, nums[I]) && (ret = I + 1); }() || ...);
    return ret;
}

template <bool Reverse>
consteval std::size_t match(auto &&r) {
    return match<Reverse>(std::forward<decltype(r)>(r),
                          std::make_index_sequence<9>{});
}

consteval std::size_t solution2(const std::string_view input) {
    std::size_t sum{};
    constexpr auto find_first = []<bool Reverse = false>(auto &&r) consteval {
        auto begin = rg::begin(r);
        auto end = rg::end(r);
        std::size_t first;
        for (; begin != end; begin = rg::next(begin)) {
            if (*begin >= '0' && *begin <= '9') {
                first = *begin - '0';
                break;
            };
            if ((first = match<Reverse>(rg::subrange(begin, end))) != 10) break;
        }
        return first;
    };
    for (auto line : input | rv::split('\n')) {
        sum += find_first(line) * 10 +
               find_first.template operator()<true>(line | rv::reverse);
    }
    return sum;
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    std::println("{}\n{}", i, j);
    return 0;
}
