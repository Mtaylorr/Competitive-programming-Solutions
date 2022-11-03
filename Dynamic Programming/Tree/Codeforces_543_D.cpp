//https://codeforces.com/problemset/problem/543/D
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
#define MODDtype int

const int MOD = 1e9 + 7;

MODDtype mul(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}

MODDtype add(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}

MODDtype sub(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}

MODDtype powe(MODDtype u, ll v, MODDtype mod = MOD) {
    MODDtype ans = 1;
    MODDtype acc = u;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

MODDtype inv(MODDtype u, MODDtype mod = MOD) { return powe(u, mod - 2, mod); }

int n;
vector<int> adj[N];
int x;
int dp[N];
int ans[N];

void dfs(int u, int p = -1) {
    int nb = 0;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        nb++;
    }
    dp[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dp[u] = mul(dp[u], add(dp[v], 1));
    }
}
void calc(int u, int dp1, int p = -1) {
    ans[u] = mul(dp1, dp[u]);
    int ndp1 = mul(dp1, dp[u]);
    if (ndp1 == 0) {
        int d = -1;
        int ndp2 = dp1;
        for (auto v : adj[u]) {
            if (v == p) continue;
            if (add(dp[v], 1) == 0) {
                d = v;
                break;
            }
        }
        for (auto v : adj[u]) {
            if (v == p || v == d) continue;
            ndp2 = mul(ndp2, add(dp[v], 1));
        }
        for (auto v : adj[u]) {
            if (v == d && v != p) {
                calc(v, add(ndp2, 1), u);
                break;
            }
        }
        for (auto v : adj[u]) {
            if (v != d && v != p) {
                calc(v, 1, u);
            }
        }
    } else {
        for (auto v : adj[u]) {
            if (v == p) continue;
            ndp1 = mul(ndp1, inv(add(dp[v], 1)));
            calc(v, add(ndp1, 1), u);
            ndp1 = mul(ndp1, add(dp[v], 1));
        }
    }
}

void solve() {
    cin >> n;
    for (int i = 1; i <= n - 1; i++) {
        cin >> x;
        x--;
        adj[x].pb(i);
        adj[i].pb(x);
    }
    dfs(0);
    calc(0, 1);

    for (int i = 0; i < n; i++) {
        cout << ans[i] << " ";
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
