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
#define ll long long
#define winSize 10
#define numbers 25
#define size 204

using namespace std;

ifstream in("input.txt");
ofstream out("output.txt");

ll sum;
ll instances[size];

ll localResult(string newLine) {

    string str;
    istringstream sin(newLine);
    sin >> str >> str;
    set <ll> win;
    ll no;
    ll localSum = 0;
    for (int i = 0; i < winSize; i++) {
        sin >> no;
        win.insert(no);
    }
    sin >> str;
    for (int i = 0; i < numbers; i++) {
        sin >> no;
        if (win.count(no)) {
            localSum++;
        }
    }
    return localSum;
}
void propagate(int index, ll terms,ll multiplier) {
    for (int i = index + 1; i <= index + terms && i < size; i++) {
        instances[i] += multiplier;
    }
}

int main()
{
    string newLine;
    int index = 0;
    while (getline(in, newLine)) {
        
        ll result = localResult(newLine);
        propagate(index, result, instances[index] + 1);
        sum += 1+instances[index];
        ++index;
    }
    cout << sum;
}