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
const int N = 5e5 + 5;

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
int val[N];
int mn, mx;
const int L = 20;
class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po[L];
    int tin[N], tout[N], ti;

    void run(int src, ADJ &adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        dpth[src] = 0;
        ti = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ &adj) {
        up[u][0] = p;
        tin[u] = ++ti;
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            dpth[v] = dpth[u] + 1;
            dfs(v, u, adj);
        }
        tout[u] = ti;
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

    int getFirstHasSubtreeOn(int u) {
        if (val[u] == 1) {
            return u;
        }
        for (int i = L - 1; i >= 0; i--) {
            if (val[up[u][i]] == 0) {
                u = up[u][i];
            }
        }
        if (u == 0) {
            return -1;
        }
        u = up[u][0];
        return u;
    }
    bool valid(int u) { return tin[u] > mn || tout[u] < mx; }

    int getFirstHasCompSubtreeOn(int u) {
        if (!valid(u)) {
            return -1;
        }
        for (int i = L - 1; i >= 0; i--) {
            if (valid(up[u][i])) {
                u = up[u][i];
            }
        }
        assert(valid(u));
        u = up[u][0];
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
    bool isLCA(int u, int v) { return tin[u] <= tin[v] && tout[u] >= tout[v]; }
} LCA;

int n, q;
void init() {
    mn = 1e9;
    mx = -1;
    for (int i = 0; i < n; i++) {
        val[i] = 0;
    }
}
void apply(int u) {
    mn = min(mn, LCA.tin[u]);
    mx = max(mx, LCA.tin[u]);
    while (!val[u]) {
        val[u] = 1;
        if (u == 0) break;
        u = LCA.up[u][0];
    }
}
int u, v;

int solveLCA(int u, int lc) {
    int ans = 0;
    int x = LCA.getFirstHasSubtreeOn(u);
    if (x != -1 && !LCA.isLCA(lc, x)) {
        return 0;
    }
    int y = LCA.getFirstHasCompSubtreeOn(u);
    if(LCA.isLCA(y,lc)){
        y=lc;
    }
    if (x != -1 && y != -1) {
        ans = max(ans, LCA.dpth[x] - LCA.dpth[y]);
    }
    return ans;
}
void test_case() {
    cin >> n >> q;
    adj.init(n);
    init();
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    LCA.run(0, adj);
    int t;
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> u;
            --u;
            apply(u);
        } else {
            cin >> u >> v;
            --u, --v;
            int ans = 0;
            if (LCA.isLCA(v, u)) {
                swap(u, v);
            }
            if (LCA.isLCA(u, v)) {
                ans = max(ans, solveLCA(v, u));
            } else {
                int lc = LCA.getlca(u, v);
                ans = max(ans, solveLCA(v, lc));
                ans = max(ans, solveLCA(u, lc));
                int x = LCA.getFirstHasSubtreeOn(u);
                int y = LCA.getFirstHasSubtreeOn(v);
                if (x != -1 && y != -1 && LCA.isLCA(lc, x) && LCA.isLCA(lc, y) && x != lc && y != lc) {
                    ans = max(ans, LCA.dpth[x] + LCA.dpth[y] - 2 * LCA.dpth[lc]);
                }
            }
            cout << ans << endl;
        }
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
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
