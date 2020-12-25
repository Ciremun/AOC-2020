#include <fstream>
#include <istream>
#include <vector>
#include <string>
#include <map>
#include <stdio.h>

using namespace std;

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

void fill_rules_map(const vector<string> &lines, map<int, string> &rules)
{
    for (const auto &line : lines)
    {
        vector<string> rule;
        split(line, ": ", rule);
        int rule_id = stoi(rule[0]);
        string &rule_str = rule[1];
        rules[rule_id] = rule_str;
    }
}

bool check_rule(string &cmp, const string &rule, map<int, string> &rules)
{
    if (rule.front() == '\"')
    {
        const char first = cmp[0];
        bool match = *(rule.end() - 2) == first;
        if (match)
        {
            cmp.erase(0, 1);
        }
        return match;
    }
    else
    {
        string cmp_init = cmp;
        vector<string> at_least_one;
        split(rule, " | ", at_least_one);
        size_t rules_count = at_least_one.size();
        for (size_t i = 0; i < rules_count; i++)
        {
            size_t matches = 0;
            const string &r = at_least_one[i];
            vector<string> rule_seq;
            split(r, " ", rule_seq);
            for (const auto &r_part : rule_seq)
            {
                int rule_id = stoi(r_part);
                const string &next_rule = rules[rule_id];
                if (check_rule(cmp, next_rule, rules))
                {
                    matches++;
                }
                else 
                {
                    cmp = cmp_init;
                    if (at_least_one.size() == 1)
                    {
                        return false;
                    }
                    else
                    {
                        break;
                    }
                }
            }
            if (matches == rule_seq.size())
            {
                return true;
            }
        }
        return false;
    }
}

void part_1(vector<string> &lines, map<int, string> &rules)
{
    int matches = 0;
    for (auto &l : lines)
    {
        if (check_rule(l, rules[0], rules) && l.length() == 0)
        {
            matches++;
        }
    }
    printf("pt.1: %d\n", matches);
}

void split_rules_and_messages(const vector<string> &lines, vector<string> &r, vector<string> &m)
{
    bool rules = true;
    for (const auto &l : lines)
    {
        if (l.empty())
        {
            rules = false;
            continue;
        }
        if (rules)
        {
            r.push_back(l);
        }
        else
        {
            m.push_back(l);
        }
    }
}

int main()
{
    vector<string> lines;
    vector<string> rule_lines;
    vector<string> messages;
    map<int, string> rules;
    read_file(lines);
    split_rules_and_messages(lines, rule_lines, messages);
    fill_rules_map(rule_lines, rules);
    part_1(messages, rules);
}
