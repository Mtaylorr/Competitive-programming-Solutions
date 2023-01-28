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

const int E = 2e5 + 5;

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

struct FenwickTree {
    vector<ll> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    ll mrg(ll &x, ll &y) { return x + y; }

    void upd(int x, ll v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    ll getprefix(int x) {
        if (x <= 0) return 0;
        ll rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    ll getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
} ft[N][2];

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    ll decompress(int p) { return values[p]; }
} compressor[N][2];

int n, m;
ll val[N];
int x[N], y[N], w[N];
const int L = 18;
int up[N][L];
int po[L];
int dpup[N][L];
int dpth[N];
int dpsz[N];
bool done[N];
int par[N];
int dist[N][22];
int ty;
ll X, V;
ll totsm = 0;

void dfs(int u, int p, int we) {
    up[u][0] = p;
    dpup[u][0] = we;
    for (int i = 1; i < L; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
        dpup[u][i] = max(dpup[u][i - 1], dpup[up[u][i - 1]][i - 1]);
    }
    neig(u, v, e, adj) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u, adj.cst[e]);
    }
}
int getMaxInPath(int u, int v) {
    if (dpth[u] < dpth[v]) {
        swap(u, v);
    }
    int l = dpth[u] - dpth[v];
    int ans = 0;
    for (int i = L - 1; i >= 0; i--) {
        if (po[i] <= l) {
            l -= po[i];
            ans = max(ans, dpup[u][i]);
            u = up[u][i];
        }
    }
    for (int i = L - 1; i >= 0; i--) {
        if (up[u][i] != up[v][i]) {
            ans = max(ans, dpup[u][i]);
            ans = max(ans, dpup[v][i]);
            u = up[u][i];
            v = up[v][i];
        }
    }
    if (u != v) {
        ans = max(ans, dpup[u][0]);
        ans = max(ans, dpup[v][0]);
    }
    return ans;
}

void calcsz(int u, int p = -1) {
    dpsz[u] = 1;
    neig(u, v, e, adj) {
        if (v == p || done[v]) continue;
        calcsz(v, u);
        dpsz[u] += dpsz[v];
    }
}

int getCentroid(int u, int p, int cursz) {
    neig(u, v, e, adj) {
        if (v == p || done[v]) continue;
        if (2 * dpsz[v] >= cursz) return getCentroid(v, u, cursz);
    }
    return u;
}

int buildCentroid(int u) {
    calcsz(u, -1);
    int cursz = dpsz[u];
    int src = getCentroid(u, -1, cursz);
    done[src] = 1;
    neig(src, v, e, adj) {
        if (done[v]) continue;
        int x = buildCentroid(v);
        par[x] = src;
    }
    return src;
}

void upd(int u, ll v) {
    totsm += v;
    int d = 0;
    int p = u;
    while (p != -1) {
        ft[p][0].upd(compressor[p][0].compress(dist[u][d]) + 1, v);
        d++;
        p = par[p];
    }
    p = u;
    d = 0;
    while (par[p] != -1) {
        ft[p][1].upd(compressor[p][1].compress(dist[u][d + 1]) + 1, v);
        d++;
        p = par[p];
    }
}

ll calc(int u, int ub) {
    ll sm = 0;
    int d = 0;
    int p = u;
    while (p != -1) {
        if (dist[u][d] <= ub) {
            int x = compressor[p][0].greatestSmallerThanOrEqual(ub);
            sm += ft[p][0].getprefix(x + 1);
        }
        d++;
        p = par[p];
    }

    p = u;
    d = 0;
    while (par[p] != -1) {
        if (dist[u][d + 1] <= ub) {
            int x = compressor[p][1].greatestSmallerThanOrEqual(ub);
            sm -= ft[p][1].getprefix(x + 1);
        }
        d++;
        p = par[p];
    }
    return sm;
}

ll query(int u, ll z) {
    if (totsm <= z) {
        return -1;
    }
    int l = 0;
    int r = 1e9 + 2;
    while (l < r) {
        int md = (l + r + 1) / 2;
        ll sm = calc(u, md);
        if (sm <= z) {
            l = md;
        } else {
            r = md - 1;
        }
    }
    return l;
}

void test_case() {
    for (int i = 0; i < L; i++) {
        po[i] = 1 << i;
    }
    cin >> n >> m;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        cin >> val[i];
    }
    vector<int> tmp;
    for (int i = 0; i < m; i++) {
        cin >> x[i] >> y[i] >> w[i];
        x[i]--, y[i]--;
        tmp.pb(i);
    }
    sort(all(tmp), [](int &a, int &b) { return w[a] < w[b]; });
    dsu.init(n);
    for (auto i : tmp) {
        if (dsu.sameSet(x[i], y[i])) {
            continue;
        }
        adj.addBiEdge(x[i], y[i], w[i]);
        dsu.uni(x[i], y[i]);
    }
    dfs(0, 0, 0);
    int src = buildCentroid(0);
    par[src] = -1;
    for (int i = 0; i < n; i++) {
        compressor[i][0].add(0);
        compressor[i][1].add(0);
        compressor[i][0].add((1e9) + 5);
        compressor[i][1].add((1e9) + 5);
    }
    for (int i = 0; i < n; i++) {
        dist[i][0] = 0;
        int p = par[i];
        int op = i;
        int d = 1;
        compressor[i][0].add(0);
        while (p != -1) {
            dist[i][d] = getMaxInPath(i, p);
            compressor[p][0].add(dist[i][d]);
            compressor[op][1].add(dist[i][d]);
            op = p;
            p = par[p];
            d++;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 2; j++) {
            compressor[i][j].run();
            ft[i][j].init(compressor[i][j].n + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        upd(i, val[i]);
    }

    int q;
    cin >> q;
    while (q--) {
        cin >> ty >> X >> V;
        if (ty == 1) {
            X--;
            upd(X, -val[X] + V);
            val[X] = V;
        } else {
            X--;
            cout << query(X, V) << "\n";
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
        test_case();
    }
    return 0;
}
