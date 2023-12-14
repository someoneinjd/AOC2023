def find_diff(pattern: list[str], diff=0) -> int:
    for i in range(len(pattern) - 1):
        pos_len = min(i + 1, len(pattern) - i - 1)
        if (
            sum(
                sum(pattern[i - x][y] != pattern[i + 1 + x][y] for y in range(len(pattern[0])))
                for x in range(pos_len)
            )
            == diff
        ):
            return i + 1
    return 0


def count(pattern: list[str], diff=0) -> int:
    i = find_diff(pattern, diff)
    if i != 0:
        return 100 * i
    else:
        return find_diff(
            ["".join(pattern[j][i] for j in range(len(pattern))) for i in range(len(pattern[0]))],
            diff,
        )


patterns = open("./dataset/day13.txt").read().strip()

print(sum(count(pattern.splitlines()) for pattern in patterns.split("\n\n")))
print(sum(count(pattern.splitlines(), 1) for pattern in patterns.split("\n\n")))
