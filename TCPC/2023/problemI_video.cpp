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
const int MOD = 1e9 + 7;
const int L = N * 30;
int val[L], ndcnt = 0;
int lf[L], rg[L];
int addnode() {
    lf[ndcnt] = rg[ndcnt] = -1;
    val[ndcnt] = 0;
    return ndcnt++;
}

void init() {
    ndcnt = 0;
    addnode();
}

int query(int qs, int qe, int nd = 0, int ns = 0, int ne = 1e9 + 7) {
    if (nd == -1) return 0;
    if (qs > ne || qe < ns) return 0;
    if (ns >= qs && ne <= qe) return val[nd];
    int md = ns + (ne - ns) / 2;
    return max(query(qs, qe, lf[nd], ns, md),
               query(qs, qe, rg[nd], md + 1, ne));
}

int getval(int nd) {
    if (nd == -1) return 0;
    return val[nd];
}

int upd(int p, int v, int nd = 0, int ns = 0, int ne = 1e9 + 7) {
    if (nd == -1) nd = addnode();
    if (ns == ne) {
        val[nd] = max(val[nd], v);
        return nd;
    }
    int md = ns + (ne - ns) / 2;
    if (p <= md) {
        lf[nd] = upd(p, v, lf[nd], ns, md);
    } else {
        rg[nd] = upd(p, v, rg[nd], md + 1, ne);
    }
    val[nd] = max(getval(lf[nd]), getval(rg[nd]));
    return nd;
}

int n;
vector<int> adj[N];
int a[N], b[N];
int sz[N], bchd[N], tin[N], tout[N], ti = -1;
int sum[N];
bool isleaf[N];
vector<int> nodes;
int dp[N];
void dfs(int u, int p = -1) {
    tin[u] = ++ti;
    int mx = 0;
    int mxv = -1;
    nodes.pb(u);
    sz[u] = 1;
    isleaf[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        isleaf[u] = 0;
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > mx) {
            mx = sz[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = ti;
}

void solve(int u, int p = -1, bool keep = 0) {
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        solve(v, u, 0);
        sum[u] = (sum[u] + sum[v]) % MOD;
    }
    if (bchd[u] != -1) {
        solve(bchd[u], u, 1);
        sum[u] = (sum[u] + sum[bchd[u]]) % MOD;
    }
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            upd(a[nodes[i]], dp[nodes[i]]);
        }
    }
    if (isleaf[u]) {
        a[u] = b[u];
    } else {
        a[u] = (b[u] * 1ll * sum[u]) % MOD;
    }
    dp[u] = 1 + query(a[u] + 1, 1e9 + 7);
    upd(a[u], dp[u]);
    sum[u] = (sum[u] + dp[u]) % MOD;
    if (!keep) {
        init();
    }
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0);
    init();
    solve(0);
    for (int i = 0; i < n; i++) {
        cout << dp[i] << " ";
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
