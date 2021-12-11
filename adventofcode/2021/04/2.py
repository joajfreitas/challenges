import sys
from pprint import pprint

with open(sys.argv[1]) as f:
    txt = f.read()

callings, *boards = txt.split("\n\n")
boards = [[[int(n) for n in row.split(" ") if n != ""] for row in board.split("\n")] for board in boards if board != []]
boards[-1] = boards[-1][:-1]
callings = [int(calling) for calling in callings.split(",")]

def call_number(board, calling):
    row_idx = -1
    col_idx = -1
    for i, row in enumerate(board):
        if calling in row:
            row_idx = i
            col_idx = row.index(calling)
            break

    if row_idx == -1 and col_idx == -1:
        return False
    board[row_idx][col_idx] = -1
    return row_idx, col_idx

def win(board):
    for row in board:
        if row.count(-1) == 5:
            return True

    for i in range(5):
        acc = 0
        for row in board:
            if row[i] == -1:
                acc+=1

        if acc == 5:
            return True

    return False

def game(callings, boards):
    L = len(boards)
    winners_count = 0
    winners = []
    winner = None
    for calling in callings:
        for board in boards:
            call_number(board, calling)
            w = win(board)
            if w == True and board not in winners:
                winners.append(board)
                winners_count += 1
            if winners_count == L:
                return board, calling

def score(winner, last_call):
    s = 0
    for row in winner:
        s += sum([n for n in row if n != -1])

    return s * last_call

winner, last_call = game(callings, boards)
print(score(winner, last_call))


