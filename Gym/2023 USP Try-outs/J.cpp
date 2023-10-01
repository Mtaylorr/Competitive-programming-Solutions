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
const int N = 1e6 + 5;
const int E = 4e6 + 5;

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

const int L = 22;

class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po[L];
    bool vis[N];

    void run(ADJ &adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        for (int i = 0; i < adj.n; i++) {
            dpth[i] = 0;
            vis[i] = 0;
        }
        for (int i = 0; i < adj.n; i++) {
            if (!vis[i]) {
                dfs(i, i, adj);
            }
        }
    }
    void dfs(int u, int p, ADJ &adj) {
        up[u][0] = p;
        vis[u] = 1;
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            if (vis[v]) continue;
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

struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;

int n, m;
int s[N];
vector<int> cnt[N];
int sum[N];
int dp[N];
bool vis[N];

void solve(int u) {
    vis[u] = 1;
    neig(u, v, e, adj) {
        if (vis[v]) continue;
        solve(v);
        dp[u] += dp[v];
    }
}

void test_case() {
    cin >> n >> m;
    adj.init(n + m);
    dsu.init(n + m);
    for (int i = 0; i < n; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        adj.addBiEdge(i + m, x);
        adj.addBiEdge(i + m, y);
        dsu.uni(i + m, x);
        dsu.uni(i + m, y);
    }
    for (int i = 0; i < m; i++) {
        cin >> s[i];
    }
    LCA.run(adj);
    for (int i = 0; i < m; i++) {
        if (s[i] == 1) {
            cnt[dsu.getid(i)].pb(i);
        }
    }
    for (int i = 0; i < n + m; i++) {
        if (cnt[i].size() % 2) {
            cout << -1;
            return;
        }
    }
    for (int i = 0; i < n + m; i++) {
        for (int j = 0; j < cnt[i].size(); j += 2) {
            int x = cnt[i][j];
            int y = cnt[i][j + 1];
            int lc = LCA.getlca(x, y);
            sum[lc]++;
            dp[lc] -= 2;
            dp[x] += 1;
            dp[y] += 1;
        }
    }
    for (int i = 0; i < n + m; i++) {
        if (!vis[i]) {
            solve(i);
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if ((dp[i + m] + sum[i + m]) % 2) {
            ans.pb(i + 1);
        }
    }
    cout << ans.size() << endl;
    for (auto &u : ans) {
        cout << u << " ";
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
