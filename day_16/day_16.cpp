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
#define UP 0
#define RIGHT 1
#define DOWN 2
#define LEFT 3
#define BACK 0
#define FRONT 1
#define VERTICAL 2
#define HORIZONTAL 3
using namespace std;

ifstream in("input.txt");

vector<string> input;
bool energized[112][112];
bool beenThere[112][112][4];

int dx[4] = { -1,0,1,0 };
int dy[4] = { 0,1,0,-1 };
vector<int> nextOf[4][4] = { { {LEFT},{DOWN},{RIGHT},{UP} },
                         { {RIGHT},{UP},{LEFT},{DOWN} },
                         { {UP},{UP,DOWN},{DOWN},{UP,DOWN} },
                         { {LEFT,RIGHT},{RIGHT},{LEFT,RIGHT},{LEFT} } };

typedef struct {
    int x;
    int y;
    int sense;
}node;
void display() {
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            cout << energized[i][j] << ' ';
        }cout << endl;
    }
    cout << endl;
}
void readInput() {
    string newLine;
    while (getline(in,newLine)) {
        input.pb(newLine);
    }
}
bool outOfBounds(node nod) {
    if (nod.x >= 0 && nod.y >= 0 && nod.x < input.size() && nod.y < input[0].size())
        return false;
    return true;
}
void simulateRays(node nod) {
    queue <node> q;
    q.push(nod);
    while (!q.empty()) {
        int x = q.front().x;
        int y = q.front().y;
        int sense = q.front().sense;
        q.pop();
        if (outOfBounds({ x,y,sense }) || beenThere[x][y][sense] == true) {//if we've been here we are entering a cycle
            continue;
        }
        energized[x][y] = true;
        beenThere[x][y][sense] = true;
        int type;
        switch (input[x][y]){
        case '.': {
            q.push({ x + dx[sense],y + dy[sense],sense });
            continue;
        }
        case '\\': {
            type = BACK;
            break;
        }
        case '/': {
            type = FRONT;
            break;
        }
        case '|': {
            type = VERTICAL;
            break;
        }
        case '-': {
            type = HORIZONTAL;
            break;
        }
        }

        for (auto nextSense : nextOf[type][sense]) {
            q.push({ x + dx[nextSense],y + dy[nextSense],nextSense });
        }

    }
}
ll solveWith(node nod) {
    memset(beenThere, 0, sizeof(beenThere));
    memset(energized, 0, sizeof(energized));
    simulateRays(nod);
    ll sum = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (energized[i][j]) {
                sum++;
            }
        }
    }
    return sum;
}
void solve() {
    
    ll maxim = 0;

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            vector<int> directions;
            int conditions = (i == 0) + (j == 0) + (i == input.size() - 1) + (j == input[0].size() - 1);
            if (i == 0) {
                directions.pb(DOWN);
            }
            if (j == 0) {
                directions.pb(RIGHT);
            }
            if (i == input.size() - 1) {
                directions.pb(UP);
            }
            if (i == input[0].size() - 1) {
                directions.pb(LEFT);
            }
            if (conditions) {
                for (auto direction : directions) {
                    maxim = max(maxim, solveWith({ i,j, direction }));
                }
            }
        }
    }

    cout << maxim;
}
int main()
{
    readInput();
    solve();
    return 0;
}