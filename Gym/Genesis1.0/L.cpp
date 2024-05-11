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
int n, c[N];
int par[N];
template <typename T>
class FenwickTree {
   public:
    vector<T> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    T mrg(T &x, T &y) { return x + y; }

    void upd(int x, T v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    T getprefix(int x) {
        if (x <= 0) return 0;
        T rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    T getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
};
FenwickTree<int> ft;

void dfs(int u, int p = -1) {
    par[u] = p;
    neig(u, v, e, adj) {
        if (v == p) continue;
        dfs(v, u);
    }
}
ll rs = 0;
void add(int u, int p, int val) {
    ft.upd(c[u], val);
    neig(u, v, e, adj) {
        if (v == p) continue;
        add(v, u, val);
    }
}

void calc(int u, int p, int val) {
    rs += ft.getrange(c[u] + 1, n + 1);
    neig(u, v, e, adj) {
        if (v == p) continue;
        calc(v, u, val);
    }
}

void addSub(int u, int p, int val) {
    if (val == 1) calc(u, p, val);
    add(u, p, val);
}

void test_case() {
    cin >> n;
    adj.init(n);
    ft.init(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    dfs(0);
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        vector<int> vs;
        neig(i, v, e, adj) {
            if (v == par[i]) continue;
            vs.pb(v);
        }
        ll mx = 0;
        rs = 0;
        ft.upd(c[i], 1);
        if (vs.size()) addSub(vs[0], i, 1);
        if (vs.size() > 1) addSub(vs[1], i, 1);
        mx = max(mx, rs);

        if (vs.size()) addSub(vs[0], i, -1);
        if (vs.size() > 1) addSub(vs[1], i, -1);
        rs = 0;
        if (vs.size() > 1) addSub(vs[1], i, 1);
        if (vs.size()) addSub(vs[0], i, 1);
        mx = max(mx, rs);
        if (vs.size() > 1) addSub(vs[1], i, -1);
        if (vs.size()) addSub(vs[0], i, -1);
        ft.upd(c[i], -1);

        ans += mx;
    }
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
