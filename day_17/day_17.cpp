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

vector<string> input;

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
bool visited[305][305][4][11];
struct node {
    int value;
    int x;
    int y;
    int sense;
    int streak;
    bool operator<(const node& other) const {
        return value > other.value;
    }
};
void display() {
    for (auto &line : input) {
        cout << line << endl;
    }
    cout << endl;
}
void readInput() {
    string newLine;
    while (getline(in, newLine)) {
        input.pb(newLine);
    }
}
bool outOfBounds(int x, int y) {
    if (x >= 0 && y >= 0 && x < input.size() && y < input[0].size()) {
        return false;
    }
    return true;
}
bool isTurning(int sense, int i) {
    return 
        (sense == 0 && i == 2) ||
        (sense == 2 && i == 0) ||
        (sense == 3 && i == 1) ||
        (sense == 1 && i == 3);
}
void solve() {
    priority_queue<node, vector<node>, less<>> q;
    q.push({ 0, 0, 0, 1,1});
    q.push({ 0, 0, 0, 2,1 });
    int minim = INT_MAX;
    while (!q.empty()) {
        int x = q.top().x;
        int y = q.top().y;
        int value = q.top().value;
        int sense = q.top().sense;
        int streak = q.top().streak;
        q.pop();
        for (int i = 0; i < 4; i++) {
            int x1 = x + dx[i];
            int y1 = y + dy[i];
            if (outOfBounds(x1, y1) || isTurning(i,sense)) {
                continue;
            }
            int newStreak=1;
            int newValue = value + (input[x1][y1] - '0');
            if (i == sense) {
                newStreak = streak + 1;
            }
            else {
                if (streak < 4)continue;
            }
            if (newStreak > 10) {
                continue;
            }
            if (visited[x1][y1][i][newStreak] == false) {
                visited[x1][y1][i][newStreak] = true;
                if (x1 == input.size()-1 && y1 == input[0].size()-1 && newStreak>3) {
                    minim = min(minim, newValue);
                }
                q.push({ newValue,x1,y1,i,newStreak });
            }
        }
    }
    cout << minim;
}
int main()
{
    readInput();
    solve();
    return 0;
}