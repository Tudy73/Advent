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

vector <vector<ll>> inputs;

void readInput() {
    string newLine;
    ll no;

    while (getline(in, newLine)) {
        istringstream sin(newLine);

        vector<ll> array;
        while (sin >> no) {
            array.pb(no);
        }
        inputs.pb(array);
    }
}
bool difZero(vector<ll> input) {
    for (auto el : input) {
        if (el != 0) {
            return true;
        }
    }
    return false;
}
void subtract(vector<ll> &input) {
    for (int i = 0; i < input.size()-1; i++) {
        input[i] = input[i + 1] - input[i];
    }
    input.pop_back();
}
void solve() {

    vector <ll> heads;
    ll totalSum = 0;
    for (auto &input : inputs) {
        while (difZero(input)) {
            heads.pb(input[0]);
            subtract(input);
        }
        ll sum = 0;
        reverse(heads.begin(), heads.end());
        for (auto head : heads) {
            sum = head - sum;
        }
        heads.clear();
        totalSum += sum;
    }
    cout << totalSum;
}
int main()
{
    readInput();
    solve();
    return 0;
}