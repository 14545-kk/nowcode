问题描述
小明需要在一条 2×n 的河床上铺设水质检测器。在他铺设之前，河床上已经存在一些检测器。如果两个检测器上下或左右相邻，那么这两个检测器就是互相连通的。
连通具有传递性，即如果 
A 和B 连通，B和C 连通，那么 A 和C 也连通。现在他需要在河床上增加铺设一些检测器，使得所有检测器都互相连通。他想知道最少需要增加铺设多少个检测器？
输入格式
输入共两行，表示一个 2×n 的河床。
每行一个长度为 n 的字符串，仅包含 # 和 ., 其中 # 表示已经存在的检测器，. 表示空白。
输出格式
输出共 1 行，一个整数，表示最少需要增加的检测器数量。
样例输入
.##.....#
.#.#.#...
样例输出
5


#include <iostream>
#include<stdio.h>
#include<string>
#include<vector>
using namespace std;
int main()
{
  // 请在此输入您的代码
  string a,b;
  cin>>a>>b;

  long long n=a.size();
  int counting=0;
  vector<vector<char>>arr(2,vector<char>(n,'*'));
  int i=0;
  int j=1;
  for(int i=0;i<a.size();i++)
  {
    arr[0][i]=a[i];  
    arr[1][i]=b[i];
  }
  //   for(int j=i+1;j<a.size();j++)
  //   {
  while(j<a.size())
  {
    if(i==j)
    {
      j++;
    }

    if((arr[0][i]!='.'||arr[1][i]!='.')&&(arr[0][j]!='.'||arr[1][j]!='.'))
    {
      if((arr[0][i]=='#'&&arr[0][j]=='#')||(arr[1][i]=='#'&&arr[1][j]=='#'))
      {
        counting+=j-i-1;
      }
      else
      {
        if(arr[0][j]=='.')
        {
          arr[0][j]='#';
        }
        if(arr[1][j]=='.')
        {
          arr[1][j]='#';
        }
        counting+=j-i;
      }
      i=j;
      j++;
    }
    else if((arr[0][i]=='.'&&arr[1][i]=='.')&&(arr[0][j]!='.'||arr[1][j]!='.'))
    {
      i++;
    }
    else
    {
      j++;
    }
  }
  cout<<counting;
  return 0;
  // vector<vector<char>>arr()
}
