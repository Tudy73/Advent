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

vector<vector<string>> input;
bool rowLike[50][50];
bool columnLike[50][50];
int n, m, x, y;
vector<string> current;
void display() {
    for (auto line : current) {
        for (auto ch : line) {
            cout << ch;
        }cout << endl;
    }
    cout << endl;
}
void readInput() {
    string newLine;
    vector<string> pattern;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        if (newLine[0] != '#' && newLine[0]!='.') {
            input.pb(pattern);
            pattern.clear();
            continue;
        }
        pattern.pb(newLine);
    }
    input.pb(pattern);
}
bool rowAlike(int r1, int r2) {
    for (int i = 0; i < m; i++) {
        if (current[r1][i] != current[r2][i]) {
            return false;
        }
    }
    return true;
}
bool columnAlike(int c1, int c2) {
    for (int i = 0; i < n; i++) {
        if (current[i][c1] != current[i][c2]) {
            return false;
        }
    }
    return true;
}
void initLookAlikes() {
    for (int i = 0; i < 50; i++) {
        for (int j = 0; j < 50; j++) {
            rowLike[i][j] = false;
            columnLike[i][j] = false;
        }
    }
    //rows
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (rowAlike(i, j)) {
                rowLike[i][j] = true;
                rowLike[j][i] = true;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        for (int j = i + 1; j < m; j++) {
            if (columnAlike(i, j)) {
                columnLike[i][j] = true;
                columnLike[j][i] = true;
            }
        }
    }
}
bool isRowReflection(int r1, int r2) {
    bool ok = false;
    for (int i = r1, j = r2; i >= 0 && j < n; j++, i--) {
        if (!rowLike[i][j]) {
            return false;
        }
        if (i == x || j == x) {
            ok = true;
        }
    }
    return true && ok;
}
bool isColumnReflection(int c1, int c2) {
    bool ok = false;
    for (int i = c1, j = c2; i >= 0 && j < m; j++, i--) {
        if (!columnLike[i][j]) {
            return false;
        }
        if (i == y || j == y) {
            ok = true;
        }
    }
    return true && ok;
}
void flip(int i, int j) {
    if (current[i][j] == '#') {
        current[i][j] = '.';
    }
    else current[i][j] = '#';
}
int findSpecificReflection() {
    //find row reflection
    initLookAlikes();
    for (int i = 0; i < n - 1; i++) {
        if (isRowReflection(i, i + 1)) {
            return 100 * (i + 1);
        }
    }
    //find column reflection
    for (int i = 0; i < m - 1; i++) {
        if (isColumnReflection(i, i + 1)) {
            return i + 1;
        }
    }
    return 0;
}
int findReflection() {
    int sum = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            flip(i, j);
            x = i;
            y = j;
            sum = findSpecificReflection();
            if (sum > 0) {
                return sum;
            }
            flip(i, j);
        }
    }
    cout << sum << endl;
}
void solve() {

    ll sum = 0;
    for (int i = 0; i < input.size(); i++) {
        current = input[i];
        n = current.size();
        m = current[0].size();
        sum += findReflection();
    }
    cout << sum;
}
int main()
{
    readInput();
    solve();
    return 0;
}