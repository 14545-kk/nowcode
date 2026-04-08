// 路径之谜
// 题目描述
// 小明冒充 X 星球的骑士，进入了一个奇怪的城堡。城堡里边什么都没有，只有方形石头铺成的地面。

// 假设城堡地面是 n×n 个方格。如下图所示。
// 按习俗，骑士要从西北角走到东南角。可以横向或纵向移动，但不能斜着走，也不能跳跃。每走到一个新方格，就要向正北方和正西方各射一箭。（城堡的西墙和北墙内各有 
// n 个靶子）同一个方格只允许经过一次。但不必走完所有的方格。如果只给出靶子上箭的数目，你能推断出骑士的行走路线吗？有时是可以的，比如上图中的例子。
// 本题的要求就是已知箭靶数字，求骑士的行走路径（测试数据保证路径唯一）
// 输入描述
// 第一行一个整数 (0≤N≤20)，表示地面有 N×N 个方格。
// 第二行 N 个整数，空格分开，表示北边的箭靶上的数字（自西向东）
// 第三行 N 个整数，空格分开，表示西边的箭靶上的数字（自北向南）
// 输出描述
// 输出一行若干个整数，表示骑士路径。
// 为了方便表示，我们约定每个小格子用一个数字代表，从西北角开始编号: 0,1,2,3 
// 比如，上图中的方块编号为：
// 0 1 2 3
// 4 5 6 7
// 8 9 10 11
// 12 13 14 15
// 输入输出样例
// 示例
// 输入
// 4
// 2 4 3 4
// 4 3 3 3
// 输出
// 0 4 5 1 2 3 7 11 10 9 13 14 15

// 利用暴力搜索，用shadow和ans数组记录路径，每次遍历上下左右四个方向的路径，每走一步，对应方向的箭靶数量减一，
// 遍历所有情况即可，需要注意的是，可以通过判断两方向箭靶数是否小于0来达到快速剪枝的效果

#include <iostream>
#include<vector>
#include<stdio.h>
using namespace std;

bool tell(vector<int>arr)
{
	int counting = 0;
	for (int i = 0; i < arr.size(); i++)
	{
		if (arr[i] != 0)
		{
			return false;
		}
	}
	return true;
}

vector<int>question(vector<vector<int>>& arr, vector<int> high, vector<int> wide, vector<int>& ans, vector<vector<int>>& shadow, int i, int j)
{
  if(high[i]-1<0)
  {
    vector<int>empty={-1};
    return empty;
  }
  else
  {
    high[i]-=1;
  }

  if(wide[j]-1<0)
  {
    vector<int>empty={-1};
    return empty;
  }
  else
  {
    wide[j]-=1;
  }
  
	if (i == arr.size()-1 && j == arr[0].size()-1)
	{
		if (tell(high) == 1 && tell(wide) == 1)
		{
			return ans;
		}
		else
		{
			vector<int>empty={-1};
			return empty;
		}
	}


	vector<int>up = {-1};
	vector<int>down = {-1};
	vector<int>right = {-1};
	vector<int>left = {-1};

	if (i - 1 >= 0 && shadow[i - 1][j]!=1)
	{
		shadow[i - 1][j] = 1;
		ans.push_back(arr[i - 1][j]);
		up = question(arr, high, wide, ans, shadow, i - 1, j);
		shadow[i - 1][j] = 0;
		ans.pop_back();
	}
	if (i + 1 < arr.size() && shadow[i + 1][j]!=1)
	{
		shadow[i + 1][j] = 1;
		ans.push_back(arr[i + 1][j]);
		down = question(arr, high, wide, ans, shadow, i + 1, j);
		shadow[i + 1][j] = 0;
		ans.pop_back();
	}
	if (j - 1 >= 0 && shadow[i][j - 1]!=1)
	{
		shadow[i][j - 1] = 1;
		ans.push_back(arr[i][j - 1]);
		left = question(arr, high, wide, ans, shadow, i, j - 1);
		shadow[i][j - 1] = 0;
		ans.pop_back();
	}
	if (j + 1 < arr[0].size() && shadow[i][j + 1]!=1)
	{
		shadow[i][j+1] = 1;
		ans.push_back(arr[i][j+1]);
		right = question(arr, high, wide, ans, shadow, i , j+1);
		shadow[i][j+1] = 0;
		ans.pop_back();
	}

	if (up[0] !=-1)
	{
		return up;
	}
	else if (down[0] !=-1)
	{
		return down;
	}
	else if (right[0] != -1)
	{
		return right;
	}
	else if (left[0] != -1)
	{
		return left;
	}
	else
	{
		vector<int>empty={-1};
		return empty;
	}
}
int main()
{
	// 请在此输入您的代码
	int N = 4;
	cin >> N;
	vector<int>wide;
	vector<int>high;
	int m = 0;
	vector<vector<int>>arr(N, vector<int>(N, 0));
  for(int i=0;i<N;i++)
  {
    cin>>m;
    wide.push_back(m);
  }
  for(int i=0;i<N;i++)
  {
    cin>>m;
    high.push_back(m);
  }
	for (int i = 0; i < N; i++)
	{
		for (int j = 0; j < N; j++)
		{
			arr[i][j] = i * N + j;
			// cout<<arr[i][j]<<" ";
		}
		// cout<<endl;
	}
	vector<int>ans_1 = {0};
	vector<vector<int>>shadow(arr.size(), vector<int>(arr[0].size(), 0));
	shadow[0][0] = 1;
	vector<int>ans = question(arr, high, wide, ans_1, shadow, 0, 0);
  for (int i = 0; i < ans.size(); ++i) {
      if (i != 0) cout << " "; // 除了第一个元素，前面都加空格
      cout << ans[i];
  }
  cout << endl;

	return 0;

}
