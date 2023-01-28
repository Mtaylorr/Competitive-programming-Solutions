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

struct SPT {
    vector<int> spt[30];
    int po[30];
    vector<int> lg;
    int n;
    void init(vector<int> &v, vector<int> &dpth) {
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
                spt[b][i] = min(mp(dpth[spt[b - 1][i]], spt[b - 1][i]),
                                mp(dpth[spt[b - 1][i + po[b - 1]]],
                                   spt[b - 1][i + po[b - 1]]))
                                .se;
            }
        }
    }
    int get(int l, int r, vector<int> &dpth) {
        int lg2 = lg[r - l + 1];
        int rs =
            min(mp(dpth[spt[lg2][l]], spt[lg2][l]),
                mp(dpth[spt[lg2][r - po[lg2] + 1]], spt[lg2][r - po[lg2] + 1]))
                .se;
        return rs;
    }
};

const int E = 1e6 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

struct ADJ {
    int head[E], to[E], nxt[E], edgcnt = 0;
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
    void init(int n) {
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
};

struct LCA {
    ADJ adj;
    vector<int> dpth;
    vector<int> ndtoid;
    vector<int> idtond;
    vector<ll> dist;
    SPT spt;
    vector<bool> vis;
    int n;
    void init(int n) {
        this->n = n;
        adj.init(n);
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

    int getlca(int u, int v) {
        return spt.get(min(ndtoid[u], ndtoid[v]), max(ndtoid[u], ndtoid[v]),
                       dpth);
    }

    ll getdist(int u, int v) {
        int lca = getlca(u, v);
        return dist[u] + dist[v] - 2 * dist[lca];
    }

} lca;

const int MAXRT = N * 30;
struct DynSegTree {
    int vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    int defalt_value = 0;

    int init() {
        ndcnt = 0;
        return addnode();
    }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    int mrg(int u, int v) { return (u + v); }

    int getval(int u) {
        if (u != -1) {
            return vals[u];
        }
        // define here the default value
        return defalt_value;
    }

    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = defalt_value;
        return ndcnt++;
    }
    void pull_up(int &id) { vals[id] = mrg(getval(lch[id]), getval(rch[id])); }

    void apply(int old_idx, int new_idx, int v) {
        vals[new_idx] = mrg(v, getval(old_idx));
    }

    template <typename... M>
    int modify(int cur, int p, int l, int r, const M &...v) {
        if (l == r) {
            int idx = addnode();
            apply(cur, idx, v...);
            return idx;
        }
        int md = l + (r - l) / 2;
        int idx = addnode();
        if (p <= md) {
            lch[idx] = modify(left(cur), p, l, md, v...);
            rch[idx] = right(cur);
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), p, md + 1, r, v...);
        }
        pull_up(idx);
        return idx;
    }

    int firstOnCondition(int na, int nb, int nc, int l, int r, int vc) {
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int la = getval(left(na));
        int lb = getval(left(nb));
        int lc = getval(left(nc));
        int sum = la + lb - 2 * lc + (vc<=md && vc!=-1);
        if (md - l + 1==sum) {
            return firstOnCondition(right(na), right(nb), right(nc), md + 1, r,vc);
        }
        return firstOnCondition(left(na), left(nb), left(nc), l, md,vc);
    }
} sg;

const int P = 3e6 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    int pos[P];
    vector<int> mob;
    int sieve_size;

    NumberTheory() { sieve_size = 0; }
    void sieve(int ub) {
        memset(pos, -1, sizeof(pos));
        sieve_size = ub;
        primes.clear();
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            pos[i] = primes.size();
            primes.pb(i);
            if (i * 1ll * i <= ub)
                for (int j = i * i; j <= ub; j += i) {
                    is_prime[j] = 0;
                }
        }
    }
} nt;

int n;
int a[N];
int nodes[N];

void dfs(int u, int p = -1) {
    neig(u, v, e, lca.adj) {
        if (v == p) continue;
        if (a[v] == -1) {
            nodes[v] = nodes[u];
        } else {
            nodes[v] = sg.modify(nodes[u], a[v], 0, sz(nt.primes) - 1, 1);
        }
        dfs(v, u);
    }
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = nt.pos[a[i]];
    }
    lca.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        lca.adj.addBiEdge(u, v);
    }
    lca.buildLCA();
    nodes[0] = sg.init();
    dfs(0);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        int lc = lca.getlca(u, v);
        int x = sg.firstOnCondition(nodes[u], nodes[v], nodes[lc], 0,
                                    sz(nt.primes) - 1, a[lc]);
        cout << nt.primes[x] << "\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    nt.sieve(3000000);
    int T;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
