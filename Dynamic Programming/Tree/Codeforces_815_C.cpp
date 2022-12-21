//https://codeforces.com/problemset/problem/815/C
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
const int N = 5e3 + 5;

int n, b;
int c[N], d[N];
vector<int> adj[N];
ll dp[2][N][N];
int id[N];
int sz[N];
ll tmp[2][N];

void mrg(int u, int v) {
    if (sz[id[u]] < sz[id[v]]) {
        swap(id[u], id[v]);
    }

    sz[id[u]] += sz[id[v]];
    for (int i = 0; i <= n; i++) {
        tmp[0][i] = 1e15;
        tmp[1][i] = 1e15;
        for (int k = 0; k <= min(i, sz[id[v]]); k++) {
            tmp[0][i] = min(tmp[0][i], dp[0][id[u]][i - k] + dp[0][id[v]][k]);
            tmp[1][i] = min(tmp[1][i], dp[1][id[u]][i - k] + dp[1][id[v]][k]);
        }
    }
    for (int i = 0; i <= n; i++) {
        dp[0][id[u]][i] = tmp[0][i];
        dp[1][id[u]][i] = tmp[1][i];
    }
}

void dfs(int u) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][u][j] = 1e15;
        }
    }
    dp[0][u][0] = 0;
    dp[0][u][1] = c[u];
    dp[1][u][1] = c[u] - d[u];

    for (auto v : adj[u]) {
        dfs(v);
        mrg(u, v);
    }

    for (int i = 0; i <= n; i++) {
        dp[1][id[u]][i] = min(dp[1][id[u]][i], dp[0][id[u]][i]);
    }
}

void solve() {
    cin >> n >> b;
    ll sm = 0;
    for (int i = 0; i < n; i++) {
        cin >> c[i] >> d[i];
        if (i > 0) {
            int x;
            cin >> x;
            x--;
            adj[x].pb(i);
        }
        id[i] = i;
        sz[i] = 1;
    }
    dfs(0);
    int mx = 0;
    for (int i = 0; i <= n; i++) {
        if (dp[1][id[0]][i] <= b) {
            mx = i;
        }
    }
    cout << mx;
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
