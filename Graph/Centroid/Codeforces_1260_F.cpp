//https://codeforces.com/contest/1260/problem/F
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

struct SPT {
    vector<int> spt[30];
    int po[30];
    vector<int> lg;
    int n;
    void init(vector<int>& v, vector<int>& dpth) {
        n = v.size();
        lg.assign(n + 1, 0);
        po[0] = 1;
        for (int i = 0; i < 30; i++) {
            spt[i].assign(n, 0);
            if (i > 0) po[i] = 2 * po[i - 1];
        }
        for (int i = 2; i <= n; i++) {
            lg[i] = 1 + lg[i / 2];
        }
        for (int i = 0; i < n; i++) {
            spt[0][i] = v[i];
        }
        for (int b = 1; po[b] <= n; b++) {
            for (int i = 0; i + po[b] <= n; i++) {
                spt[b][i] = min(mp(dpth[spt[b - 1][i]], spt[b - 1][i]), mp(dpth[spt[b - 1][i + po[b - 1]]], spt[b - 1][i + po[b - 1]])).se;
            }
        }
    }
    int get(int l, int r, vector<int>& dpth) {
        int lg2 = lg[r - l + 1];
        int rs = min(mp(dpth[spt[lg2][l]], spt[lg2][l]), mp(dpth[spt[lg2][r - po[lg2] + 1]], spt[lg2][r - po[lg2] + 1])).se;
        return rs;
    }
};

struct LCASPT {
    vector<int> dpth;
    vector<int> ndtoid;
    vector<int> idtond;
    vector<ll> dist;
    SPT spt;
    vector<bool> vis;
    int n;
    void init(int n) {
        this->n = n;
        dpth.assign(n, 0);
        dist.assign(n, 0);
        ndtoid.assign(n, 0);
        vis.assign(n, 0);
        idtond.clear();
    }

    void buildLCA() {
        for (int i = 0; i < n; i++) {
            if (!vis[i]) {
                dfs(i);
            }
        }
        spt.init(idtond, dpth);
    }

    void dfs(int u) {
        vis[u] = 1;
        ndtoid[u] = idtond.size();
        idtond.pb(u);
        neig(u, v, e, adj) {
            if (vis[v]) continue;
            dpth[v] = dpth[u] + 1;
            dist[v] = dist[u] + adj.cst[e];
            dfs(v);
            idtond.pb(u);
        }
    }

    int getlca(int u, int v) { return spt.get(min(ndtoid[u], ndtoid[v]), max(ndtoid[u], ndtoid[v]), dpth); }

    ll getdist(int u, int v) {
        int lca = getlca(u, v);
        return dist[u] + dist[v] - 2 * dist[lca];
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

    int run(ADJ& adj) {
        for (int i = 0; i < adj.n; i++) {
            done[i] = 0;
        }
        return buildCentroid(0, adj);
    }
} CD;

int n;
int u, v;
vector<int> addv[N], rem[N];
int l[N], r[N];
int invsz[N];
ll freq[N];
ll sumDist[N][2];

void upd(int u, int v) {
    int m = invsz[u];
    freq[u] = (freq[u] + 0ll + MOD + m * v) % MOD;
    int p = CD.par[u];
    int inu = u;
    while (p != -1) {
        freq[p] = (freq[p] + 0ll + MOD + m * v) % MOD;
        int d = LCA.getdist(inu, p);
        ll x = (d * 1ll * m) % MOD;
        sumDist[p][0] = (sumDist[p][0] + 0ll + MOD + v * x) % MOD;
        sumDist[u][1] = (sumDist[u][1] + 0ll + MOD + v * x) % MOD;
        u = p;
        p = CD.par[u];
    }
}

int calcAns(int u) {
    int rs = 0;
    int m = invsz[u];
    rs = (rs + (m * 1ll * sumDist[u][0]) % MOD) % MOD;
    int p = CD.par[u];
    int inu = u;
    while (p != -1) {
        int d = LCA.getdist(inu, p);
        ll x = (d * 1ll * m) % MOD;
        rs = (rs + (x * 1ll * freq[p]) % MOD) % MOD;
        rs = (rs + 0ll + MOD - (x * 1ll * freq[u]) % MOD) % MOD;
        rs = (rs + (m * 1ll * sumDist[p][0]) % MOD) % MOD;
        rs = (rs + 0ll + MOD - (m * 1ll * sumDist[u][1]) % MOD) % MOD;
        u = p;
        p = CD.par[u];
    }
    return rs;
}

void test_case() {
    cin >> n;
    adj.init(n);
    LCA.init(n);
    int multiplier = 1;
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        addv[l[i]].pb(i);
        rem[r[i]].pb(i);
        multiplier = (multiplier * 1ll * (r[i] - l[i] + 1)) % MOD;
        invsz[i] = inv(r[i] - l[i] + 1);
    }
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v, 1);
    }
    LCA.buildLCA();
    int src = CD.run(adj);
    ll res = 0;
    ll ans = 0;
    for (int i = 1; i <= 1e5; i++) {
        for (auto& u : addv[i]) {
            upd(u, 1);
            res = (res + calcAns(u)) % MOD;
        }
        ans = (ans + res) % MOD;
        for (auto& u : rem[i]) {
            res = (res + 0ll + MOD - calcAns(u)) % MOD;
            upd(u, -1);
        }
    }
    ans = (ans * multiplier) % MOD;
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
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
