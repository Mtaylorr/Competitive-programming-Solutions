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
const int N = 5e4 + 5;
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
vector<int> primes[N];
vector<int> divs[N];
int par[N];
int mob[N];
int po[20];
int c[N];
int n;
int freq[2][N];
int tin[N], tout[N], ti = -1;
int sz[N], bchld[N];
vector<int> nodes;
void dfs(int u, int p = -1) {
    sz[u] = 1;
    int mx = 0;
    int mxv = -1;
    tin[u] = ++ti;
    nodes.pb(u);
    neig(u, v, e, adj) {
        if (v == p) continue;
        par[v] = adj.cst[e];
        dfs(v, u);
        sz[u] += sz[v];
        if (sz[v] > mx) {
            mx = sz[v];
            mxv = v;
        }
    }
    bchld[u] = mxv;
    tout[u] = ti;
}
ll sum = 0;
ll ans[N];

void upd(int i, int v) {
    for (auto u : divs[i]) {
        freq[1][u] += v;
    }
}
void rem(int i) {
    for (auto u : divs[i]) {
        sum -= freq[1][u] * mob[u];
    }
}

void add(int i) {
    for (auto u : divs[i]) {
        sum += (freq[0][u] - freq[1][u]) * mob[u];
    }
}

void solve(int u, int p = -1, bool keep = 0) {
    if (u == -1) return;
    neig(u, v, e, adj) {
        if (v == p || v == bchld[u]) continue;
        solve(v, u, 0);
    }
    solve(bchld[u], u, 1);
    rem(u);
    neig(u, v, e, adj) {
        if (v == p || v == bchld[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            rem(nodes[i]);
        }
    }
    neig(u, v, e, adj) {
        if (v == p || v == bchld[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            upd(nodes[i], 1);
        }
    }
    upd(u, 1);
    add(u);
    neig(u, v, e, adj) {
        if (v == p || v == bchld[u]) continue;
        for (int i = tin[v]; i <= tout[v]; i++) {
            add(nodes[i]);
        }
    }

    if (par[u] != -1) {
        ans[par[u]] = sum;
    }
    if (!keep) {
        for (int i = tin[u]; i <= tout[u]; i++) {
            upd(nodes[i], -1);
        }
        sum = 0;
    }
}

void test_case() {
    memset(par,-1, sizeof(par));
    for (int i = 0; i < 20; i++) {
        po[i] = 1 << i;
    }
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        int x = c[i];
        for (int j = 2; j * j <= x; j++) {
            if (x % j == 0) {
                primes[i].pb(j);
                while (x % j == 0) {
                    x /= j;
                }
            }
        }
        if (x > 1) {
            primes[i].pb(x);
        }
        int m = primes[i].size();
        for (int msk = 0; msk < po[m]; ++msk) {
            int nb = 0;
            int x = 1;
            for (int j = 0; j < m; j++) {
                if ((po[j]) & msk) {
                    nb++;
                    x *= primes[i][j];
                }
            }
            divs[i].pb(x);
            freq[0][x]++;
            mob[x] = nb % 2 == 0 ? 1 : -1;
        }
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v, i);
    }
    dfs(0);
    solve(0);
    for(int i=0;i<n-1;i++){
        cout << ans[i] << " ";
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
