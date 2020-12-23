#include <algorithm>
#include <fstream>
#include <vector>
#include <string>
#include <stdio.h>

#define ADD 0x01
#define MULTIPLY 0x02

using namespace std;

void perform_op(int op, int val, long long &out)
{
    if (op == 0)
    {
        out = val;
    }
    else if (op == ADD)
    {
        out += val;
    }
    else if (op == MULTIPLY)
    {
        out *= val;
    }
}

void split(string s, string delimiter, vector<string> &out)
{
    size_t pos = 0;
    while ((pos = s.find(delimiter)) != std::string::npos)
    {
        out.push_back(s.substr(0, pos));
        s.erase(0, pos + delimiter.length());
    }
    if (!s.empty())
    {
        out.push_back(s);
    }
}

int eval_expr(string &expr, long long &out)
{
    vector<string> parts;
    split(expr, " ", parts);
    int op = 0;
    for (auto it = parts.begin(); it != parts.end(); ++it)
    {
        auto &part = *it;
        if (part == "+")
        {
            op = ADD;
            if (it == (--parts.end()))
            {
                return op;
            }
        }
        else if (part == "*")
        {
            op = MULTIPLY;
            if (it == (--parts.end()))
            {
                return op;
            }
        }
        else
        {
            part.erase(std::remove(part.begin(), part.end(), '('), part.end());
            part.erase(std::remove(part.begin(), part.end(), ')'), part.end());
            int val = stoi(part);
            perform_op(op, val, out);
        }
    }
    return 0;
}

bool evaluable(string &str)
{
    int p = 0;
    for (const auto &chr : str)
    {
        if (chr == '(')
        {
            p++;
        }
    }
    return p < 2;
}

void eval_string(string &str)
{
    for (auto it = str.begin(); it != str.end(); ++it)
    {
        auto &chr = *it;
        if (chr == '(')
        {
            int p = 1;
            auto it2 = next(it);
            for (; it2 != str.end(); ++it2)
            {
                auto &inchr = *it2;
                if (inchr == '(')
                {
                    p++;
                }
                if (inchr == ')')
                {
                    p--;
                }
                if (p == 0)
                {
                    it2 = next(it2);
                    break;
                }
            }
            string el(it, it2);
            if (evaluable(el))
            {
                long long expr_res = 0;
                eval_expr(el, expr_res);
                str.replace(it, it2, to_string(expr_res));
            }
        }
    }
}

void part_1(vector<string> &lines)
{
    vector<long long> result;
    for (auto &line : lines)
    {
        while (!evaluable(line))
        {
            eval_string(line);
        }
        eval_string(line);
        long long line_res = 0;
        eval_expr(line, line_res);
        result.push_back(line_res);
    }
    long long sum = 0;
    for (const auto &num : result)
    {
        sum += num;
    }
    printf("pt.1: %lld\n", sum);
}

void read_file(vector<string> &lines)
{
    ifstream file("input.txt");
    if (file.is_open())
    {
        string line;
        while (getline(file, line))
        {
            lines.push_back(line);
        }
        file.close();
    }
}

int main()
{
    vector<string> lines;
    read_file(lines);
    part_1(lines);
}
