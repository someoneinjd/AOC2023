#include <algorithm>
#include <cstddef>
#include <format>
#include <functional>
#include <ranges>
#include <string_view>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day05_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

constexpr auto parse_map(auto &&r) {
    return r | rv::split('\n') | rv::filter([](auto &&r) { return util::is_digit(*r.begin()); }) |
           rv::transform([](auto line) {
               std::array<std::size_t, 3> nums{};
               std::size_t i = 0;
               for (auto num : line | rv::split(' ')) nums[i++] = util::parse_digits(num);
               return std::array{nums[1], nums[1] + nums[2], nums[0]};
           });
}

constexpr auto parse_seeds(const std::string_view str) {
    std::vector<std::size_t> seeds{};
    const auto begin = str.find(' ');
    const auto end = str.find('\n');
    for (auto seed :
         str.substr(begin, end - begin) | rv::split(' ') | rv::filter(std::not_fn(rg::empty)))
        seeds.push_back(util::parse_digits(seed));
    return std::pair{seeds, str.substr(end + 1)};
}

constexpr auto solution1(const std::string_view str) {
    auto [seeds, left] = parse_seeds(str);
    for (auto map : left | rv::split(':')) {
        auto new_seeds = seeds;
        for (auto [s_beg, s_end, d_beg] : parse_map(map)) {
            std::size_t idx = 0;
            for (auto i : seeds) {
                if (i >= s_beg && i < s_end) new_seeds[idx] = i - s_beg + d_beg;
                idx++;
            }
        }
        seeds = new_seeds;
    }
    return rg::min(seeds);
}

constexpr auto solution2(const std::string_view str) {
    auto [nums, left] = parse_seeds(str);

    using R = std::pair<std::size_t, std::size_t>;
    std::vector<R> seeds{};
    for (std::size_t i = 0; i < nums.size(); i += 2)
        seeds.emplace_back(nums[i], nums[i] + nums[i + 1]);
    for (auto map : left | rv::split(':')) {
        decltype(seeds) new_seeds{};
        for (auto [s_beg, s_end, d_beg] : parse_map(map)) {
            for (std::size_t idx = 0; idx < seeds.size();) {
                auto [beg, end] = seeds[idx];
                if (beg < s_end && end > s_beg) {
                    seeds.erase(rg::next(seeds.begin(), idx));
                    if (beg < s_beg) {
                        seeds.emplace_back(beg, s_beg);
                        if (end <= s_end) {
                            new_seeds.emplace_back(d_beg, end - s_beg + d_beg);
                        } else {
                            new_seeds.emplace_back(d_beg, s_end - s_beg + d_beg);
                            seeds.emplace_back(s_end, end);
                        }
                    } else {
                        if (end <= s_end) {
                            new_seeds.emplace_back(beg - s_beg + d_beg, end - s_beg + d_beg);
                        } else {
                            new_seeds.emplace_back(beg - s_beg + d_beg, s_end - s_beg + d_beg);
                            seeds.emplace_back(s_end, end);
                        }
                    }
                } else {
                    idx++;
                }
            }
        }
        seeds.insert(seeds.end(), new_seeds.begin(), new_seeds.end());
    }

    return rg::min(seeds, {}, &R::first).first;
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
