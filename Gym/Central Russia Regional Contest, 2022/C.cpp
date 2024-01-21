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
const int L = 20;
class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    ll sum[N];
    int po[L];

    void run(int src, ADJ &adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        for(int i=0;i<adj.n;i++){
            sum[i]=1;
        }
        dpth[src] = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ &adj) {
        up[u][0] = p;

        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            dpth[v] = dpth[u] + 1;
            sum[v] = (sum[u] * 1ll * adj.cst[e]) % MOD;
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

    ll getWeighteddist(int u, int v) {
        int lc = getlca(u, v);
        ll ans = (sum[u] * 1ll * sum[v]) % MOD;
        ll rans = inv(sum[lc]);
        rans = (rans * rans) % MOD;
        return (ans * rans) % MOD;
    }
} LCA;

int n;
int q, u, v;
void test_case() {
    ll ans = 0;
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v, w;
        cin >> u >> v >> w;
        --u, --v;
        adj.addBiEdge(u, v, w);
    }
    LCA.run(0, adj);
    cin >> q;
    while (q--) {
        cin >> u >> v;
        --u, --v;
        cout << LCA.getWeighteddist(u, v) % MOD << endl;
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
