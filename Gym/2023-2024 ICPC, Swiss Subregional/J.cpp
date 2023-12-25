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

struct SCC {
    int n;
    vector<int> adj[N], radj[N], topSort, vis, scc, sccid, sccsz;
    int scccnt;
    int ans;
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            radj[i].clear();
        }
        vis.assign(n, 0);
        scc.assign(n, 0);
        topSort.clear();
        sccid.assign(n, -1);
        sccsz.assign(n, 0);
        ans = 0;
        scccnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].pb(v);
        radj[v].pb(u);
    }

    void dfsSort(int u) {
        if (vis[u]) return;
        vis[u] = 1;
        for (auto v : adj[u]) {
            dfsSort(v);
        }
        topSort.pb(u);
    }

    void rdfs(int u, int id) {
        if (vis[u]) return;
        vis[u] = 1;
        scc.pb(u);
        sccsz[id]++;
        sccid[u] = id;
        for (auto v : radj[u]) {
            rdfs(v, id);
        }
    }

    void topoSort() {
        vis.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfsSort(i);
        }
    }

    void getSCC() {
        topoSort();
        reverse(all(topSort));
        vis.assign(n, 0);
        for (auto u : topSort) {
            if (vis[u]) continue;
            scc.clear();
            rdfs(u, scccnt);
            scccnt++;
        }
    }
} scc;
int n, m, k, y;
int a[N], b[N], c[N];
ll dp[N];
bool inscc[N];
bool vis[N];
bool reach[N];
void dfscalc(int u) {
    if (vis[u]) return;
    vis[u] = 1;

    if (u == scc.sccid[y]) {
        dp[u] = 0;
        reach[u] = 1;
        if (scc.sccsz[u] >= 2) {
            dp[u] = 1e9;
        }
        return;
    }
    dp[u] = 0;
    neig(u, v, e, adj) {
        dfscalc(v);
        if (reach[v]) {
            dp[u] = max(dp[u], adj.cst[e] + dp[v]);
            reach[u] = 1;
        }
    }
     if (scc.sccsz[u] >= 2 && reach[u]) {
            dp[u] = 1e9;
        }
}

void test_case() {
    cin >> n >> m >> k >> y;
    scc.init(n);
    for(int i=0;i<n;i++){
        reach[i]=dp[i]=vis[i]=0;
    }
    for (int i = 0; i < m; i++) {
        int u, v, e;
        cin >> u >> v >> e;
        --u, --v;
        a[i] = u;
        b[i] = v;
        c[i] = e;
        scc.addEdge(u, v);
    }
    scc.getSCC();
    for (int i = 0; i < n; i++) {
        if (scc.sccsz[scc.sccid[i]] >= 2) {
            inscc[i] = 1;
        }
    }
    y--;
    adj.init(scc.scccnt);
    for (int i = 0; i < m; i++) {
        int ida = scc.sccid[a[i]];
        int idb = scc.sccid[b[i]];
        if (ida != idb) {
            adj.addEdge(ida, idb, c[i]);
        }
    }
    for (int i = 0; i < scc.scccnt; i++) {
        dfscalc(i);
        if (dp[i] >= k && reach[i]) {
            cout << "YES\n";
            return;
        }
    }
    cout << "NO\n";
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
