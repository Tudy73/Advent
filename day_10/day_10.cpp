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

pii circuit[141][141][2];
bool visited[142][142],bigVisited[500][500];
int bigMap[500][500];
vector<string> inputMap;
int n, m;
int sx, sy;
int x = 2, y = 3;
pii from = { 2,2 };
int input[141][141];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };

int xx[9] = { -1,-1,-1,0,0,0,1,1,1 };
int xy[9] = { -1,0,1,-1,0,1,-1,0,1 };

void readInput() {
    string newLine;
    for (int i = 0; i < 142; i++) {
        newLine.pb(' ');
    }
    inputMap.pb(newLine);
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        n++;
        m = 0;
        for (auto character : newLine) {
            m++;
            switch (character) {
            case '.':
            {
                break;
            }
            case 'S':
            {
                sx = n;
                sy = m;
                break;
            }
            case '-':
            {
                circuit[n][m][0] = { n,m - 1 };
                circuit[n][m][1] = { n,m + 1 };
                break;
            }
            case 'F':
            {
                circuit[n][m][0] = { n + 1,m };
                circuit[n][m][1] = { n,m + 1 };
                break;
            }
            case 'J':
            {
                circuit[n][m][0] = { n - 1,m };
                circuit[n][m][1] = { n,m - 1 };
                break;
            }
            case 'L':
            {
                circuit[n][m][0] = { n - 1,m };
                circuit[n][m][1] = { n,m + 1 };
                break;
            }
            case '|':
            {
                circuit[n][m][0] = { n - 1,m };
                circuit[n][m][1] = { n + 1,m };
                break;
            }
            case '7':
            {
                circuit[n][m][0] = { n,m - 1 };
                circuit[n][m][1] = { n + 1,m };
                break;
            }
            }
        }
        string line = ' ' + newLine;
        inputMap.pb(line);
    }
}
void findCycle() {
    input[sx][sy] = 1;
    while (!(x == sx && y == sy)) {
        input[x][y] = 1;
        for (int i = 0; i < 2; i++) {
            if (circuit[x][y][i] != from) {
                from = { x,y };
                int aux = x;
                x = circuit[x][y][i].first;
                y = circuit[aux][y][i].second;
                break;
            }
        }
    }
    inputMap[sx][sy] = 'F';
}
bool inBounds(int x, int y) {
    if (x < 1 || y<1 || x>n || y>m) {
        return false;
    }
    return true;
}
bool inBoundsBig(int x, int y) {
    if (x < 1 || y<1 || x>(n-1)*2+1 || y>(m-1)*2+1) {
        return false;
    }
    return true;
}
void bfs(int x, int y) {
    queue <pii> q;
    stack <pii> toEnclose;
    q.push({ x,y });
    visited[x][y] = true;
    bool isInCycle = true;
    while (!q.empty()) {
        pii current = q.front();
        input[current.first][current.second] = 2;
        q.pop();
        toEnclose.push(current);
        for (int k = 0; k < 4; k++) {
            int x1 = current.first + dx[k];
            int y1 = current.second + dy[k];
            if (!inBounds(x1, y1))isInCycle = false;
            if (inBounds(x1, y1) && input[x1][y1] == 0 && visited[x1][y1] == false) {
                q.push({ x1,y1 });
                visited[x1][y1] = true;
            }
        }
    }
    
    if (isInCycle)return;

    while (toEnclose.empty() == false) {
        pii current = toEnclose.top();
        toEnclose.pop();
        input[current.first][current.second] = 0;
    }

}
void bigBfs(int x, int y) {
    stack<pii> toEnclose;
    queue <pii> q;
    q.push({ x,y });
    bool isInCycle = true;
    while (!q.empty()) {
        pii current = q.front();
        bigMap[current.first][current.second] = 2;
        toEnclose.push(current);
        q.pop();
        for (int k = 0; k < 4; k++) {
            int x1 = current.first + dx[k];
            int y1 = current.second + dy[k];
            if (!inBoundsBig(x1, y1))isInCycle = false;
            if (inBoundsBig(x1, y1) && bigMap[x1][y1] !=1 && bigVisited[x1][y1] == false) {
                q.push({ x1,y1 });
                bigVisited[x1][y1] = true;
            }
        }
    }

    if (isInCycle)return;
    while (toEnclose.empty() == false) {
        pii current = toEnclose.top();
        toEnclose.pop();
        bigMap[current.first][current.second] = 0;
    }
}
void findEnclosed1() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (input[i][j] == 0 && visited[i][j] == false)
                bfs(i, j);
        }
    }
}
void initBigMap() {
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            int bigX = (i - 1) * 2 + 1;
            int bigY = (j - 1) * 2 + 1;
            bigMap[bigX][bigY] = input[i][j];

            if (input[i][j] != 1) {
                for (int k = 0; k < 9; k++) {
                    int xnew = i + xx[k];
                    int ynew = j + xy[k];
                    if (inBounds(xnew, ynew)) {
                        bigMap[bigX + xx[k]][bigY + xy[k]] = input[i][j];
                    }
                }
            }

            if (j < m) {
                if (input[i][j] != 1) {
                    bigMap[bigX][bigY+1] = input[i][j];
                }
                else if (input[i][j + 1] != 1) {
                    bigMap[bigX][bigY + 1] = input[i][j + 1];
                }
                else if (inputMap[i][j] == 'F' || inputMap[i][j] == 'L' ||inputMap[i][j] == '-') {
                    bigMap[bigX][bigY+1] = 1;
                }
                else bigMap[bigX][bigY+1] = 0;
            }
            else {
            }
            if (i < n) {
                if (input[i][j] != 1) {
                    bigMap[bigX+1][bigY] = input[i][j];
                }
                else if (input[i + 1][j] != 1) {
                    bigMap[bigX + 1][bigY] = input[i + 1][j];
                }
                else if (inputMap[i][j] == 'F' || inputMap[i][j] == '|' || inputMap[i][j] == '7') {
                    bigMap[bigX+1][bigY] = 1;
                }
                else bigMap[bigX+1][bigY] = 0;
            }
        }
    }
    int bigN = (n - 1) * 2 + 1;
    int bigM = (m - 1) * 2 + 1;

    for (int i = 1; i <= bigN; i++) {
        for (int j = 1; j <= bigM; j++) {
            if (bigMap[i][j] == 0)cout << '.';
            else cout << bigMap[i][j];
        }cout << endl;
    }cout << endl;

    for (int i = 1; i <= bigN; i++) {
        for (int j = 1; j <= bigM; j++) {
            if (bigMap[i][j] == 2 && bigVisited[i][j] == false) {
                bigBfs(i, j);
            }
        }
    }
    for (int i = 1; i <= bigN; i++) {
        for (int j = 1; j <= bigM; j++) {
            if (bigMap[i][j] == 0)cout << '.';
            else cout << bigMap[i][j];
        }cout << endl;
    }

}
ll findEnclosedFinal() {
    initBigMap();
    ll solution=0;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            if (bigMap[(i - 1) * 2 + 1][(j - 1) * 2 + 1] == 2) {
                solution++;
            }
        }
    }
    return solution;
}
void solve() {
    findCycle();
    findEnclosed1();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= m; j++) {
            cout << input[i][j];
        }cout << endl;
    }
    cout << endl;
    cout<<findEnclosedFinal();

}
int main()
{
    readInput();
    solve();
    return 0;
}