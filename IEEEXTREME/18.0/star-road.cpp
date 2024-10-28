//https://csacademy.com/ieeextreme18/task/star-road/
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

template <typename node>
struct SegTree {
    vector<node> tree;
    vector<node> lazy;
    int n;

    void apply(int id, int ns, int ne, int v) {
        // define apply operation here
        if (v == 0) {
            tree[id] = v;
        } else {
            tree[id] = max(tree[id], v);
        }
    }
    node mrg(const node &l, const node &r) {
        node res;
        // merge nodes
        return res = max(l, r);
    }
    void pull(int id, int ns, int ne) {
        int l = 2 * id + 1;
        int r = l + 1;
        tree[id] = mrg(tree[l], tree[r]);
    }

    void push(int id, int ns, int ne) {
        if (lazy[id] && ns != ne) {
            int l = 2 * id + 1;
            int r = l + 1;
            int md = ns + (ne - ns) / 2;
            apply(l, ns, md, lazy[id]);
            apply(r, md + 1, ne, lazy[id]);
            lazy[id] = 0;
        }
    }
    template <typename M>
    void build(int id, int ns, int ne, const vector<M> &v) {
        if (ns == ne) {
            apply(id, ns, ne, v[ns]);
            return;
        }
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        build(l, ns, md, v);
        build(r, md + 1, ne, v);
        pull(id, ns, ne);
    }
    void build(int id, int ns, int ne) {
        if (ns == ne) {
            return;
        }
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        build(l, ns, md);
        build(r, md + 1, ne);
        pull(id, ns, ne);
    }
    node query(int qs, int qe, int id, int ns, int ne) {
        if (qs <= ns && qe >= ne) {
            return tree[id];
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        node res;
        if (qe <= md) {
            res = query(qs, qe, l, ns, md);
        } else {
            if (qs > md) {
                res = query(qs, qe, r, md + 1, ne);
            } else {
                node rl = query(qs, qe, l, ns, md);
                node rr = query(qs, qe, r, md + 1, ne);
                res = mrg(rl, rr);
            }
        }
        pull(id, ns, ne);
        return res;
    }

    int getFirstOnCondition(int qs, int qe, int dir, int id, int ns, int ne, int k) {
        if (qs > ne || qe < ns) return -1;
        if (qs <= ns && qe >= ne) {
            // check condition on interval
        }
        if (ns == ne) {
            return ns;
        }
        push(id, ns, ne);
        int p;
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        if (dir == 0)
            p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        else
            p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
        if (p == -1) {
            if (dir == 0)
                p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
            else
                p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        }
        pull(id, ns, ne);
        return p;
    }

    template <typename... M>
    void update(int qs, int qe, int id, int ns, int ne, const M &...v) {
        if (qs > ne || qe < ns) return;
        if (qs <= ns && qe >= ne) {
            apply(id, ns, ne, v...);
            return;
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        update(qs, qe, l, ns, md, v...);
        update(qs, qe, r, md + 1, ne, v...);
        pull(id, ns, ne);
    }
    SegTree(int _n) {
        n = _n;
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(0, 0, n - 1);
    }
    SegTree(const vector<node> &v) {
        n = v.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(0, 0, n - 1, v);
    }
    node query(int qs, int qe) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        return query(qs, qe, 0, 0, n - 1);
    }

    node query(int p) {
        assert(p >= 0 && p <= n - 1);
        return query(p, p, 0, 0, n - 1);
    }
    template <typename... M>
    int getFirstOnCondition(int qs, int qe, int dir, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1 && dir >= 0 && dir <= 1);
        return getFirstOnCondition(qs, qe, dir, 0, 0, n - 1, v...);
    }
    template <typename... M>
    void update(int qs, int qe, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        update(qs, qe, 0, 0, n - 1, v...);
    }
};

int ans = 0;
int n, s[N];

int dpup[N];
int dpdown[N];

struct SmallToBigMerge {
    int tin[N], tout[N], sz[N], bchd[N], nodes[N], ti;

    void init(int n) { ti = -1; }
    void dfs(int u, ADJ &adj, int pa = -1) {
        tin[u] = ++ti;
        sz[u] = 1;
        nodes[ti] = u;
        pair<int, int> p = {-1, -1};
        neig(u, v, e, adj) {
            if (v == pa) continue;
            dfs(v, adj, u);
            sz[u] += sz[v];
            p = max(p, mp(sz[v], v));
        }
        bchd[u] = p.se;
        tout[u] = ti;
    }

    void solve(int u, ADJ &adj, SegTree<int> &sgmin, SegTree<int> &sgmax, int p = -1, bool keep = 1) {
        neig(u, v, e, adj) {
            if (v == p || v == bchd[u]) continue;
            solve(v, adj, sgmin, sgmax, u, 0);
        }
        if (bchd[u] != -1) {
            solve(bchd[u], adj, sgmin, sgmax, u, 1);
        }
        // don't forget to handle or add the value for u
        int dpmin = 1 + sgmin.query(0, s[u] - 1);
        int dpmax = 1 + sgmax.query(s[u] + 1, 1e5 + 1);
        ans = max({ans, dpmin, dpmax});
        sgmin.update(s[u], s[u], dpmin);
        sgmax.update(s[u], s[u], dpmax);
        // dbg(u, dpmin, dpmax);
        neig(u, v, e, adj) {
            if (v == p || v == bchd[u]) continue;
            for (int i = tin[v]; i <= tout[v]; i++) {
                int nd = nodes[i];
                int dpmin = sgmin.query(0, s[nd] - 1) + dpup[nd];
                int dpmax = sgmax.query(s[nd] + 1, 1e5 + 1) + dpdown[nd];
                ans = max({ans, dpmin, dpmax});
                sgmin.update(s[nd], s[nd], dpdown[nd]);
                sgmax.update(s[nd], s[nd], dpup[nd]);
            }
        }
        dpmin = 1 + sgmin.query(0, s[u] - 1);
        dpmax = 1 + sgmax.query(s[u] + 1, 1e5 + 1);
        dpup[u] = dpmax;
        dpdown[u] = dpmin;
        ans = max({ans, dpmin, dpmax});
        sgmin.update(s[u], s[u], dpmin);
        sgmax.update(s[u], s[u], dpmax);

        if (!keep) {
            // clear data structure
            //  loop from tin to tout and undo
            for (int i = tin[u]; i <= tout[u]; i++) {
                int nd = nodes[i];
                sgmin.update(s[nd], s[nd], 0);
                sgmax.update(s[nd], s[nd], 0);
            }
            // use clear() if possible
        }
    }

    void run(ADJ &adj) {
        SegTree<int> sgmn = SegTree<int>(100002);
        SegTree<int> sgmx = SegTree<int>(100002);
        init(adj.n);
        dfs(0, adj);
        solve(0, adj, sgmn, sgmx);
    }
} stb;

void test_case() {
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    int u, v;
    for (int i = 0; i < n - 1; i++) {
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    stb.run(adj);
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
