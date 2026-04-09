// 题目描述
// X 国王有一个地宫宝库。是 n\times m 个格子的矩阵。每个格子放一件宝贝。每个宝贝贴着价值标签。
// 地宫的入口在左上角，出口在右下角。
// 小明被带到地宫的入口，国王要求他只能向右或向下行走。
// 走过某个格子时，如果那个格子中的宝贝价值比小明手中任意宝贝价值都大，小明就可以拿起它（当然，也可以不拿）。
// 当小明走到出口时，如果他手中的宝贝恰好是 k 件，则这些宝贝就可以送给小明。
// 请你帮小明算一算，在给定的局面下，他有多少种不同的行动方案能获得这 k 件宝贝。
// 输入描述
// 输入一行 3 个整数，用空格分开：n,m,k\mathrm{\ \biggr\biggr\biggr\biggr\biggr}(1\le n,m\le50,1\le k\le12)。
// 接下来有 n 行数据，每行有 m 个整数 C_i\mathrm{\ \biggr\biggr\biggr\biggr\biggr}(0\le C_i\le12) 代表这个格子上的宝物的价值。
// 输出描述
// 要求输出一个整数，表示正好取 k 个宝贝的行动方案数。该数字可能很大，输出它对 10^9+7 取模的结果。
// 输入输出样例
// 示例
// 输入
// 2 2 2
// 1 2
// 2 1
// 输出
// 2

// 法一：暴力递归
#include <iostream>
#include<vector>
using namespace std;
// long long dp[100][100][100][100]//在i位置
long long question(vector<vector<int>>&arr,vector<int>&path,int i,int j,int k)
{
  if(k<0)
  {
    return 0;
  }
  
  // 到达终点
  if(i==arr.size()-1&&j==arr[0].size()-1)
  {
    if(k==0) return 1;
    if(k==1 && arr[i][j] > path.back()) return 1;
    return 0;
  }
  

  long long p1_1=0;
  long long p1_2=0;
  long long p2_2=0;
  long long p2_1=0;
  
  // 向下走
  if(i+1<arr.size())
  {
    // 拿当前格子
    if(arr[i][j] > path.back())
    {
      path.push_back(arr[i][j]);
      p1_1=question(arr,path,i+1,j,k-1);
      path.pop_back();
    }
    // 不拿当前格子
    p1_2=question(arr,path,i+1,j,k);
  }

  // 向右走
  if(j+1<arr[0].size())
  {
    // 拿当前格子
    if(arr[i][j] > path.back())
    {
      path.push_back(arr[i][j]);
      p2_1=question(arr,path,i,j+1,k-1);
      path.pop_back();
    }
    // 不拿当前格子
    p2_2=question(arr,path,i,j+1,k);
  }
  
  return (p1_1 + p1_2 + p2_1 + p2_2) % 1000000007;
}

int main()
{
  int n,m,k;
  cin>>n>>m>>k;
  vector<vector<int>>arr(n,vector<int>(m,0));
  for(int i=0;i<arr.size();i++)
  {
    for(int j=0;j<arr[0].size();j++)
    {
      cin>>arr[i][j];
    }
  }

  vector<int>path={-1};  // 改为-1，因为宝物价值可能为0
  long long ans=question(arr,path,0,0,k);
  cout<<ans % 1000000007;
  
  return 0;
}



法二：记忆化搜索
#include <iostream>
#include<vector>
#include<cstring>
using namespace std;
long long dp[100][100][55][55];//在[i][j]位置下还剩k个要取，此时最大的值为m,从当前位置到终点有多少路径

long long question(vector<vector<int>>&arr,vector<int>&path,int i,int j,int k)
{
  if(k<0)
  {
    return 0;
  }
  
  // 到达终点
  if(i==arr.size()-1&&j==arr[0].size()-1)
  {
    if(k==0) return 1;
    if(k==1 && arr[i][j] > path.back()) return 1;
    return 0;
  }
  if(dp[i][j][k][path[path.size()-1]]!=-1)
  {
    return dp[i][j][k][path[path.size()-1]];
  }

  long long p1_1=0;
  long long p1_2=0;
  long long p2_2=0;
  long long p2_1=0;
  
  // 向下走
  if(i+1<arr.size())
  {
    // 拿当前格子
    if(arr[i][j] > path.back())
    {
      path.push_back(arr[i][j]);
      p1_1=question(arr,path,i+1,j,k-1);
      path.pop_back();
    }
    // 不拿当前格子
    p1_2=question(arr,path,i+1,j,k);
  }

  // 向右走
  if(j+1<arr[0].size())
  {
    // 拿当前格子
    if(arr[i][j] > path.back())
    {
      path.push_back(arr[i][j]);
      p2_1=question(arr,path,i,j+1,k-1);
      path.pop_back();
    }
    // 不拿当前格子
    p2_2=question(arr,path,i,j+1,k);
  }
  dp[i][j][k][path[path.size()-1]]=(p1_1 + p1_2 + p2_1 + p2_2) % 1000000007;
  return dp[i][j][k][path[path.size()-1]];
}

int main()
{
  int n,m,k;
  cin>>n>>m>>k;
  vector<vector<int>>arr(n,vector<int>(m,0));
  for(int i=0;i<arr.size();i++)
  {
    for(int j=0;j<arr[0].size();j++)
    {
      cin>>arr[i][j];
    }
  }
  memset(dp,-1,sizeof(dp)); 

  vector<int>path={-1};  // 改为-1，因为宝物价值可能为0
  long long ans=question(arr,path,0,0,k);
  cout<<ans % 1000000007;
  
  return 0;
}
