#include <algorithm>
#include <cstdint>
#include <ranges>
#include <string_view>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day07_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

using P = std::tuple<std::array<std::uint8_t, 5>, std::size_t, std::size_t>;

constexpr auto get_kind(const auto &cards) {
    std::vector<std::pair<std::size_t, std::uint8_t>> parts{};
    auto begin = ZERO, count_j = ZERO;
    while (begin < 5) {
        std::size_t count = 1;
        while (count + begin < 5 && cards[begin] == cards[begin + count]) count++;
        if (cards[begin] == 0)
            count_j = count;
        else
            parts.emplace_back(count, cards[begin]);
        begin += count;
    }
    rg::sort(parts);
    if (parts.empty()) return 6;
    parts.back().first += count_j;
    switch (parts.size()) {
        case 1: return 6;
        case 2: return 4 + (parts.back().first == 4);
        case 3: return 2 + (parts.back().first == 3);
        case 4: return 1;
        case 5: return 0;
    }
    return 0;
}

constexpr auto solution(const std::string_view str, std::uint8_t j_num) {
    std::vector<P> hands{};
    for (auto line : str | rv::split('\n')) {
        const std::string_view ls{line.begin(), line.end()};
        std::array<std::uint8_t, 5> cards_{};
        rg::transform(ls.substr(0, 5), cards_.begin(), [=](char ch) -> std::uint8_t {
            if (ch <= '9') return ch - '0';
            switch (ch) {
                case 'T': return 10;
                case 'J': return j_num;
                case 'Q': return 12;
                case 'K': return 13;
                case 'A': return 14;
            }
            return 255;
        });
        auto cards = cards_;
        rg::sort(cards);
        hands.emplace_back(cards_, get_kind(cards), util::parse_digits(ls.substr(6)));
    }
    rg::sort(hands, [](const auto &a, const auto &b) {
        const auto i = std::get<1>(a), j = std::get<1>(b);
        return (i != j) ? i < j : std::get<0>(a) < std::get<0>(b);
    });
    auto sum = ZERO;
    for (auto i = ZERO; i < hands.size(); i++) sum += (i + 1) * std::get<2>(hands[i]);
    return sum;
}

constexpr auto solution1(const std::string_view str) { return solution(str, 11); }

constexpr auto solution2(const std::string_view str) { return solution(str, 0); }

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
