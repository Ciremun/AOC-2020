#include <fstream>
#include <iostream>
#include <vector>

// find entries that sum to 2020, multiply them together

// input.txt:

// 1721
// 979
// 366
// 299
// 675
// 1456

// solve2: 514579
// solve3: 241861950

int solve2(std::vector<int> &entries)
{
    size_t entries_size = entries.size();
    for (size_t i = 0; i < entries_size; i++)
        for (size_t j = 1; j < entries_size; j++)
            if (entries[i] + entries[j] == 2020)
                return entries[i] * entries[j];
    return -1;
}

int solve3(std::vector<int> &entries)
{
    size_t entries_size = entries.size();
    for (size_t x = 0; x < entries_size; x++)
        for (size_t y = 1; y < entries_size; y++)
            for (size_t z = 2; z < entries_size; z++)
                if (entries[x] + entries[y] + entries[z] == 2020)
                    return entries[x] * entries[y] * entries[z];
    return -1;
}

void print_result(int result, const char *puzzle_type)
{
    if (result == -1)
        printf("%s: nothing sums to 2020\n", puzzle_type);
    else
        printf("%s: %u\n", puzzle_type, result);
}

int main()
{
    std::ifstream infile("input.txt");
    std::vector<int> entries;
    int x;
    while (infile >> x)
        entries.push_back(x);
    print_result(solve2(entries), "solve2");
    print_result(solve3(entries), "solve3");
    std::cin.get();
}
