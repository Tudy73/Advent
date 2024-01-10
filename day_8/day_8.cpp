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
#include <map>
#define ll long long
#define ull unsigned long long
#define pb push_back
using namespace std;

ifstream in("input.txt");

string sequence;
map <string, string> leftOf;
map <string, string> rightOf;

vector<string> current, toUpdate;
vector<ll> cycles;

void readInput() {
    string newLine;
    getline(in, newLine);
    istringstream sin(newLine);
    sin >> sequence;
    getline(in, newLine);
    
    string str,str2;

    while (getline(in, newLine)) {
        istringstream tin(newLine);
        tin >> str;
        tin >> str2 >> str2;
        str2.erase(0,1);
        str2.pop_back();
        leftOf[str] = str2;
        
        tin >> str2;
        str2.pop_back();
        rightOf[str] = str2;

        if (str.at(2) == 'A') {
            current.pb(str);
        }
    }
}
void solve() {
    ll count = 0;
    int index = 0;
    while (current.size() > 0) {
        for (auto elem : current) {
            if (elem.at(2) != 'Z') {
                string str;
                if (sequence[index] == 'L')
                    str = leftOf[elem];
                else str = rightOf[elem];
                toUpdate.pb(str);
            }
            else {
                cycles.pb(count);
            }
        }
        count++;
        current.assign(toUpdate.begin(), toUpdate.end());
        toUpdate.clear();
        ++index;
        if (index == sequence.size())index = 0;
    }
    ull result = 1;
    for (auto cycle : cycles) {
        result = lcm(result, cycle);
    }
    cout << result;
}
int main()
{
    readInput();
    solve();
    return 0;
}