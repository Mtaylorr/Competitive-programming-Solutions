//https://codeforces.com/contest/1479/problem/D
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }

const int MAXRT = N * 100;
ll vals[MAXRT];
int lch[MAXRT], rch[MAXRT], ndcnt = 0;

int addnode() {
    lch[ndcnt] = rch[ndcnt] = -1;
    return ndcnt++;
}

void pull_up(int &id) { vals[id] = vals[lch[id]] ^ vals[rch[id]]; }

int build(int l, int r) {
    if (l == r) {
        return addnode();
    }
    int idx = addnode();
    int md = l + (r - l) / 2;
    lch[idx] = build(l, md);
    rch[idx] = build(md + 1, r);
    pull_up(idx);
    return idx;
}

int upd(int cur, int p, int l, int r, ll &v) {
    if (l == r) {
        int idx = addnode();
        if (vals[cur] == 0) {
            vals[idx] = v;
        } else {
            vals[idx] = 0;
        }
        return idx;
    }
    int md = l + (r - l) / 2;
    int idx = addnode();
    if (p <= md) {
        lch[idx] = upd(lch[cur], p, l, md, v);
        rch[idx] = rch[cur];
    } else {
        lch[idx] = lch[cur];
        rch[idx] = upd(rch[cur], p, md + 1, r, v);
    }
    pull_up(idx);
    return idx;
}

int query(int nl, int nr, int qs, int qe, int l, int r) {
    if (qs > r || qe < l) return -1;
    if (qs <= l && qe >= r) {
        if (vals[nl] == vals[nr]) {
            return -1;
        }
    }
    if (l == r) {
        return l;
    }
    int md = l + (r - l) / 2;
    int x = query(lch[nl], lch[nr], qs, qe, l, md);
    if (x == -1) {
        return query(rch[nl], rch[nr], qs, qe, md + 1, r);
    }
    return x;
}

int n, q, a[N], tin[N], tout[N];
ll H1[N];
vector<int> path;
int ti = 0;

const int E = 1e6 + 5;

#define neig(u, v, e, g) \
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
};

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
        neig(u, v, e, adj) {
            if (vis[v]) continue;
            dpth[v] = dpth[u] + 1;
            dist[v] = dist[u] + adj.cst[e];
            dfs(v);
            idtond.pb(u);
        }
    }

    int getlca(int u, int v) {
        return spt.get(min(ndtoid[u], ndtoid[v]), max(ndtoid[u], ndtoid[v]),
                       dpth);
    }

    ll getdist(int u, int v) {
        int lca = getlca(u, v);
        return dist[u] + dist[v] - 2 * dist[lca];
    }

} lca;

bool isancestor(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

void dfs(int u, int p = -1) {
    tin[u] = ti++;
    path.pb(u);
    neig(u, v, e, lca.adj) {
        if (v == p) continue;
        dfs(v, u);
    }
    tout[u] = ti++;
    path.pb(u);
}
int u, v, l, r;

void solve() {
    scanf("%d%d", &n, &q);
    lca.init(n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &a[i]);
    }
    for (int i = 1; i <= n; i++) {
        do {
            H1[i] = myRand(1ll << 60);
        } while (H1[i] == 0);
    }
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        scanf("%d%d", &x, &y);
        --x, --y;
        lca.adj.addBiEdge(x, y);
    }
    lca.buildLCA();

    dfs(0);

    vector<int> nodes;
    nodes.pb(build(1, n));
    for (auto u : path) {
        int v = a[u];
        nodes.pb(upd(nodes.back(), v, 1, n, H1[v]));
    }

    while (q--) {
        scanf("%d%d%d%d", &u, &v, &l, &r);
        u--, v--;
        if (tin[u] > tin[v]) swap(u, v);
        int w = -1;
        if (isancestor(u, v)) {
            u = tin[u];
            v = tin[v];
        } else {
            w = lca.getlca(u, v);
            u = tout[u];
            v = tin[v];
        }
        if (w != -1) nodes[v + 1] = upd(nodes[v + 1], a[w], 1, n, H1[a[w]]);
        int nl = nodes[v + 1];
        int nr = nodes[u];
        int x = query(nl, nr, l, r, 1, n);
        printf("%d\n",x);
        if (w != -1) nodes[v + 1] = upd(nodes[v + 1], a[w], 1, n, H1[a[w]]);
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    // ios::sync_with_stdio(0);
    // cin.tie(0);
    // cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
