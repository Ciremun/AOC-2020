#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_LINES 1024
#define MAX_LINE_LEN 5
#define EAST 'E'
#define WEST 'W'
#define SOUTH 'S'
#define NORTH 'N'

long parse_value(char l[MAX_LINES][MAX_LINE_LEN], int i)
{
    char value_str[4];
    int pos = 0;
    for (int j = 1; j < 5; j++)
    {
        if (l[i][j] == '\0' || l[i][j] == '\n')
        {
            break;
        }
        value_str[pos] = l[i][j];
        pos++;
    }
    if (pos == 0)
    {
        return -1;
    }
    value_str[pos] = '\0';
    const char *val = value_str;
    return strtol(val, NULL, 0);
}

void calc_cardinal(long *c1, long *c2, long value)
{
    *c1 += value - *c2;
    if (*c1 >= 0)
    {
        *c2 = 0;
    }
    else
    {
        *c2 = -*c1;
        *c1 = 0;
    }
}

void solve1(char l[MAX_LINES][MAX_LINE_LEN], int lcount)
{
    char facing = EAST;
    long east = 0;
    long west = 0;
    long south = 0;
    long north = 0;
    for (int i = 0; i < lcount; i++)
    {
        char action = l[i][0];
        long value = parse_value(l, i);
        if (value == -1)
        {
            continue;
        }
        switch (action)
        {
        case 'F':
            switch (facing)
            {
            case EAST:
                calc_cardinal(&east, &west, value);
                break;
            case WEST:
                calc_cardinal(&west, &east, value);
                break;
            case SOUTH:
                calc_cardinal(&south, &north, value);
                break;
            case NORTH:
                calc_cardinal(&north, &south, value);
                break;
            default:
                assert(0 && "unknown facing");
            }
            break;
        case 'E':
            calc_cardinal(&east, &west, value);
            break;
        case 'W':
            calc_cardinal(&west, &east, value);
            break;
        case 'S':
            calc_cardinal(&south, &north, value);
            break;
        case 'N':
            calc_cardinal(&north, &south, value);
            break;
        case 'R':;
            int rsteps = value / 90;
            for (int z = 0; z < rsteps; z++)
            {
                switch (facing)
                {
                case EAST:
                    facing = SOUTH;
                    break;
                case WEST:
                    facing = NORTH;
                    break;
                case SOUTH:
                    facing = WEST;
                    break;
                case NORTH:
                    facing = EAST;
                    break;
                default:
                    assert(0 && "unknown facing");
                }
            }
            break;
        case 'L':;
            int lsteps = value / 90;
            for (int z = 0; z < lsteps; z++)
            {
                switch (facing)
                {
                case EAST:
                    facing = NORTH;
                    break;
                case WEST:
                    facing = SOUTH;
                    break;
                case SOUTH:
                    facing = EAST;
                    break;
                case NORTH:
                    facing = WEST;
                    break;
                default:
                    assert(0 && "unknown facing");
                }
            }
            break;
        default:
            assert(0 && "unknown action");
        }
    }
    printf("pt.1: %d\n", east + west + south + north);
}

void solve2(char l[MAX_LINES][MAX_LINE_LEN], int lcount)
{
    long s_east = 0;
    long s_west = 0;
    long s_south = 0;
    long s_north = 0;
    long w_east = 10;
    long w_west = 0;
    long w_south = 0;
    long w_north = 1;
    for (int i = 0; i < lcount; i++)
    {
        char action = l[i][0];
        long value = parse_value(l, i);
        if (value == -1)
        {
            continue;
        }
        switch (action)
        {
        case 'F':
            calc_cardinal(&s_east, &s_west, w_east * value);
            calc_cardinal(&s_west, &s_east, w_west * value);
            calc_cardinal(&s_south, &s_north, w_south * value);
            calc_cardinal(&s_north, &s_south, w_north * value);
            break;
        case 'E':
            calc_cardinal(&w_east, &w_west, value);
            break;
        case 'W':
            calc_cardinal(&w_west, &w_east, value);
            break;
        case 'S':
            calc_cardinal(&w_south, &w_north, value);
            break;
        case 'N':
            calc_cardinal(&w_north, &w_south, value);
            break;
        case 'L':;
            int rsteps = value / 90;
            for (int z = 0; z < rsteps; z++)
            {
                long w_east_copy = w_east;
                long w_west_copy = w_west;
                long w_south_copy = w_south;
                long w_north_copy = w_north;
                w_east = w_south_copy;
                w_west = w_north_copy;
                w_south = w_west_copy;
                w_north = w_east_copy;
            }
            break;
        case 'R':;
            int lsteps = value / 90;
            for (int z = 0; z < lsteps; z++)
            {
                long w_east_copy = w_east;
                long w_west_copy = w_west;
                long w_south_copy = w_south;
                long w_north_copy = w_north;
                w_east = w_north_copy;
                w_west = w_south_copy;
                w_south = w_east_copy;
                w_north = w_west_copy;
            }
            break;
        default:
            assert(0 && "unknown action");
        }
    }
    printf("pt.2: %d\n", s_east + s_west + s_south + s_north);
}

int read_file(char l[MAX_LINES][MAX_LINE_LEN])
{
    int i = 0;
    FILE *fp = fopen("input.txt", "r");
    while (i < MAX_LINES && fgets(l[i], sizeof(l[0]), fp))
    {
        i++;
    }
    fclose(fp);
    return i;
}

int main()
{
    char l[MAX_LINES][MAX_LINE_LEN];
    int lcount = read_file(l);
    solve1(l, lcount);
    solve2(l, lcount);
}
