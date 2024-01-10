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
vector<string> auxInput;
map <ll, ll> found;

void display() {
    for (auto line : input) {
        cout << line << endl;
    }
    cout << endl;
}
void readInput() {
    string newLine;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        input.pb(newLine);
    }
}
void slideNorth(int row,int col) {
    input[row][col] = '.';
    int newRow = row;
    while (newRow - 1 >= 0 && input[newRow - 1][col] == '.') {
        newRow--;
    }
    input[newRow][col] = 'O';
}
void slideWest(int row, int col) {
    input[row][col] = '.';
    int newColumn = col;
    while (newColumn - 1 >= 0 && input[row][newColumn - 1] == '.') {
        newColumn--;
    }
    input[row][newColumn] = 'O';
}
void slideSouth(int row, int col) {
    input[row][col] = '.';
    int newRow = row;
    while (newRow + 1 <input.size() && input[newRow + 1][col] == '.') {
        newRow++;
    }
    input[newRow][col] = 'O';
}
void slideEast(int row, int col) {
    input[row][col] = '.';
    int newColumn = col;
    while (newColumn + 1 <= input[0].size() && input[row][newColumn + 1] == '.') {
        newColumn++;
    }
    input[row][newColumn] = 'O';
}
void slide() {
    //NORTH
    for (int i = 0; i < input[0].size(); i++) {//each column
        for (int j = 0; j < input.size(); j++) {//slide on row 
            if(input[j][i]=='O')
                slideNorth(j, i);
        }
    }
    //WEST
    for (int i = 0; i < input.size(); i++) {//each row
        for (int j = 0; j < input[0].size(); j++) {//slide on column
            if (input[i][j] == 'O')
                slideWest(i, j);
        }
    }
    //SOUTH
    for (int i = 0; i < input[0].size(); i++) {//each column
        for (int j = input.size() - 1; j >= 0; j--) {//slide on row 
            if (input[j][i] == 'O')
                slideSouth(j, i);
        }
    }
    //EAST
    for (int i = 0; i < input[0].size(); i++) {//each row
        for (int j = input.size(); j >= 0; j--) {//slide on column
            if (input[i][j] == 'O')
                slideEast(i, j);
        }
    }
}
ll computeLoad() {

    ll sum = 0;
    for (int i = 0; i < input.size(); i++) {
        int toAdd = input.size() - i;
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == 'O') {
                sum += toAdd;
            }
        }
    }
    return sum;
}
ll hashInput() {///situational hash map(not good)
    ll value = 0;
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[0].size(); j++) {
            if (input[i][j] == 'O') {
                value += (i * (100000) + (j + 1) * (j + 1));
            }
        }
    }
    return value;
}
void solve() {
    display();
    auxInput = input;
    ll currentHash=0;
    ll cyclesNeeded=0;
    ll offset=0;
    for (int i = 1;; i++) {
        slide();
        currentHash = hashInput();
        cout << "cycle " << i<< endl;
        if (found[currentHash]) {
            offset = found[currentHash]-1;
            ll cycles = i - offset -1;
            cyclesNeeded = (1000000000-offset) % cycles;
            cout << cyclesNeeded << endl;
            if (cyclesNeeded == 0) {
                cyclesNeeded=cycles;
            }
            cyclesNeeded+=offset;
            cout << "we've been here before " << endl << endl << endl;
            break;
        }
        found[currentHash] = i;
        display();
    }
    input = auxInput;
    for (int i = 0; i < cyclesNeeded; i++) {
        slide();
    }
    cout << computeLoad();
}
int main()
{
    readInput();
    solve();
    return 0;
}