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
const int M = 1e6;
int threshold = 2e5;

int n, q;
int c[N];
vector<int> adj[N];
int csum[N];
int dpth[N];
int g[N];
int par[N];
vector<int> nodes;
int ti = -1, tin[N], tout[N];
void dfs(int u, int p) {
    par[u] = p;
    csum[u] = csum[p] + c[u];
    nodes.pb(u);
    tin[u] = ++ti;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
    }
    g[u] = dpth[u] - 2 * csum[u];
    tout[u] = ti;
}
vector<int> freq[M];
int ans[N];

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
    for (int i = 0; i < n; i++) {
        freq[g[nodes[i]] + threshold].pb(i);
    }
    for (int i = 1; i <= n; i++) {
        int l = tin[i];
        int r = tout[i];
        int t = g[par[i]] + threshold;
        int lf = lower_bound(all(freq[t]), l) - freq[t].begin();
        int rg = upper_bound(all(freq[t]), r) - freq[t].begin();
        rg--;
        if (rg >= lf) {
            ans[i] = rg - lf + 1;
        }
    }
    while (q--) {
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
