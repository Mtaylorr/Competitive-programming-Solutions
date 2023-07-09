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

#define left(x) (2 * (x) + 1)
#define right(x) (2 * (x) + 2)
#define mid(ns, ne) ((ns) + ((ne) - (ns)) / 2)

class segtree {
   public:
    struct node {
        // define the variables
        int add = 0;
        int mx;
        node() {
            // define initial values
            mx = 0;
        }
        void apply(int ns, int ne, int v) {
            // define apply operation
            mx = v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.mx = max(a.mx, b.mx);
        return res;
    }

    inline void push(int id, int ns, int ne) {
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        if (tree[id].add != 0) {
            tree[l].apply(ns, md, tree[id].add);
            tree[r].apply(md + 1, ne, tree[id].add);
            tree[id].add = 0;
        }
    }

    inline void pull(int id, int l, int r) {
        tree[id] = unite(tree[l], tree[r]);
    }
    int n;
    vector<node> tree;

    void build(int id, int ns, int ne) {
        if (ns == ne) {
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        build(l, ns, md);
        build(r, md + 1, ne);
        pull(id, l, r);
    }
    template <typename M>
    void build(int id, int ns, int ne, const vector<M> &v) {
        if (ns == ne) {
            tree[id].apply(ns, ne, v[ns]);
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        build(l, ns, md, v);
        build(r, md + 1, ne, v);
        pull(id, l, r);
    }
    node get(int qs, int qe, int id, int ns, int ne) {
        if (qs <= ns && qe >= ne) {
            return tree[id];
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        push(id, ns, ne);
        node res{};
        if (qe <= md) {
            res = get(qs, qe, l, ns, md);
        } else {
            if (qs > md) {
                res = get(qs, qe, r, md + 1, ne);
            } else {
                res = unite(get(qs, qe, l, ns, md), get(qs, qe, r, md + 1, ne));
            }
        }
        pull(id, l, r);
        return res;
    }

    template <typename... M>
    void modify(int qs, int qe, int id, int ns, int ne, const M &...v) {
        if (qs <= ns && qe >= ne) {
            tree[id].apply(ns, ne, v...);
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        push(id, ns, ne);
        if (qs <= md) {
            modify(qs, qe, l, ns, md, v...);
        }
        if (qe > md) {
            modify(qs, qe, r, md + 1, ne, v...);
        }
        pull(id, l, r);
    }

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    template <typename M>
    segtree(const vector<M> &v) {
        n = v.size();
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }

    node get(int qs, int qe) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        return get(qs, qe, 0, 0, n - 1);
    }
    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(p, p, 0, 0, n - 1);
    }

    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, v...);
    }
};

const int B_TRIE = 2;
const int L_TRIE = 21;
const int N_TRIE = N * L_TRIE;

struct TrieNode {
    int nxt[B_TRIE];
    int isEnd;
    int cnt;
    void init() {
        memset(nxt, -1, sizeof(nxt));
        cnt = 0;
        isEnd = -1;
    }
    TrieNode() { init(); }
};

class Trie {
   public:
    TrieNode nodes[N_TRIE];
    int ndcnt = 0;
    int addnode() {
        nodes[ndcnt].init();
        return ndcnt++;
    }
    void init() {
        ndcnt = 0;
        addnode();
    }
    void ins(int x) {
        // x is the number to add to the trie
        int cur = 0;
        for (int i = L_TRIE - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            int &nx = nodes[cur].nxt[id];
            if (nx == -1) {
                nx = addnode();
            }
            nodes[nx].cnt++;
            cur = nx;
        }
    }

    int srch(int cur, int x, int mx, int b) {
        if (cur == -1) return 0;
        if (b < 0) return 0;
        int bx = (x >> b) & 1;
        int by = (mx >> b) & 1;
        // dbg(cur, x, mx, b);
        if (by == 0) {
            if (bx == 0) {
                int nx =
                    nodes[cur].nxt[1] != -1 ? nodes[nodes[cur].nxt[1]].cnt : 0;
                return nx + +srch(nodes[cur].nxt[0], x, mx, b - 1);
            } else {
                int nx =
                    nodes[cur].nxt[0] != -1 ? nodes[nodes[cur].nxt[0]].cnt : 0;
                return nx + srch(nodes[cur].nxt[1], x, mx, b - 1);
            }
        } else {
            if (bx == 0) {
                return srch(nodes[cur].nxt[1], x, mx, b - 1);
            } else {
                return srch(nodes[cur].nxt[0], x, mx, b - 1);
            }
        }
    }
} trie;

queue<int> q[1000002];
int n;
vector<int> a;
int ndcnt = 0;
int getnewnode() { return ndcnt++; }
vector<int> adj[N];
int idx[N];
int preprocess(int l, int r, segtree &sg) {
    if (l > r) return -1;
    int mx = sg.get(l, r).mx;
    int bef = -1;
    while (!q[mx].empty() && q[mx].front() <= r) {
        int pos = q[mx].front();
        q[mx].pop();
        int p = preprocess(l, pos - 1, sg);
        int nd = getnewnode();
        idx[nd] = pos;
        if (bef != -1) {
            adj[nd].pb(bef);
        }
        if (p != -1) {
            if (bef == -1) {
                adj[nd].pb(p);
            } else {
                adj[bef].pb(p);
            }
        }
        bef = nd;
        l = pos + 1;
    }
    int p = preprocess(l, r, sg);
    if (p != -1) {
        adj[bef].pb(p);
    }
    return bef;
}
int dpsz[N];
int bchd[N], tin[N], tout[N], ti;
vector<int> nodes;
void dfs(int u) {
    dpsz[u] = 1;
    int mx = 0;
    int mxv = -1;
    tin[u] = ++ti;
    nodes.pb(u);
    for (auto v : adj[u]) {
        dfs(v);
        dpsz[u] += dpsz[v];
        if (dpsz[v] > mx) {
            mx = dpsz[v];
            mxv = v;
        }
    }
    bchd[u] = mxv;
    tout[u] = ti;
}

ll ans = 0;

void solve(int u, bool keep = 0) {
    if (u == -1) return;
    for (auto v : adj[u]) {
        if (v == bchd[u]) continue;
        solve(v, 0);
    }
    solve(bchd[u], 1);
    int mx = a[idx[u]];
    ans += mx * 1ll * trie.srch(0, a[idx[u]], mx, L_TRIE - 1);
    trie.ins(a[idx[u]]);
    for (auto v : adj[u]) {
        if (v == bchd[u]) continue;
        for (int j = tin[v]; j <= tout[v]; j++) {
            int x = a[idx[nodes[j]]];
            int val = trie.srch(0, x, mx, L_TRIE - 1);
            // dbg(u, idx[nodes[j]], x, mx, val);
            ans += mx * 1ll * val;
        }
        for (int j = tin[v]; j <= tout[v]; j++) {
            int x = a[idx[nodes[j]]];
            trie.ins(x);
        }
    }
    if (!keep) {
        trie.init();
    }
}

void test_case() {
    cin >> n;
    trie.init();
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    a.clear();
    ndcnt = 0;
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        a.pb(x);
    }
    for (int i = 0; i < n; i++) {
        q[a[i]].push(i);
    }
    segtree sg = segtree(a);
    nodes.clear();
    int src = preprocess(0, n - 1, sg);
    ti = -1;
    ans = 0;
    dfs(src);
    solve(src);
    cout << ans << endl;
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
