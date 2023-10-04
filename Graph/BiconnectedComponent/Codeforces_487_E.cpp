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
} adj, nadj;

struct BCC {
    vector<vector<pair<int, int> > > bcc_edges;
    vector<vector<int> > bcc_nodes;
    vector<vector<int> > has_bcc;
    stack<pair<int, int> > st;
    int bcccnt = 0;
    void init(int n) {
        bcc_edges.clear();
        bcc_nodes.clear();
        has_bcc.clear();
        has_bcc.resize(n);
    }
    void clear_stack() {
        while (st.size()) {
            st.pop();
        }
    }
    void push(int u, int v) { st.push({u, v}); }
    void createBCC(int u, int v) {
        bcc_edges.emplace_back();
        while (st.top() != mp(u, v)) {
            bcc_edges.back().pb(st.top());
            st.pop();
        }
        bcc_edges.back().pb(st.top());
        st.pop();
        bcccnt++;
    }
    void createBCC() {
        if (st.size() == 0) return;
        bcc_edges.emplace_back();
        while (st.size()) {
            bcc_edges.back().pb(st.top());
            st.pop();
        }
        bcccnt++;
    }
    void generateBCCNode() {
        unordered_set<int> st;
        for (auto &bcc : bcc_edges) {
            st.clear();
            for (auto &edge : bcc) {
                st.insert(edge.fi);
                st.insert(edge.se);
            }
            bcc_nodes.emplace_back();
            for (auto &u : st) {
                bcc_nodes.back().pb(u);
                has_bcc[u].pb(bcc_nodes.size() - 1);
            }
        }
    }
} bcc;

struct AritculationPoints {
    unordered_set<int> nodes;
    void init() { nodes.clear(); }
    bool is_apoint(int p) { return nodes.count(p); }
    void add(int p) { nodes.insert(p); }
} apoints;

pair<int, int> getpair(int x, int y) { return {min(x, y), max(x, y)}; }
struct Bridges {
    set<pair<int, int> > bridges;
    void init() { bridges.clear(); }
    bool is_bridge(int u, int v) { return bridges.count(getpair(u, v)); }
    void add(int u, int v) { bridges.insert(getpair(u, v)); }
} bridges;

struct Tarjan {
    vector<int> visited;
    vector<int> tin, low;
    vector<int> par;
    bool with_bridges, with_bcc, with_apoints;
    int timer;
    void dfs(int u, ADJ &adj) {
        visited[u] = 1;
        tin[u] = low[u] = timer++;
        int children = 0;
        neig(u, v, e, adj) {
            if (v == par[u]) continue;
            if (visited[v] == 1) {
                if (with_bcc && tin[v] < low[u]) bcc.push(u, v);
                low[u] = min(tin[v], low[u]);
            } else if (!visited[v]) {
                if (with_bcc) bcc.push(u, v);
                ++children;
                par[v] = u;
                dfs(v, adj);
                low[u] = min(low[u], low[v]);
                if (with_bcc) {
                    if (par[u] == -1 && children > 1) bcc.createBCC(u, v);
                    if (par[u] != -1 && low[v] >= tin[u]) {
                        bcc.createBCC(u, v);
                    }
                }
                if (with_bridges && low[v] > tin[u]) bridges.add(u, v);
                if (with_apoints && low[v] >= tin[u] && par[u] != -1) {
                    apoints.add(u);
                }
            }
        }
        if (with_apoints && par[u] == -1 && children > 1) {
            apoints.add(u);
        }
    }

    void init(int n) {
        timer = 0;
        visited.assign(n, 0);
        tin.assign(n, -1);
        low.assign(n, -1);
        par.assign(n, -1);
        if (with_apoints) bridges.init();
        if (with_bridges) apoints.init();
        if (with_bcc) bcc.init(adj.n);
    }

