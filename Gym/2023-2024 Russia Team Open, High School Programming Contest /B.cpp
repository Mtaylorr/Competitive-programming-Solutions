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

int n;
vector<int> adj[N];
int p;
int dpth[N];
int closest[N];
int isleaf[N];
vector<int> nodes;
int tin[N], tout[N];
int sz[N], bchd[N];
int ti = -1;
int dpdpth[N];
int dpnode[N];

void dfs(int u, int pa = -1) {
    tin[u] = ++ti;
    sz[u] = 1;
    closest[u] = 1e9;
    nodes.pb(u);
    pair<int, int> p = {-1, -1};
    for (auto v : adj[u]) {
        if (v == pa) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
        sz[u] += sz[v];
        p = max(p, mp(sz[v], v));
        closest[u] = min(closest[u], closest[v]);
    }
    bchd[u] = p.se;
    tout[u] = ti;
    if (p.se == -1) {
        isleaf[u] = 1;
        closest[u] = dpth[u];
    }
}

void solve(int u, int p = -1, bool keep = 1) {
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        solve(v, u, 0);
    }
    if (bchd[u] != -1) {
        solve(bchd[u], u, 1);
    }
    for (auto v : adj[u]) {
        if (v == p) continue;
        dpnode[u] = max(dpnode[u], dpnode[v]);
    }

    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            int nd = nodes[i];
            int d = dpth[nd];
            dpdpth[d] = max(dpdpth[d], dpnode[nd]);
        }
    }
    dpnode[u] = max(dpnode[u], 1 + dpdpth[closest[u]]);
    dpdpth[dpth[u]] = max(dpdpth[dpth[u]], dpnode[u]);
    if (!keep) {
        for (int i = tin[u]; i <= tout[u]; i++) {
            dpdpth[dpth[nodes[i]]] = 0;
        }
    }
}

void test_case() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        cin >> p;
        --p;
        adj[i].pb(p);
        adj[p].pb(i);
    }
    dfs(0);
    solve(0);
    cout << dpnode[0] - 1 << endl;
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
