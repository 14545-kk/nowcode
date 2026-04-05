// 链接：https://ac.nowcoder.com/acm/contest/24213/1006
// 来源：牛客网
// SERKOI最新推出了一种叫做“免费馅饼”的游戏:游戏在一个舞台上进行。舞台的宽度为W格，天幕的高度为H格，游戏者占一格。开始时游戏者站在舞台的正中央，手里拿着一个托盘。下图为天幕的高度为4格时某一个时刻游戏者接馅饼的情景。
// 游戏开始后，从舞台天幕顶端的格子中不断出现馅饼并垂直下落。游戏者左右移动去接馅饼。游戏者每秒可以向左或向右移动一格或两格，也可以站在原地不动。
// 馅饼有很多种，游戏者事先根据自己的口味，对各种馅饼依次打了分。同时，在8-308电脑的遥控下，各种馅饼下落的速度也是不一样的，下落速度以格/秒为单位。
// 当馅饼在某一秒末恰好到达游戏者所在的格子中，游戏者就收集到了这块馅饼。
// 写一个程序，帮助我们的游戏者收集馅饼，使得所收集馅饼的分数之和最大。
  
// 输入描述:
// 第一行是用空格隔开的两个正整数，分别给出了舞台的宽度W（1到99之间的奇数）和高度H（1到100之间的整数）。
// 接下来依馅饼的初始下落时间顺序给出了所有馅饼的信息。每一行给出了一块馅饼的信息。由四个正整数组成，分别表示了馅饼的初始下落时刻（0到1000秒），水平位置、下落速度（1到100）以及分值。游戏开始时刻为0。从1开始自左向右依次对水平方向的每格编号。
// 输入文件中同一行相邻两项之间用一个或多个空格隔开
// 输出描述:
// 第一行给出了一个正整数，表示你的程序所收集的最大分数之和。
// 其后的每一行依时间顺序给出了游戏者每秒的决策。输出0表示原地不动、1或2表示向右移动一步或两步、-1 或-2表示向左移动一步或两步。输出应持续到游戏者收集完他要收集的最后一块馅饼为止
// 示例1
// 输入
// 复制
// 3 3
// 0 1 2 5 
// 0 2 1 3
// 1 2 1 3
// 1 3 1 4
// 输出
// 复制
// 12
// -1
// 1
// 1

// 正向dp:
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main() 
{
    int W, H;
    cin >> W >> H;
    H--;
    
    vector<vector<int>> pies;
    int t, x, v, s;
    int t_max = 0;
    
    while (cin >> t >> x >> v >> s)
    {
        if (H % v == 0)
        {
            int land_time = t + H / v;
            t_max = max(t_max, land_time);
            pies.push_back({t, x, v, s});
        }
    }
    
    if (pies.empty()) {
        cout << 0 << endl;
        return 0;
    }
    
    // 关键修改：交换维度，让时间在外层（和题解一样）
    vector<vector<int>> score(t_max + 2, vector<int>(W + 2, 0));
    for(auto &p : pies)
    {
        int tt = p[0], xx = p[1], vv = p[2], ss = p[3];
        int land_time = tt + H / vv;
        score[land_time][xx] += ss;
    }
    
    // dp[时间][位置]
    vector<vector<int>> dp(t_max + 5, vector<int>(W + 5, -1e9));
    vector<vector<int>> path(t_max + 5, vector<int>(W + 5, 0));
    
    int start_pos = W / 2 + 1;
    dp[0][start_pos] = 0;
    
    // 正向DP
    for (int time = 1; time <= t_max; time++)
    {
        for (int pos = 1; pos <= W; pos++)
        {
            for (int step = -2; step <= 2; step++)
            {
                int prev_pos = pos - step;
                if (prev_pos >= 1 && prev_pos <= W)
                {
                    if (dp[time-1][prev_pos] > -1e8)
                    {
                        int val = dp[time-1][prev_pos] + score[time][pos];
                        if (val >= dp[time][pos])
                        {
                            dp[time][pos] = val;
                            path[time][pos] = step;
                        }
                    }
                }
            }
        }
    }
    
    // 找最大分数和对应时间
    int max_score = -1e9;
    int best_time = 0;
    int best_pos = start_pos;
    
    for (int time = 0; time <= t_max; time++)
    {
        for (int pos = 1; pos <= W; pos++)
        {
            if (dp[time][pos] > max_score)
            {
                max_score = dp[time][pos];
                best_time = time;
                best_pos = pos;
            }
        }
    }
    
    cout << max_score << endl;
    
    if (max_score == 0) return 0;
    
    // 关键修改2：只输出到接完最后一块馅饼的时间
    // 找到最后一个有馅饼被接住的时间
    int last_pie_time = best_time;
    while (last_pie_time > 0) {
        bool has_pie = false;
        for (int pos = 1; pos <= W; pos++) {
            if (score[last_pie_time][pos] > 0 && dp[last_pie_time][pos] == max_score) {
                has_pie = true;
                break;
            }
        }
        if (has_pie) break;
        last_pie_time--;
    }
    
    // 回溯路径
    vector<int> decisions;
    int cur_pos = best_pos;
    int cur_time = best_time;
    
    while (cur_time > 0)
    {
        int step = path[cur_time][cur_pos];
        decisions.push_back(step);
        cur_pos = cur_pos - step;
        cur_time--;
    }
    
    // 只输出到last_pie_time
    int output_count = min((int)decisions.size(), last_pie_time);
    for (int i = decisions.size() - 1; i >= (int)decisions.size() - output_count; i--)
    {
        cout << decisions[i] << endl;
    }
    
    return 0;
}
