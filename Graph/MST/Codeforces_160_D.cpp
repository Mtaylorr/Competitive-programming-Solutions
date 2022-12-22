//https://codeforces.com/contest/160/problem/D
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
const int N = 3e5 + 5;

struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;

const int E = 1e6 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

struct ADJ {
    int head[E], to[E], nxt[E], edgcnt = 0, n;
    ll cst[E];

    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }

    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

pair<int, int> getpair(int x, int y) { return {min(x, y), max(x, y)}; }
struct Bridges {
    vector<int> visited;
    vector<int> tin, low;
    set<pair<int, int> > bridges;
    int vid;
    int timer;

    void is_bridge(int u, int v) { bridges.insert(getpair(u, v)); }

    void dfs(int u, ADJ &adj, int p = -1) {
        visited[u] = vid;
        tin[u] = low[u] = timer++;
        neig(u, v, e, adj) {
            if (e == (p ^ 1)) continue;
            if (visited[v] == vid) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, adj, e);
                low[u] = min(low[u], low[v]);
                if (low[v] > tin[u]) is_bridge(u, v);
            }
        }
    }

    void init(int n) {
        ++vid;
        bridges.clear();
        timer = 0;
        visited.assign(n, 0);
        tin.assign(n, -1);
        low.assign(n, -1);
    }

    void init(set<int> &s) {
        ++vid;
        bridges.clear();
        timer = 0;
        for (auto u : s) {
            tin[u] = -1;
            low[u] = -1;
        }
    }

    void find_bridges(set<int> &s, ADJ &adj) {
        init(s);
        for (auto i : s) {
            if (visited[i] != vid) dfs(i, adj);
        }
    }

    void find_bridges(ADJ &adj) {
        init(adj.n);
        for (int i = 0; i < adj.n; ++i) {
            if (visited[i] != vid) dfs(i, adj);
        }
    }
} bridges;

map<pair<int, int>, int> pos;
bool notin[N];
bool atleast[N];
bool isin[N];
bool prob[N];
bool an[N];
int a[N], b[N], w[N];
int n, m;
vector<int> edges[E];

void solve() {
    cin >> n >> m;
    adj.init(n);
    for (int i = 0; i < m; ++i) {
        cin >> a[i] >> b[i] >> w[i];
        --a[i], --b[i];
        pos[getpair(a[i], b[i])] = i;
        edges[w[i]].pb(i);
    }
    dsu.init(n);
    bridges.init(n);
    for (int i = 0; i <= 1e6; i++) {
        set<int> s;
        for (auto u : edges[i]) {
            s.insert(dsu.getid(a[u]));
            s.insert(dsu.getid(b[u]));
            if (dsu.sameSet(a[u], b[u])) {
                notin[u] = 1;
            }
        }
        for (auto u : s) {
            adj.head[u] = -1;
            adj.edgcnt = 0;
        }
        for (auto u : edges[i]) {
            if (!dsu.sameSet(a[u], b[u])) {
                atleast[u] = 1;
                adj.addBiEdge(dsu.getid(a[u]), dsu.getid(b[u]));
            }
        }
        bridges.find_bridges(s, adj);
        for (auto u : edges[i]) {
            int l = dsu.getid(a[u]);
            int r = dsu.getid(b[u]);
            if (!dsu.sameSet(a[u], b[u])) {
                if (bridges.bridges.count(getpair(l, r)) == 1) {
                    an[u] = 1;
                }
            }
        }
        for (auto u : edges[i]) {
            int l = dsu.getid(a[u]);
            int r = dsu.getid(b[u]);
            if (!dsu.sameSet(a[u], b[u])) {
                dsu.uni(a[u], b[u]);
            }
        }
    }

    for (int i = 0; i < m; i++) {
        if (atleast[i]) {
            if (!an[i]) {
                cout << "at least one\n";
            } else {
                cout << "any\n";
            }
        } else {
            cout << "none\n";
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}