    void run(ADJ &adj, bool _with_apoints, bool _with_bridges, bool _with_bcc) {
        with_apoints = _with_apoints;
        with_bridges = _with_bridges;
        with_bcc = _with_bcc;
        init(adj.n);
        for (int i = 0; i < adj.n; ++i) {
            if (!visited[i]) {
                dfs(i, adj);
                if (with_bcc) {
                    bcc.createBCC();
                }
            }
        }
    }
} tarjan;

#define left(x) (2 * (x) + 1)
#define right(x) (2 * (x) + 2)
#define mid(ns, ne) ((ns) + ((ne) - (ns)) / 2)

struct node {
    // define the variables
    int add = 0;
    int mn = 1e9;
    node() {
        // define initial values
    }
    void apply(int ns, int ne, int v) {
        // define apply operation
        mn = v;
    }
};
class segTreeHLD {
   public:
    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.mn = min(a.mn, b.mn);
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
    void build(int id, int ns, int ne, const vector<M> &v,
               const vector<int> &idxToNd) {
        if (ns == ne) {
            tree[id].apply(ns, ne, v[idxToNd[ns]]);
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        build(l, ns, md, v, idxToNd);
        build(r, md + 1, ne, v, idxToNd);
        pull(id, l, r);
    }
    node get(int qs, int qe, int id, int ns, int ne) {
        if (qs <= ns && qe >= ne) {
            return tree[id];
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        // push(id, ns, ne);
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
        // push(id, ns, ne);
        if (qs <= md) {
            modify(qs, qe, l, ns, md, v...);
        }
        if (qe > md) {
            modify(qs, qe, r, md + 1, ne, v...);
        }
        pull(id, l, r);
    }

    segTreeHLD(){};
    segTreeHLD(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    template <typename M>
    segTreeHLD(const vector<M> &v, const vector<int> &idxToNd) {
        n = v.size();
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1, v, idxToNd);
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

class HLD {
   public:
    vector<int> par, sze, dpth, ndToIdx, chHead, heavyChld, idxToNd;
    int n, curPos;
    segTreeHLD sg;
    HLD() {}
    void run(ADJ &adj) {
        n = adj.n;
        curPos = 0;
        par.assign(n, -1);
        sze.assign(n, 0);
        dpth.assign(n, 0);
        ndToIdx.assign(n, 0);
        chHead.assign(n, 0);
        heavyChld.assign(n, 0);
        idxToNd.assign(n, 0);
        calcsz(0, adj);
        HLD_util(0, adj);
    }

    void initSegmentTree() { sg = segTreeHLD(n); }
    template <typename M>
    void initSegmentTree(vector<M> &v) {
        sg = segTreeHLD(v, idxToNd);
    }
    void calcsz(int u, ADJ &adj) {
        heavyChld[u] = -1;
        sze[u] = 1;
        int mx = 0, mxv;
        neig(u, v, e, adj) {
            if (par[u] == v) continue;
            par[v] = u;
            dpth[v] = dpth[u] + 1;
            calcsz(v, adj);
            if (sze[v] > mx) {
                mx = sze[v];
                mxv = v;
            }
            sze[u] += sze[v];
        }
        if (mx * 2 > sze[u]) {
            heavyChld[u] = mxv;
        }
    }

    void HLD_util(int u, ADJ &adj, int c = 0) {
        if (u == -1) return;
        idxToNd[curPos] = u;
        ndToIdx[u] = curPos++;
        chHead[u] = c;
        HLD_util(heavyChld[u], adj, c);
        neig(u, v, e, adj) {
            if (v == par[u]) continue;
            if (v == heavyChld[u]) continue;
            HLD_util(v, adj, v);
        }
    }
    int lca(int u, int v) {
        while (chHead[u] != chHead[v]) {
            if (dpth[chHead[v]] > dpth[chHead[u]]) swap(u, v);
            u = par[chHead[u]];
        }
        if (dpth[u] > dpth[v]) swap(u, v);
        return u;
    }
    int getDist(int u, int v) {
        int l = lca(u, v);
        return dpth[u] + dpth[v] - 2 * dpth[l];
    }
    // make sure to update the return type based on the type of the segment
    // tree
    int query(int u, int v) {
        node du, dv;

        while (chHead[u] != chHead[v]) {
            if (dpth[chHead[v]] > dpth[chHead[u]]) {
                swap(u, v);
                swap(du, dv);
            }
            node tmp = sg.get(ndToIdx[chHead[u]], ndToIdx[u]);
            du = sg.unite(tmp, du);
            u = par[chHead[u]];
        }
        if (dpth[u] > dpth[v]) {
            swap(u, v);
            swap(du, dv);
        }
        //             (u) --------  the direction of the query is always
        //      (tmp) /  | \ (du)    from top to bottom so make sure that
        //           /   |  \        if the direction matters to update
        // --------(v)               the function
        //   (dv)  / |
        //        /  |
        // replace ndToIdx[u]  to ndToIdx[u]+1 if you want to not include the
        // lca ATTENTION : handle the case u=v alone !!
        auto tmp = sg.get(ndToIdx[u], ndToIdx[v]);
        dv = sg.unite(tmp, dv);
        // define what to return here
        return sg.unite(dv, du).mn;
    }
    template <typename... M>
    void update(int u, int v, const M &...val) {
        sg.upd(ndToIdx[u], ndToIdx[v], val...);
    }
} hld;

int n, m, q;
int w[N];
int id[N];
multiset<int> st[N];

void test_case() {
    cin >> n >> m >> q;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }

    tarjan.run(adj, 1, 1, 1);
    bcc.generateBCCNode();
    int nb = 0;
    int cid = 0;
    for (int i = 0; i < n; i++) {
        if (apoints.is_apoint(i)) {
            nb++;
            id[i] = cid++;
        }
    }
    nb += bcc.bcccnt;
    nadj.init(nb);
    for (int i = 0; i < n; i++) {
        if (apoints.is_apoint(i)) {
            set<int> st;
            for (auto &x : bcc.has_bcc[i]) {
                st.insert(cid + x);
            }
            for (auto &v : st) {
                nadj.addBiEdge(id[i], v);
            }
        } else {
            id[i] = cid + bcc.has_bcc[i][0];
        }
    }

    hld.run(nadj);

    vector<int> vals(nb, 1e9);
    for (int i = 0; i < n; i++) {
        if (apoints.is_apoint(i)) {
            st[id[i]].insert(w[i]);
            int p = hld.par[id[i]];
            if (p >= cid) {
                st[p].insert(w[i]);
            }
        } else {
            st[id[i]].insert(w[i]);
        }
    }
    for (int i = 0; i < nb; i++) {
        vals[i] = *st[i].begin();
    }
    hld.initSegmentTree(vals);
    while (q--) {
        char c;
        int a, b;
        cin >> c >> a >> b;
        --a;
        if (c == 'C') {
            if (apoints.is_apoint(a)) {
                st[id[a]].erase(st[id[a]].find(w[a]));
                int p = hld.par[id[a]];
                if (p >= cid) {
                    st[p].erase(st[p].find(w[a]));
                }
                w[a] = b;
                st[id[a]].insert(w[a]);
                hld.update(id[a], id[a], *st[id[a]].begin());
                if (p >= cid) {
                    st[p].insert(w[a]);
                    hld.update(p, p, *st[p].begin());
                }
            } else {
                st[id[a]].erase(st[id[a]].find(w[a]));
                w[a] = b;
                st[id[a]].insert(w[a]);
                hld.update(id[a], id[a], *st[id[a]].begin());
            }
        } else {
            --b;
            if (a == b) {
                cout << w[a] << endl;
                continue;
            }
            a = id[a];
            b = id[b];
            int lc = hld.lca(a, b);
            int ans = 1e9;
            if (lc >= cid && hld.par[lc] != -1) {
                ans = *st[hld.par[lc]].begin();
            }
            ans = min(ans, hld.query(a, b));
            cout << ans << endl;
        }
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
