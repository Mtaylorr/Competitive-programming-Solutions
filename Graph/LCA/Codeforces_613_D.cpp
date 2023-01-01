//https://codeforces.com/problemset/problem/613/D

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
const int L = 17;

struct FenwickTree {
    vector<int> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    int mrg(int &x, int &y) { return x + y; }

    void upd(int x, int v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    int getprefix(int x) {
        if (x <= 0) return 0;
        int rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    int getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
} ft;
int n;
int q;
vector<int> adj[N];
int up[N][30];
int dpth[N];
int tin[N], tout[N], timer = 0;
int k;
int a[N];
bool inset[N];
int po[L];

void dfs(int u, int p) {
    tin[u] = ++timer;
    up[u][0] = p;
    for (int i = 1; i < L; i++) {
        up[u][i] = up[up[u][i - 1]][i - 1];
    }
    for (auto v : adj[u]) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
    }
    tout[u] = timer;
}

bool is_lca(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }

int get_lca(int u, int v) {
    if (is_lca(u, v)) return u;
    if (is_lca(v, u)) return v;
    for (int i = L - 1; i >= 0; i--) {
        if (!is_lca(up[u][i], v)) {
            u = up[u][i];
        }
    }
    return up[u][0];
}
int dp[N];
int ans = 0;
void calc(int u, int p = 0) {
    dp[u] = 0;
    int nb = 0;
    for (auto v : adj[u]) {
        if (v == p) continue;
        calc(v, u);
        nb += dp[v] > 0;
    }
    if (inset[u]) {
        ans += nb;
        dp[u] = 1;
    } else if (nb <= 1) {
        dp[u] = nb;
    } else {
        dp[u] = 0;
        ans++;
    }
}
set<int> s;

void solve() {
    for (int i = 0; i < L; i++) {
        po[i] = 1 << i;
    }
    cin >> n;
    ft.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        u--, v--;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0, 0);
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    cin >> q;

    while (q--) {
        cin >> k;
        for (int i = 0; i < k; i++) {
            cin >> a[i];
            a[i]--;
            inset[a[i]] = 1;
        }
        bool cond = true;
        for (int i = 0; i < k; i++) {
            if (a[i] != 0 && inset[up[a[i]][0]]) {
                cond = false;
            }
        }

        if (!cond) {
            for (int i = 0; i < k; i++) {
                inset[a[i]] = 0;
            }
            cout << -1 << "\n";
            continue;
        }
        s.clear();
        for (int i = 0; i < k; i++) {
            s.insert(a[i]);
        }
        sort(a, a + k, [](int x, int y) { return tin[x] < tin[y]; });
        if (k >= 2)
            for (int i = 0; i < k - 1; i++) {
                s.insert(get_lca(a[i], a[i + 1]));
            }
        s.insert(0);
        for (auto u : s) {
            ft.upd(tin[u], 1);
            adj[u].clear();
        }

        for (auto u : s) {
            if (u == 0) continue;
            int p = u;
            int cursm = ft.getrange(tin[p], tout[p]);
            for (int i = L - 1; i >= 0; i--) {
                int nexp = up[p][i];
                int sm = ft.getrange(tin[nexp], tout[nexp]);
                if (po[i] <= dpth[p] && sm == cursm) {
                    p = nexp;
                }
            }
            p = up[p][0];
            adj[p].pb(u);
        }

        ans = 0;
        calc(0, 0);
        cout << ans << endl;
        for (auto u : s) {
            inset[u] = 0;
            ft.upd(tin[u], -1);
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
        solve();
    }
    return 0;
}
