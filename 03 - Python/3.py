from typing import List, Iterable

def get_trees(patterns: List[str], *, right: int, down: int) -> int:
    skip = 0
    cursor_pos = 0
    trees_count = 0
    do_skip = down - 1
    for pattern in patterns[down:]:
        if skip:
            skip -= 1
            continue
        cursor_pos += right
        while cursor_pos >= len(pattern):
            pattern += pattern
        if pattern[cursor_pos] == '#':
            trees_count += 1
        if do_skip:
            skip = do_skip
    return trees_count

def multiply(iterable: Iterable):
    prod = 1
    for x in iterable:
        prod *= x
    return prod

def main():
    lines = open('input.txt').read().split('\n')
    result_p1 = get_trees(lines, right=3, down=1)
    pt2_args = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]
    result_p2 = [get_trees(lines, right=args[0], down=args[1]) for args in pt2_args]
    print(f'pt.1: {result_p1}\n'
          f'pt.2: {multiply(result_p2)}')

if __name__ == '__main__':
    main()
