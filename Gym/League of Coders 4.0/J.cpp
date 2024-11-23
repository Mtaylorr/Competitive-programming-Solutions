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
const int N = 1e5 + 5;
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
} adj, adj1;

int modular_inverse(int a, int m) {
    int m0 = m, t, q;
    int x0 = 0, x1 = 1;

    if (m == 1) return 0;  // Modular inverse doesn't exist if modulus is 1

    while (a > 1) {
        // q is quotient
        q = a / m;
        t = m;

        // m is remainder now, process the same as Euclid's algorithm
        m = a % m, a = t;
        t = x0;

        // Update x0 and x1
        x0 = x1 - q * x0;
        x1 = t;
    }

    // Make x1 positive
    if (x1 < 0) x1 += m0;

    return x1;
}
const int L = 18;
int pref[2][N];
int n, k;
int c[N];
int po[N], invpo[N];
ll ans = 0;
unordered_map<int, int> freq;
class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po2[L];

    void run(int src, ADJ& adj) {
        for (int i = 0; i < L; i++) {
            po2[i] = (1 << i);
        }
        dpth[src] = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ& adj) {
        up[u][0] = p;
        pref[0][u] = (c[u] * 1ll * po[dpth[u]]) % k;
        pref[1][u] = c[u] % k;
        if (u) {
            pref[0][u] = (pref[0][u] + pref[0][p]) % k;
            pref[1][u] = (pref[1][u] + (pref[1][p] * 1ll * 2) % k) % k;
        }
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            dpth[v] = dpth[u] + 1;
            dfs(v, u, adj);
        }
    }

    int getpref1(int u, int p) {
        int rs = pref[1][u];
        if (p != 0) {
            p = up[p][0];
            int d = dpth[u] - dpth[p];
            rs = (rs + 0ll + k - (po[d] * 1ll * pref[1][p]) % k) % k;
        }
        return rs;
    }
    int getpref0(int u, int p, bool goup = false) {
        int rs = pref[0][u];
        if (goup) {
            if (p == 0) {
                return rs;
            }
            p = up[p][0];
        }
        int d = dpth[p];
        rs = (rs + 0ll + k - pref[0][p]) % k;
        rs = (rs * 1ll * invpo[d + 1]) % k;
        return rs;
    }

    int getpath(int u, int v) {
        int lc = getlca(u, v);
        if (lc == u) {
            return getpref0(v, u, true);
        }
        int rs = getpref1(u, lc);
        if (v != lc) {
            int d = dpth[u] - dpth[lc] + 1;
            rs = (rs + (po[d] * 1ll * getpref0(v, lc)) % k) % k;
        }
        return rs;
    }
    int getlca(int u, int v) {
        if (dpth[u] < dpth[v]) {
            swap(u, v);
        }
        int l = dpth[u] - dpth[v];
        for (int i = L - 1; i >= 0; i--) {
            if (po2[i] <= l) {
                l -= po2[i];
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
            adj1.addBiEdge(x, src);
            par[x] = src;
        }
        return src;
    }

    int run(ADJ& adj) {
        for (int i = 0; i < adj.n; i++) {
            done[i] = 0;
        }
        return buildCentroid(0, adj);
    }

    void upd(int u, int p, int val) {
        freq[LCA.getpath(p, u)] += val;
        // dbg(u);
        neig(u, v, e, adj1) {
            if (v == par[u]) continue;
            upd(v, p, val);
        }
    }

    void calcAns(int u, int p) {
        int val = LCA.getpath(u, p);
        ans += LCA.getpath(p, u) == 0;
        int d = LCA.getdist(u, p);

        int x = freq[(((k - val + 0ll + po[d] * c[p]) % k) * 1ll * invpo[d]) % k];
        ans += x;

        neig(u, v, e, adj1) {
            if (v == par[u]) continue;
            calcAns(v, p);
        }
    }

    void solve(int u) {
        upd(u, u, 1);

        neig(u, v, e, adj1) {
            if (v == par[u]) continue;
            upd(v, u, -1);
            calcAns(v, u);
            upd(v, u, 1);
        }
        upd(u, u, -1);
        neig(u, v, e, adj1) {
            if (v == par[u]) continue;
            solve(v);
        }
    }
} CD;

void test_case() {
    cin >> n;
    adj.init(n);
    adj1.init(n);
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        --a, --b;
        adj.addBiEdge(a, b);
    }
    cin >> k;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        ans += c[i] == 0;
    }
    if (k == 1) {
        ll ans = (n * 1ll * (n + 1)) / 2;
        cout << ans << endl;
        return;
    }
    if (k == 2) {
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (!c[i]) {
                ans += n;
            }
        }
        cout << ans << endl;
        return;
    }
    int inv2 = modular_inverse(2, k);
    int src = CD.run(adj);
    po[0] = invpo[0] = 1;
    for (int i = 1; i <= n; i++) {
        po[i] = (2 * 1ll * po[i - 1]) % k;
        invpo[i] = (inv2 * 1ll * invpo[i - 1]) % k;
    }
    LCA.run(0, adj);

    CD.solve(src);
    cout << ans << endl;
}

int main() {
    #ifndef ONLINE_JUDGE
        freopen("in.txt", "r", stdin);
    #endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
