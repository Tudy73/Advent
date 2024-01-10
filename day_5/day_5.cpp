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
#define seed_soil 0
#define soil_fertilizer 1
#define fertilizer_water 2
#define water_light 3
#define light_temperature 4
#define temperature_humidity 5
#define humidity_location 6
#define location 7
using namespace std;

ifstream in("input.txt");

typedef struct {
    ll dest;
    ll source;
    ll size;
}node;

typedef struct {
    ll start;
    ll size;
}seed;

vector <node> map[7];
vector <seed> seeds;

bool compareBySource(node a, node b) {
    return a.source < b.source;
}

void readMap(int index) {
    string str, newLine;
    ll a,b,c;
    getline(in,newLine);

    while (getline(in,newLine)) {
        if (!isdigit(newLine[0]))
            break;
        istringstream sin(newLine);
        sin >> a >> b >> c;
        map[index].pb({ a,b,c });
    }
    sort(map[index].begin(), map[index].end(), compareBySource);
}
void readInput() {
    string str,newLine;
    ll no,no2;
    getline(in, newLine);
    istringstream sin(newLine);
    sin >> str;
    while (sin >> no >> no2) {
        seeds.pb({ no,no2 });
    }
    getline(in, str);
    readMap(seed_soil);
    readMap(soil_fertilizer);
    readMap(fertilizer_water);
    readMap(water_light);
    readMap(light_temperature);
    readMap(temperature_humidity);
    readMap(humidity_location);
}
ll findMin(seed item, int type) {

    if (type == location) {
        return item.start;
    }
    ll minim = LLONG_MAX;
    ll last = item.start;
    ll itemEnd = item.start + item.size -1;
    ll nodEnd;
    for (auto nod : map[type]) {
        nodEnd = nod.source + nod.size - 1;
        if (nodEnd < last)
            continue;
        if (nod.source > itemEnd) {
            minim = min(minim, findMin({ last,itemEnd - last + 1 }, type + 1));
            break;
        }
        if (last < nod.source)
            minim = min(minim, findMin({ last,nod.source - last }, type + 1));

        ll begin, size;

        if (last > nod.source) {
            begin = nod.dest + (last-nod.source);
            size = min(itemEnd, nodEnd) - last + 1;
        }
        else {
            begin = nod.dest;
            size = min(itemEnd, nodEnd) - nod.source + 1;
        }
        minim = min(minim, findMin({ begin,size }, type + 1));

        last = nodEnd + 1;        
        if (itemEnd <= nodEnd)
            break;
    }
    if (last <= itemEnd) {
        minim = min(minim, findMin({ last,itemEnd - last + 1 }, type + 1));
    }
    return minim;
}
int main()
{
    readInput();
    ll sol = LLONG_MAX;
    for (auto item : seeds) {
        sol = min(sol, findMin(item, seed_soil));
    }
    cout << sol;
    return 0;
}