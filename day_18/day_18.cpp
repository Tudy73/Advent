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
using namespace std;

ifstream in("input.txt");

typedef struct {
    ll direction;
    ll amount;
}node;

typedef struct {
    ll row;
    ll startY;
    ll endY;
    ll position;
}line;

vector<node> input;
vector <line> lines;
vector<ll> intervals;
map<ll, ll> walls;
ll dx[4] = { -1,0,1,0 };
ll dy[4] = { 0,1,0,-1 };
ll startX, startY;
ull sumTotal = 0;
ull sumLines = 0;
ull sumCorners = 0;

void display() {
}
void readInput() {
    string newLine,actual;
    char direction;
    ll amount, newDir = 0;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        sin >> direction >> amount>>actual;
        amount = stoll(actual.substr(2, actual.size() - 4), 0, 16);
        direction = actual[actual.size() - 2];
        switch (direction)
        {
        case '0':
            newDir = 1;
            break;
        case '1':
            newDir = 2;
            break;
        case '2':
            newDir = 3;
            break;
        case '3':
            newDir = 0;
            break;
        }
        input.pb({ newDir,amount });
    }
}
void digRoad() {
    ll curX = 0, curY = 0,pos=0;
    for (auto &move : input) {
        pos++;
        if (move.direction == 1) {
            lines.pb({ curX,curY,curY + move.amount,pos});
        }
        else if (move.direction == 3) {
            lines.pb({ curX,curY - move.amount,curY,pos});
        }
        else {
            intervals.pb(curY);
            walls[curY] += move.amount + 1;
        }
        curX += dx[move.direction] * move.amount;
        curY += dy[move.direction] * move.amount;
        sumLines += move.amount;
    }
}
bool compare(line a, line b) {
    return a.row < b.row;
}
void solve() {
    digRoad();
    sort(intervals.begin(), intervals.end());
    sort(lines.begin(), lines.end(),compare);
    ll first = 1;
    for (int i = 0; i < intervals.size()-1; i++) {
        ll startY = intervals[i];
        ll endY = intervals[i + 1];
        if (startY == endY) {
            continue;
        }
        ll area = 5;
        ll lastX = 0;
        queue<pair<ll, ll> > q;
        for (auto &line:lines) {
            if (line.startY <= startY && line.endY >= endY) {
                if (area == 0) {
                    area = (line.row - lastX -1) * (endY - startY -1);
                    q.push({ lastX,line.row });
                    sumTotal += area;
                }
                else {
                    lastX = line.row;
                    area = 0;
                }
            }
        }
        area = 5;
        for (auto& line : lines) {
            if (line.endY > endY && endY>=line.startY) {
                if (area == 0) {
                    area = 5;
                    while (!q.empty() && q.front().first < line.row) {
                        ll x1 = q.front().first;
                        ll x2 = q.front().second;

                        if (x2 < lastX) {
                            q.pop();
                            continue;
                        }
                        if (x1 > line.row) {
                            break;
                        }

                        ll startX = max(lastX, x1);
                        ll endX = min(line.row, x2);

                        sumTotal += endX - startX - 1;

                        if (x2 > line.row) {
                            break;
                        }
                        q.pop();
                    }

                }
                else {
                    lastX = line.row;
                    area = 0;
                }
            }
        }
    }
    sumTotal += sumLines;
    cout << sumTotal;
}
int main()
{
    readInput();
    solve();
    return 0;
}