// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
#define endl '\n';
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

int n, q;
int c[N];
vector<int> adj[N];
int csum[N];
int par[N];
int sz[N];
int bchld[N];
int dpth[N];
int g[N];
vector<int> nodes;
int ti = -1, tin[N], tout[N];
void dfs(int u, int p) {
    csum[u] = csum[p] + c[u];
    int mxv = -1, mxsz = 0;
    sz[u] = 1;
    nodes.pb(u);
    tin[u] = ++ti;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
        sz[v] += sz[u];
        if (sz[v] > mxsz) {
            mxsz = sz[v];
            mxv = v;
        }
    }
    g[u] = dpth[u] - 2 * csum[u];
    tout[u] = ti;
    bchld[u] = mxv;
}
map<int, int> freq;
int ans[N];
void solve(int u, int p, bool keep = 0) {
    if (u == -1) return;
    for (auto v : adj[u]) {
        if (v == p || v == bchld[u]) continue;
        solve(v, u, 0);
    }
    solve(bchld[u], u, 1);
    freq[g[u]]++;
    for (auto v : adj[u]) {
        if (v == p || v == bchld[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            freq[g[nodes[i]]]++;
        }
    }
    ans[u] = freq[g[p]];
    if (!keep) freq.clear();
}

void test_case() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dpth[1] = 1;
    dfs(1, 0);
    solve(1, 0, 0);
    while(q--){
        int u;
        cin >> u;
        cout << ans[u] << endl;
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
