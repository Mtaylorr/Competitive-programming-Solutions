//https://atcoder.jp/contests/agc002/tasks/agc002_d
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

struct dsu_save {
    int v, rnkv, u, rnku;

    dsu_save() {}

    dsu_save(int _v, int _rnkv, int _u, int _rnku)
        : v(_v), rnkv(_rnkv), u(_u), rnku(_rnku) {}
};

struct dsu_with_rollbacks {
    vector<int> p, rnk;
    int comps;
    stack<dsu_save> op;
    vector<int> sz;

    dsu_with_rollbacks() {}

    dsu_with_rollbacks(int n) {
        p.resize(n);
        rnk.resize(n);
        sz.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rnk[i] = 0;
            sz[i] = 1;
        }
        comps = n;
    }

    int find_set(int v) { return (v == p[v]) ? v : find_set(p[v]); }

    bool unite(int v, int u) {
        v = find_set(v);
        u = find_set(u);
        if (v == u) return false;
        comps--;
        if (rnk[v] > rnk[u]) swap(v, u);
        op.push(dsu_save(v, rnk[v], u, rnk[u]));
        sz[u] += sz[v];
        p[v] = u;
        if (rnk[u] == rnk[v]) rnk[u]++;
        return true;
    }

    void rollback() {
        if (op.empty()) return;
        dsu_save x = op.top();
        op.pop();
        comps++;
        p[x.v] = x.v;
        rnk[x.v] = x.rnkv;
        p[x.u] = x.u;
        rnk[x.u] = x.rnku;
        sz[x.u] -= sz[x.v];
    }
} dsu;

int n, m, q;
int a[N], b[N];
int x[N], y[N], z[N];
int ans[N];
bool exec[N];

void add_edges(int id, int mul) {
    if (mul == 1) {
        exec[id] = dsu.unite(a[id], b[id]);
    } else {
        if (exec[id]) {
            dsu.rollback();
        }
    }
}

void rec(int low, int high, vector<int> &queries, int &e_idx) {
    if (queries.size() == 0) return;
    int md = low + (high - low) / 2;
    while (e_idx < md) {
        add_edges(++e_idx, 1);
    }
    while (e_idx > md) {
        add_edges(e_idx--, -1);
    }
    vector<int> left_queries, right_queries;
    for (auto u : queries) {
        int a = dsu.find_set(x[u]);
        int b = dsu.find_set(y[u]);
        int sz = dsu.sz[a] + dsu.sz[b];
        if (a == b) sz -= dsu.sz[a];
        if (sz >= z[u]) {
            ans[u] = high;
            left_queries.pb(u);
        } else {
            right_queries.pb(u);
        }
    }
    queries.clear();
    if (low == high) return;
    rec(low, md, left_queries, e_idx);
    rec(md + 1, high, right_queries, e_idx);
}

void solve() {
    cin >> n >> m;
    dsu = dsu_with_rollbacks(n);

    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        --a[i], --b[i];
    }
    cin >> q;
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        queries.pb(i);
        cin >> x[i] >> y[i] >> z[i];
        --x[i], --y[i];
        ans[i] = 1e9;
    }
    int e_idx = -1;
    rec(0, m - 1, queries, e_idx);
    for (int i = 0; i < q; i++) {
        if (ans[i] < 1e9) {
            cout << ans[i]+1 << "\n";
        } else {
            cout << -1 << "\n";
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
