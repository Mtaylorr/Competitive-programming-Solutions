//https://codeforces.com/contest/1822/problem/F
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

vector<int> adj[N];
int c, k, n;
int dp[N];
int dist[N];
ll ans = 0;

void dfs(int u, int d = 0, int p = -1) {
    dist[u] = d;
    dp[u] = 0;

    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, d + 1, u);
        dp[u] = max(dp[u], 1 + dp[v]);
    }
}

void solve(int u, int up, int p = -1) {
    ans = max(ans, max(up, dp[u]) * 1ll * k - dist[u] * 1ll * c);
    multiset<int> s;
    s.insert(-up);
    for (auto v : adj[u]) {
        if (v == p) continue;
        s.insert(-(1 + dp[v]));
    }
    for (auto v : adj[u]) {
        if (v == p) continue;
        s.erase(s.find(-(1 + dp[v])));
        int x = -(*s.begin());
        solve(v, x + 1, u);
        s.insert(-(1 + dp[v]));
    }
}

void test_case() {
    ans = 0;
    cin >> n >> k >> c;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
        dp[i] = 0;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    dfs(0);
    solve(0, 0);
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
