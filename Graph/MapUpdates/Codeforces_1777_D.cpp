//https://codeforces.com/contest/1777/problem/D

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
const int MOD = 1e9 + 7;
template <typename T, typename U>
int mul(T u, U v, int mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}
template <typename T, typename U>
int add(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}
template <typename T, typename U>
int sub(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}
template <typename T>
int powe(T u, ll v, int mod = MOD) {
    int ans = 1;
    int acc = u % mod;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}
template <typename T>
int inv(T u, int mod = MOD) {
    return powe(u, mod - 2, mod);
}

int n;
int u, v;
int dpth[N];
int bchd[N];
int dp[N];
int po[N];
int tin[N], tout[N], timer;
vector<int> ve;
vector<int> adj[N];
ll cusum;
ll ans;
ll sum[N];

void dfs(int u, int p = -1) {
    tin[u] = ++timer;
    ve.pb(u);
    dp[u] = 1;
    int mxv = -1;
    int mx = 0;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
        dp[u] += dp[v];
        if (dp[v] > mx) {
            mx = dp[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = timer;
}

void solve(int u, int p = -1, bool keep = 0) {
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) {
            continue;
        }
        solve(v, u, 0);
    }
    if (bchd[u] != -1) {
        solve(bchd[u], u, 1);
    }
    for (auto v : adj[u]) {
        if (v == p || v == bchd[u]) {
            continue;
        }
        for (int i = tin[v]; i <= tout[v]; i++) {
            int x = ve[i];
            int d = dpth[x];
            sum[d]++;
            if (sum[d] == 1) {
                cusum = (cusum + 1) % MOD;
            }
        }
    }
    sum[dpth[u]]++;
    cusum = (cusum + 1) % MOD;
    ans = add(ans, cusum);
    if (!keep) {
        cusum = 0;
        for (int i = tin[u]; i <= tout[u]; i++) {
            int x = ve[i];
            sum[dpth[x]] = 0;
        }
    }
}

void test_case() {
    cin >> n;
    ve.clear();
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    po[0] = 1;
    for (int i = 0; i <= n; i++) {
        sum[i] = 0;
        if (i > 0) {
            po[i] = mul(po[i - 1], 2);
        }
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    timer = -1;
    dpth[0] = 0;
    ans = 0;
    dfs(0);
    cusum = 0;
    solve(0);
    ans=mul(ans, po[n-1]);
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
