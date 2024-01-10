#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <fstream>
#include <sstream>
#include <set>
#include <algorithm>
#include <numeric>
#include <cmath>
#include <queue>
#include <numeric>
#include <chrono>
#include <thread>
#include <stack>
#include <map>
#define ll long long
#define ull unsigned long long
#define pb push_back
#define pii pair<int,int>
#define LOW false
#define HIGH true
#define YES 1
#define NO 0

using namespace std;

ifstream in("input.txt");


class GFG {
public:
    // dfs Function to reach destination
    bool dfs(int curr, int des, vector<vector<int> >& adj,
        vector<int>& vis)
    {

        // If curr node is destination return true
        if (curr == des) {
            return true;
        }
        vis[curr] = 1;
        for (auto x : adj[curr]) {
            if (!vis[x]) {
                if (dfs(x, des, adj, vis)) {
                    return true;
                }
            }
        }
        return false;
    }

    // To tell whether there is path from source to
    // destination
    bool isPath(int src, int des, vector<vector<int> >& adj)
    {
        vector<int> vis(adj.size() + 1, 0);
        return dfs(src, des, adj, vis);
    }

    // Function to return all the strongly connected
    // component of a graph.
    vector<vector<int> > findSCC(int n,
        vector<vector<int> >& a)
    {
        // Stores all the strongly connected components.
        vector<vector<int> > ans;

        // Stores whether a vertex is a part of any Strongly
        // Connected Component
        vector<int> is_scc(n+1, 0);

        vector<vector<int> > adj(n+1);

        for (int i = 0; i < a.size(); i++) {
            adj[a[i][0]].push_back(a[i][1]);
        }

        // Traversing all the vertices
        for (int i = 1; i <= n; i++) {

            if (!is_scc[i]) {

                // If a vertex i is not a part of any SCC
                // insert it into a new SCC list and check
                // for other vertices whether they can be
                // thr part of thidl ist.
                vector<int> scc;
                scc.push_back(i);

                for (int j = i + 1; j <= n; j++) {

                    // If there is a path from vertex i to
                    // vertex j and vice versa put vertex j
                    // into the current SCC list.
                    if (!is_scc[j] && isPath(i, j, adj)
                        && isPath(j, i, adj)) {
                        is_scc[j] = 1;
                        scc.push_back(j);
                    }
                }

                // Insert the SCC containing vertex i into
                // the final list.
                ans.push_back(scc);
            }
        }
        return ans;
    }
};


enum moduleType {
    broadcaster,
    flip_flop,
    conjunct,
    output
};
typedef struct {
    bool signal;
    string last;
    string cur;
}node;

map<string, vector<string > > nextUp;
map<string, moduleType> type;
map<string, bool> state;
map<string, vector<string>> inputs;
map<string, int>toInt;
map<int, string>toString;

set<string> modules;
map<string, map<string, bool> > conjunc;
map<string, int> component;
map<string, bool> isOutput;
map<string, bool> isInput;
vector<int> nextComponent[12];


