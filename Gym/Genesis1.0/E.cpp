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

#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

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

const int L = 20;
class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po[L];
    int sz[N];
    ll dp[N];
    ll dist[N];

    void run(int src, ADJ &adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        dpth[src] = 0;
        dist[src] = 0;
        sz[src] = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ &adj) {
        up[u][0] = p;
        dp[u] = 0;
        sz[u] = 1;
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            dist[v] = dist[u] + adj.cst[e];
            dpth[v] = dpth[u] + 1;
            dfs(v, u, adj);
            dp[u] += (adj.cst[e]) * sz[v] + dp[v];
            sz[u] += sz[v];
        }
    }
    int getlca(int u, int v) {
        if (dpth[u] < dpth[v]) {
            swap(u, v);
        }
        int l = dpth[u] - dpth[v];
        for (int i = L - 1; i >= 0; i--) {
            if (po[i] <= l) {
                l -= po[i];
                u = up[u][i];
            }
        }
        for (int i = L - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        if (u != v) {
            u = up[u][0];
        }
        return u;
    }

    int getParent(int u) {
        int c = u;
        for (int i = L - 1; i >= 0; i--) {
            int p = up[u][i];

            if (2 * dist[p] > dist[c]) {
                u = up[u][i];
            }
        }
        return u;
    }

    int getkthpar(int u, int k) {
        for (int i = L - 1; i >= 0; i--) {
            if (k >= po[i]) {
                u = up[u][i];
                k -= po[i];
            }
        }
        return u;
    }
    int getkthonpath(int u, int v, int k) {
        int lc = getlca(u, v);
        int d = dpth[u] - dpth[lc];
        if (d >= k) return getkthpar(u, k);
        d = dpth[u] + dpth[v] - 2 * dpth[lc];
        return getkthpar(v, d - k);
    }

    int getdist(int u, int v) {
        int lc = getlca(u, v);
        return dpth[u] + dpth[v] - 2 * dpth[lc];
    }
} LCA;

ll dpsumup[N];
ll dpszup[N];
int par[N];
ll anssum[N];
ll anssz[N];

int n, s;

void solve(int u, int p = -1) {
    if (u != s) {
        anssum[u] = LCA.dp[u] + dpsumup[u] - dpsumup[par[u]] - dpszup[par[u]] * (LCA.dist[u] - LCA.dist[par[u]]);
        anssz[u] = n - dpszup[par[u]];
    }
    neig(u, v, e, adj) {
        if (v == p) continue;
        dpsumup[v] = LCA.dp[u] - LCA.dp[v] - adj.cst[e] * LCA.sz[v] + dpsumup[u] + adj.cst[e] * (n - LCA.sz[v]);
        dpszup[v] = n - LCA.sz[v];
        solve(v, u);
    }
}

void test_case() {
    cin >> n >> s;
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        u--, v--;
        adj.addBiEdge(u, v, d);
    }
    --s;
    LCA.run(s, adj);

    for (int i = 0; i < n; i++) {
        int x = LCA.getParent(i);
        par[i] = x;
    }
    solve(s);
    for (int i = 0; i < n; i++) {
        cout << anssz[i] << " " << anssum[i] << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
