from enum import IntEnum


graph = ["." + line.strip() + "." for line in open("./dataset/day10.txt")]
graph.insert(0, "." * len(graph[0]))
graph.append("." * len(graph[0]))


class Dir(IntEnum):
    U = 0
    D = 1
    L = 2
    R = 3


def get_next(dir: Dir, current: tuple[int, int]) -> tuple[Dir, tuple[int, int]]:
    i, j = current
    match graph[i][j]:
        case "F":
            if dir == Dir.U:
                return (Dir.R, (i, j + 1))
            elif dir == Dir.L:
                return (Dir.D, (i + 1, j))
        case "7":
            if dir == Dir.R:
                return (Dir.D, (i + 1, j))
            elif dir == Dir.U:
                return (Dir.L, (i, j - 1))
        case "J":
            if dir == Dir.R:
                return (Dir.U, (i - 1, j))
            elif dir == Dir.D:
                return (Dir.L, (i, j - 1))
        case "L":
            if dir == Dir.D:
                return (Dir.R, (i, j + 1))
            elif dir == Dir.L:
                return (Dir.U, (i - 1, j))
        case "-":
            if dir == Dir.L:
                return (dir, (i, j - 1))
            elif dir == Dir.R:
                return (dir, (i, j + 1))
        case "|":
            if dir == Dir.D:
                return (dir, (i + 1, j))
            elif dir == Dir.U:
                return (dir, (i - 1, j))
    return dir, current


start = (0, 0)
start_action = Dir.U
for i in range(len(graph)):
    for j in range(len(graph[i])):
        if graph[i][j] == "S":
            start = (i, j)

current = start
dir = Dir.U
i, j = current
all_action = []

match graph[i - 1][j]:
    case "|" | "F" | "7":
        current = (i + 1, j)
        dir = Dir.U
        all_action.append(dir)
match graph[i][j + 1]:
    case "-" | "7" | "J":
        current = (i, j + 1)
        dir = Dir.R
        all_action.append(dir)
match graph[i + 1][j]:
    case "|" | "L" | "J":
        current = (i + 1, j)
        dir = Dir.D
        all_action.append(dir)
match graph[i][j - 1]:
    case "-" | "L" | "F":
        current = (i, j - 1)
        dir = Dir.L
        all_action.append(dir)


replace_s = ""
match sorted(all_action):
    case [Dir.U, Dir.D]:
        replace_s = "|"
    case [Dir.U, Dir.L]:
        replace_s = "J"
    case [Dir.U, Dir.R]:
        replace_s = "L"
    case [Dir.D, Dir.L]:
        replace_s = "7"
    case [Dir.D, Dir.R]:
        replace_s = "F"
    case [Dir.L, Dir.R]:
        replace_s = "-"

path = [start]
while True:
    i, j = current
    if graph[i][j] == "S":
        graph[i] = graph[i].replace("S", replace_s)
        break
    path.append(current)
    dir, current = get_next(dir, current)

path = set(path)


def count_inside():
    total_count = 0
    for i in range(1, len(graph) - 1):
        count = 0
        before = "|"
        for j in range(1, len(graph[0]) - 1):
            if (i, j) in path and graph[i][j] != "-":
                match (graph[i][j], before):
                    case ("|", _):
                        count += 1
                    case ("F" | "L", _):
                        count += 1
                        before = graph[i][j]
                    case ("7", "F") | ("J", "L"):
                        count += 1
            elif (i, j) not in path and (count % 2) == 1:
                total_count += 1
    return total_count


print(len(path) // 2)
print(count_inside())
