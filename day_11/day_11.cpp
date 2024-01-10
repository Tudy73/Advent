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
vector<pii> galaxies;
vector<ll> partialX, partialY;

void readInput() {
    string newLine;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        input.pb(newLine);
    }
}
void expandSpace() {
    for (auto line : input) {
        cout << line << endl;
    }
    cout << endl;
    for (auto line : input) {
        bool empty = true;
        for (auto el : line) {
            if (el == '#') {
                empty = false;
            }
        }
        if (empty) {
            partialX.pb(partialX[partialX.size() - 1] + 1000000);
        }
        else {
            if (partialX.empty())
                partialX.pb(1);
            else
                partialX.pb(partialX[partialX.size() - 1] + 1);
        }
    }
    for (int i = 0; i < input[0].size(); i++) {
        bool empty = true;
        for (int j = 0; j < input.size(); j++) {
            if (input[j][i] == '#') {
                empty = false;
            }
        }
        if (empty) {
            partialY.pb(partialY[partialY.size() - 1] + 1000000);
        }
        else {
            if (partialY.empty()) {
                partialY.pb(1);
            }
            else
                partialY.pb(partialY[partialY.size() - 1] + 1);
        }
    }

}
void getGalaxies() {
    for (int i = 0; i < input.size(); i++) {
        for (int j = 0; j < input[i].size(); j++) {
            if (input[i][j] == '#') {
                galaxies.pb({ i,j });
            }
        }
    }
}
void solve() {
    expandSpace();
    getGalaxies();
    ll sum = 0;
    for (auto galaxy1 : galaxies) {
        for (auto galaxy2 : galaxies) {
            if (galaxy1 != galaxy2) {
                sum += (abs(partialX[galaxy1.first] - partialX[galaxy2.first]) 
                    + abs(partialY[galaxy1.second] - partialY[galaxy2.second]));
            }
        }
    }
    cout << sum / 2;
}
int main()
{
    readInput();
    solve();
    return 0;
}