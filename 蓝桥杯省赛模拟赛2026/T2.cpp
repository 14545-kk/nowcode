// 试题 B: 矩阵染色
// 本题总分：5 分
// 【问题描述】
// 小红给定如下一个 6 × 6 矩阵：
// 11 8 3 27 24 1
// 2 21 16 35 17 4
// 9 29 20 30 5 10
// 36 33 13 6 23 7
// 31 14 15 28 12 25
// 34 19 18 37 22 39
// 小苯需要从中恰好选择 3 个两两不重叠的 1 × 2 或 2 × 1 子矩形并染红，要求每个
// 被染红区域内两个数的和都是奇数。
// 如果两个方案选出的 3 个区域每个都完全相同，则认为它们是同一种方案，选择顺
// 序不作区分。
// 你不需要输出具体方案，你的任务就是求出满足条件的方案数。


// 暴力搜索所有可能即可，需要注意的是每下一次递归时需i,j虽然起始位置有变化，但是超过起始行时j需变为0而不是继续为n

#include<iostream>
#include<stdio.h>
#include<vector>
using namespace std;
bool tell(int a, int b)
{
	return ((a + b) % 2 == 1) ? true : false;
}
long long question(vector<vector<int>>arr, vector<vector<int>>&brr, long long counting, int m,int n)
{
	if (counting == 3)
	{
		return 1;
	}
	long long right = 0;
	long long down = 0;
	int start = n;
  // star的运用需注意
	for (int i = m; i < arr.size(); i++)
	{
		if (i > m )
		{
			start = 0;
		}
		for (int j = start; j < arr[0].size(); j++)
		{
			//if()
			if (brr[i][j] == 1)
			{
				continue;
			}
			else
			{
				brr[i][j] = 1;
				if (j + 1 < arr[0].size()&&tell(arr[i][j],arr[i][j+1])==1&&brr[i][j+1]!=1)
				{
					brr[i][j + 1] = 1;
					right += question(arr, brr, counting + 1,i,j);
					brr[i][j + 1] = 0;
				}
				if (i + 1 < arr.size()&&tell(arr[i][j], arr[i+1][j]) == 1&&brr[i+1][j]!=1)
				{
					brr[i+1][j] = 1;
					down += question(arr, brr, counting + 1,i,j);
					brr[i+1][j] = 0;
				}
				brr[i][j] = 0;
			}
		}
	}
	return right + down;
}
int main()
{
	vector<vector<int>>arr = { {11, 8, 3, 27, 24, 1 },
							{2, 21, 16, 35, 17, 4},
							{9, 29, 20, 30, 5, 10},
							{36, 33, 13, 6, 23, 7 },
							{31, 14, 15, 28, 12, 25 },
							{34, 19, 18, 37, 22, 39 } };
	//vector<vector<int>>arr = { {2,5,2}, {2,2,2}, {3,5,7} };
	//vector<vector<int>>arr = { {1,2},{1,2} };
	//vector<vector<int>>arr = { {1,2,2}, {2,2,1}};
	vector<vector<int>>brr(arr.size(), vector<int>(arr[0].size(), 0));
	cout << question(arr,brr,0,0,0);
	//cout << tell(2, 2);
	return 0;
}
