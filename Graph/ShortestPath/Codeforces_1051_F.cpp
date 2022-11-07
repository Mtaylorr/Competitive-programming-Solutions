//https://codeforces.com/contest/1051/problem/F
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
const int N = 1e5 + 5;

const int E = 3e5 + 5;
int u[N], v[N], d[N];
int n, m;

#define neig(u, e, v, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

struct ADJ {
    int head[E], to[E], nxt[E], edgcnt = 0;
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
    void init(int n) {
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

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

struct SPT {
    vector<int> spt[30];
    int po[30];
    vector<int> lg;
    int n;
    void init(vector<int> &v, vector<int> &dpth) {
        n = v.size();
        lg.assign(n + 1, 0);
        po[0] = 1;
        for (int i = 0; i < 30; i++) {
            spt[i].assign(n, 0);
            if (i > 0) po[i] = 2 * po[i - 1];
        }
        for (int i = 2; i <= n; i++) {
            lg[i] = 1 + lg[i / 2];
        }
        for (int i = 0; i < n; i++) {
            spt[0][i] = v[i];
        }
        for (int b = 1; po[b] <= n; b++) {
            for (int i = 0; i + po[b] <= n; i++) {
                spt[b][i] = min(mp(dpth[spt[b - 1][i]], spt[b - 1][i]),
                                mp(dpth[spt[b - 1][i + po[b - 1]]],
                                   spt[b - 1][i + po[b - 1]]))
                                .se;
            }
        }
    }
    int get(int l, int r, vector<int> &dpth) {
        int lg2 = lg[r - l + 1];
        int rs =
            min(mp(dpth[spt[lg2][l]], spt[lg2][l]),
                mp(dpth[spt[lg2][r - po[lg2] + 1]], spt[lg2][r - po[lg2] + 1]))
                .se;
        return rs;
    }
};

struct LCA {
    ADJ adj;
    vector<int> dpth;
    vector<int> ndtoid;
    vector<int> idtond;
    vector<ll> dist;
    SPT spt;
    vector<bool> vis;
    int n;
    void init(int n) {
        this->n = n;
        adj.init(n);
        dpth.assign(n, 0);
        dist.assign(n, 0);
        ndtoid.assign(n, 0);
        vis.assign(n, 0);
        idtond.clear();
    }

    void buildLCA() {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        spt.init(idtond, dpth);
    }

    void dfs(int u) {
        vis[u] = 1;
        ndtoid[u] = idtond.size();
        idtond.pb(u);
        neig(u, e, v, adj) {
            if (vis[v]) continue;
            dpth[v] = dpth[u] + 1;
            dist[v] = dist[u] + adj.cst[e];
            dfs(v);
            idtond.pb(u);
        }
    }

    ll getdist(int u, int v) {
        int lca =
            spt.get(min(ndtoid[u], ndtoid[v]), max(ndtoid[u], ndtoid[v]), dpth);
        return dist[u] + dist[v] - 2 * dist[lca];
    }

} lca;

bool isdeleted[N];
vector<int> compheads;
int headid[N];
int ishead[N];
ll dist[50][N];
bool vis[N];
void dijk(int u, int id) {
    for (int i = 0; i < n; i++) {
        dist[id][i] = 1e18;
        vis[i] = 0;
    }
    set<pair<ll, int> > pq;
    dist[id][u] = 0;
    pq.insert({0, u});
    pair<ll, int> p;
    while (!pq.empty()) {
        p = *pq.begin();
        pq.erase(pq.begin());
        if (vis[p.se]) continue;
        ll d = p.fi;
        u = p.se;
        vis[p.se] = 1;
        neig(u, e, v, adj) {
            if (vis[v]) continue;
            if (dist[id][v] > d + adj.cst[e]) {
                dist[id][v] = d + adj.cst[e];
                pq.insert({dist[id][v], v});
            }
        }
    }
}

void solve() {
    cin >> n >> m;
    adj.init(n);
    lca.init(n);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> d[i];
        u[i]--, v[i]--;
        adj.addBiEdge(u[i], v[i], d[i]);
    }
    bool cond = true;
    while (cond) {
        cond = false;
        dsu.init(n);
        for (int i = 0; i < m; i++) {
            if (isdeleted[i]) continue;
            if (dsu.sameSet(u[i], v[i])) {
                isdeleted[i] = 1;
                ishead[u[i]] = ishead[v[i]] = 1;
                cond = true;
            } else {
                dsu.uni(u[i], v[i]);
            }
        }
    }
    dsu.init(n);

    for (int i = 0; i < m; i++) {
        if (isdeleted[i]) continue;
        lca.adj.addBiEdge(u[i], v[i], d[i]);
    }
    lca.buildLCA();
    int c = 0;
    for (int i = 0; i < n; i++) {
        if (ishead[i]) {
            headid[i] = c++;
            dijk(i, headid[i]);
            compheads.pb(i);
        }
    }
    int q;
    cin >> q;
    while (q--) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        ll d = 1e18;
        d = min(d, lca.getdist(x, y));
        for (auto u : compheads) {
            d = min(d, dist[headid[u]][x] + dist[headid[u]][y]);
        }

        cout << d << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
