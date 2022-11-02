//https://codeforces.com/problemset/problem/592/D
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

int n, m;
vector<int> adj[N];
bool isscared[N];
int sz[N];
int dp[2][N];
int ans = 1e9;
int pans;

void dfs(int u, int p = -1) {
    int nb = 0;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        nb++;
        sz[u] += sz[v];
    }

    if (sz[u] == 0 || nb == 0) {
        dp[0][u] = dp[1][u] = 0;
    } else {
        int sm0 = 0;
        for (auto v : adj[u]) {
            if (v == p) continue;
            if (sz[v] == 0) continue;
            sm0 += 2 + dp[0][v];
        }
        dp[0][u] = sm0;
        dp[1][u] = 1e9;
        for (auto v : adj[u]) {
            if (v == p) continue;
            if (sz[v] == 0) continue;
            dp[1][u] = min(dp[1][u], sm0 - 1 - dp[0][v] + dp[1][v]);
        }
    }
    sz[u] += isscared[u];
}

void calc(int u, int p = -1, int s = 0, int dp0 = 0, int dp1 = 0) {
    if (s == 0) {
        int x = min(dp[0][u], dp[1][u]);
        if (x < ans) {
            ans = x;
            pans = u;
        } else if (x == ans) {
            pans = min(pans, u);
        }
    } else {
        int x = min(dp0 + dp[1][u], dp1 + dp[0][u]);
        if (x < ans) {
            ans = x;
            pans = u;
        } else if (x == ans) {
            pans = min(pans, u);
        }
    }
    s += sz[u];
    multiset<int> ss;
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (sz[v] == 0) continue;
        ss.insert(dp[1][v] + 1 - (2 + dp[0][v]));
    }
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (sz[v] == 0) continue;
        ss.erase(ss.find(dp[1][v] + 1 - (2 + dp[0][v])));
        int ns = s - sz[v];
        int ndp0 = dp0 + dp[0][u] - (2 + dp[0][v]) + 2;
        int ndp1 = dp1 + dp[0][u] - (2 + dp[0][v]) + 1;
        if (ss.size()) {
            ndp1 = min(ndp1, 1 + dp0 + dp[0][u] - 2 - dp[0][v] + (*ss.begin()));
        }
        if (ns == 0) {
            calc(v, u, 0, 0, 0);
        } else {
            calc(v, u, ns, ndp0, ndp1);
        }

        ss.insert(dp[1][v] + 1 - (2 + dp[0][v]));
    }
}

void solve() {
    cin >> n >> m;
    for (int i = 0; i < n - 1; i++) {
        int x, y;
        cin >> x >> y;
        x--, y--;
        adj[x].pb(y);
        adj[y].pb(x);
    }
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        isscared[--x] = 1;
    }
    dfs(0);
    calc(0);

    cout << pans + 1 << endl;
    cout << ans << endl;
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
