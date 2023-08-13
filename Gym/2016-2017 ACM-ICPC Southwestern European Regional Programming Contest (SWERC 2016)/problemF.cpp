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
FenwickTree<ll> ft;

int n;
int r[N], t[N];
vector<int> nodes;
vector<int> adj[N];
int tin[N], tout[N], ti = -1;
int bchd[N];
int sze[N];
ll ans[N];

void dfs(int u, int p = -1) {
    sze[u] = 1;
    int mxsz = 0;
    int mxv = -1;
    nodes.pb(u);
    tin[u] = ++ti;

    for (auto v : adj[u]) {
        dfs(v, u);
        sze[u] += sze[v];
        if (sze[v] >= mxsz) {
            mxsz = sze[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = ti;
}
void solve(int u, int p = -1, bool keep = 0) {
    for (auto v : adj[u]) {
        if (v == bchd[u]) continue;
        solve(v, u, 0);
    }

    if (bchd[u]!=-1) {
        solve(bchd[u], u, 1);
    }
    for (auto v : adj[u]) {
        if (v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            ft.upd(r[nodes[i]], t[nodes[i]]);
        }
    }

    ans[u] = ft.getprefix(r[u] - 1);
    ft.upd(r[u], t[u]);
    if (!keep) {
        for (int i = tin[u]; i <= tout[u]; i++) {
            ft.upd(r[nodes[i]], -t[nodes[i]]);
        }
    }
}

void test_case() {
    ft.init(1e5 + 5);
    int src = -1;
    cin >> n;
    for (int i = 0; i < n; i++) {
        int p;
        cin >> p >> r[i] >> t[i];
        if (p == -1) {
            src = i;
        } else {
            --p;
            adj[p].pb(i);
        }
    }
    dfs(src);
    solve(src);
    for (int i = 0; i < n; i++) {
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