bool goalReached = false;
int rx, qn;
ll status;
ll global = 0, lastGlobal = 0;
ll high, low;
void display() {
}
int conv_int(string s) {
    return (s[0] - 'a') * 27 + (s[1] - 'a');
}
string conv_string(int a) {
    string t;
    t.pb(a / 27 + 'a');
    t.pb(a % 27 + 'a');
    if (t == "br") {
        return "broadcaster";
    }
    return t;
}
void readInput() {
    string newLine;

    string reader, receiver;
    while (getline(in, newLine)) {
        istringstream sin(newLine);
        sin >> reader;
        string sender;
        if (reader[0] == '%' || reader[0] == '&') {
            sender = reader.substr(1, reader.size() - 1);
        }
        else sender = reader;
        if (reader[0] == '%') {
            type[sender] = flip_flop;
        }
        else if (reader[0] == '&') {
            type[sender] = conjunct;
        }
        else if (reader[0] == 'b') {
            type[sender] = broadcaster;
            modules.insert(sender);
        }
        sin >> receiver;
        while (sin >> reader) {
            if (reader[reader.size() - 1] == ',') {
                receiver = reader.substr(0, reader.size() - 1);
            }
            else {
                receiver = reader;
            }
            nextUp[sender].pb(receiver);
            inputs[receiver].pb(sender);
            modules.insert(receiver);
        }
    }
}
bool conjunctSignal(string signal) {

    for (auto &input : inputs[signal]) {
        if (conjunc[signal][input] == LOW) {
            return HIGH;
        }
    }
    return LOW;
}
void Cyclying() {

    queue<node> q;
    q.push({ LOW,"broadcaster","tl" });
    while (!q.empty()) {
        bool signal = q.front().signal;
        string last = q.front().last;
        string current = q.front().cur;
        if (type[current] == conjunct) {
            conjunc[current][last] = signal;
            state[current] = conjunctSignal(current);
        }
        else if (type[current] == flip_flop) {
            state[current] = not(state[current]);
        }
        if (isOutput[current] && state[current] == LOW) {
            cout << "("<<state[current] << " " << global<<" "<<global-lastGlobal << ") ";
            lastGlobal = global;
        }
        q.pop();
        for (string& nextt : nextUp[current]) {
            if (component[current] != component[nextt]) {
                continue;
            }
            if (type[nextt] == flip_flop && state[current] == HIGH) {
                continue;
            }
            if (type[nextt] == output) {
                continue;
            }
            q.push({ state[current], current, nextt });
        }
    }//cout << endl;
}
void solve() {
    ll i = 0;
    for (; goalReached == false; i++) {
        global++;
        Cyclying();
        if (i % 50000 == 0) {
            cout << i << endl;
        }
    }
}
int main()
{
    readInput();
    vector<vector<int>> edges;
    GFG obj;
    int V = 0;
    int mods = 0;
    for (auto t : modules) {
        toInt[t] = ++mods;
        toString[mods] = t;
    }
    for (auto t : modules) {
        for (auto nx : nextUp[t]) {
            edges.pb({ toInt[t],toInt[nx]});
            V++;
        }
    }
    vector<vector<int> > ans = obj.findSCC(V, edges);
    cout << "Strongly Connected Components are:\n";
    int nr = 0;
    bool ok1;
    for (auto x : ans) {
        ok1 = false;
        int no = 0;
        for (auto y : x) {
            if (y > 59)break;
            ok1 = true;
            cout << toString[y] << " ";
            component[toString[y]] = nr+1;
            if (type[toString[y]] == conjunct) {
                for (auto el : inputs[toString[y]]) {
                    no++;
                }
            }
            else if (type[toString[y]] == flip_flop) {
                no++;
            }
        }
        if (ok1) {
            nr++;
            cout << ":  " << no;
            cout << endl;
        }
    }
    cout << "\noutputs for components:\n";
    for (auto el : modules) {
        for (auto inp : nextUp[el]) {
            if (component[inp] != component[el]) {
                isOutput[el] = true;
                isInput[inp] = true;
                nextComponent[component[el]].pb(component[inp]);
            }
        }
    }
    for (auto x : ans) {
        bool ok1 = false;
        for (auto y : x) {
            if (isOutput[toString[y]]) {
                cout << toString[y] << ' ';
                ok1 = true;
            }
        }
        if (ok1) {
            cout << endl;
        }
    }
    cout << "\n\ninputs for components:\n";
    for (auto x : ans) {
        bool ok1 = false;
        for (auto y : x) {
            if (isInput[toString[y]]) {
                cout << toString[y] << ' ';
                ok1 = true;
            }
        }
        if (ok1) {
            cout << endl;
        }
    }
    cout << "\nour new pathway:\n";
    for (int i = 1; i <= nr;i++) {
        cout << i << ": ";
        for (auto el : nextComponent[i]) {
            cout << el << ' ';
        }
        cout << endl;
    }
    //solve();
    // I observed that the first 4 strongly connected components output LOW values in cycles of 3907,3911,..
    cout << lcm(lcm(lcm(1LL,3907), 3931), lcm(3911, 4021));
    return 0;
}