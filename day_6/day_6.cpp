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
#define pb push_back
using namespace std;

ifstream in("input.txt");

ll duration;
ll length;

void readInput() {
    string newLine,line2;
    char no;
    getline(in, newLine);
    istringstream sin(newLine);
    while (sin >> no) {
        if (isdigit(no))
            duration = duration * 10 + (no - '0');
    }
    getline(in, line2);
    istringstream tin(line2);
    while (tin >> no) {
        if (isdigit(no))
            length = length * 10 + (no - '0');
    }
    cout << duration << ' ' << length << endl;

}
ll noWays() {
    double delta = duration * duration - 4 * (length+0.01);
    double k1 = ((duration - sqrt(delta)) / 2);
    double k2 = ((duration + sqrt(delta)) / 2);
    ll start = ll(k1);
    ll end = ll(k2);
    return end - start;
}
int main()
{
    readInput();
    cout << noWays();
    return 0;
}