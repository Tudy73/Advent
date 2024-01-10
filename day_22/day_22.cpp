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
    int x;
    int y;
    int z;
}coordinate;
typedef struct {
    coordinate start;
    coordinate end;
}brick;

vector<brick> input;
vector<int> support[1505];
int pillars[1505];
bool compare(brick a, brick b) {
    if (a.start.z == b.start.z) {
        return a.end.z < b.end.z;
    }
    return a.start.z < b.start.z;
}
void display() {
    for (auto br : input) {
        cout << br.start.x << ' ' << br.start.y << ' ' << br.start.z << ' ';
        cout << br.end.x << ' ' << br.end.y << ' ' << br.end.z << endl;
    }
}
void readInput() {
    string newLine;
    while (getline(in, newLine)) {
        for (int i = 0; i < newLine.size(); i++) {
            if (newLine[i] == ',' || newLine[i] == '~') {
                newLine[i] = ' ';
            }
        }
        
        istringstream sin(newLine);
        coordinate begin, last; 
        int x, y, z;
        sin >> x >> y >> z;
        begin = { x,y,z };
        sin >> x >> y >> z;
        last = { x,y,z };
        input.pb({ begin,last });
    }
    sort(input.begin(), input.end(), compare);
    display();
}
bool intersect(int x, int y) {
    if (input[x].start.x <= input[y].end.x && input[x].end.x >= input[y].start.x &&
        input[x].start.y <= input[y].end.y && input[x].end.y >= input[y].start.y) {
        return true;
    }
    return false;
}
int bfs(int startBrick) {

    queue <int> q;
    int sum = 0;
    q.push(startBrick);
    int count[1500];
    for (int i = 0; i < 1500; i++) {
        count[i] = 0;
    }

    while (!q.empty()) {
        int index = q.front();
        q.pop();
        for (auto onTop : support[index]) {

            count[onTop]++;
            if (pillars[onTop] == count[onTop]) {//desintegrate onTop brick
                sum++;
                q.push(onTop);
            }
        }
    }
    return sum;
}
void calculateFirst() {
    int sum = 0;
    for (int i = 0; i < input.size(); i++) {
        bool ok = true;
        for (auto onTop : support[i]) {
            if (pillars[onTop] == 1) {
                ok = false;
                break;
            }
        }
        if (ok) {
            sum++;
        }
    }
    cout << sum << endl;
}
void solve() {


    for (int i = 0; i < input.size(); i++) {
        int minimZ = 0;
        for (int j = 0; j < i; j++) {
            if (intersect(i, j)) {
                minimZ = max(minimZ, input[j].end.z + 1);
            }
        }
        int height = input[i].end.z - input[i].start.z;
        input[i].start.z = minimZ;
        input[i].end.z = minimZ + height;
    }

    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (intersect(i, j) && input[i].start.z == input[j].end.z + 1) {
                pillars[i]++;
                support[j].pb(i);
            }
        }
    }

    calculateFirst();
    int sum = 0;
    for (int i = 0; i < input.size();i++) {//choose brick to desintegrate
        sum+=bfs(i);
    }
    cout << sum;
}
int main()
{
    readInput();
    solve();
    return 0;
}