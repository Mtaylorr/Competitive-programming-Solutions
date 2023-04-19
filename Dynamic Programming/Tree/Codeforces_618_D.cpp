//https://codeforces.com/contest/618/problem/D
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

int n, x, y;
int diag = 0;
int dp[2][N];
set<int> adj[N];

void solve(int u, int p = -1) {
    dp[0][u] = dp[1][u] = 0;
    vector<int> tmp;
    int sum = 0;
    for (auto v : adj[u]) {
        if (v == p) continue;
        solve(v, u);
        sum += dp[0][v];
        tmp.pb(1 + dp[1][v] - dp[0][v]);
    }
    sort(all(tmp));
    if (tmp.size() && tmp.back() > 0) {
        sum += tmp.back();
        tmp.pop_back();
    }
    dp[1][u] = sum;
    if (tmp.size() && tmp.back() > 0) {
        sum += tmp.back();
        tmp.pop_back();
    }
    dp[0][u] = sum;
}

bool vis[N];

set<int> rem;

void dfs(int u) {
    set<int> to_rem;
    vis[u] = 1;
    for (auto v : rem) {
        if (adj[u].count(v)) continue;
        to_rem.insert(v);
    }
    for (auto v : to_rem) {
        rem.erase(v);
    }
    for (auto v : to_rem) {
        dfs(v);
    }
}
void test_case() {
    cin >> n >> x >> y;
    if (n == 2) {
        cout << x << endl;
        return;
    } else if (n == 3) {
        cout << min(x + y, 2 * x) << endl;
        return;
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].insert(v);
        adj[v].insert(u);
    }
    solve(0);
    ll ans = dp[0][0] * 1ll * x + (n - 1 - dp[0][0]) * 1ll * y;
    int mxy = n;
    for (int i = 0; i < n; i++) {
        rem.insert(i);
    }
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        rem.erase(i);
        dfs(i);
        mxy--;
    }
    ans = min(ans, (mxy)*1ll * y + (n - 1 - mxy) * 1ll * x);
    cout << ans;
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
