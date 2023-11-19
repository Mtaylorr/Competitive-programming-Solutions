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
const int N = 1005 + 5;

const int MOD = 1e9 + 7;

int dp[1005][1005];
int sum[1005];
int n;
vector<int> adj[1005];
int sz[1005];
int tmp[1005];
ll tot = 0;
void dfs(int u, int p = -1) {
    dp[u][1] = 1;
    dp[u][0] = 1;
    sz[u] = 1;
    int mxchld = -1;
    int mxsz = 0;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
        if (sz[v] > mxsz) {
            mxsz = sz[v];
            mxchld = v;
        }
    }
    for (auto& v : adj[u]) {
        if (v == p) continue;
        memset(tmp, 0, sizeof(tmp));
        for (int i = 1; i <= sz[u]; i++) {
            for (int j = 1; j <= sz[v]; j++) {
                tmp[i + j] =
                    (tmp[i + j] + (dp[v][j] * 1ll * dp[u][i]) % MOD) % MOD;
            }
        }
        sz[u] += sz[v];
        for (int i = 1; i <= sz[u]; i++) {
            dp[u][i] = (dp[u][i] + tmp[i]) % MOD;
        }
    }
}

void test_case() {
    cin >> n;
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        adj[i].pb(p);
        adj[p].pb(i);
    }
    dfs(0);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j <= n; j++) {
            sum[j] = (sum[j] + dp[i][j]) % MOD;
        }
    }
    for (int i = 1; i <= n; i++) {
        cout << sum[i] << "\n";
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
