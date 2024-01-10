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
bool visited[200][200];
int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
int n, m;

void display() {

}
void readInput() {
    string newLine;
    while (getline(in, newLine)) {
        input.pb(newLine);
    }
    n = input.size();
    m = input[0].size();
}
bool outOfBounds(int x, int y) {
    if (x >= 0 && y >= 0 && x < n && y < m) {
        return false;
    }
    return true;
}
bool isValid(int x, int y) {
    if (outOfBounds(x, y)==false && input[x][y]!='#') {
        return true;
    }
    return false;
}
void solve() {
    int sum = 0,valid=0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            int count = 0;
            if (!isValid(i, j))continue;
            valid++;
            for (int k = 0; k < 4; k++) {
                int i1 = i + dx[k];
                int j1 = j + dy[k];
                if (isValid(i1, j1))
                {
                    if (k == 0) {
                        if (input[i1][j1] == 'V')continue;
                    }
                    else if (k == 1) {
                        if (input[i1][j1] == '<')continue;
                    }
                    else if (k == 2) {
                        if (input[i1][j1] == '^')continue;
                    }
                    else if (input[i1][j1] == '>')continue;
                    count++;
                }
            }
            if (count > 2) {
                sum++;
            }
        }
    }
}
int main()
{
    readInput();
    solve();
    return 0;
}