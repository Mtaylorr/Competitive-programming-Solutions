//https://codeforces.com/problemset/problem/1615/D
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

const int E = 2e6 + 5;

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

class TwoSat {
   public:
    ADJ adj;
    vector<int> low, dfst, vis, val, nodes, comp;
    int curt, ndcnt, comps;
    int n;
    void init(int _n) {
        n = _n;
        adj.init(n);
        low.assign(n, 0);
        dfst.assign(n, 0);
        vis.assign(n, 0);
        comp.assign(n, 0);
        nodes.assign(n, 0);
    }
    void dfs(int u) {
        vis[u] = 1;
        low[u] = dfst[u] = curt++;
        comp[u] = -1;
        nodes[ndcnt++] = u;
        neig(u, v, e, adj) {
            if (!vis[v]) {
                dfs(v);
                low[u] = min(low[v], low[u]);
            } else {
                if (comp[v] == -1) {
                    low[u] = min(low[u], low[v]);
                }
            }
        }
        if (dfst[u] == low[u]) {
            do {
                comp[nodes[--ndcnt]] = comps;
            } while (nodes[ndcnt] != u);
            comps++;
        }
    }

    void tarjan() {
        curt = 0;
        comps = 0;
        ndcnt = 0;
        for (int i = 0; i < adj.n; i++) {
            if (!vis[i]) dfs(i);
        }
    }
    void getsol(int u) {
        if (vis[u] == 1) return;
        vis[u] = 1;
        neig(u, v, e, adj) {
            if (vis[v]) continue;
            getsol(v);
        }
        if (val[comp[u]] == -1) {
            val[comp[u]] = 1;
            val[comp[u ^ 1]] = 0;
        }
    }

    bool run() {
        tarjan();
        vis.assign(n, 0);
        val.assign(n, -1);
        for (int i = 0; i < adj.n; i += 2) {
            getsol(i);
            getsol(i + 1);
            if (comp[i] == comp[i + 1]) {
                return 0;
            }
        }
        return 1;
    }
    int var(int x) { return x << 1; }
    int notvar(int x) { return x ^ 1; }
    void addor(int x, int y) {
        adj.addEdge(notvar(x), y);
        adj.addEdge(notvar(y), x);
    }
    void addImplication(int x, int y) { addor(notvar(x), y); }
    void addEqual(int x, int y) {
        addImplication(x, y);
        addImplication(y, x);
    }
    void addNotEqual(int x, int y) {
        addEqual(notvar(x), y);
        addEqual(notvar(y), x);
    }
    void addEqualTrue(int x) { adj.addEdge(notvar(x), var(x)); }
    void addEqualFalse(int x) { adj.addEdge(var(x), notvar(x)); }

} twosat;

int n, m;
int a[N], b[N], p;
void dfs(int u, int p = -1) {
    neig(u, v, e, adj) {
        if (v == p) continue;
        if (adj.cst[e] != -1) {
            int x = __builtin_popcount(adj.cst[e]);
            if (x % 2 == 0) {
                twosat.addEqual(twosat.var(u), twosat.var(v));
            } else {
                twosat.addNotEqual(twosat.var(u), twosat.var(v));
            }
        }
        dfs(v, u);
    }
}
void printAns(int u, int c = 0, int p = -1) {
    // dbg(u + 1, twosat.comp[twosat.var(u)],
    //     twosat.val[twosat.comp[twosat.var(u)]]);
    neig(u, v, e, adj) {
        if (v == p) continue;
        // dbg(u+1,v+1, twosat.comp[twosat.var(v)],c);
        cout << u + 1 << " " << v + 1 << " ";
        int x = __builtin_popcount(adj.cst[e]);
        int nc = c;
        if (adj.cst[e] != -1) {
            cout << adj.cst[e] << "\n";
            nc += (x);
            nc %= 2;
        } else {
            x = (x + c) % 2;
            if (twosat.val[twosat.comp[twosat.var(v)]] == x) {
                cout << 0 << "\n";
            } else {
                cout << 1 << "\n";
                nc++;
            }
        }
        printAns(v, nc, u);
    }
}

void test_case() {
    cin >> n >> m;
    adj.init(n);
    twosat.init(2 * n);
    for (int i = 0; i < n - 1; i++) {
        int x, y, v;
        cin >> x >> y >> v;
        --x, --y;
        adj.addBiEdge(x, y, v);
    }
    dfs(0);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i] >> p;
        a[i]--, b[i]--;
        if (p % 2 == 0) {
            twosat.addEqual(twosat.var(a[i]), twosat.var(b[i]));
        } else {
            twosat.addNotEqual(twosat.var(a[i]), twosat.var(b[i]));
        }
    }
    twosat.addEqualFalse(twosat.var(0));
    bool ans = twosat.run();
    if (!ans) {
        cout << "NO\n";
        return;
    }
    cout << "YES\n";
    printAns(0);
}

int main() {
    // freopen("input.txt", "r", stdin);
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
