from functools import cache


@cache
def arrangement(cond_str: str, nums: tuple[int, ...]) -> int:
    if len(nums) == 0:
        return not any(x == "#" for x in cond_str)
    elif len(cond_str) == 0:
        return 0
    else:
        n = nums[0]
        match cond_str[0]:
            case ".":
                return arrangement(cond_str[1:], nums)
            case "?":
                return arrangement("#" + cond_str[1:], nums) + arrangement(cond_str[1:], nums)
            case "#":
                if len(cond_str) < n:
                    return 0
                elif len(cond_str) == n and not any(x == "." for x in cond_str):
                    return len(nums) == 1
                elif (
                    len(cond_str) > n
                    and not any(x == "." for x in cond_str[:n])
                    and cond_str[n] != "#"
                ):
                    return arrangement(cond_str[n + 1 :], nums[1:])
                else:
                    return 0
        return 0


def count(record: str, repeat=1) -> int:
    cond_str, nums_str = record.split(" ")
    return arrangement(
        "?".join(cond_str for _ in range(repeat)),
        tuple([int(x) for x in nums_str.split(",")] * repeat),
    )


print(sum(count(line, 1) for line in open("./dataset/day12.txt")))
print(sum(count(line, 5) for line in open("./dataset/day12.txt")))
