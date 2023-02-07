//https://codeforces.com/problemset/problem/891/C
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
const int N = 5e5 + 5;

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

int n, m;
int u[N], v[N], w[N];
vector<int> edges[N];
int it[N];
set<int> hasqueries[N];
vector<int> sorted[N];
bool ans[N];
int k;

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> w[i];
        u[i]--, v[i]--;
        sorted[w[i]].pb(i);
    }
    dsu_rb.init(n);
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        ans[i] = 1;
        it[i] = 0;
        cin >> k;
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            edges[i].pb(--x);
        }
        sort(all(edges[i]), [](int &x, int &y) { return w[x] < w[y]; });
        for (auto u : edges[i]) {
            hasqueries[w[u]].insert(i);
        }
    }

    for (int we = 1; we <= 5e5; we++) {

        for (auto i : hasqueries[we]) {
            int nb = 0;
            bool cond = true;

            while (it[i] < edges[i].size() && w[edges[i][it[i]]] == we) {
                int e = edges[i][it[i]];
                if (dsu_rb.sameSet(u[e], v[e])) {
                    ans[i] = 0;
                    it[i]++;
                    continue;
                }
                dsu_rb.uni(u[e], v[e]);
                nb++;
                it[i]++;
            }
            while (nb--) {
                dsu_rb.rollback();
            }
        }

        for (auto e : sorted[we]) {
            dsu_rb.uni(u[e], v[e]);
        }
    }
    for (int i = 0; i < q; i++) {
        if (ans[i]) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
        }
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
