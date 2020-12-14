from typing import List, Tuple

start = open('input.txt').read().split('\n')
rows_count = len(start)


def change_seat(rows: List[str], row: List[str], row_pos: int, seat_pos: int, value: str) -> Tuple[List[str], str]:
    row_str = list(row)
    row_str[seat_pos] = value
    rows[row_pos] = "".join(row_str)
    return rows, rows[row_pos]


def get_positions(check_left: bool, check_right: bool,
                  check_top: bool, check_bottom: bool,
                  left: int, right: int, top: int,
                  bottom: int, rows: List[str],
                  row_pos: int, seat_pos: int) -> List[str]:
    positions = []
    if check_bottom:
        positions += rows[bottom][seat_pos]
    if check_top:
        positions += rows[top][seat_pos]
    if check_left:
        positions += rows[row_pos][left]
    if check_left and check_top:
        positions += rows[top][left]
    if check_left and check_bottom:
        positions += rows[bottom][left]
    if check_right:
        positions += rows[row_pos][right]
    if check_right and check_top:
        positions += rows[top][right]
    if check_right and check_bottom:
        positions += rows[bottom][right]
    return positions


def check_seats(rows: List[str], row_pos: int, seat_pos: int, *, occupied: bool) -> bool:
    left = seat_pos - 1
    right = seat_pos + 1
    bottom = row_pos + 1
    top = row_pos - 1
    row_length = len(rows[row_pos])
    check_left = left >= 0
    check_right = right < row_length
    check_bottom = bottom < rows_count
    check_top = top >= 0
    if not occupied:
        positions = get_positions(check_left, check_right, check_top,
                                  check_bottom, left, right, top, bottom, rows, row_pos, seat_pos)
        if all(x != '#' for x in positions):
            return True
    else:
        occupied_count = 0
        positions = get_positions(check_left, check_right, check_top,
                                  check_bottom, left, right, top, bottom, rows, row_pos, seat_pos)
        for seat in positions:
            if seat == '#':
                occupied_count += 1
            if occupied_count == 4:
                return True
    return False


def loop_rows(r: List[str]):
    new_rows = r.copy()
    for row_pos, row in enumerate(r):
        for seat_pos, seat in enumerate(row):
            if seat == 'L' and check_seats(r, row_pos, seat_pos, occupied=False):
                new_rows, row = change_seat(
                    new_rows, row, row_pos, seat_pos, '#')
            elif seat == '#' and check_seats(r, row_pos, seat_pos, occupied=True):
                new_rows, row = change_seat(
                    new_rows, row, row_pos, seat_pos, 'L')
    return new_rows


def solve1():
    global start
    previous = None
    while True:
        if start == previous:
            break
        previous = start.copy()
        start = loop_rows(start)
    occupied = 0
    for line in start:
        print(line)
        for seat in line:
            if seat == '#':
                occupied += 1
    print(occupied)


solve1()
