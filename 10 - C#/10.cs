using System;
using System.Linq;
using System.Collections.Generic;

class Solution
{
    static void Main()
    {
        int[] inp = Array.ConvertAll(System.IO.File.ReadAllLines(@"input.txt"), int.Parse);
        Array.Sort(inp);
        int j1 = 1;
        int j3 = 1;
        for (int i = 0; i < inp.Length - 1; i++)
        {
            int diff = inp[i+1] - inp[i];
            if (diff == 1) j1 += 1;
            else if (diff == 3) j3 += 1;
        }
        Console.WriteLine(String.Format("pt.1: {0}", j1 * j3));
        List<int> ins = inp.ToList();
        ins.Add(ins[ins.Count-1] + 3);
        Dictionary<long, long> count = new Dictionary<long, long>(){{0, 1}};
        foreach (var i in inp)
        {
            for (int j = 0; j < 4; j++)
                if (!count.ContainsKey(i-j)) count.Add(i-j, 0);
            count[i] = count[i-1] + count[i-2] + count[i-3];
        }
        Console.WriteLine(String.Format("pt.2: {0}", count[count.Keys.Max()]));
    }
}