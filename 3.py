from typing import List, Iterable

# how many trees would you encounter?

# input.txt:

# ..##.........##.........##.........##.........##.........##.......
# #...#...#..#...#...#..#...#...#..#...#...#..#...#...#..#...#...#..
# .#....#..#..#....#..#..#....#..#..#....#..#..#....#..#..#....#..#.
# ..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#..#.#...#.#
# .#...##..#..#...##..#..#...##..#..#...##..#..#...##..#..#...##..#.
# ..#.##.......#.##.......#.##.......#.##.......#.##.......#.##.....
# .#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#.#.#.#....#
# .#........#.#........#.#........#.#........#.#........#.#........#
# #.##...#...#.##...#...#.##...#...#.##...#...#.##...#...#.##...#...
# #...##....##...##....##...##....##...##....##...##....##...##....#
# .#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#.#..#...#.#

# pt.1: 7 trees encountered
# pt.2 336 trees multiplied together, 2, 7, 3, 4, 2 trees encountered


def get_trees(patterns: List[str], *, right: int, down=1) -> int:
    down -= 1
    cursor_pos = 0
    trees_count = 0
    skip = 0
    for pattern in patterns[down+1:]:
        if skip:
            skip -= 1
            continue
        cursor_pos += right
        while cursor_pos > len(pattern) - 1:
            pattern += pattern
        if pattern[cursor_pos] == '#':
            trees_count += 1
        if down:
            skip = down
    return trees_count


def multiply(iterable: Iterable):
    prod = 1
    for x in iterable:
        prod *= x
    return prod


def main():
    inp = open('input.txt').read()
    lines = inp.split('\n')
    trees = get_trees(lines, right=3)
    print(f'pt.1: {trees} trees encountered')
    pt2_args = [(1, 1), (3, 1), (5, 1), (7, 1), (1, 2)]
    trees = [get_trees(lines, right=args[0], down=args[1])
             for args in pt2_args]
    print(f'pt.2: {multiply(trees)} trees multiplied together, {", ".join(str(x) for x in trees)} trees encountered')


if __name__ == '__main__':
    main()
