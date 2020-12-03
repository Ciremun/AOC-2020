#include <fstream>
#include <iostream>
#include <vector>

// find the two entries that sum to 2020

int solve()
{
    std::ifstream infile("input.txt");
    std::vector<int> entries;
    int x;
    while (infile >> x)
    {
        entries.push_back(x);
    }
    for (int i = 0; i < entries.size(); i++)
    {
        for (int j = 0; j < entries.size(); j++)
        {
            if (j == i)
            {
                continue;
            }
            if (entries[i] + entries[j] == 2020)
            {
                return entries[i] * entries[j];
            }
        }
    }
    return -1;
}

int main()
{
    int result = solve();
    if (result == -1)
    {
        printf("nothing sums to 2020\n");
    }
    else
    {
        printf("%u\n", result);
    }
    std::cin.get();
}