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
vector<vector<int>> result;
int island[200];
int dots[200];
int limit[200];
ll dp[120][120][120];

void readInput() {
    string newLine,array;
    char comma;
    int no;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        sin >> array;
        input.pb(array);
        sin >> no;
        vector<int> aux;
        aux.pb(no);
        while (sin >> comma >> no) {
            aux.pb(no);
        }
        result.pb(aux);
    }
}
bool hasDot(int l,int r) {
    if (l == 0)return dots[r] > 0;
    return (dots[r] - dots[l - 1]) > 0;
}
int islands(int l,int r) {
    if (l == 0)return island[r];
    return island[r] - island[l-1];
}
void initLimit(string str,int mux) {
    vector <int> current = result[mux];
    int size = str.size();
    for (int i = current.size() - 1; i >= 0; i--) {
        if (i == current.size() - 1) {
            limit[i] = size - current[i];
        }
        else {
            limit[i] = limit[i + 1] - 1 - current[i];
        }
    }
}
void dotsAndHash(string current) {
    for (int i = 0; i <current.size(); i++) {
        if (i == 0) {
            island[i] = 0;
            dots[i] = 0;
        }
        else {
            island[i] = island[i - 1];
            dots[i] = dots[i - 1];
        }
            
        if (current[i] == '#') {
            island[i] ++;
        }
        if (current[i] == '.') {
            dots[i]++;
        }
    }
}
ll ways(string current,int left,int index,int mux,int islandNo,int islandCounted) {
    ll total = 0;
    ll maxim = limit[index];
    ll temp;
    for (int i = left; i <= maxim; i++) {
        while(i<=maxim && hasDot(i, i + result[mux][index]-1)) {
            i++;
        }
        if (i > maxim)return total;
        if (index + 1 == result[mux].size()) {
            if (islandNo != islandCounted + islands(i,i+result[mux][index]-1)) {
                continue;
            }
            total++;
            continue;
        }
        int afterChar = i + result[mux][index];
        if (afterChar<current.size() && current[afterChar] == '#') {
            continue;
        }
        temp = dp[i + result[mux][index]][index + 1][islandCounted + islands(i, i + result[mux][index] - 1)];
        if (temp==-1)
        {
            temp = ways(current, i + result[mux][index] + 1, index + 1, 
            mux, islandNo, islandCounted + islands(i, i + result[mux][index] - 1));

            dp[i + result[mux][index]][index + 1][islandCounted + islands(i, i + result[mux][index] - 1)] = temp;
        }
           total += temp;
        
    }
    return total;
}
void enlarge(int index) {
    string current;
    for (int j = 0; j < 5; j++) {
        current += input[index];
        if (j < 4)
            current += '?';
    }
    input[index] = current;
    vector<int> aux = result[index];
    for (int j = 0; j < 4; j++) {
        for (auto k : aux) {
            result[index].pb(k);
        }
    }
}
void refreshDp() {
    for (int i = 0; i < 120; i++) {
        for (int j = 0; j < 120; j++) {
            for (int k = 0; k < 120; k++) {
                dp[i][j][k] = -1;
            }
        }
    }
}
void solve() {

    ll sum = 0;
    for (int i = 0; i < input.size();i++) {
        enlarge(i);
        dotsAndHash(input[i]);
        initLimit(input[i], i);
        refreshDp();
        ll islandNo = islands( 0, input[i].size() - 1);
        sum += ways(input[i],0, 0, i, islandNo, 0);
        cout << i + 1 << "/" << input.size() << endl;
    }
    cout << sum;
}
int main()
{
    readInput();
    solve();
    return 0;
}