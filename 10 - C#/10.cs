using System;

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
    }
}