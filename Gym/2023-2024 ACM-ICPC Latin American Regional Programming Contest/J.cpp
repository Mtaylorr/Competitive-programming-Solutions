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

const int L = 18;
class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po[L];

    void run(int src, ADJ& adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        dpth[src] = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ& adj) {
        up[u][0] = p;
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            dpth[v] = dpth[u] + 1;
            dfs(v, u, adj);
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

class CentroidDecomposition {
   public:
    bool done[N];
    int dpsz[N];
    int par[N];
    void calcsz(int u, int p, ADJ& adj) {
        dpsz[u] = 1;
        neig(u, v, e, adj) {
            if (v == p || done[v]) continue;
            calcsz(v, u, adj);
            dpsz[u] += dpsz[v];
        }
    }

    int getCentroid(int u, int p, int cursz, ADJ& adj) {
        neig(u, v, e, adj) {
            if (v == p || done[v]) continue;
            if (2 * dpsz[v] >= cursz) return getCentroid(v, u, cursz, adj);
        }
        return u;
    }

    int buildCentroid(int u, ADJ& adj) {
        calcsz(u, -1, adj);
        int cursz = dpsz[u];
        int src = getCentroid(u, -1, cursz, adj);
        done[src] = 1;
        par[src] = -1;
        neig(src, v, e, adj) {
            if (done[v]) continue;
            int x = buildCentroid(v, adj);
            par[x] = src;
        }
        return src;
    }

    void run(ADJ& adj) {
        for (int i = 0; i < adj.n; i++) {
            done[i] = 0;
        }
        buildCentroid(0, adj);
    }
} CD;
int n;

pair<ll, int> mn[N];
int ans[N];

void upd(int u) {
    int orig = u;
    while (u != -1) {
        pair<ll, int> p = {LCA.getdist(orig, u), orig};
        mn[u] = min(mn[u], p);
        u = CD.par[u];
    }
}

int getAns(int u) {
    int orig = u;
    pair<ll, int> a = {1e9, 0};

    while (u != -1) {
        ll d = LCA.getdist(orig, u);
        pair<ll, int> p = mn[u];
        p.fi += d;
        a = min(a, p);
        u = CD.par[u];
    }
    return a.se;
}

void test_case() {
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    CD.run(adj);
    LCA.run(0, adj);
    for (int i = 0; i < n; i++) {
        mn[i] = {1e9, i};
    }
    ans[n - 1] = n - 1;
    for (int i = n - 2; i >= 0; i--) {
        upd(i + 1);
        ans[i] = getAns(i);
    }
    for (int i = 0; i < n; i++) {
        cout << ans[i] + 1 << " ";
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
