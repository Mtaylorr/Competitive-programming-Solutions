//https://codeforces.com/problemset/problem/715/C
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

int gcd(int a, int b, int& x, int& y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    int x1, y1;
    int d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

int n, M;
int po[N], invpo[N], inv10;
int val[N];
int dp[2][N];
int dpth[N];
int sze[N], bchld[N];
int tin[N], tout[N], timer = -1;
vector<int> nodes;
ll ans = 0;

void dfs(int u, int curpo = 1, int d = 0, int p = -1) {
    tin[u] = ++timer;
    nodes.pb(u);
    dpth[u] = d;
    int nxpo = (curpo * 1ll * 10) % M;
    sze[u] = 1;
    int mxsz = 0;
    int mxv = -1;
    neig(u, v, e, adj) {
        if (v == p) continue;
        val[v] = adj.cst[e];
        dp[1][v] = ((curpo *1ll* val[v]) % M + 0ll + dp[1][u]) % M;
        dp[0][v] = ((dp[0][u] * 1ll * 10) % M + 0ll + val[v]) % M;
        dfs(v, nxpo, d + 1, u);
        sze[u] += sze[v];
        if (sze[v] > mxsz) {
            mxsz = sze[v];
            mxv = v;
        }
    }
    tout[u] = timer;
    bchld[u] = mxv;
}
unordered_map<int, int> freq[2];
void calc(int nd, int u) {
    int k = dpth[u];
    int d = dpth[nd];
    int diff = d - k;
    int x = (dp[0][nd] + 0ll + M - (po[diff] * 1ll * dp[0][u]) % M) % M;
    int y = (2 * k - d >= 0) ? po[2 * k - d] : invpo[d - 2 * k];
    x = (x * 1ll * y) % M;
    x = (x + 0ll + M - dp[1][u]) % M;
    ans += freq[1][(M - x) % M];
    x = (dp[1][nd] + 0ll + M - dp[1][u]) % M;
    x = (x + 0ll + M - (po[k] * 1ll * dp[0][u]) % M) % M;
    x = (x * 1ll * invpo[2 * k]) % M;
    ans += freq[0][(M - x) % M];
}
void solve(int u, int p, bool keep) {
    neig(u, v, e, adj) {
        if (v == p || v == bchld[u]) continue;
        solve(v, u, 0);
    }
    if (bchld[u] != -1) {
        solve(bchld[u], u, 1);
    }
    calc(u, u);
    freq[0][(dp[0][u] * 1ll * invpo[dpth[u]]) % M]++;
    freq[1][dp[1][u]]++;
    neig(u, v, e, adj) {
        if (v == p || v == bchld[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            calc(nodes[i], u);
        }
        for (int i = tin[v]; i <= tout[v]; i++) {
            int nd = nodes[i];
            freq[0][(dp[0][nd] * 1ll * invpo[dpth[nd]]) % M]++;
            freq[1][dp[1][nd]]++;
        }
    }
    if (!keep) {
        freq[0].clear();
        freq[1].clear();
    }
}

void test_case() {
    cin >> n >> M;
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        adj.addBiEdge(u, v, w);
    }
    int a, b, g;
    g = gcd(10, M, a, b);
    inv10 = (a % M + M) % M;
    po[0] = invpo[0] = 1;
    for (int i = 1; i <= 2 * n; i++) {
        po[i] = (po[i - 1] * 1ll * 10) % M;
        invpo[i] = (invpo[i - 1] * 1ll * inv10) % M;
    }
    dfs(0);
    solve(0, -1, 1);
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
