#include <algorithm>
#include <cstdint>
#include <functional>
#include <ranges>
#include <string_view>
#include <utility>
#include <vector>

#include "util.hpp"

constexpr static std::string_view input{
#include "../dataset/day09_1.txt"
};

namespace rv = std::ranges::views;
namespace rg = std::ranges;

using P = std::pair<std::int64_t, std::int64_t>;

template <bool Last = true>
constexpr auto predict(const auto &line) {
    std::vector<std::int64_t> nums{};
    std::int64_t ret{}, sign = 1;
    for (auto num : line | rv::split(' '))
        nums.push_back((*num.begin()) == '-' ? -(std::int64_t)util::parse_digits(num | rv::drop(1))
                                             : util::parse_digits(num));
    while (rg::any_of(nums, std::identity{})) {
        if constexpr (Last) {
            ret += nums.back();
        } else {
            ret += sign * nums[0];
            sign = -sign;
        }
        for (auto i : rv::iota(ZERO, nums.size() - 1)) nums[i] = nums[i + 1] - nums[i];
        nums.pop_back();
    }
    return ret;
}

constexpr auto solution1(const std::string_view str) {
    return util::reduce(str | rv::split('\n'), [](auto &&r) { return predict(FWD(r)); });
}

constexpr auto solution2(const std::string_view str) {
    return util::reduce(str | rv::split('\n'), [](auto &&r) { return predict<false>(FWD(r)); });
}

int main() {
    constexpr auto i = solution1(input);
    constexpr auto j = solution2(input);
    util::print(i, j);
}
