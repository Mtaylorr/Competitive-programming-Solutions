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
const int E = 1e6 + 5;

vector<int> adj[N];
int n, q;
int a, b;

int dp[N];
int dpth[N];
int val[N];

void dfs(int u, int p = -1) {
    dp[u] = val[u];
    for (auto v : adj[u]) {
        if (v == p) continue;
        dpth[v] = dpth[u] + 1;
        dfs(v, u);
        dp[u] += dp[v];
    }
}

void test_case() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    while (q--) {
        int k, m;
        cin >> k >> m;
        vector<int> tmp;
        for (int i = 0; i < n; i++) {
            val[i] = 0;
        }
        for (int i = 0; i < m; i++) {
            int x;
            cin >> x;
            --x;
            val[x] = 1;
        }
        dpth[0] = 0;
        dfs(0);
        int mxdpth = -1;
        for (int i = 0; i < n; i++) {
            if (dp[i] >= k) {
                mxdpth = max(mxdpth, dpth[i]);
            }
        }
        int ans = 0;
        for (int i = 0; i < n; i++) {
            if (dp[i] >= k && mxdpth == dpth[i]) {
                ans++;
            }
        }
        cout << ans << endl;
    }
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
