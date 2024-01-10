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

vector<pair<string,string> > input;
vector<pair<string, int>> boxSet[3005];

void display() {
    for (int i = 0; i < 4; i++) {
        auto box = boxSet[i];
        for (auto lens : box) {
            cout << lens.first << ' ' << lens.second<<", ";
        }
        if(box.size()>0)
        cout << endl;
    }
    cout << endl;
}
void readInput() {
    char c;
    string newLine,second;
    while (in>>c) {
        if (c == ',') {
            input.pb({ newLine,second });
            newLine.clear();
            second.clear();
        }
        else if(c == '-' || c == '=') {
            second.pb(c);
            if (c == '=') {
                in >> c;
                second.pb(c);
            }
        }
        else {
            newLine.pb(c);
        }
    }
    input.pb({ newLine,second });
}
int hashAlgorithm(string line) {
    int result = 0;
    for (auto c : line) {
        result += c;
        result *= 17;
        result %= 256;
    }
    return result;
}
int findLens(string label, int currentBox) {
    auto &box = boxSet[currentBox];
    for (int i = 0; i < box.size(); i++) {
        if (box[i].first == label) {
            return i;
        }
    }
    return -1;
}
void removeLens(string label, int currentBox) {
    int lens = findLens(label, currentBox);
    if (lens != -1) {
        boxSet[currentBox].erase(boxSet[currentBox].begin() + lens);
    }
}
void addLens(string label, char no, int currentBox) {
    int lens = findLens(label, currentBox);
    if (lens != -1) {
        boxSet[currentBox][lens].second = no;
        return;
    }
    boxSet[currentBox].pb({ label,no });
}
ll computeFocusingPower() {
    ll focusingPower=0;
    for (int boxNo = 0; boxNo < 3000;boxNo++) {
        auto &box = boxSet[boxNo];
        for (int i = 0; i < box.size(); i++) {
            focusingPower += (1LL * (boxNo + 1) * (i+1)*box[i].second);
        }
    }
    return focusingPower;
}
void solve() {

    ll sum = 0;
    for (auto &line : input) {
        int box = hashAlgorithm(line.first);
        if (line.second[0] == '-') {
            removeLens(line.first,box);
        }
        else {
            addLens(line.first,line.second[1]-'0', box);
        }
    }
    display();
    cout << computeFocusingPower();
}
int main()
{
    readInput();
    solve();
    return 0;
}