#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <cmath>
#include <queue>
#include <numeric>
#include <stack>
#include <map>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pii pair<int,int>
#define pll pair<ll,ll>

using namespace std;

ifstream in("input.txt");

vector<string> input;
ull no_steps[9][1500];
bool visited[150][150];
ull n, m;
ull dx[4] = { -1,0,1,0 };
ull dy[4] = { 0,1,0,-1 };

typedef struct {
    ull x;
    ull y;
}node;
enum directionEnum {
    Middle,
    Left_up,
    Up,
    Right_up,
    Right,
    Right_bottom,
    Bottom,
    Left_bottom,
    Left
};
node start[9];
vector<int> near[9];
ull fromTo[9][9];
node entering[9];
ull dp[150][150];

ull max_no_steps[9];

void initialization() {
    start[Middle] = { 65,65 };
    start[Left_up] = { 0,0 };
    start[Up] = { 0,65 };
    start[Right_up] = { 0,130 };
    start[Right] = { 65,130 };
    start[Right_bottom] = { 130,130 };
    start[Bottom] = { 130,65 };
    start[Left_bottom] = { 130,0 };
    start[Left] = { 65,0 };
}
void display() {
    for (auto& line : input) {
        cout << line << endl;
    }cout << endl;
}
void readInput() {
    string newLine;
    while (getline(in, newLine)) {
        input.pb(newLine);
    }
    n = input.size();
    m = input[0].size();
    for (int i = 0; i < input.size();i++) {
        for (int j = 0; j < input[0].size();j++) {
            if (input[i][j] == 'S') {
                input[i][j] = '.';
            }
        }
    }
}
bool outOfBounds(int x, int y) {
    if (x >= 0 && y >= 0 && x < n && y < m) {
        return false;
    }
    return true;
}
bool isValid(int x, int y) {
    if (!outOfBounds(x, y) && !visited[x][y] && input[x][y]=='.') {
        return true;
    }
    return false;
}
ull bfs(ull direction) {
    queue<node>q;
    ull maxim = 0;
    node START = start[direction];
    q.push(START);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            visited[i][j] = false;
            dp[i][j] = INT_MAX;
        }
    }
    dp[START.x][START.y] = 0;
    visited[START.x][START.y] = true;
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        q.pop();
        for (int i = 0; i < 4; i++) {
            ull x1 = x + dx[i];
            ull y1 = y + dy[i];
            if (isValid(x1, y1)) {
                q.push({ x1,y1 });
                visited[x1][y1] = true;
                dp[x1][y1] = dp[x][y] + 1;
                maxim = max(maxim, dp[x1][y1]);
            }
        }
    }
    return maxim;
}

void solve() {
    ull sum = 0;
    for (int direction = 0; direction < 9; direction++) {
        max_no_steps[direction] = bfs(direction);
        cout << max_no_steps[direction] << endl;
        for (int steps = 1; steps <= max_no_steps[direction]; steps++) {
            sum = 0;
            for (int i = 0; i < n; i++) {
                for (int j = 0; j < m; j++) {
                    if (dp[i][j] <= steps) {
                        if (steps % 2 == dp[i][j] % 2) {
                            sum++;
                        }
                    }
                }
            }
            no_steps[direction][steps] = sum;
        }
        cout << no_steps[direction][max_no_steps[direction]]
            <<' '<<no_steps[direction][max_no_steps[direction] - 1] << endl;
    }
    cout << (26501365 - 65) % 131<<' ';
    ull sides = (26501365 - 65) / 131;
    cout << sides << endl;
    ull rectangle = (2 * sides + 1) * (2 * sides + 1);
    ull corner = ((sides+2) * (sides + 1)) / 2 - 1;
    ull fullArea = rectangle -  corner * 4;
    cout << fullArea * 7444
    + sides * (no_steps[Left_up][64] + no_steps[Left_bottom][64]
        + no_steps[Right_up][64] + no_steps[Right_bottom][64])
    + (sides-1)*(no_steps[Right_up][195] + no_steps[Left_up][195] 
            + no_steps[Right_bottom][195] + no_steps[Left_bottom][195])
    + no_steps[Right][130] + no_steps[Left][130] + no_steps[Up][130] + no_steps[Bottom][130];
}
int main()
{
    readInput();
    initialization();
    solve();
    return 0;
}