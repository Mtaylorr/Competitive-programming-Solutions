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

int n, a, b;
vector<pair<int, int>> adj[N];
int rs, ans;
int id[N];
int par[N];
int dpth[N];
void dfs(int u, int p = -1) {
    for (auto &v : adj[u]) {
        if (v.fi == p) continue;
        par[v.fi] = u;
        dpth[v.fi] = dpth[u] + 1;
        dfs(v.fi, u);
    }
}

void dfs2(int u, int p = -1) {
    for (auto &v : adj[u]) {
        if (v.fi == p) continue;
        id[v.fi] = v.se + 1;
        dfs2(v.fi, u);
    }
}

int dp[N];

void calcans(int u, int p = -1) {
    dp[u] = 0;
    for (auto &v : adj[u]) {
        if (v.fi == p) continue;
        calcans(v.fi, u);
        // dbg(u + 1, v.fi + 1, id[u] - 1, v.se);
        dp[u] = max(dp[u], (id[u] - 1 != v.se) + dp[v.fi]);
    }
    //dbg(u, dp[u]);
}
void test_case() {
    cin >> n;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        --a, --b;
        adj[a].pb({b, i});
        adj[b].pb({a, i});
    }

    int src = 0;
    dfs(0, -1);
    int mxdpth = 0;
    for (int i = 0; i < n; i++) {
        if (dpth[i] > mxdpth) {
            mxdpth = dpth[i];
            src = i;
        }
    }
    dpth[src] = 0;
    dfs(src, -1);
    int snk = 0;
    mxdpth = 0;
    for (int i = 0; i < n; i++) {
        if (dpth[i] > mxdpth) {
            mxdpth = dpth[i];
            snk = i;
        }
    }
    int d = mxdpth / 2;
    memset(id, -1, sizeof(id));
    while (d--) {
        snk = par[snk];
    }
    dfs2(snk, -1);
    if (mxdpth % 2 == 1) {
        int f = par[snk];
        for (auto &v : adj[snk]) {
            if (v.fi == f) {
                id[snk] = v.se + 1;
            }
        }
    }
    ans = 0;
    dpth[snk] = 0;
    calcans(snk, -1);
    cout << dp[snk] << endl;
    for (int i = 0; i < n; i++) {
        cout << id[i] << " ";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
