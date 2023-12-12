graph = [line.strip() for line in open("./dataset/day11.txt")]

galaxy = []
galaxy_row = [0 for _ in range(len(graph))]
galaxy_col = [0 for _ in range(len(graph[0]))]

for i in range(len(graph)):
    for j in range(len(graph[0])):
        if graph[i][j] == "#":
            galaxy.append((i, j))
            galaxy_row[i] = 1
            galaxy_col[j] = 1


def d(x0: int, y0: int, x1: int, y1: int) -> tuple[int, int, int]:
    max_row = max(x0, x1)
    min_row = min(x0, x1)
    max_col = max(y0, y1)
    min_col = min(y0, y1)

    return (
        sum(galaxy_row[min_row + 1 : max_row]) + sum(galaxy_col[min_col + 1 : max_col]),
        max_row - min_row,
        max_col - min_col,
    )


def distance(count: int, row_d: int, col_d: int, expand: int) -> int:
    return (
        max(expand * (row_d - 1) + 1, 0) + max(expand * (col_d - 1) + 1, 0) - count * (expand - 1)
    )


sum_0 = 0
sum_1 = 0
for i, (x0, y0) in enumerate(galaxy):
    for x1, y1 in galaxy[i + 1 :]:
        count, row_d, col_d = d(x0, y0, x1, y1)
        sum_0 += distance(count, row_d, col_d, 2)
        sum_1 += distance(count, row_d, col_d, 1000000)
print(sum_0, sum_1)
