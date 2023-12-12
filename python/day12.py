def arrangement(nums: list[int], cond_str: str) -> int:
    len_i, len_j = len(nums), len(cond_str)
    a = [[0 for _ in range(len_j + 1)] for _ in range(len_i + 1)]
    for j in range(len_j + 1):
        a[0][j] = not any(x == "#" for x in cond_str[len_j - j :])
    for i in range(1, len_i + 1):
        for j in range(1, len_j + 1):
            n = nums[len_i - i]
            if cond_str[len_j - j] == ".":
                a[i][j] = a[i][j - 1]
            else:
                if j == n and not any(x == "." for x in cond_str[len_j - j :]):
                    a[i][j] = i == 1
                elif (
                    j > n
                    and not any(x == "." for x in cond_str[len_j - j : len_j - j + n])
                    and cond_str[len_j - j + n] != "#"
                ):
                    a[i][j] = a[i - 1][j - n - 1]
                if cond_str[len_j - j] == "?":
                    a[i][j] += a[i][j - 1]
    return a[-1][-1]


def count(record: str, repeat=1) -> int:
    cond_str, nums_str = record.split(" ")
    return arrangement(
        [int(x) for x in nums_str.split(",")] * repeat,
        "?".join(cond_str for _ in range(repeat)),
    )


print(sum(count(line, 1) for line in open("./dataset/day12.txt")))
print(sum(count(line, 5) for line in open("./dataset/day12.txt")))
