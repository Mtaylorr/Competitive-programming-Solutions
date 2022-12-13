//https://www.hackerrank.com/contests/may-world-codesprint/challenges/travel-in-hackerland/problem
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
    vector<map<int, int> > freq;
    vector<int> sz;

    dsu_with_rollbacks() {}

    dsu_with_rollbacks(int n, vector<int> &T) {
        p.resize(n);
        rnk.resize(n);
        sz.resize(n);
        freq.resize(n);
        for (int i = 0; i < n; i++) {
            p[i] = i;
            rnk[i] = 0;
            freq[i][T[i]]++;
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

        for (auto x : freq[v]) {
            if (freq[u][x.fi] == 0) {
                sz[u]++;
            }
            freq[u][x.fi] += x.se;
        }

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
        for (auto z : freq[x.v]) {
            freq[x.u][z.fi] -= z.se;
            if (freq[x.u][z.fi] == 0) {
                sz[x.u]--;
            }
        }
    }
} dsu;

int n, m, q;
int xe[N], ye[N], ue[N], x[N], y[N], k[N], ans[N];
bool exec[N];
vector<int> ord;
vector<int> T;

void add_edge(int id, int ty) {
    if (ty == 1) {
        if (dsu.unite(xe[ord[id]], ye[ord[id]])) {
            exec[id] = 1;
        }
    } else {
        if (exec[id]) dsu.rollback();
    }
}

void rec(int low, int high, vector<int> &queries, int &e_idx) {
    if (queries.size() == 0) return;
    int md = low + (high - low) / 2;
    while (e_idx < md) {
        add_edge(++e_idx, +1);
    }
    while (e_idx > md) {
        add_edge(e_idx--, -1);
    }
    vector<int> left_queries, right_queries;
    for (auto u : queries) {
        int px = dsu.find_set(x[u]);
        int py = dsu.find_set(y[u]);
        if (px == py && dsu.sz[px] >= k[u]) {
            ans[u] = ue[ord[high]];
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
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        T.pb(x);
    }
    dsu = dsu_with_rollbacks(n, T);
    for (int i = 0; i < m; i++) {
        cin >> xe[i] >> ye[i] >> ue[i];
        ord.pb(i);
        --xe[i];
        --ye[i];
    }
    sort(all(ord), [](int &a, int &b) { return ue[a] < ue[b]; });
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        cin >> x[i] >> y[i] >> k[i];
        --x[i], --y[i];
        queries.pb(i);
        ans[i] = 2e9;
    }
    int e_idx = -1;
    rec(0, m - 1, queries, e_idx);
    for (int i = 0; i < q; i++) {
        if (ans[i] < 2e9) {
            cout << ans[i];
        } else {
            cout << -1;
        }
        cout << "\n";
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
