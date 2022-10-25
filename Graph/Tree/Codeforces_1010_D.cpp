//https://codeforces.com/problemset/problem/1010/D

// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
#define sz(x) ((int)(x).size())
#define all(x) (x).begin(), (x).end()
#define rall(x) (x).rbegin(), (x).rend()
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
typedef long long ll;
const int N = 1e6 + 5;

string op[N];
vector<int> adj[N];
int ans[N];
vector<int> leafs;
int val[N];

void dfs(int u) {
    for (auto v : adj[u]) {
        dfs(v);
    }
    if (op[u] == "NOT") {
        
        val[u] = !val[adj[u][0]];
    } else if (op[u] == "OR") {
        val[u] = (val[adj[u][0]] | (val[adj[u][1]]));
    } else if (op[u] == "XOR") {
        val[u] = val[adj[u][0]] ^ (val[adj[u][1]]);
    } else if (op[u] == "AND") {
        val[u] = val[adj[u][0]] & (val[adj[u][1]]);
    }
}
void assign(int u, int p) {
    ans[u] = p%2;
    for (auto v : adj[u]) {
        assign(v, p);
    }
}

void calcans(int u, int p = 0) {
    
    if (op[u] == "IN") {
        ans[u] = (val[u] + p+1) % 2;
    } else if (op[u] == "NOT") {
        calcans(adj[u][0], p + 1);
    } else if (op[u] == "OR") {
        int l = val[adj[u][0]];
        int r = val[adj[u][1]];
        if (l == 1) {
            assign(adj[u][1], (p + 1) % 2);
        } else {
            calcans(adj[u][1], (p));
        }
        if (r == 1) {
            assign(adj[u][0], (p + 1) % 2);
        } else {
            calcans(adj[u][0], (p));
        }
    } else if (op[u] == "XOR") {
        int l = val[adj[u][0]];
        int r = val[adj[u][1]];
        if (l == 1) {
            calcans(adj[u][1], p + 1);
        } else {
            calcans(adj[u][1], p);
        }
        if (r == 1) {
            calcans(adj[u][0], p + 1);
        } else {
            calcans(adj[u][0], p);
        }
    } else if (op[u] == "AND") {
        int l = val[adj[u][0]];
        int r = val[adj[u][1]];
        
        if (l == 1) {
            calcans(adj[u][1], p);
        } else {
            assign(adj[u][1], p);
        }
        if (r == 1) {
            calcans(adj[u][0], p);
        } else {
            assign(adj[u][0], p);
        }
    }
}

int n;
void solve() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> op[i];
        if (op[i] == "AND" || op[i] == "OR" || op[i] == "XOR") {
            int l, r;
            cin >> l >> r;
            adj[i].pb(l);
            adj[i].pb(r);
        } else if (op[i] == "NOT") {
            int l;
            cin >> l;
            adj[i].pb(l);
        } else {
            cin >> val[i];
            leafs.pb(i);
        }
    }
    dfs(1);
    calcans(1);
    for (auto u : leafs) {
        cout << ans[u];
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
