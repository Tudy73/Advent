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

#define X 0
#define M 1
#define A 2
#define S 3

using namespace std;

ifstream in("input.txt");

vector<string> input;

typedef struct {
    int left;
    int right;
}interval;

typedef struct {
    int type;
    interval range;
    string nextUp;
}workState;
map<string, vector<workState>> workflow;
vector<vector<int>> category;

ll cur;

typedef interval state[4];

void display(state currentState) {
    cout << "( " << currentState[0].left << ' ' << currentState[0].right << ", " <<
        currentState[1].left << ' ' << currentState[1].right << ", " <<
        currentState[2].left << ' ' << currentState[2].right << ", " <<
        currentState[3].left << ' ' << currentState[3].right << " )";
}
void readCategories(string categories) {
    istringstream sin(categories);
    string condition;
    vector<int> list;
    char type, sign;
    int number;
    while(sin >> condition) {
        istringstream tin(condition);
        tin >> type >> sign >> number;
        list.pb(number);
    }
    category.pb(list);
}
void readWorkflow(string line) {
    string actual, condition;
    int toConvert;
    string statement, nextUp;
    istringstream sin(line);
    sin >> actual;
    char type,sign;
    while (sin >> condition) {
        if (condition[1] == '<' || condition[1] == '>') {

            for (int i = 0; i < condition.size(); i++) {
                if (condition[i] == ':') {
                    condition[i] = ' ';
                }
            }
            istringstream tin(condition);
            tin >> statement;
            istringstream yin(statement);
            yin >> type >> sign >> toConvert;
            interval newInterval;
            if (sign == '<') {
                newInterval = { 1,toConvert - 1 };
            }
            else {
                newInterval = { toConvert+1,4000 };
            }
            int typ;
            if (type == 'x')
                typ = X;
            if (type == 'm')
                typ = M;
            if (type == 'a')
                typ = A;
            if (type == 's')
                typ = S;
            tin >> nextUp;
            workflow[actual].pb({ typ,newInterval, nextUp });
        }
        else {
            workflow[actual].pb({ S,{1,4000},condition});
        }
    }
}
void readInput() {
    string newLine;
    bool ok = 0;
    while (getline(in, newLine)) {
        if (newLine.size() <= 0) {
            ok = true;
            continue;
        }
        
        for (int i = 0; i < newLine.size(); i++) {
            if (newLine[i] == '{' || newLine[i] == '}' ||
                newLine[i] == ',') {
                newLine[i] = ' ';
            }
        }

        if (ok) {
            return;
        }
        else {
            readWorkflow(newLine);
        }
    }
}
bool evaluateCondition(string condition) {
    istringstream sin(condition);
    char type, sign;
    int number;
    sin >> type >> sign >> number;
    int y;
    if (type == 'x')y = X;
    if (type == 'm')y = M;
    if (type == 'a')y = A;
    if (type == 's')y = S;
    int left = category[cur][y];
    if (sign == '<') {
        if (left < number) {
            return true;
        }
        return false;
    }
    if (sign == '>') {
        if (left > number) {
            return true;
        }
        return false;
    }
    if (sign == '=') {
        if (left == number) {
            return true;
        }
        return false;
    }
}
interval intervalMatching(interval a, interval b) {
    return { max(a.left,b.left),min(a.right,b.right) };
}
interval intervalRemaining(interval a, interval b) {
    if (a.left < b.left) {
        return { a.left,min(a.right,b.left-1) };
    }
    if (a.right > b.right) {
        return { max(b.right + 1,a.left),a.right };
    }
    return { 0,0 };
}
ull between(interval currentInterval) {
    return currentInterval.right - currentInterval.left + 1;
}
ull numberOfStates(state currentState) {
    return between(currentState[0]) * between(currentState[1]) *
        between(currentState[2]) * between(currentState[3]);
}
ull work(vector<workState>& list,state currentState) {
    string nextUp;
    int type;
    interval newInterval;
    interval currentInterval;
    ull sum = 0;
    for (int i = 0; i < list.size();i++) {
        type = list[i].type;
        newInterval = list[i].range;
        nextUp = list[i].nextUp;
        currentInterval = currentState[type];
        interval forwardInterval = intervalMatching(currentInterval, newInterval);
        interval remainingInterval = intervalRemaining(currentInterval, newInterval);

        currentState[type] = forwardInterval;
        if (nextUp == "A") {
            sum += numberOfStates(currentState);
        }
        else if (nextUp != "R") {
            state copyState;
            for (int j = 0; j < 4; j++) {
                copyState[j] = currentState[j];
            }
            sum += work(workflow[nextUp], copyState);
        }
        currentState[type] = remainingInterval;
    }
    return sum;
}
void solve() {
    state firstState = { {1,4000},{1,4000},{1,4000},{1,4000}};
    cout<< work(workflow["in"],firstState);
}
int main()
{
    readInput();
    solve();
    return 0;
}