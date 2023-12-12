def predict(line: str, b: bool) -> int:
    seqs = [[int(i) for i in line.split(" ")]]
    while not all(i == 0 for i in seqs[-1]):
        seqs.append(list(seqs[-1][i + 1] - seqs[-1][i] for i in range(len(seqs[-1]) - 1)))
    return sum(i[-1] for i in seqs) if b else sum(b[0] * (-1) ** a for (a, b) in enumerate(seqs))


lines = open("./dataset/day09.txt").readlines()
print(sum(predict(line, True) for line in lines))
print(sum(predict(line, False) for line in lines))
