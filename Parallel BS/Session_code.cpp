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
const int N = 3e5 + 5;

class DSUWithRollBack {
   public:
    struct dsu_save {
        int u, rnku, v, rnkv;
        bool ex;
        dsu_save() {}

        dsu_save(int _u, int _rnku, int _v, int _rnkv, bool _ex)
            : u(_u), rnku(_rnku), v(_v), rnkv(_rnkv), ex(_ex) {}
    };
    vector<int> id, sz, rnk;
    stack<dsu_save> op;
    vector<map<int, int> > freq;
    vector<int> distincts;
    int comps;
    void init(int n) {
        comps = n;
        id.assign(n, 0);
        sz.assign(n, 0);
        distincts.assign(n, 0);
        rnk.assign(n, 0);
        freq.resize(n);
        while (!op.empty()) {
            op.pop();
        }
        for (int i = 0; i < n; i++) {
            freq[i].clear();
            distincts[i] = 1;
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
        for (auto x : freq[v]) {
            distincts[u] += (freq[u][x.fi] == 0 && x.se >= 1);
            freq[u][x.fi] += x.se;
        }
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
        for (auto y : freq[x.v]) {
            freq[x.u][y.fi] -= y.se;
            distincts[x.u] -= (freq[x.u][y.fi] == 0 && y.se >= 1);
        }
    }
} dsu_rb;

int n, m, q;
vector<int> soed;
int u[N], v[N], w[N];
int x[N], y[N], k[N];
int ans[N];
int t[N];

void upd(int x, int c) {
    if (c == 1) {
        dsu_rb.uni(u[soed[x]], v[soed[x]]);
    } else {
        dsu_rb.rollback();
    }
}

void rec(int l, int r, vector<int> queries, int &it) {
    if (queries.size() == 0) return;
    int md = l + (r - l) / 2;
    vector<int> left_queries, right_queries;
    while (it < md) {
        upd(++it, 1);
    }
    while (it > md) {
        upd(it--, -1);
    }
    for (auto q : queries) {
        int a = dsu_rb.getid(x[q]);
        int b = dsu_rb.getid(y[q]);
        int c = k[q];

        if (a == b && dsu_rb.distincts[a] >= c) {
            ans[q] = w[soed[md]];
            left_queries.pb(q);
        } else {
            right_queries.pb(q);
        }
    }
    queries.clear();
    if (l == r) {
        return;
    }
    rec(l, md, left_queries, it);
    rec(md + 1, r, right_queries, it);
}

void test_case() {
    cin >> n >> m >> q;
    for (int i = 0; i < n; i++) {
        cin >> t[i];
    }
    dsu_rb.init(n);
    for (int i = 0; i < n; i++) {
        dsu_rb.freq[i][t[i]]++;
    }

    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        u[i]--, v[i]--;
        soed.pb(i);
    }
    sort(all(soed), [](int &x, int &y) { return w[x] < w[y]; });
    for (int i = 0; i < q; i++) {
        cin >> x[i] >> y[i] >> k[i];
        x[i]--;
        y[i]--;
        ans[i] = 2e9;
    }
    vector<int> queries;
    for (int i = 0; i < q; i++) {
        queries.pb(i);
    }
    int it = -1;

    rec(0, m - 1, queries, it);
    for (int i = 0; i < q; i++) {
        if (ans[i] < 2e9)
            cout << ans[i] << "\n";
        else
            cout << -1 << "\n";
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
        test_case();
    }
    return 0;
}
