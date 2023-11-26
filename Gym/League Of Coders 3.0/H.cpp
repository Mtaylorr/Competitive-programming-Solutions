// Mtaylor
// dp n*m
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
const int N = 1e5 + 5;
const int E = 1e6 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E];

    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }

    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

int n, m;
ll dp[N][2][202];
ll sz[N];
ll ans = 0;
void dfs(int u, int p = -1) {
    sz[u] = 1;
    neig(u, v, e, adj) {
        if (v == p) continue;
        dfs(v, u);
        for (int i = 1; i <= m; i++) {
            for (int j = 0; j < 2; j++) {
                dp[u][j][i] += dp[v][j][i - 1];
            }
        }
        sz[u] += sz[v];
    }
    dp[u][0][0] = 1;
    dp[u][1][0] = sz[u] * sz[u];
}

void solve(int u, int p = -1) {
    ans += dp[u][1][m];
    neig(u, v, e, adj) {
        if (v == p) continue;
        for (int i = 1; i <= m - 1; i++) {
            int rem = m - i;
            ans += dp[v][0][i - 1] * (dp[u][1][rem] - dp[v][1][rem - 1]);
        }
        ll y = (n - sz[u]);
        ll x = dp[u][1][0] - 2 * sz[v] * (sz[u] - sz[v]) - dp[v][1][0] +
               2 * (n - sz[u]) * (sz[u] - sz[v]) + y * y;
        ;
        ans += dp[v][0][m - 1] * x;
    }
    neig(u, v, e, adj) {
        if (v == p) continue;
        solve(v, u);
    }
}

void test_case() {
    cin >> n >> m;
    m--;
    if (m == 0) {
        ll x = n;
        ll ans = n * n * n;
        cout << ans << endl;
        return;
    }
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    dfs(0);
    solve(0);
    cout << ans << endl;
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
