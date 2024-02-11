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
const int N = 2e5 + 5;
const int Q = 1e6 + 5;

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

template <typename T>
class FenwickTree {
   public:
    vector<T> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    T mrg(T &x, T &y) { return x + y; }

    void upd(int x, T v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    T getprefix(int x) {
        if (x <= 0) return 0;
        T rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    T getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
};
FenwickTree<int> ft;

int n, q;
int x[Q], k[Q];
vector<int> qu[N];
ll ans[Q];
int dpth[N];
int sz[N], tin[N], tout[N], ti = -1, bchd[N];
vector<int> nodes;
void dfs(int u, int p = -1) {
    nodes.pb(u);
    sz[u] = 1;
    tin[u] = ++ti;
    int bsz = 0;
    int bv = -1;
    neig(u, v, e, adj) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
        if (sz[v] > bsz) {
            bsz = sz[v];
            bv = v;
        }
        sz[u]+=sz[v];
    }
    bchd[u] = bv;
    tout[u] = ti;
}

void solve(int u, int p = -1, bool keep = 1) {
    neig(u, v, e, adj) {
        if (v == p || v == bchd[u]) continue;
        solve(v, u, 0);
    }
    if (bchd[u] != -1) {
        solve(bchd[u], u, 1);
    }
    for (auto &id : qu[u]) {
        ans[id] += ft.getrange(dpth[u] + k[id], 2 * n);
    }
    ft.upd(dpth[u], 1);
    neig(u, v, e, adj) {
        if (v == p || v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            int nd = nodes[i];
            for (auto &id : qu[u]) {
                int lb = max(0, k[id] - (dpth[nd] - dpth[u]));
                ans[id] += ft.getrange(dpth[u] + lb, 2 * n);
            }
        }
        for (int i = tin[v]; i <= tout[v]; i++) {
            int nd = nodes[i];
            ft.upd(dpth[nd], 1);
        }
    }
    if (!keep) {
        for (int i = tin[u]; i <= tout[u]; i++) {
            int nd = nodes[i];
            ft.upd(dpth[nd], -1);
        }
    }
}

void test_case() {
    cin >> n >> q;
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    ft.init(2 * n);
    dpth[0] = 1;
    for (int i = 0; i < q; i++) {
        cin >> x[i] >> k[i];
        x[i]--;
        qu[x[i]].pb(i);
    }

    dfs(0);
    solve(0);
    for (int i = 0; i < q; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
