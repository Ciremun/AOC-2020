#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

long accumulator = 0;

#define MAX_LINES 1024
#define MAX_LINE_LEN 10

int parse_value(char l[MAX_LINES][MAX_LINE_LEN], int i)
{
    char val[4];
    size_t len = strlen(l[i]) - 1;
    int ival = 0;
    for (int z = 5; z < len; z++)
    {
        val[ival] = l[i][z];
        ival++;
    }
    val[ival] = '\0';
    const char *inc = val;
    return strtol(inc, NULL, 0);
}

void solve(char l[MAX_LINES][MAX_LINE_LEN], int lcount)
{
    bool seen[MAX_LINES] = {};
    for (long i = 0; i < lcount; i++)
    {
        if (seen[i] == true)
        {
            printf("pt.1: accumulator: %d", accumulator);
            break;
        }
        seen[i] = true;
        char op[4] = {l[i][0], l[i][1], l[i][2], '\0'};
        char sign[2] = {l[i][4], '\0'};
        int opsign = 0x01;
        if (strcmp(sign, "+") == 0)
        {
            opsign = 0x02;
        }
        long val = parse_value(l, i);
        if (strcmp(op, "acc") == 0)
        {
            if (opsign == 0x02)
            {
                accumulator += val;
            }
            else
            {
                accumulator -= val;
            }
        }
        else if (strcmp(op, "jmp") == 0)
        {
            if (opsign == 0x02)
            {
                val -= 1;
                i += val;
            }
            else
            {
                val += 1;
                i -= val;
            }
        }
    }
}

int read_file(char l[MAX_LINES][MAX_LINE_LEN])
{
    int i = 0;
    FILE *fp = fopen("input.txt", "r");
    while (i < MAX_LINES && fgets(l[i], sizeof(l[0]), fp))
    {
        i++;
    }
    l[i-1][6] = '\n';
    fclose(fp);
    return i;
}

int main()
{
    char l[MAX_LINES][MAX_LINE_LEN];
    int lcount = read_file(l);
    solve(l, lcount);
}