from typing import Tuple
from enum import IntEnum


graph = ["." + line.strip() + "." for line in open("./dataset/day10.txt")]
graph.insert(0, "." * len(graph[0]))
graph.append("." * len(graph[0]))


class Action(IntEnum):
    Up = 0
    Down = 1
    Left = 2
    Right = 3


def get_next(
    before: Action, current: Tuple[int, int]
) -> Tuple[Action, Tuple[int, int]]:
    i, j = current
    if graph[i][j] == "F":
        if before == Action.Up:
            return (Action.Right, (i, j + 1))
        elif before == Action.Left:
            return (Action.Down, (i + 1, j))
        else:
            raise KeyError()
    elif graph[i][j] == "7":
        if before == Action.Right:
            return (Action.Down, (i + 1, j))
        elif before == Action.Up:
            return (Action.Left, (i, j - 1))
        else:
            raise KeyError()
    elif graph[i][j] == "J":
        if before == Action.Right:
            return (Action.Up, (i - 1, j))
        elif before == Action.Down:
            return (Action.Left, (i, j - 1))
        else:
            raise KeyError()
    elif graph[i][j] == "L":
        if before == Action.Down:
            return (Action.Right, (i, j + 1))
        elif before == Action.Left:
            return (Action.Up, (i - 1, j))
        else:
            raise KeyError()
    elif graph[i][j] == "-":
        if before == Action.Left:
            return (before, (i, j - 1))
        elif before == Action.Right:
            return (before, (i, j + 1))
        else:
            raise KeyError()
    elif graph[i][j] == "|":
        if before == Action.Down:
            return (before, (i + 1, j))
        elif before == Action.Up:
            return (before, (i - 1, j))
        else:
            raise KeyError()
    else:
        raise KeyError()


start = (0, 0)
start_action = Action.Up
for i in range(len(graph)):
    for j in range(len(graph[i])):
        if graph[i][j] == "S":
            start = (i, j)

current = start
before = Action.Up
i, j = current
all_action = []

if graph[i - 1][j] == "|" or graph[i - 1][j] == "F" or graph[i - 1][j] == "7":
    current = (i + 1, j)
    before = Action.Up
    all_action.append(before)
if graph[i][j + 1] == "-" or graph[i][j + 1] == "7" or graph[i][j + 1] == "J":
    current = (i, j + 1)
    before = Action.Right
    all_action.append(before)
if graph[i + 1][j] == "|" or graph[i + 1][j] == "L" or graph[i + 1][j] == "J":
    current = (i + 1, j)
    before = Action.Down
    all_action.append(before)
if graph[i][j - 1] == "-" or graph[i][j - 1] == "L" or graph[i][j - 1] == "F":
    current = (i, j - 1)
    before = Action.Left
    all_action.append(before)


_1, _2 = sorted(all_action)
replace_s = ""
if (_1, _2) == (Action.Up, Action.Down):
    replace_s = "|"
elif (_1, _2) == (Action.Up, Action.Left):
    replace_s = "J"
elif (_1, _2) == (Action.Up, Action.Right):
    replace_s = "L"
elif (_1, _2) == (Action.Down, Action.Left):
    replace_s = "7"
elif (_1, _2) == (Action.Down, Action.Right):
    replace_s = "F"
elif (_1, _2) == (Action.Left, Action.Right):
    replace_s = "-"
else:
    print((_1, _2))
    raise KeyError()

path = [start]
while True:
    i, j = current
    if graph[i][j] == "S":
        graph[i] = graph[i].replace("S", replace_s)
        break
    path.append(current)
    before, current = get_next(before, current)

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
