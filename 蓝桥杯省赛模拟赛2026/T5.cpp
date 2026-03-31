// 试题 E: 擂台轮转
// 【问题描述】
// 某地正在举办算法擂台赛，具体规则如下：
// • 一共有 n 位参赛选手排成一列，其中第一个位置（i = 1）表示擂台。
// • 最初第 i 位选手的战力为 ai，已知两位选手比拼时，战力更高的一方一定会获胜。
// • 每回合，位于队列前两个位置的两名选手将进行比拼，获胜的一方留在擂台上（即
// i = 1），失败的一方排到队伍末尾（即 i = n）。
// 现在作为裁判的小苯想知道，在经过 k 回合后，场上所有人的位置是什么样的。你
// 的任务就是求出 k 回合后，选手队列的模样。
// 【输入格式】
// 每个测试文件均包含多组测试数据。第一行输入一个整数 T (1 ≤ T ≤ 105
// ) 代表数
// 据组数，每组测试数据描述如下：
// 第一行两个整数 n, k (2 ≤ n ≤ 3 × 105
// , 0 ≤ k ≤ 109
// )，分别表示选手数量以及比赛
// 进行的回合数。
// 第二行 n 个整数 ai (1 ≤ ai ≤ n)，表示每位选手的战力。保证 a 是一个排列，也就
// 是说所有数字两两不同。
// 除此之外，保证单个测试文件内所有测试数据的 n 之和不超过 3 × 105。
// 【输出格式】
// 对于每组测试数据，在一行中输出 n 个整数，表示经过 k 回合后，选手队列的模
// 样。
// 【样例输入】
// 3
// 5 0
// 3 4 1 5 2
// 5 1
// 3 4 1 5 2
// 5 3
// 3 4 1 5 2
// 【样例输出】
// 3 4 1 5 2
// 4 1 5 2 3
// 5 2 3 1 4


// 可以基于队列实现或数组实现
#include<iostream>
#include<stdio.h>
#include<vector>	
#include<queue>
using namespace std;

int main()
{
	int T;
	cin >> T;
	for (int j = 0; j < T; j++)
	{
		long long n, k;
		cin >> n;
		cin >> k;
// 		queue<long long>brr;
// 		queue<long long>drr;
        vector<long long> arr;
		for (int i = 0; i < n; i++)
		{
			int a = 0;
			cin >> a;
			arr.push_back(a);
		}
		for (int i = 0; i < k; i++)
		{
// 			drr = brr;
			long long first = arr[i];
// 			brr.pop();
			long long second = arr[i+1];
// 			brr.pop();
//             cout<<first<<" "<<second<<endl;
			if (first > second)
			{
// 				brr.push(second);
// 				brr.front() = first;
                arr[i]=0;
                arr[i+1]=first;
                arr.push_back(second);
			}
			else
			{
                arr[i]=0;
//                 arr[i+1]=second;
                arr.push_back(first);
			}
		}
        for (int i = k; i < n+k; i++)
		{
			cout << arr[i] << " ";
		}
        cout<<endl;
	}
	return 0;
}
