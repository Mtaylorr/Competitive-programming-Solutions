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

const int E = 1e6 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
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
    set<int> apoints;
    int vid = 0;
    int timer;

    void is_bridge(int u, int v) { bridges.insert(getpair(u, v)); }
    void is_ap(int u) { apoints.insert(u); }

    void dfs(int u, ADJ &adj, int p = -1) {
        visited[u] = vid;
        tin[u] = low[u] = timer++;
        int children = 0;
        neig(u, v, e, adj) {
            if (e == (p ^ 1)) continue;
            if (visited[v] == vid) {
                low[u] = min(low[u], tin[v]);
            } else {
                dfs(v, adj, e);
                low[u] = min(low[u], low[v]);
                if (low[v] >= tin[u] && p != -1) is_ap(u);
                ++children;
            }
        }
        if (p == -1 && children > 1) {
            is_ap(u);
        }
    }

    void init(int n) {
        ++vid;
        bridges.clear();
        apoints.clear();
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

int n, l;
int k[N];
void test_case() {
    cin >> n >> l;
    adj.init(n + l);
    for (int i = 0; i < l; i++) {
        cin >> k[i];
        for (int j = 0; j < k[i]; j++) {
            int x;
            cin >> x;
            --x;
            adj.addBiEdge(i + n, x);
        }
    }
    bridges.find_bridges(adj);
    int nb = 0;
    for (int i = 0; i < l; i++) {
        if (bridges.apoints.count(i + n)) nb++;
    }
    cout << nb << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
