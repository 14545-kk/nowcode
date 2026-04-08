// 给你一个下标从 0 开始的 二进制 字符串 floor ，它表示地板上砖块的颜色。

// floor[i] = '0' 表示地板上第 i 块砖块的颜色是 黑色 。
// floor[i] = '1' 表示地板上第 i 块砖块的颜色是 白色 。
// 同时给你 numCarpets 和 carpetLen 。你有 numCarpets 条 黑色 的地毯，每一条 黑色 的地毯长度都为 carpetLen 块砖块。
// 请你使用这些地毯去覆盖砖块，使得未被覆盖的剩余 白色 砖块的数目 最小 。地毯相互之间可以覆盖。
// 请你返回没被覆盖的白色砖块的 最少 数目。

// 输入：floor = "10110101", numCarpets = 2, carpetLen = 2
// 输出：2
// 解释：
// 上图展示了剩余 2 块白色砖块的方案。
// 没有其他方案可以使未被覆盖的白色砖块少于 2 块。

// 从暴力搜索到记忆化搜索的转变过程中注意白色砖块的处理方式发生变化，暴力搜索在一次递归结束后计算整个字符串白色砖块的数量
// 而由于dp[i][j]代表在i位置时还剩j个黑毯，所以在一次递归后只计算i到结尾的白色砖块数量即可

法一：暴力搜索：
#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
class Solution {
public:
    int min(int a,int b)
    {
        return a>b?b:a;
    }
    int rest_white(string a)
    {
        int counting = 0;
        for (int i = 0; i < a.size(); i++)
        {
            if (a[i] == '1')
            {
                counting++;
            }
        }
        return counting;
    }
    int question(string floor, int numCarpets, int carpetLen,int n)
    {
        if (n>=floor.size()||numCarpets==0)
        {
            return rest_white(floor);
        }
        int p1 = 1000005;
        int p2 = 1000005;

        if (floor[n] == '0')
        {
            p1= question(floor, numCarpets, carpetLen, n + 1);
        }
        else
        {
            p2 = question(floor, numCarpets, carpetLen, n + 1);


            for (int i = n; i < min(floor.size(),n + carpetLen); i++)
            {
                floor[i] = '0';
            }
            p1 = question(floor, numCarpets - 1, carpetLen, n + carpetLen);
            //floor[n] = '1';
        }
        return min(p1, p2);
    }

    int minimumWhiteTiles(string floor, int numCarpets, int carpetLen) 
    {
        return question(floor,numCarpets,carpetLen,0); 
    }
};


法二:记忆化搜索：
#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
int min(int a, int b)
{
	return a > b ? b : a;
}
int rest_white(string a,int n)
{
	int counting = 0;
	for (int i = n; i < a.size(); i++)
	{
		if (a[i] == '1')
		{
			counting++;
		}
	}
	return counting;
}
int question(string &floor, vector<vector<int>>& dp, int numCarpets, int carpetLen, int n)
{
	if (n >= floor.size() || numCarpets == 0)
	{
		return rest_white(floor,n);
	}
	if (dp[n][numCarpets] != -1)
	{
		return dp[n][numCarpets];
	}

	int p1 = 1000005;
	int p2 = 1000005;

	if (floor[n] == '0')
	{
		p1 = question(floor, dp, numCarpets, carpetLen, n + 1);
		dp[n][numCarpets] = p1;
		return p1;
	}
	else
	{
		p2 = 1+question(floor, dp, numCarpets, carpetLen, n + 1);

		string l = floor;
		int min_num = min(n + carpetLen, floor.size());
		for (int i = n; i <min_num; i++)
		{
			l[i] = '0';
		}
		p1 = question(l, dp, numCarpets - 1, carpetLen, n + carpetLen);
		//floor[n] = '1';
		dp[n][numCarpets] = min(p1, p2);
		return dp[n][numCarpets];
	}

}
//string question_1(string a)
//{
//	a[0] = '3';
//	return a;
//}
int main()
{
	string floor = "10110101";
	int numCarpets = 2;
	int carpetLen = 2;
	vector<vector<int>>dp(floor.size(), vector<int>(numCarpets+1, -1));
	cout << question(floor,dp ,numCarpets, carpetLen,0);
