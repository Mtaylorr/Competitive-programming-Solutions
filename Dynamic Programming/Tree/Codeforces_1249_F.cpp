//https://codeforces.com/problemset/problem/1249/F
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

int n, k;
int a[N];
vector<int> adj[N];
int dp[205][205];
void solve(int u, int p = -1) {
    int tmp[205];
    dp[u][0] = a[u];
    for (auto v : adj[u]) {
        if (v == p) continue;
        for (int i = 0; i <= n; i++) {
            tmp[i] = dp[u][i];
        }
        solve(v, u);
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= n; j++) {
                if (i + j > k) {
                    int x = min(i, j);
                    tmp[x] = max(tmp[x], dp[u][j] + dp[v][i - 1]);
                }
            }
        }
        for (int i = n; i >= 0; i--) {
            dp[u][i] = max(tmp[i], dp[u][i]);
            dp[u][i] = max(dp[u][i], dp[u][i+1]);
        }
    }
}

void test_case() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    solve(0);
    int ans = 0;
    for (int i = 0; i <= n; i++) {
        ans = max(ans, dp[0][i]);
    }
    cout << ans << "\n";
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
        test_case();
    }
    return 0;
}
