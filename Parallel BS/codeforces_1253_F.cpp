//https://codeforces.com/problemset/problem/1253/F

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

#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

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
class DSUWithRollBack {
   public:
    struct dsu_save {
        int u, rnku, v, rnkv;
        bool ex;
        dsu_save() {}

        dsu_save(int _u, int _rnku, int _v, int _rnkv, bool _ex) : u(_u), rnku(_rnku), v(_v), rnkv(_rnkv), ex(_ex) {}
    };
    vector<int> id, sz, rnk;
    stack<dsu_save> op;
    int comps;
    void init(int n) {
        comps = n;
        id.assign(n, 0);
        sz.assign(n, 0);
        rnk.assign(n, 0);
        while (!op.empty()) {
            op.pop();
        }
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    bool uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) {
            op.push(dsu_save(u, rnk[u], v, rnk[v], 0));
            return 0;
        }
        if (rnk[v] > rnk[u]) swap(v, u);
        op.push(dsu_save(u, rnk[u], v, rnk[v], 1));
        id[v] = u;
        sz[u] += sz[v];
        comps--;
        if (rnk[u] == rnk[v]) rnk[u]++;
        return 1;
    }

    void rollback() {
        if (op.empty()) {
            return;
        }
        dsu_save x = op.top();
        op.pop();
        if (x.ex == 0) {
            return;
        }
        comps++;
        id[x.u] = x.u;
        id[x.v] = x.v;
        rnk[x.u] = x.rnku;
        rnk[x.v] = x.rnkv;
        sz[x.u] -= sz[x.v];
    }
} dsu_rb;
bool vis[N];
ll dist[N];
int par[N];
int u[N], v[N], w[N];
int n, m, k, q;
int a[N], b[N];
ll ans[N];
vector<vector<ll>> edges;
void dijk1D() {
    set<pair<ll, int>> pq;
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
        dist[i] = 1e18;  //  can be changed to 1e9 in case of int
        par[i] = -1;
    }
    for (int i = 0; i < k; i++) {
        dist[i] = 0;
        pq.insert({0, i});
        par[i] = i;
    }

    pair<ll, int> p;
    while (!pq.empty()) {
        p = *pq.begin();
        pq.erase(pq.begin());
        int u = p.se;
        ll d = p.fi;
        if (vis[u]) continue;
        vis[u] = 1;
        neig(u, v, e, adj) {
            if (vis[v]) continue;
            ll nd = d + adj.cst[e];
            if (nd < dist[v]) {
                par[v] = par[u];
                dist[v] = nd;
                pq.insert({nd, v});
            }
        }
    }
}

void solve(int l, int r, int ql, int qr, vector<int> &queries, int &qid) {
    if (ql > qr) return;
    int md = (ql + qr) / 2;
    while (qid > md) {
        dsu_rb.rollback();
        qid--;
    }
    while (qid < md) {
        qid++;
        dsu_rb.uni(edges[qid][1], edges[qid][2]);
    }
    vector<int> left_queries, right_queries;
    for (auto &qu : queries) {
        if (dsu_rb.sameSet(a[qu], b[qu])) {
            ans[qu] = min(ans[qu], edges[md][0]);
            left_queries.pb(qu);
        } else {
            right_queries.pb(qu);
        }
    }
    queries.clear();
    solve(l, r, ql, md - 1, left_queries, qid);
    solve(l, r, md + 1, qr, right_queries, qid);
}

void test_case() {
    cin >> n >> m >> k >> q;
    adj.init(n);
    dsu_rb.init(k);
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        --u[i], --v[i];
        adj.addBiEdge(u[i], v[i], w[i]);
    }
    dijk1D();
    for (int i = 0; i < m; i++) {
        edges.push_back({dist[u[i]] + dist[v[i]] + w[i], par[u[i]], par[v[i]]});
    }
    sort(all(edges));
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        cin >> a[i] >> b[i];
        --a[i], --b[i];
        queries.pb(i);
        ans[i] = 1e18;
    }
    int qid = -1;
    solve(0, edges.size() - 1, 0, edges.size() - 1, queries, qid);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
