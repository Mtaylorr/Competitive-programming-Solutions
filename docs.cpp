// Graph Mtaylor

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

const int E = 1e6 + 5;
#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJAug {
   public:
    int head[N], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E], cap[E];

    void addEdge(int a, int b, int cs, int cp) {
        // cs = cost
        // cp = capacity
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cap[edgcnt] = cp;
        cst[edgcnt] = cs;
        edgcnt++;
    }

    void addAug(int a, int b, int cs, int c, int d = 0) {
        // cs : cost
        // c  : forward capacity
        // d  : backward capacity
        addEdge(a, b, cs, c);
        addEdge(b, a, -cs, d);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

struct BCC {
    vector<vector<pair<int, int>>> bcc_edges;
    vector<vector<int>> bcc_nodes;
    vector<vector<int>> has_bcc;
    stack<pair<int, int>> st;
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
    set<pair<int, int>> bridges;
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
        if (with_bridges) bridges.init();
        if (with_apoints) apoints.init();
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

class CentroidDecomposition {
   public:
    bool done[N];
    int dpsz[N];
    int par[N];
    void calcsz(int u, int p, ADJ &adj) {
        dpsz[u] = 1;
        neig(u, v, e, adj) {
            if (v == p || done[v]) continue;
            calcsz(v, u, adj);
            dpsz[u] += dpsz[v];
        }
    }

    int getCentroid(int u, int p, int cursz, ADJ &adj) {
        neig(u, v, e, adj) {
            if (v == p || done[v]) continue;
            if (2 * dpsz[v] >= cursz) return getCentroid(v, u, cursz, adj);
        }
        return u;
    }

    int buildCentroid(int u, ADJ &adj) {
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

    void run(ADJ &adj) {
        for (int i = 0; i < adj.n; i++) {
            done[i] = 0;
        }
        buildCentroid(0, adj);
    }
} CD;

struct Dinic {
    int work[N];
    int vis[N], vid = 0, dist[N], par[N], src, snk;

    void init(int n) {
        memset(vis, 0, n * sizeof(vis[0]));
        vid = 0;
    }
    bool bfs(ADJAug &adj) {
        queue<int> q;
        dist[src] = 0;
        vis[src] = ++vid;
        q.push(src);
        while (q.size()) {
            int u = q.front();
            q.pop();
            neig(u, v, e, adj) {
                if (!adj.cap[e] || vis[v] == vid) continue;
                dist[v] = dist[u] + 1;
                vis[v] = vid;
                q.push(v);
            }
        }
        return vis[snk] == vid;
    }

    ll dfs(int u, ADJAug &adj, T fl = 1e18) {
        if (u == snk) return fl;

        for (int &e = work[u], v; (~e) && (v = adj.to[e], 1); e = adj.nxt[e]) {
            if (!adj.cap[e] || dist[v] != dist[u] + 1) continue;
            ll f = dfs(v, adj, min(adj.cap[e], fl));
            if (f) {
                adj.cap[e] -= f;
                adj.cap[e ^ 1] += f;
                return f;
            }
        }
        return 0;
    }

    ll run(ADJAug &adj) {
        init(adj.n);
        ll flow = 0, f = 0;
        while (bfs(adj)) {
            memcpy(work, adj.head, adj.n * sizeof(adj.head[0]));
            do {
                f = dfs(src, adj);
                flow += f;
            } while (f);
        }
        return flow;
    }
} dinic;

class DSUWithRollBack {
   public:
    struct dsu_save {
        int u, rnku, v, rnkv;
        bool ex;
        dsu_save() {}

        dsu_save(int _u, int _rnku, int _v, int _rnkv, bool _ex) : u(_u), rnku(_rnku), v(_v), rnkv(_rnkv), ex(_ex) {}
    };
    vector<int> id, sz, rnk;
    stack<dsu_save> op;
    int comps;
    void init(int n) {
        comps = n;
        id.assign(n, 0);
        sz.assign(n, 0);
        rnk.assign(n, 0);
        while (!op.empty()) {
            op.pop();
        }
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    bool uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) {
            op.push(dsu_save(u, rnk[u], v, rnk[v], 0));
            return 0;
        }
        if (rnk[v] > rnk[u]) swap(v, u);
        op.push(dsu_save(u, rnk[u], v, rnk[v], 1));
        id[v] = u;
        sz[u] += sz[v];
        comps--;
        if (rnk[u] == rnk[v]) rnk[u]++;
        return 1;
    }

    void rollback() {
        if (op.empty()) {
            return;
        }
        dsu_save x = op.top();
        op.pop();
        if (x.ex == 0) {
            return;
        }
        comps++;
        id[x.u] = x.u;
        id[x.v] = x.v;
        rnk[x.u] = x.rnku;
        rnk[x.v] = x.rnkv;
        sz[x.u] -= sz[x.v];
    }
} dsu_rb;

const int MAXM_EULER = N;

class EulerPath {
   public:
    int u[MAXM_EULER], v[MAXM_EULER];
    bool done[MAXM_EULER];
    ADJ adj;

    void init(int n, int m) {
        memset(done, 0, m * sizeof(done[0]));
        adj.init(n);
    }
    void run() {
        for (int i = 0; i < adj.n; i++) {
            dfs(i);
        }
    }

    void dfs(int x) {
        while (adj.head[x] != -1 && done[adj.cst[adj.head[x]]] == 1) {
            adj.head[x] = adj.nxt[adj.head[x]];
        }
        if (adj.head[x] == -1) {
            return;
        }
        int e = adj.head[x];
        int cst = adj.cst[e];
        int y = adj.to[e];
        u[cst] = x;
        v[cst] = y;
        done[cst] = 1;
        adj.head[x] = adj.nxt[e];
        dfs(y);
    }
} euler;

#define left(x) (2 * (x) + 1)
#define right(x) (2 * (x) + 2)
#define mid(ns, ne) ((ns) + ((ne) - (ns)) / 2)

struct node {
    // define the variables
    int add = 0;
    node() {
        // define initial values
    }
    void apply(int ns, int ne, ll v) {
        // define apply operation
    }
};
class segTreeHLD {
   public:
    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
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

    inline void pull(int id, int l, int r) { tree[id] = unite(tree[l], tree[r]); }
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
    void build(int id, int ns, int ne, const vector<M> &v, const vector<int> &idxToNd) {
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

    segTreeHLD() {};
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
    ll query(int u, int v) {
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
        if (u != v) {
            auto tmp = sg.get(ndToIdx[u] + 1, ndToIdx[v]);
            dv = sg.unite(tmp, dv);
        }
        // define what to return here
        return sg.unite(dv, du).sm;
    }
    template <typename... M>
    void update(int u, int v, const M &...val) {
        while (chHead[u] != chHead[v]) {
            if (dpth[chHead[v]] > dpth[chHead[u]]) {
                swap(u, v);
            }
            sg.upd(ndToIdx[chHead[u]], ndToIdx[u], val...);
            u = par[chHead[u]];
        }
        if (dpth[u] > dpth[v]) {
            swap(u, v);
        }
        sg.upd(ndToIdx[u], ndToIdx[v], val...);
    }
} hld;

const int L = 20;

class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po[L];

    void run(int src, ADJ &adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        dpth[src] = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ &adj) {
        up[u][0] = p;
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
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
                spt[b][i] = min(mp(dpth[spt[b - 1][i]], spt[b - 1][i]), mp(dpth[spt[b - 1][i + po[b - 1]]], spt[b - 1][i + po[b - 1]])).se;
            }
        }
    }
    int get(int l, int r, vector<int> &dpth) {
        int lg2 = lg[r - l + 1];
        int rs = min(mp(dpth[spt[lg2][l]], spt[lg2][l]), mp(dpth[spt[lg2][r - po[lg2] + 1]], spt[lg2][r - po[lg2] + 1])).se;
        return rs;
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

    int getlca(int u, int v) { return spt.get(min(ndtoid[u], ndtoid[v]), max(ndtoid[u], ndtoid[v]), dpth); }

    ll getdist(int u, int v) {
        int lca = getlca(u, v);
        return dist[u] + dist[v] - 2 * dist[lca];
    }

} lca;

struct MinCostMaxFlow {
    int vis[N], vid = 0, par[N], inq[N], src, snk;
    ll dist[N], fl[N];

    void init(int n) {
        memset(vis, 0, n * sizeof(vis[0]));
        vid = 0;
    }
    bool bellmanford(ADJAug &adj) {
        queue<int> q;
        q.push(src);
        memset(dist, 63, adj.n * sizeof(dist[0]));
        dist[src] = 0;
        inq[src] = ++vid;
        int ncnt = adj.n;
        fl[snk] = 0, fl[src] = INT_MAX;
        while (--ncnt && q.size()) {
            int s = q.size();
            while (s--) {
                int u = q.front();
                q.pop();
                inq[u] = 0;
                neig(u, v, e, adj) {
                    if (!adj.cap[e]) continue;
                    int d = dist[u] + adj.cst[e];

                    if (d < dist[v]) {
                        fl[v] = min(fl[u], adj.cap[e]);
                        dist[v] = d;
                        par[v] = e;
                        if (inq[v] != vid) {
                            inq[v] = vid;
                            q.push(v);
                        }
                    }
                }
            }
        }
        return fl[snk] > 0;
    }
    pair<ll, ll> run(ADJAug &adj) {
        init(adj.n);
        ll c = 0, f = 0;
        while (bellmanford(adj)) {
            c += dist[snk] * fl[snk];
            f += fl[snk];
            for (int u = snk; u != src; u = adj.to[par[u] ^ 1]) {
                adj.cap[par[u]] -= fl[snk];
                adj.cap[par[u] ^ 1] += fl[snk];
            }
        }
        return {c, f};
    }
} mcmf;

struct MinmumSpanningTree {
    template <typename T>
    ll kruskal(int n, vector<vector<T>> &edges) {
        // need dsu
        DSUGraph dsu;
        dsu.init(n);
        ll ans = 0;
        sort(all(edges), [](vector<T> &x, vector<T> &y) { return x[2] < y[2]; });
        for (auto &e : edges) {
            int u = e[0];
            int v = e[1];
            ll w = e[2];
            if (dsu.sameSet(u, v)) {
                continue;
            }
            dsu.uni(u, v);
            ans += w;
        }
        // // no MST found
        // for (int i = 0; i < n; i++) {
        //     if (!dsu.sameSet(0, i)) {
        //         ans = -1;
        //     }
        // }
        return ans;
    }

    ll Prims(int src, ADJ &adj) {
        // need adj
        set<pair<ll, int>> st;
        int n = adj.n;
        vector<bool> vis(n, 0);
        st.insert({src, 0});
        pair<ll, int> p;
        ll ans = 0;
        while (!st.empty()) {
            p = *st.begin();
            st.erase(st.begin());
            if (vis[p.se]) continue;
            vis[p.se] = 1;
            ans += p.fi;
            int u = p.se;
            neig(u, v, e, adj) {
                if (vis[v]) continue;
                st.insert({adj.cst[e], v});
            }
        }
        // // no MST found
        // for (int i = 0; i < n; i++) {
        //     if (!vis[i]) {
        //         ans = -1;
        //     }
        // }
        return ans;
    }
} mst;

struct PersistentDSUGraph {
    vector<int> id, sz, tail, nxt, roots, pos;
    void init(int n) {
        id.resize(n);
        sz.resize(n, 1);
        tail.resize(n);
        roots.resize(n);
        pos.resize(n);
        nxt.resize(n, -1);
        iota(all(id), 0);
        iota(all(tail), 0);
        iota(all(roots), 0);
        iota(all(pos), 0);
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    bool uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return 0;
        if (sz[v] < sz[u]) swap(u, v);
        id[u] = v;
        sz[v] += sz[u];
        int p = pos[u];
        roots[p] = roots.back();
        pos[roots[p]] = p;
        roots.pop_back();
        nxt[tail[v]] = u;
        tail[v] = tail[u];
        return 1;
    }
    void loopOverSubset(int u) {
        u = getid(u);
        for (int v = u; ~v; v = nxt[v]) {
            // do something
        }
    }
} dsu;

class PersistentDSUWithRollBack {
   public:
    struct dsu_save {
        int u, v;
        int p, tailv;
        bool ex;
        dsu_save() {}

        dsu_save(int _u, int _v, bool _ex, int _p, int _tailv) : u(_u), v(_v), ex(_ex), p(_p), tailv(_tailv) {}
    };
    vector<int> id, sz, tail, nxt, roots, pos;
    stack<dsu_save> op;
    int comps;
    void init(int n) {
        id.resize(n);
        sz.resize(n, 1);
        tail.resize(n);
        roots.resize(n);
        pos.resize(n);
        nxt.resize(n, -1);
        iota(all(id), 0);
        iota(all(tail), 0);
        iota(all(roots), 0);
        iota(all(pos), 0);
        comps = n;
        while (!op.empty()) {
            op.pop();
        }
    }
    int getid(int u) { return (u == id[u] ? u : getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    bool uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) {
            op.push(dsu_save(u, v, 0, 0, 0));
            return 0;
        }
        if (sz[v] < sz[u]) swap(u, v);
        int p = pos[u];
        op.push(dsu_save(u, v, 1, p, tail[v]));
        id[u] = v;
        sz[v] += sz[u];
        roots[p] = roots.back();
        pos[roots[p]] = p;
        roots.pop_back();
        nxt[tail[v]] = u;
        tail[v] = tail[u];
        comps--;
        return 1;
    }

    void rollback() {
        if (op.empty()) {
            return;
        }
        dsu_save x = op.top();
        op.pop();
        if (x.ex == 0) return;
        comps++;
        id[x.u] = x.u;
        id[x.v] = x.v;
        sz[x.v] -= sz[x.u];
        tail[x.v] = x.tailv;
        nxt[tail[x.v]] = -1;
        roots.push_back(roots[x.p]);
        pos[roots[x.p]] = roots.size() - 1;
        roots[x.p] = x.u;
        pos[x.u] = x.p;
    }

    void loopOverSubset(int u) {
        u = getid(u);
        for (int v = u; ~v; v = nxt[v]) {
            // do something
        }
    }
} dsu_rb;

struct SCC {
    int n;
    vector<int> adj[N], radj[N], topSort, vis, scc, sccid, sccsz;
    int scccnt;
    int ans;
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            radj[i].clear();
        }
        vis.assign(n, 0);
        scc.assign(n, 0);
        topSort.clear();
        sccid.assign(n, -1);
        sccsz.assign(n, 0);
        ans = 0;
        scccnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].pb(v);
        radj[v].pb(u);
    }

    void dfsSort(int u) {
        if (vis[u]) return;
        vis[u] = 1;
        for (auto v : adj[u]) {
            dfsSort(v);
        }
        topSort.pb(u);
    }

    void rdfs(int u, int id) {
        if (vis[u]) return;
        vis[u] = 1;
        scc.pb(u);
        sccsz[id]++;
        sccid[u] = id;
        for (auto v : radj[u]) {
            rdfs(v, id);
        }
    }

    void topoSort() {
        vis.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfsSort(i);
        }
    }

    void getSCC() {
        topoSort();
        reverse(all(topSort));
        vis.assign(n, 0);
        for (auto u : topSort) {
            if (vis[u]) continue;
            scc.clear();
            rdfs(u, scccnt);
            scccnt++;
        }
    }
} scc;

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

    void solve(int u, ADJ &adj, int p = -1, bool keep = 1) {
        neig(u, v, e, adj) {
            if (v == p || v == bchd[u]) continue;
            solve(v, adj, u, 0);
        }
        if (bchd[u] != -1) {
            solve(bchd[u], adj, u, 1);
        }
        // don't forget to handle or add the value for u

        neig(u, v, e, adj) {
            if (v == p || v == bchd[u]) continue;
            for (int i = tin[v]; i <= tout[v]; i++) {
                int nd = nodes[i];
            }
        }

        if (!keep) {
            // clear data structure
            //  loop from tin to tout and undo
            // for (int i = tin[u]; i <= tout[u]; i++) {
            //     int nd = nodes[i];
            // }
            // use clear() if possible
        }
    }

    void run(ADJ &adj) {
        init(adj.n);
        dfs(0, adj);
        solve(0, adj);
    }
} stb;

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
    void addEqualTrue(int x) { adj.addEdge(notvar(x), x); }
    void addEqualFalse(int x) { adj.addEdge(x), notvar(x));
    }

} twosat;

// Maximum matching
const int N = 50000 + 5, E = 150000 + 5, M = N;
const int MOD = 1e9 + 7;

#define neig(u, v, e) for (int e = head[u], v; (~e) && (v = to[e], 1); e = nxt[e])
int head[N], nxt[E], to[E], edgcnt, n;
int vis[N], vid = 0, dist[N];
int l2r[N], r2l[M];

void addEdge(int a, int b) {
    nxt[edgcnt] = head[a];
    head[a] = edgcnt;
    to[edgcnt] = b;
    edgcnt++;
}

void init() {
    memset(head, -1, n * sizeof(head[0]));
    edgcnt = 0;
}

void bfs() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (l2r[i] == -1) {
            q.push(i);
            dist[i] = 0;
        } else {
            dist[i] = -1;
        }
    }
    while (q.size()) {
        int lid = q.front();
        q.pop();
        neig(lid, rid, e) {
            int newlid = r2l[rid];
            if (newlid != -1 && dist[newlid] == -1) {
                dist[newlid] = dist[lid] + 1;
                q.push(newlid);
            }
        }
    }
}

int dfs(int lid) {
    neig(lid, rid, e) {
        if (r2l[rid] != -1 && dist[r2l[rid]] != dist[lid] + 1) continue;
        if (r2l[rid] == -1 || dfs(r2l[rid])) {
            r2l[rid] = lid;
            l2r[lid] = rid;
            return 1;
        }
    }
    return 0;
}
int m, x, y;
int maxMatching() {
    int res = 0;
    memset(r2l, -1, m * sizeof(r2l[0]));
    memset(l2r, -1, n * sizeof(r2l[0]));
    bool bl = true;
    while (bl) {
        bl = false;
        bfs();
        for (int i = 0; i < n; i++) {
            if (dist[i] == 0 && dfs(i)) {
                res++;
                bl = true;
            }
        }
    }
    return res;
}

struct EdmondsKarp {
    int snk;
    vector<int> vis;
    vector<int> par;
    vector<int> dist;
    int vid = 0;

    bool bfs(int src, ADJ &adj) {
        vid++;
        fill(all(dist), 0);
        queue<int> q;
        q.push(src);
        vis[src] = vid;
        dist[src] = INT_MAX;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            neig(u, v, e, adj) {
                if (adj.cap[e] == 0) continue;
                if (vis[v] == vid) continue;
                vis[v] = vid;
                q.push(v);
                dist[v] = min(dist[u], adj.cap[e]);
                par[v] = e;
            }
        }
        return vis[snk] == vid;
    }

    long long run(ADJ &adj, int src, int _snk) {
        snk = _snk;
        long long maxFlow = 0;
        long long flow = 0;
        vis.assign(adj.n, 0);
        dist.resize(adj.n);
        par.resize(adj.n);
        while (bfs(src, adj)) {
            flow = dist[snk];
            maxFlow += flow;
            int u = snk;
            while (u != src) {
                int e = par[u];
                adj.cap[e] -= flow;
                adj.cap[e ^ 1] += flow;
                u = adj.to[e ^ 1];
            }
        }
        return maxFlow;
    }
} ek;

struct FordFulkerson {
    int snk;
    vector<int> vis;
    int vid = 0;

    long long dfs(int u, int f, ADJ &adj) {  // O(E+V) E > V =>O(E)
        if (u == snk) {
            return f;
        }
        vis[u] = vid;
        neig(u, v, e, adj) {
            if (vis[v] == vid) continue;
            if (adj.cap[e] == 0) continue;
            int fl = dfs(v, min(f, adj.cap[e]), adj);
            if (fl) {
                adj.cap[e] -= fl;
                adj.cap[e ^ 1] += fl;
                return fl;
            }
        }
        return 0;
    }

    long long run(ADJ &adj, int src, int _snk) {  // O(MaxFlow*E)
        snk = _snk;
        long long maxFlow = 0;
        long long flow = 0;
        vis.assign(adj.n, 0);
        vid = 1;
        while (flow = dfs(src, INT_MAX, adj)) {  // O(MaxFlow)
            maxFlow += flow;
            vid++;
        }
        return maxFlow;
    }
} fc;

struct FlowScaling {
    int snk;
    vector<int> vis;
    int vid = 0;

    long long dfs(int u, int f, ADJ &adj) {  // O(E+V) E > V =>O(E)
        if (f == 0) return 0;
        if (u == snk) {
            return f;
        }
        vis[u] = vid;
        neig(u, v, e, adj) {
            if (vis[v] == vid) continue;
            if (adj.cap[e] < f) continue;
            int fl = dfs(v, f, adj);
            if (fl) {
                adj.cap[e] -= fl;
                adj.cap[e ^ 1] += fl;
                return fl;
            }
        }
        return 0;
    }

    long long run(ADJ &adj, int src, int _snk) {
        snk = _snk;
        long long maxFlow = 0;
        long long flow = 0;
        vis.assign(adj.n, 0);
        vid = 1;
        for (int i = 30; i >= 0; i--) {
            vid++;
            while (flow = dfs(src, 1 << i, adj)) {
                maxFlow += flow;
                vid++;
            }
        }

        return maxFlow;
    }
} fs;

// Data structures Mtaylor

template <typename T>
class BSFenwickTree {
   public:
    vector<T> tree;
    int n;
    void init(int n, T v = 0) {
        this->n = 1 << (__lg(n) + !!(n & (n - 1)));
        tree.assign(this->n + 1, v);
    }
    T mrg(T &x, T &y) { return x + y; }

    void upd(int x, T v) {
        for (++x; x <= n; x += (x) & (-x)) tree[x - 1] = mrg(tree[x - 1], v);
    }
    T getprefix(int x) {
        if (x < 0) return 0;
        T rs = 0;
        for (++x; x; x -= (x) & (-x)) rs = mrg(rs, tree[x - 1]);
        return rs;
    }
    T getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }

    int lower_bound(T v) {
        int p = 0;
        if (tree[n - 1] < v) {
            return n;
        }
        for (int sz = n >> 1; sz; sz >>= 1) {
            if (tree[p + sz - 1] < v) {
                v -= tree[p + sz - 1];
                p += sz;
            }
        }
        return p;
    }
};

struct BitVectorRank {
    typedef unsigned u32;
    typedef size_t Index;
    Index length, blockslength, count;
    vector<u32> blocks;
    vector<Index> ranktable;
    BitVectorRank(Index len = 0) { init(len); }
    void init(Index len) {
        length = len;
        blockslength = (len + 31) / 32 + 1;
        blocks.assign(blockslength, 0);
    }
    inline void set(Index i) {
        // add element to set
        blocks[i / 32] |= 1 << i % 32;
    }
    void build() {
        count = 0;
        if (length == 0) return;
        ranktable.assign(blockslength + 1, 0);
        for (Index i = 0; i < blockslength; i++) {
            ranktable[i] = count;
            count += popcount(blocks[i]);
        }
        ranktable[blockslength] = count;
    }
    inline bool access(Index pos) const {
        // check if element in index pos exist (0 based)
        return blocks[pos / 32] >> pos % 32 & 1;
    }
    inline Index rank(Index pos) const {
        // count the the number of elements between [0..pos)
        int block_idx = pos / 32;
        return ranktable[block_idx] + popcount(blocks[block_idx] & (1U << pos % 32) - 1);
    }
    inline Index rank(bool b, Index pos) const { return b ? rank(pos) : pos - rank(pos); }
    inline Index rank(bool b, Index left, Index right) const { return rank(b, right) - rank(b, left); }

   private:
    static inline int popcount(u32 x) {
        x = x - ((x >> 1) & 0x55555555);
        x = (x & 0x33333333) + ((x >> 2) & 0x33333333);
        return ((x + (x >> 4) & 0xF0F0F0F) * 0x1010101) >> 24;
    }
};

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) { return (upper_bound(all(values), x) - values.begin()) - 1; }
    int greaterThanOrEqual(ll x) { return (lower_bound(all(values), x) - values.begin()); }
    ll decompress(int p) { return values[p]; }
} compressor;

struct WaveletMatrix {
    typedef BitVectorRank BitVector;
    typedef unsigned int Val;
    typedef size_t Index;
    int bitnum;
    Index length;
    Val maxval;
    vector<BitVector> bitvectors;
    vector<Index> mids;

    WaveletMatrix() { init(vector<Val>()); }
    void init(const vector<Val> &data) {
        length = data.size();
        maxval = length == 0 ? 0 : *max_element(data.begin(), data.end());
        bitnum = 1;
        while ((maxval >> 1 >> (bitnum - 1)) != 0) ++bitnum;

        bitvectors.assign(bitnum, BitVector(length));
        mids.resize(bitnum);

        vector<Val> cur = data, next;
        next.resize(length);
        for (int i = 0; i < bitnum; i++) {
            Val mask = Val(1) << (bitnum - 1 - i);
            Index zeros = 0;
            for (Index j = 0, n = length; j < n; j++) zeros += (cur[j] & mask) == 0;
            mids[i] = zeros;

            BitVector &bv = bitvectors[i];
            Index zeroPos = 0, onePos = zeros;
            for (Index j = 0, n = length; j < n; j++) {
                bool b = (cur[j] & mask) != 0;
                if (b)
                    next[onePos++] = cur[j], bv.set(j);
                else
                    next[zeroPos++] = cur[j];
            }
            bv.build();
            next.swap(cur);
        }
    }
    Val access(Index pos) {
        // return v[pos];
        Val val = 0;
        for (int i = 0; i < bitnum; i++) {
            const BitVector &bv = bitvectors[i];
            bool dir = bv.access(pos);
            val = val << 1 | (dir ? 1 : 0);
            pos = bv.rank(dir, pos);
            if (dir) pos += mids[i];
        }
        return val;
    }
    // count i s.t. (0 <= i < right) && v[i] == x
    Index rank(const Val &x, int right) {
        int left = 0;
        for (int i = 0; i < bitnum; i++) {
            Val mask = Val(1) << (bitnum - 1 - i);
            const BitVector &bv = bitvectors[i];
            bool dir = (mask & x) != 0;
            left = bv.rank(dir, left), right = bv.rank(dir, right);
            if (dir) left += mids[i], right += mids[i];
        }
        return right - left;
    }
    // return kth smallest in range [left, right), k 0 based
    Val kth_smallest(int left, int right, int k) {
        if (k < 0 || right - left <= k) {
            return -1;
        }
        Val val = 0;
        for (int i = 0; i < bitnum; i++) {
            const BitVector &bv = bitvectors[i];
            int count = bv.rank(false, left, right);
            bool dir = k >= count;
            val = val << 1 | (dir ? 1 : 0);
            if (dir) k -= count;
            left = bv.rank(dir, left), right = bv.rank(dir, right);
            if (dir) left += mids[i], right += mids[i];
        }
        return val;
    }
    Val kth_biggest(int left, int right, int k) {
        // k 0 based
        return kth_smallest(left, right, right - left - 1 - k);
    }
    int rank_all(Val val, int left, int right, int &res_lt, int &res_gt) {
        if (val > maxval) {
            res_lt = right - left;
            res_gt = 0;
            return 0;
        }
        res_lt = res_gt = 0;
        for (int i = 0; i < bitnum; i++) {
            const BitVector &bv = bitvectors[i];
            bool dir = val >> (bitnum - i - 1) & 1;
            int leftcount = bv.rank(dir, left), rightcount = bv.rank(dir, right);
            (dir ? res_lt : res_gt) += (right - left) - (rightcount - leftcount);
            left = leftcount, right = rightcount;
            if (dir) left += mids[i], right += mids[i];
        }
        return right - left;
    }
    vector<vector<long long>> sum;
    template <typename I>
    void build_sum(const vector<Val> &data, const vector<I> &s) {
        length = data.size();
        maxval = length == 0 ? 0 : *max_element(data.begin(), data.end());
        bitnum = 1;
        while ((maxval >> 1 >> (bitnum - 1)) != 0) ++bitnum;
        vector<int> l(length), r(length), idx(length);
        mids.resize(bitnum);
        iota(idx.begin(), idx.end(), 0);
        for (int i = 0; i < bitnum; i++) {
            Val mask = Val(1) << (bitnum - 1 - i);
            sum[i].assign(length + 1, 0);
            int left = 0, right = 0;
            for (Index j = 0, n = length; j < n; j++) {
                bool b = (data[idx[j]] & mask) != 0;
                if (b)
                    r[right++] = idx[j];
                else
                    l[left++] = idx[j];
            }
            idx.swap(l);
            mids[i] = left;
            for (int j = 0; j < right; i++) {
                idx[left + i] = r[i];
            }
            for (int j = 0; j < length; j++) {
                sum[i][j + 1] = sum[i][j] + s[idx[j]];
            }
        }
    }
    // k is 0-indexed
    long long kth_ascend_sum(int left, int right, int k) {
        long long ret = 0;
        Val val = 0;
        for (int i = 0; i < bitnum; i++) {
            BitVector &bv = bitvectors[i];
            int count = bv.rank(false, left, right);
            bool dir = k >= count;
            val = val << 1 | (dir ? 1 : 0);
            if (!dir) {
                k -= count;
                ret += sum[i][right] - sum[i][left - 1];
            }
            left = bv.rank(dir, left), right = bv.rank(dir, right);
            if (dir) left += mids[i], right += mids[i];
        }
        return ret;
    }
    long long kth_descend_sum(int left, int right, int k) {
        long long ret = 0;
        Val val = 0;
        for (int i = 0; i < bitnum; i++) {
            BitVector &bv = bitvectors[i];
            int count = bv.rank(true, left, right);
            bool dir = k < count;
            val = val << 1 | (dir ? 1 : 0);
            if (dir) {
                ret += sum[i][right] - sum[i][left - 1];
                k -= count;
            }
            left = bv.rank(dir, left) + mids[i] * dir, right = bv.rank(dir, right) + mids[i] * dir;
        }
        return ret;
    }

    // count i s.t. (l <= i < r) && (v[i] < upper)
    int range_freq(int left, int right, Val upper) {
        int ret = 0;
        for (int i = 0; i < bitnum; i++) {
            BitVector &bv = bitvectors[i];
            Val mask = Val(1) << (bitnum - 1 - i);
            bool dir = (mask & upper) != 0;
            if (dir) ret += bv.rank(false, left, right);
            left = bv.rank(dir, left), right = bv.rank(dir, right);
            if (dir) left += mids[i], right += mids[i];
        }
        return ret;
    }

    // count i s.t. (l <= i < r) && (lower <= v[i] < upper)
    int range_freq(int l, int r, Val lower, Val upper) { return range_freq(l, r, upper) - range_freq(l, r, lower); }

    // max v[i] s.t. (l <= i < r) && (v[i] < upper)
    Val prev_value(int l, int r, Val upper) {
        int cnt = range_freq(l, r, upper);
        return cnt == 0 ? Val(-1) : kth_smallest(l, r, cnt - 1);
    }

    // min v[i] s.t. (l <= i < r) && (lower <= v[i])
    Val next_value(int l, int r, Val lower) {
        int cnt = range_freq(l, r, lower);
        return cnt == r - l ? Val(-1) : kth_smallest(l, r, cnt);
    }
} wm;

template <typename T>
struct CompressedWaveletMatrix {
    typedef size_t Index;
    WaveletMatrix wm;
    Compressor compressor;
    CompressedWaveletMatrix() { wm.init(vector<WaveletMatrix::Val>()); }
    void init(const vector<T> &data) {
        compressor.init();
        for (auto &u : data) {
            compressor.add(u);
        }
        vector<WaveletMatrix::Val> ndata;
        compressor.run();
        for (auto &u : data) {
            ndata.push_back(compressor.compress(u));
        }
        wm.init(ndata);
    }
    T access(Index pos) { return compressor.values[wm.access(pos)]; }
    T kth_smallest(int left, int right, int k) { return compressor.values[wm.kth_smallest(left, right, k)]; }

    T kth_biggest(int left, int right, int k) { return compressor.values[wm.kth_biggest(left, right, k)]; }
    int rank_all(T val, int left, int right, int &res_lt, int &res_gt) {
        WaveletMatrix::Val p = compressor.greaterThanOrEqual(val);
        return wm.rank_all(p, left, right, res_lt, res_gt);
    }
    template <typename I>
    void build_sum(const vector<T> &data, const vector<I> &s) {
        wm.build_sum(data, s);
    }
    long long kth_ascend_sum(int left, int right, int k) { return wm.kth_ascend_sum(left, right, k); }
    long long kth_descend_sum(int left, int right, int k) { return wm.kth_descend_sum(left, right, k); }
    int range_freq(int l, int r, T upper) { return wm.range_freq(l, r, compressor.greaterThanOrEqual(upper)); }
    int range_freq(int l, int r, T upper, T lower) { return wm.range_freq(l, r, compressor.greaterThanOrEqual(lower), compressor.greaterThanOrEqual(lower)); }
    T prev_value(int l, int r, T upper) {
        auto ret = wm.prev_value(l, r, compressor.greaterThanOrEqual(upper));
        return ret == -1 ? T(-1) : compressor.decompress(ret);
    }
    T next_value(int l, int r, T lower) {
        auto ret = wm.next_value(l, r, compressor.greaterThanOrEqual(lower));
        return ret == -1 ? T(-1) : compressor.decompress(ret);
    }
};
CompressedWaveletMatrix<ll> cwm;

const int N_CSUM = 2005;
template <typename T>
struct CSUM2D {
    T sum[N_CSUM][N_CSUM];
    int n, m;
    void init(int _n, int _m) {
        // MAKE SURE TO UPDATE N_SUM
        n = _n;
        m = _m;
        for (int i = 0; i <= n + 1; i++) {
            for (int j = 0; j <= m + 1; j++) {
                sum[i][j] = 0;
            }
        }
    }
    void setPoint(int x, int y, T v) {
        // use 1 based indices
        sum[x][y] += v;
    }

    void setRectangle(int x1, int y1, int x2, int y2, T v) {
        // use 1 based indices
        sum[x1][y1] += v;
        sum[x2 + 1][y1] -= v;
        sum[x1][y2 + 1] -= v;
        sum[x2 + 1][y2 + 1] += v;
    }
    void run() {
        for (int i = 1; i <= n; i++) {
            for (int j = 1; j <= m; j++) {
                sum[i][j] += sum[i - 1][j] + sum[i][j - 1] - sum[i - 1][j - 1];
            }
        }
    }

    T getPrefix(int x, int y) {
        // use 1 based indices
        return sum[x][y];
    }
    T getRectange(int x1, int y1, int x2, int y2) {
        // use 1 based indices
        return sum[x2][y2] + sum[x1 - 1][y1 - 1] - sum[x2][y1 - 1] - sum[x1 - 1][y2];
    }
};
CSUM2D<int> csum2d;

struct custom_hash {
    static uint64_t splitmix64(uint64_t x) {
        // http://xorshift.di.unimi.it/splitmix64.c
        x += 0x9e3779b97f4a7c15;
        x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
        x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
        return x ^ (x >> 31);
    }

    size_t operator()(uint64_t x) const {
        static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
        return splitmix64(x + FIXED_RANDOM);
    }
};

const int MAXRT = N * 30;
template <typename T>
class DynSegTree {
   public:
    T vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    T defalt_value = 0;

    void init() { ndcnt = 0; }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    T mrg(T u, T v) { return (u + v); }

    T getval(int u) {
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

    void apply(int old_idx, int new_idx, T v) { vals[new_idx] = mrg(v, getval(old_idx)); }

    template <typename... M>
    int modify(int cur, int p, int l, int r, bool inplace, const M &...v) {
        if (l == r) {
            int idx = cur;
            if (cur == -1 || !inplace) {
                idx = addnode();
            }
            apply(cur, idx, v...);
            return idx;
        }
        int md = l + (r - l) / 2;
        int idx = cur;
        if (cur == -1 || !inplace) {
            idx = addnode();
        }
        if (p <= md) {
            lch[idx] = modify(left(cur), p, l, md, inplace, v...);
            rch[idx] = right(cur);
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), p, md + 1, r, inplace, v...);
        }
        pull_up(idx);
        return idx;
    }

    int firstOnCondition(int nd, int qs, int qe, int l, int r, function<bool(int)> ch) {
        if (qs > r || qe < l) return -1;
        if (qs <= l && qe >= r) {
            if (ch(getval(nd))) {
                return -1;
            }
        }
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int x = firstOnCondition(left(nd), qs, qe, l, md, ch);
        if (x == -1) {
            return firstOnCondition(right(nd), qs, qe, md + 1, r, ch);
        }
        return x;
    }

    T query(int nd, int qs, int qe, int l, int r) {
        if (qs <= l && qe >= r) {
            return getval(nd);
        }
        int md = l + (r - l) / 2;
        if (qe <= md) {
            return query(left(nd), qs, qe, l, md);
        } else {
            if (qs > md) {
                return query(right(nd), qs, qe, md + 1, r);
            } else {
                return mrg(query(left(nd), qs, qe, l, md), query(right(nd), qs, qe, md + 1, r));
            }
        }
    }
};

template <typename T>
class FenwickTree2D {
   public:
    vector<vector<T>> tree;
    int n;
    int m;
    void init(int n, int m) {
        tree.assign(n + 2, vector<T>(m + 2, 0));
        this->n = n;
        this->m = m;
    }
    T mrg(T &x, T &y) { return x + y; }

    void upd(int x, int y, T v) {
        for (; x <= n; x += (x) & (-x)) {
            for (int z = y; z <= m; z += (z) & (-z)) {
                tree[x][z] = mrg(tree[x][z], v);
            }
        }
    }

    T getprefix(int x, int y) {
        if (x <= 0) return 0;
        T rs = 0;
        for (; x; x -= (x) & (-x)) {
            for (int z = y; z; z -= (z) & (-z)) {
                rs = mrg(rs, tree[x][z]);
            }
        }
        return rs;
    }
    T getsquare(int xl, int xr, int yl, int yr) { return getprefix(xr, yr) + getprefix(xl - 1, yl - 1) - getprefix(xr, yl - 1) - getprefix(xl - 1, yr); }
};

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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }
typedef struct item *pitem;

int get_cnt(pitem &nd);
struct item {
    int prior, value, cnt;
    bool has_lazy;
    pitem l, r;
    item(int value, int prior) : value(value), prior(prior), cnt(1), has_lazy(0), l(NULL), r(NULL) {}
    void pull() { cnt = 1 + get_cnt(l) + get_cnt(r); }
    void apply() {}
    void apply(int val) {
        if (val) {
            swap(l, r);
        }
        has_lazy = 1;
        // update the lazy values to push
    }
    void push() {
        if (has_lazy) {
            // define here the values to push
            if (l) l->apply();
            if (r) r->apply();
            // clear here the values you pushed
            has_lazy = 0;
        }
    }
};

int get_cnt(pitem &nd) { return nd ? nd->cnt : 0; }

template <typename T>
class Treap {
   public:
    pitem root = NULL;
    void init() { clear(root); }

    void clear(pitem &p) {
        if (!p) return;
        clear(p->l);
        clear(p->r);
        delete p;
    }
    int size() { return get_cnt(root); }
    void push(pitem &p) {
        if (p) p->push();
    }

    void pull(pitem &p) {
        if (p) p->pull();
    }
    void split(pitem t, T key, pitem &l, pitem &r, int add = 0) {
        if (!t) return void(l = r = NULL);
        push(t);
        int cur_key = add + get_cnt(t->l);
        if (cur_key < key) {
            split(t->r, key, t->r, r, add + 1 + get_cnt(t->l));
            l = t;
        } else
            split(t->l, key, l, t->l, add), r = t;
        pull(l);
        pull(r);
    }

    pitem insert_with_return(int idx, T value) {
        int prior = myRand(1e9);
        pitem it = new item(value, prior);
        insert(root, it, idx);
        return it;
    }

    void push_back(int value) {
        int prior = myRand(1e9);
        pitem it = new item(value, prior);
        mrg(root, root, it);
    }
    void insert(int idx, T value) {
        int prior = myRand(1e9);
        pitem it = new item(value, prior);
        insert(root, it, idx);
    }

    void insert(pitem &t, pitem it, int idx) {
        pitem t1, t2;
        split(root, idx, t1, t2);
        mrg(t1, t1, it);
        mrg(root, t1, t2);
    }

    void erase(int idx) { erase(root, idx); }
    void erase(pitem &t, int idx) {
        pitem t1, t2, t3;
        split(root, idx, t1, t2);
        split(t2, 1, t2, t3);
        mrg(root, t1, t3);
    }

    void mrg(pitem &t, pitem l, pitem r) {
        push(l);
        push(r);
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            mrg(l->r, l->r, r), t = l;
        else
            mrg(r->l, l, r->l), t = r;
        pull(t);
    }

    void erase_range(T a, T b) {
        pitem t1, t2, t3;
        split(root, b + 1, t2, t3);
        split(t2, a, t1, t2);
        mrg(root, t1, t3);
    }

    int query(T a, T b) {
        pitem t1, t2, t3;
        split(root, b + 1, t2, t3);
        split(t2, a, t1, t2);
        // define here the query operation
        mrg(root, t1, t2);
        mrg(root, root, t3);
        // return here the value of the query
        return 0;
    }

    template <typename... M>
    void upd(T a, T b, const M &...v) {
        pitem t1, t2, t3;
        split(root, b + 1, t2, t3);
        split(t2, a, t1, t2);
        // define here the update operation
        t2->apply(v...);
        mrg(root, t1, t2);
        mrg(root, root, t3);
    }

    void replace(int idx, T value) {
        erase(idx);
        insert(idx, value);
    }

    void shif_k_left(int a, int b, int k) {
        if (a > b) swap(a, b);
        int sz = b - a + 1;
        k %= sz;
        if (!k) return;
        pitem t1, t2, t3, t4;
        split(root, b + 1, t2, t4);
        split(t2, a, t1, t2);
        split(t2, k, t2, t3);
        mrg(root, t1, t3);
        mrg(root, root, t2);
        mrg(root, root, t4);
    }

    void shif_k_right(int a, int b, int k) {
        if (a > b) swap(a, b);
        int sz = b - a + 1;
        k %= sz;
        shif_k_left(a, b, sz - k);
    }

    void swap_positions(int a, int b) {
        if (i == j) return;
        if (a > b) swap(a, b);
        pitem t1, t2, t3, t4, t5;
        split(root, b + 1, t2, t5);
        split(t2, a, t1, t2);
        split(t2, 1, t2, t3);
        split(t3, b - a - 1, t3, t4);
        mrg(root, t1, t2);
        mrg(root, root, t3);
        mrg(root, root, t4);
        mrg(root, root, t5);
    }

    void show() { show(root); }
    void show(pitem &p) {
        push(p);
        if (!p) return;
        show(p->l);
        cout << p->value << " ";
        show(p->r);
    }
};
Treap<int> treap;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }
typedef struct item *pitem;

int get_cnt(pitem &nd);
struct item {
    int prior, key, cnt, freq;
    pitem l, r;
    item(int key, int prior, int freq = 1) : key(key), prior(prior), freq(freq), cnt(freq), l(NULL), r(NULL) {}
    void pull() { cnt = freq + get_cnt(l) + get_cnt(r); }
};

int get_cnt(pitem &nd) { return nd ? nd->cnt : 0; }

template <typename T>
class Treap {
   public:
    pitem root = NULL;
    void init() { clear(root); }

    // Clear the whole treap : erase all items
    void clear(pitem &p) {
        if (!p) return;
        clear(p->l);
        clear(p->r);
        delete p;
    }
    // size of the treap
    int size() { return get_cnt(root); }

    // split the treap into 2 treap where treap l have all valus <= key
    // and treap r have all values > key
    void split(pitem t, T key, pitem &l, pitem &r) {
        if (!t)
            l = r = NULL;
        else if (t->key <= key)
            split(t->r, key, t->r, r), l = t;
        else
            split(t->l, key, l, t->l), r = t;
        if (l) l->pull();
        if (r) r->pull();
    }

    // insert key and return the node of that key
    pitem insert_with_return(T key, int freq = 1) {
        int prior = myRand(1e9);
        pitem it = new item(key, prior, freq);
        insert(root, it);
        return it;
    }

    // insert key
    void insert(T key, int freq = 1) {
        int prior = myRand(1e9);
        pitem it = new item(key, prior, freq);
        insert(root, it);
    }

    void insert(pitem &t, pitem it) {
        if (!t)
            t = it;
        else if (it->prior > t->prior)
            split(t, it->key, it->l, it->r), t = it;
        else
            insert(t->key <= it->key ? t->r : t->l, it);
        if (t) t->pull();
    }

    // mrg 2 treaps such that all values in l < all values in r
    void mrg(pitem &t, pitem l, pitem r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            mrg(l->r, l->r, r), t = l;
        else
            mrg(r->l, l, r->l), t = r;
        if (t) t->pull();
    }

    // remove freq key items from the treap
    void erase(T key, int freq) { erase(root, key, freq); }
    void erase(pitem &t, T key, int freq) {
        if (!t) return;
        if (t->key == key) {
            pitem th = t;
            t->freq -= freq;
            t->cnt -= freq;
            if (t->freq > 0) return;
            mrg(t, t->l, t->r);
            delete th;
        } else
            erase(key < t->key ? t->l : t->r, key);
        if (t) t->pull();
    }
    // remove all frequencies of key in the treap
    void erase_all_freq(T key) { erase_all_freq(root, key); }
    void erase_all_freq(pitem &t, T key) { erase_range(key, key); }

    // remove range of values from the treap between a and b
    void erase_range(T a, T b) {
        if (a > b) swap(a, b);
        pitem t1, t2, t3;
        split(root, a - 1, t1, t2);
        split(t2, b, t2, t3);
        clear(t2);
        mrg(root, t1, t3);
    }

    // union of 2 treaps
    pitem unite(pitem l, pitem r) {
        if (!l || !r) return l ? l : r;
        if (l->prior < r->prior) swap(l, r);
        pitem lt, rt;
        split(r, l->key, lt, rt);
        l->l = unite(l->l, lt);
        l->r = unite(l->r, rt);
        l->pull();
        return l;
    }

    // check if an element exists or not
    bool has(T key) { return has(root, key); }
    bool has(pitem &t, T key) {
        if (!t) return 0;
        if (t->key == key) return 1;
        if (t->key < key) {
            return has(t->r, key);
        }
        return has(t->l, key);
    }

    // count the number of elements in the range [a,b]
    int count_range(T a, T b) {
        if (a > b) swap(a, b);
        pitem t1, t2, t3;
        split(root, a - 1, t1, t2);
        split(t2, b, t2, t3);
        int sz = t2->cnt;
        mrg(root, t1, t2);
        mrg(root, root, t3);
        return sz;
    }
    // count the frequency of key
    int count(T key) { return count_range(key, key); }

    // return the lowest element >= key
    T lower_bound(T key) { return lower_bound(root, key); }
    T lower_bound(pitem &t, T key) {
        if (!t) return numeric_limits<T>::max();
        if (t->key >= key) {
            return min(t->key, lower_bound(t->l, key));
        } else {
            return lower_bound(t->r, key);
        }
    }

    // return the highest element <= key
    T r_lower_bound(T key) { return r_lower_bound(root, key); }
    T r_lower_bound(pitem &t, T key) {
        if (!t) return numeric_limits<T>::min();
        if (t->key <= key) {
            return max(t->key, r_lower_bound(t->r, key));
        } else {
            return r_lower_bound(t->l, key);
        }
    }
    // return the first value after key != key
    T next_value(T key) { return lower_bound(key + 1); }
    // return the first value before key != key
    T prev_value(T key) { return r_lower_bound(root, key - 1); }

    // return the value at index idx
    T get_value_at_idx(int idx) { return get_value_at_idx(root, idx); }
    T get_value_at_idx(pitem &t, int idx) {
        if (!t) return numeric_limits<T>::max();
        int lsz = get_cnt(t->l);
        if (idx >= lsz && idx < lsz + t->freq) return t->key;
        if (idx < lsz) return get_value_at_idx(t->l, idx);
        return get_value_at_idx(t->r, idx - lsz - t->freq);
    }

    // return the number of items < key
    int count_less_than(T key) { return count_less_than(root, key); }
    int count_less_than(pitem &t, T key) {
        if (!t) return 0;
        if (t->key < key) {
            return get_cnt(t->l) + t->freq + count_less_than(t->r, key);
        }
        return count_less_than(t->l, key);
    }
};
Treap<int> treap;

const int MAX_UPPER_BOUND = N;
struct IntervalSet {
    set<int> intervals;
    int nxt[MAX_UPPER_BOUND];
    int val[MAX_UPPER_BOUND];
    IntervalSet() {}
    void init() {
        intervals.clear();
        // clear some data structure if you have
    }

    void updateRange(int l, int r, int x) {
        // update x with the corerect type/number of params
        set<int>::iterator it;
        it = intervals.lower_bound(l);
        if (it != intervals.begin()) it--;
        vector<int> to_rem;
        vector<int> to_add;
        while (it != intervals.end()) {
            int a = *it;
            int b = nxt[a];
            if (a > r) break;
            if (a < l && b < l) {
                it++;
                continue;
            }
            if (a < l) {
                // remove range a, nxt[a];
                nxt[a] = l - 1;
                // add range a, nxt[a];
            } else {
                // remove range a, nxt[a]
                to_rem.pb(a);
            }
            if (b > r) {
                to_add.pb(r + 1);
                val[r + 1] = val[a];
                nxt[r + 1] = b;
                // add range r+1, nxt[r+1]=b
            }
            it++;
        }
        nxt[l] = r;
        val[l] = x;
        // add range l, nxt[l]=r
        for (auto &u : to_rem) {
            assert(intervals.count(u));
            intervals.erase(u);
        }
        for (auto &u : to_add) {
            intervals.insert(u);
        }
        intervals.insert(l);
    }
};

const int MAXND_LI_CHAO = N * 40;

typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) { return (conj(a) * b).x(); }

ftype f(point a, ftype x) { return dot(a, {x, 1}); }

struct LiChaoTree {
    point vals[MAXND_LI_CHAO];
    point initial_pt = {0, (long long)1e18};
    int lch[MAXND_LI_CHAO], rch[MAXND_LI_CHAO], ndcnt = 0;
    ftype lb, ub;
    int init(ftype _lb, ftype _ub) {
        lb = _lb;
        ub = _ub;
        ndcnt = 0;
        return addnode();
    }
    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }
    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = initial_pt;
        return ndcnt++;
    }
    int addnode(int p) {
        int np = addnode();
        if (p != -1) vals[np] = vals[p];
        return np;
    }

    int modify(int cur, int l, int r, point nw) {
        if (cur == -1) {
            int idx = addnode();
            vals[idx] = nw;
            return idx;
        }
        int idx = addnode(cur);
        int md = (l + r) / 2;
        bool lef = f(nw, l) < f(vals[idx], l);
        bool mid = f(nw, md) < f(vals[idx], md);
        if (mid) {
            swap(vals[idx], nw);
        }
        if (r - l == 1) {
            return idx;
        } else if (lef != mid) {
            lch[idx] = modify(left(cur), l, md, nw);
            rch[idx] = right(cur);
            return idx;
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), md, r, nw);
            return idx;
        }
    }
    ftype query(int nd, ftype x, int l, int r) {
        if (nd == -1) {
            return f(initial_pt, x);
        }
        int md = (l + r) / 2;
        if (r - l + 1 == 1) {
            return f(vals[nd], x);
        } else if (x < md) {
            return min(f(vals[nd], x), query(left(nd), x, l, md));
        } else {
            return min(f(vals[nd], x), query(right(nd), x, md, r));
        }
    }

    int modify(int cur, point nw) { return modify(cur, lb, ub, nw); }

    ftype query(int nd, ftype x) { return query(nd, x, lb, ub); }
} lichao;

// should be increasing in x
//  to minimize answer
typedef int ftype;
typedef complex<ftype> point;
#define x real
#define y imag

ftype dot(point a, point b) {
    return (conj(a) * b).x();
}

ftype cross(point a, point b) {
    return (conj(a) * b).y();
}


vector<point> hull, vecs;

void add_line(ftype k, ftype b) {
    point nw = {k, b};
    while(!vecs.empty() && dot(vecs.back(), nw - hull.back()) < 0) {
        hull.pop_back();
        vecs.pop_back();
    }
    if(!hull.empty()) {
        vecs.push_back(1i * (nw - hull.back()));
    }
    hull.push_back(nw);
}

int get(ftype x) {
    point query = {x, 1};
    auto it = lower_bound(vecs.begin(), vecs.end(), query, [](point a, point b) {
        return cross(a, b) > 0;
    });
    return dot(query, hull[it - vecs.begin()]);
}

template <typename node>
struct SegTree {
    vector<node> tree;
    vector<node> lazy;
    int n;

    void apply(int id, int ns, int ne, int v) {
        // define apply operation here
    }
    node mrg(const node &l, const node &r) {
        node res;
        // merge nodes
        return res;
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

const double EPS = 1e-9;

struct pt {
    double x, y;
};

struct seg {
    pt p, q;
    int id;

    double get_y(double x) const {
        if (abs(p.x - q.x) < EPS) return p.y;
        return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};

bool intersect1d(double l1, double r1, double l2, double r2) {
    if (l1 > r1) swap(l1, r1);
    if (l2 > r2) swap(l2, r2);
    return max(l1, l2) <= min(r1, r2) + EPS;
}

int vec(const pt &a, const pt &b, const pt &c) {
    double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    return abs(s) < EPS ? 0 : s > 0 ? +1 : -1;
}

bool intersect(const seg &a, const seg &b) { return intersect1d(a.p.x, a.q.x, b.p.x, b.q.x) && intersect1d(a.p.y, a.q.y, b.p.y, b.q.y) && vec(a.p, a.q, b.p) * vec(a.p, a.q, b.q) <= 0 && vec(b.p, b.q, a.p) * vec(b.p, b.q, a.q) <= 0; }

bool operator<(const seg &a, const seg &b) {
    double x = max(min(a.p.x, a.q.x), min(b.p.x, b.q.x));
    double ya = a.get_y(x);
    double yb = b.get_y(x);
    if (abs(ya - yb) < EPS) {
        return a.id < b.id;
    } else {
        return (a.id != b.id) && ya < yb - EPS;
    }
}

struct event {
    double x;
    int tp, id;

    event() {}
    event(double x, int tp, int id) : x(x), tp(tp), id(id) {}

    bool operator<(const event &e) const {
        if (abs(x - e.x) > EPS) return x < e.x;
        return tp > e.tp;
    }
};
struct LineSweep {
    set<seg> s;
    vector<set<seg>::iterator> where;

    set<seg>::iterator prev(set<seg>::iterator it) { return it == s.begin() ? s.end() : --it; }

    set<seg>::iterator next(set<seg>::iterator it) { return ++it; }

    bool add_intersection(int x, int y) {
        // apply intersection operation here
        return false;
    }

    void solve(const vector<seg> &a, bool first_intersection = false) {
        /*
            vector<seg> a : is a vector of all the segments
            first_intersection : if True it will stop the algorithm on the first found intersection
        */
        vector<event> e;
        for (int i = 0; i < a.size(); ++i) {
            e.push_back(event(min(a[i].p.x, a[i].q.x), +1, i));
            e.push_back(event(max(a[i].p.x, a[i].q.x), -1, i));
        }
        sort(e.begin(), e.end());

        s.clear();
        where.resize(a.size());
        for (size_t i = 0; i < e.size(); ++i) {
            int id = e[i].id;
            if (e[i].tp == +1) {
                set<seg>::iterator nxt = s.lower_bound(a[id]), prv = prev(nxt);
                if (nxt != s.end() && intersect(*nxt, a[id]))
                    if (add_intersection(nxt->id, a[id].id) && first_intersection) return;
                if (prv != s.end() && intersect(*prv, a[id]))
                    if (add_intersection(prv->id, a[id].id) && first_intersection) return;
                where[id] = s.insert(nxt, a[id]);
            } else {
                set<seg>::iterator nxt = next(where[id]), prv = prev(where[id]);
                if (nxt != s.end() && prv != s.end() && intersect(*nxt, *prv))
                    if (add_intersection(prv->id, nxt->id) && first_intersection) return;
                s.erase(where[id]);
            }
        }
        return;
    }
} lsp;

template <class T>
struct MonoStack {
    stack<pair<T, T>> st;
    void push(T val) {
        if (st.empty())
            st.emplace(val, val);
        else
            st.emplace(val, std::max(val, st.top().second));
    }
    void pop() { st.pop(); }
    T max() { return st.top().second; }
    T top() { return st.top().first; }
    int size() { return st.size(); }
    bool empty() { return st.empty(); }

    void clear() {
        while (!st.empty()) st.pop();
    }
};

template <class T>
struct MonoQueue {
    MonoStack<T> push_st, pop_st;

    void push(T val) { push_st.push(val); }

    void move() {
        if (!pop_st.empty()) return;
        while (!push_st.empty()) {
            pop_st.push(push_st.top());
            push_st.pop();
        }
    }
    void pop() {
        move();
        pop_st.pop();
    }
    T max() {
        if (push_st.empty()) return pop_st.max();
        if (pop_st.empty()) return push_st.max();
        return std::max(push_st.max(), pop_st.max());
    }
    T front() {
        move();
        return pop_st.top();
    }
    int size() { return push_st.size() + pop_st.size(); }
    bool empty() { return push_st.empty() && pop_st.empty(); }
    void clear() {
        push_st.clear();
        pop_st.clear();
    }
};

template <typename T>
struct MovingMedian {
    set<T> inf, sup;

    void init() {
        inf.clear();
        sup.clear();
    }
    void add(T x) {
        inf.insert(-x);
        while (inf.size() && sup.size() && (-*inf.begin()) > (*sup.begin())) {
            T x = -*inf.begin();
            inf.erase(inf.begin());
            sup.insert(x);
        }
        while (inf.size() && inf.size() - sup.size() >= 2) {
            T x = -*inf.begin();
            inf.erase(inf.begin());
            sup.insert(x);
        }
        while (sup.size() && sup.size() - inf.size() >= 2) {
            T x = *sup.begin();
            sup.erase(sup.begin());
            inf.insert(-x);
        }
    }
    T getMedian() { return -*(inf.begin()); }
}

template <typename T>
class OrderedMultiSet {
   public:
    BSFenwickTree<T> ft;
    int len = 0;
    void init(int n) {
        ft.init(n);
        ft.upd(0, -1);
        len = 0;
    }
    void insert(int u) { ft.upd(u, 1), len++; }
    void erase(int u) { ft.upd(u, -1), len--; }
    int getByIdx(int u) { return ft.lower_bound(u); }
    void eraseByIdx(int idx) { erase(getByIdx(idx)); }
    int size() { return len; }
    bool empty() { return len == 0; };
};

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }

struct node {
    // define states here
    bool has_lazy;
    int lazy = 0;
    node() {
        // initialize states here
        has_lazy = false;
        lazy = 0;
    }

    void apply(int ns, int ne, int v) {
        // update value

        // update lazy
        has_lazy = 0;
    }
    void clear_lazy() {
        has_lazy = 0;
        lazy = 0;
    }
};

struct SegTree {
    vector<node> tree;
    int n;
    node mrg(const node &l, const node &r) {
        node res;
        // merge nodes
        return res;
    }
    void pull(int id, int ns, int ne) {
        int l = 2 * id + 1;
        int r = l + 1;
        tree[id] = mrg(tree[l], tree[r]);
    }

    void push(int id, int ns, int ne) {
        if (tree[id].has_lazy && ns != ne) {
            int l = 2 * id + 1;
            int r = l + 1;
            int md = ns + (ne - ns) / 2;
            tree[l].apply(ns, md, tree[id].lazy);
            tree[r].apply(md + 1, ne, tree[id].lazy);
            tree[id].clear_lazy();
        }
    }
    template <typename M>
    void build(int id, int ns, int ne, const vector<M> &v) {
        if (ns == ne) {
            tree[id].apply(ns, ne, v[ns]);
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
            tree[id].apply(ns, ne, v...);
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
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }
    template <typename M>
    SegTree(const vector<M> &v) {
        n = v.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }
    node get(int qs, int qe) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        return query(qs, qe, 0, 0, n - 1);
    }

    node get(int p) {
        assert(p >= 0 && p <= n - 1);
        return query(p, p, 0, 0, n - 1);
    }
    template <typename... M>
    int getFirstOnCondition(int qs, int qe, int dir, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1 && dir >= 0 && dir <= 1);
        return getFirstOnCondition(qs, qe, dir, 0, 0, n - 1, v...);
    }
    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        update(qs, qe, 0, 0, n - 1, v...);
    }
};

const int LOGSPT = 17;
template <typename T>
class SPT {
   public:
    vector<T> spt[LOGSPT];
    int po[LOGSPT];
    vector<int> lg;
    int n;

    T mrg(T &x, T &y) { return min(x, y); }

    void init(vector<T> &v) {
        n = v.size();
        lg.assign(n + 1, 0);
        po[0] = 1;
        for (int i = 0; i < LOGSPT; i++) {
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
                spt[b][i] = mrg(spt[b - 1][i], spt[b - 1][i + po[b - 1]]);
            }
        }
    }
    T getLog(int l, int r) {
        int d = r - l + 1;
        T rs = 1e9;
        for (int i = LOGSPT - 1; i >= 0; i--) {
            if (po[i] <= d) {
                rs = mrg(rs, spt[i][l]);
                d -= po[i];
                l += po[i];
            }
        }
        return rs;
    }

    T get(int l, int r) {
        int lg2 = lg[r - l + 1];
        return mrg(spt[lg2][l], spt[lg2][r - po[lg2] + 1]);
    }
};
SPT<ll> spt;

struct SQRTDecomposition {
    int sq;
    int n;
    void init(int _n) {
        n = _n;
        sq = sqrt(n);
    }
    void build(int l, int r) {
        int bl = l / sq;
        int br = r / sq;
        for (int i = bl; i <= br; i++) {
            // clear data
        }
        for (int i = l; i <= r; i++) {
            int bi = i / sq;
            // update the value
        }
    }

    inline int bstart(int bi) { return bi * sq; }
    inline int bend(int bi) { return min(n - 1, (bi + 1) * sq); }

    void unlazy(int bi) {
        // bi : block index
        // apply stored changes to the block
        int l = bstart(bi);
        int r = bend(bi);
        // for (int i = l; i <= r; i++) {
        // }
    }

    void updateIterative(int l, int r, int v) {
        // update the parameters here and apply change for each position
        int bi = l / sq;
        unlazy(bi);  // apply stored changes
                     // for (int i = l; i <= r; i++) {
                     // }

        // build the block
        l = bstart(bi);
        r = bend(bi);
        build(l, r);
    }
    void updateBlock(int bi, int v) {
        // update the parameters here and store the changes for the block
    }

    template <typename... M>
    void updateRange(int l, int r, const M &...v) {
        int bl = l / sq;
        int br = r / sq;
        if (bl == br) {
            updateIterative(l, r, v...);
        } else {
            updateIterative(l, (bl + 1) * sq - 1, v...);
            for (int i = bl + 1; i < br; i++) {
                updateBlock(i, v...);
            }
            updateIterative(br * sq, r, v...);
        }
    }

    // !!!  ATTENTION to the return type and type of ans in query function  !!!

    int queryIterative(int l, int r, int v) {
        // query the full range l to r
        // for (int i = l; i <= r; i++) {
        // }
    }
    int queryBlock(int bi, int v) {
        // query the block bi
    }

    int mrg(int l, int r) {
        // apply merge operation here
    }

    template <typename... M>
    int query(int l, int rn, const M &...v) {
        int bl = l / sq;
        int br = r / sq;
        int ans = 0;
        if (bl == br) {
            ans = queryIterative(l, r, v...);
        } else {
            ans = queryIterative(l, (bl + 1) * sq - 1, v...);
            for (int i = bl + 1; i < br; i++) {
                ans = mrg(ans, queryBlock(i, v...));
            }
            ans = mrg(ans, queryIterative(br * sq, r, v...));
        }
        return ans;
    }
} sqde;

//  Persistent segment tree
merge(seg[l].begin(), seg[l].end(), seg[r].begin(), seg[r].end(), inserter(seg[ind], seg[ind].begin()));



//  String Mtaylor


const int MAX_AHO = N;
const int ALPHA = 128;

class AhoCorasick {
   public:
    int trie[MAX_AHO][ALPHA], ndcnt, szs[MAX_AHO], F[MAX_AHO], ids[MAX_AHO],
        nxtId[MAX_AHO];
    char children[MAX_AHO][ALPHA];
    int addnode() {
        memset(trie[ndcnt], -1, sizeof(trie[ndcnt]));
        ids[ndcnt] = -1;
        szs[ndcnt] = 0;
        return ndcnt++;
    }

    void init() {
        ndcnt = 0;
        addnode();
    }
    int getNext(int f, char c) {
        while (trie[f][c] == -1) f = F[f];
        f = trie[f][c];
        return f;
    }

    void buildFail() {
        queue<int> q;
        for (int i = 0; i < ALPHA; i++) {
            int &r = trie[0][i];
            if (~r) {
                F[r] = 0;
                nxtId[r] = 0;
                q.push(r);
            } else {
                r = 0;
            }
        }

        while (q.size()) {
            int cur = q.front();
            q.pop();
            for (int i = 0; i < szs[cur]; i++) {
                char c = children[cur][i];
                int f = F[cur];
                int &nxt = trie[cur][c];
                nxtId[nxt] = F[nxt] = getNext(f, c);
                q.push(nxt);
            }
        }
    }

    int insert(string &str, int id) {
        int cur;
        int i = 0;
        for (cur = 0, i = 0; i < str.size(); i++) {
            int &nxt = trie[cur][str[i]];
            if (nxt == -1) {
                nxt = addnode();
                children[cur][szs[cur]++] = str[i];
            }
            cur = nxt;
        }
        if (ids[cur] == -1) {
            ids[cur] = id;
        }
        return ids[cur];
    }
    int getNxtId(int cur) {
        if (cur == 0) return 0;
        int &nxt = nxtId[cur];
        if (ids[nxt] != -1) {
            return nxt;
        }
        return nxt = getNxtId(nxt);
    }
    bool hasSuffixString(int cur) {
        return ids[cur] != -1 || ids[getNxtId(cur)] != -1;
    }

    vector<vector<int> > match(string str, int cnt) {
        vector<vector<int> > v(cnt);
        for (int cur = 0, i = 0; i < str.size(); i++) {
            cur = getNext(cur, str[i]);
            for (int j = cur; j; j = getNxtId(j)) {
                if (ids[j] != -1) {
                    v[ids[j]].pb(i);
                }
            }
        }
        return v;
    }
} aho;

struct KMP {
    int F[KMP_N];

    int getNextLen(int len, char c, string &pat) {
        while (len && pat[len] != c) len = F[len - 1];
        if (pat[len] == c) len++;
        return len;
    }
    void run(string &pat) {
        F[0] = 0;
        for (int i = 1; i < pat.size(); i++) {
            F[i] = getNextLen(F[i - 1], pat[i], pat);
        }
    }

    void match(string &s, string &pat) {
        int len = 0;
        for (int i = 0; i < s.size(); i++) {
            len = getNextLen(len, s[i], pat);
            if (!pat[len]) printf("%d\n", i - len + 1);
        }
    }
} kmp;

const int MAX_PAL_TREE = N;
struct PalindromicTree {
    map<char, int> child[MAX_PAL_TREE];
    int ndcnt = 0, pos[MAX_PAL_TREE], fail[MAX_PAL_TREE], len[MAX_PAL_TREE];
    int lst;
    int add_node(int p, int l) {
        pos[ndcnt] = p;
        child[ndcnt].clear();
        len[ndcnt] = l;
        return ndcnt++;
    }
    void init() {
        ndcnt = 0;
        lst = 1;
        fail[1] = 0;
        add_node(-2, -1);
        add_node(-1, 0);
    }
    void add_edg(int f, int t, char c) {
        child[f][c] = t;
    }

    int get_fail(int u, int idx, string &s) {
        char c = s[idx];
        while (1) {
            int m = idx - len[u] - 1;
            if (m >= 0 && c == s[m]) break;
            u = fail[u];
        }
        return u;
    }
    void add_char(int idx, string &s) {
        int u = get_fail(lst, idx, s);
        auto c = s[idx];
        int &v = child[u].emplace(c, -1).first->second;
        if (~v) {
            lst = v;
            return;
        }
        lst = v = add_node(idx, len[u] + 2);
        add_edg(u, v, c);
        if (u == 0) {
            fail[v] = 1;
            return;
        }
        u = get_fail(fail[u], idx, s);
        fail[v] = child[u][c];
    }

    void insert_string(string &s) {
        for (int i = 0; i < s.size(); i++) {
            add_char(i, s);
        }
    }

    int get_longest() {
        return *max_element(eertree.len, eertree.len + eertree.ndcnt);
    }

    int get_distincts() {
        return ndcnt - 2;
    }
} eertree;

const int MAX_SUFF = 3e5 + 5;
const int LOGSPT = 20;
template <typename T>
class SPT {
   public:
    vector<T> spt[LOGSPT];
    int po[LOGSPT];
    vector<int> lg;
    int n;

    T mrg(T &x, T &y) { return min(x, y); }

    void init(vector<T> &v) {
        n = v.size();
        lg.assign(n + 1, 0);
        po[0] = 1;
        for (int i = 0; i < LOGSPT; i++) {
            spt[i].assign(n, 0);
            if (i > 0) po[i] = 2 * po[i - 1];
        }
        lg[0] = -1;
        for (int i = 1; i <= n; i++) {
            lg[i] = 1 + lg[i / 2];
        }
        for (int i = 0; i < n; i++) {
            spt[0][i] = v[i];
        }
        for (int b = 1; po[b] <= n; b++) {
            for (int i = 0; i + po[b] <= n; i++) {
                spt[b][i] = mrg(spt[b - 1][i], spt[b - 1][i + po[b - 1]]);
            }
        }
    }
    T getLog(int l, int r) {
        int d = r - l + 1;
        T rs = 1e9;
        for (int i = LOGSPT - 1; i >= 0; i--) {
            if (po[i] <= d) {
                rs = mrg(rs, spt[i][l]);
                d -= po[i];
                l += po[i];
            }
        }
        return rs;
    }

    T getConstant(int l, int r) {
        int lg2 = lg[r - l + 1];
        return mrg(spt[lg2][l], spt[lg2][r - po[lg2] + 1]);
    }
};

class SuffixArray {
   public:
    int suff[MAX_SUFF], newsuff[MAX_SUFF];
    char s[MAX_SUFF];
    vector<int> lcp;
    int rnk[MAX_SUFF], newrnk[MAX_SUFF], bst[MAX_SUFF], bcnt;
    SPT<int> spt;
    int n;
    void buildSuffixArray() {
        iota(suff, suff + n, 0);
        bcnt = 0;
        sort(suff, suff + n, [this](int &x, int &y) { return s[x] < s[y]; });
        bst[0] = 0;
        rnk[suff[0]] = 0;
        for (int i = 1; i < n; i++) {
            if (s[suff[i]] == s[suff[i - 1]]) {
                rnk[suff[i]] = bcnt;
            } else {
                bcnt++;
                bst[bcnt] = i;
                rnk[suff[i]] = bcnt;
            }
        }

        int cur = 1;
        do {
            auto cmp = [this, cur](int &x, int &y) {
                return mp(rnk[x], rnk[x + cur]) < mp(rnk[y], rnk[y + cur]);
            };
            newsuff[0] = suff[0];
            for (int i = 0; i < n; i++) {
                if (suff[i] - cur >= 0) {
                    int x = suff[i] - cur;
                    newsuff[bst[rnk[x]]++] = x;
                }
            }
            for (int i = 0; i < n; i++) {
                suff[i] = newsuff[i];
            }
            bcnt = 0;
            bst[0] = 0;
            newrnk[suff[0]] = 0;
            for (int i = 1; i < n; i++) {
                if (!cmp(suff[i - 1], suff[i])) {
                    newrnk[suff[i]] = bcnt;
                } else {
                    bcnt++;
                    bst[bcnt] = i;
                    newrnk[suff[i]] = bcnt;
                }
            }
            for (int i = 0; i < n; i++) {
                rnk[i] = newrnk[i];
            }
            cur *= 2;
        } while (bcnt != n - 1);
    }
    void buildLCP() {
        int cur = 0;
        lcp[0] = 0;
        for (int i = 0; i < n - 1; i++) {
            int j = suff[rnk[i] - 1];
            while (s[i + cur] == s[j + cur]) {
                cur++;
            }
            lcp[rnk[i]] = cur;
            if (cur) --cur;
        }
    };
    void init(string &t, bool spt_query = false) {
        for (int i = 0; i < t.size(); i++) {
            s[i] = t[i];
        }
        s[t.size()] = 0;
        n = t.size() + 1;
        memset(rnk, 0, 2 * n * sizeof(rnk[0]));
        lcp.assign(n + 1, 0);
        buildSuffixArray();
        buildLCP();
        if (spt_query) {
            spt.init(lcp);
        }
    }

    int getlcp(int x, int y) {
        int l = rnk[x];
        int r = rnk[y];
        if (l == r) {
            return n - x;
        }
        if (l > r) swap(l, r);
        return spt.getConstant(l + 1, r);
    }

    void print() {
        for (int i = 0; i < n; i++) {
            printf("%s ", s + suff[i]);
            cout << lcp[i] << endl;
        }
    }
} SA;


const int B_TRIE = 2;
const int L_TRIE = 30;  // only for binary trie, L is the maximum bit +1
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

    void ins(string &s, int p = 1, int from = 0, int to = -1) {
        // s is the string to add to the trie
        // p is the index of the string if we want to get it after
        // from is where to start to the string from
        // to is the until when we need to add the string
        int cur = 0;
        if (to == -1) to = sz(s) - 1;
        for (int i = from; i <= to; i++) {
            // To change if the characters change
            int id = s[i] - 'a';
            int &nx = nodes[cur].nxt[id];
            if (nx == -1) {
                nx = addnode();
            }
            nodes[nx].cnt++;
            cur = nx;
        }
        nodes[cur].isEnd = p;
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
} trie;

const int Z_N = N;
struct ZAlgo {
    int Z[Z_N];
    void run(string &s) {
        Z[0] = 0;
        int l = 1, r = 1;
        int n = s.size();
        for (int i = 1; i < n; i++) {
            int x = Z[i - l];
            if (i + x >= r) {
                l = i;
                r = max(r, i);
                while (r < n && s[r - l] == s[r]) r++;
                Z[i] = r - l;
            } else {
                Z[i] = Z[i - l];
            }
        }
    }
} z_algo;


vector<int> manacher_odd(string s) {
    int n = s.size();
    s = "$" + s + "^";
    vector<int> p(n + 2);
    int l = 1, r = 1;
    for(int i = 1; i <= n; i++) {
        p[i] = max(0, min(r - i, p[l + (r - i)]));
        while(s[i - p[i]] == s[i + p[i]]) {
            p[i]++;
        }
        if(i + p[i] > r) {
            l = i - p[i], r = i + p[i];
        }
    }
    return vector<int>(begin(p) + 1, end(p) - 1);
}

vector<int> manacher(string s) {
    string t;
    for(auto c: s) {
        t += string("#") + c;
    }
    auto res = manacher_odd(t + "#");
    return vector<int>(begin(res) + 1, end(res) - 1);
}

// Math

// Don't forget to initialize fft and set up the correct values of M and LOGM
using cd = complex<double>;
const double PI = acos(-1);

const int M = (1 << 20) + 3, LOGM = 20;
int po[LOGM + 2];
void init_fft() {
    for (int i = 0; i < LOGM + 2; i++) {
        po[i] = 1 << i;
    }
}

int reverse(int x, int logn) {
    int ans = 0;
    for (int i = 0; i < logn; i++)
        if (x & po[i]) ans |= po[logn - 1 - i];
    return ans;
}

void fft(cd a[M], int n, bool invert) {
    static cd vv[LOGM][M];
    static bool prepared = false;
    if (!prepared) {
        prepared = true;
        for (int i = 0; i < LOGM; i++) {
            double ang = 2 * PI / (1 << (i + 1));
            for (int j = 0; j < po[i]; j++)
                vv[i][j] = cd(cos(ang * j), sin(ang * j));
        }
    }
    int logn = 0;
    while (po[logn] < n) logn++;
    for (int i = 1, j = 0; i < n; i++) {
        int ni = reverse(i, logn);
        if (i < ni) swap(a[i], a[ni]);
    }
    for (int i = 0; po[i] < n; i++)
        for (int j = 0; j < n; j += po[i + 1])
            for (int k = j; k < j + po[i]; k++) {
                cd cur = invert ? conj(vv[i][k - j]) : vv[i][k - j];
                cd l = a[k], r = cur * a[k + po[i]];
                a[k] = l + r;
                a[k + po[i]] = l - r;
            }
    if (invert)
        for (int i = 0; i < n; i++) a[i] /= double(n);
}

void mul(int result[M], int a[M], int b[M]) {
    static cd fp[M], p1[M], p2[M];
    int n = po[LOGM], m = po[LOGM];
    while (n && !a[n - 1]) n--;
    while (m && !b[m - 1]) m--;
    int cnt = n + m;
    while (cnt & (cnt - 1)) cnt++;
    if (cnt > po[LOGM]) return;

    for (int i = 0; i < cnt; i++) fp[i] = cd(a[i], b[i]);
    fft(fp, cnt, false);
    for (int i = 0; i < cnt; i++) {
        p1[i] = (fp[i] + conj(fp[(cnt - i) % cnt])) / cd(2, 0);
        p2[i] = (fp[i] - conj(fp[(cnt - i) % cnt])) / cd(0, 2);
    }
    for (int i = 0; i < cnt; i++) fp[i] = p1[i] * p2[i];
    fft(fp, cnt, true);

    for (int i = 0; i < cnt; i++) result[i] = int(fp[i].real() + 0.5);
}

void mul(int* a, int* b) { mul(a, b, a); }

void binPow(int* a, int b) {
    static int ans[M];
    for (int i = 0; i < po[LOGM]; i++) ans[i] = !i;

    while (b) {
        if (b & 1) mul(ans, a);
        mul(a, a);
        b >>= 1;
    }

    for (int i = 0; i < po[LOGM]; i++) a[i] = ans[i];
}

using cd = complex<double>;
const double PI = acos(-1);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        for (; j & bit; bit >>= 1) j ^= bit;
        j ^= bit;

        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double ang = 2 * PI / len * (invert ? -1 : 1);
        cd wlen(cos(ang), sin(ang));
        for (int i = 0; i < n; i += len) {
            cd w(1);
            for (int j = 0; j < len / 2; j++) {
                cd u = a[i + j], v = a[i + j + len / 2] * w;
                a[i + j] = u + v;
                a[i + j + len / 2] = u - v;
                w *= wlen;
            }
        }
    }

    if (invert) {
        for (cd& x : a) x /= n;
    }
}
vector<int> multiply(vector<int> const& a, vector<int> const& b) {
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size()) n <<= 1;
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<int> result(n);
    for (int i = 0; i < n; i++) result[i] = round(fa[i].real());
    return result;
}


vector<int> generateAllPossibleFloorDivisors(int x) {
    vector<int> rs;
    int cur = x;
    while (1) {
        if (cur <= 0) break;
        int y = a[i] / cur;
        int z = a[i] / (y + 1) + 1;
        if (y > cur) break;
        rs.pb(y);
        if (a[i] / y != y) {
            rs.pb(a[i] / y);
        }
        cur = z - 1;
    }
    return rs;
}

struct Interpolation {
    vector<int> yi;
    vector<int> dp[2];
    vector<int> xi;
    vector<int> denom;
    template <typename... M>
    void init(int d, const M &...v) {
        yi.clear();
        yi.assign(d + 1, 0);
        xi.clear();
        denom.assign(d + 1, 0);
        for (int i = 1; i <= d + 1; i++) {
            xi.pb(i);
        }
        for (int i = 0; i < xi.size(); i++) {
            yi[i] = f(xi[i], v...);
        }
        int cur = 1;
        for (int i = xi.size() - 1; i >= 0; i--) {
            denom[i] =
                mul(cur, mul(invfact[xi.size() - xi[i]], invfact[xi[i] - 1]));
            cur *= -1;
        }
    }

    int f(int x, int n) {
        // define here brute force solution
        int rs = 0;
        return rs;
    }

    int interpolate(int x) {
        dp[0].assign(xi.size(), 0);
        dp[1].assign(xi.size(), 0);
        int bef = 1;
        for (int i = 0; i < xi.size(); i++) {
            dp[0][i] = bef;
            bef = mul(bef, sub(x, xi[i]));
        }
        bef = 1;
        for (int i = xi.size() - 1; i >= 0; i--) {
            dp[1][i] = bef;
            bef = mul(bef, sub(x, xi[i]));
        }
        int ans = 0;
        for (int i = 0; i < xi.size(); i++) {
            int rs = mul(yi[i], dp[0][i]);
            rs = mul(rs, dp[1][i]);
            rs = mul(rs, denom[i]);
            ans = add(ans, rs);
        }
        return ans;
    }

} interploator;

void next_r(ll &r0, ll &r1, ll &r) {
    ll r2 = r0 - r * r1;
    r0 = r1, r1 = r2;
}

// r0 = a, r1 = b
// return gcd =  a * x0 + b * y0
ll egcd(ll r0, ll r1, ll &x0, ll &y0) {
    ll x1 = y0 = 0, y1 = x0 = 1;
    while (r1) {
        ll r = r0 / r1;
        next_r(r0, r1, r);
        next_r(x0, x1, r);
        next_r(y0, y1, r);
    }
    return r0;
}

// c = x * a + y * b
// x' = x - (b/g) * k , y' = y + (a/g) * k
bool solve_LDE(ll a, ll b, ll c, ll &x, ll &y, ll &g) {
    g = egcd(a, b, x, y);
    ll m = c / g;
    x *= m;
    y /= m;
    return m * g == c;
}


typedef vector<vector<ll> > M;

const int MOD = 1e9 + 7;
int D = 3;
void initM(M &v) {
    v.resize(D);
    for (int i = 0; i < D; i++) {
        v[i].assign(D, 0);
    }
}

void getIdentity(M &rs) {
    initM(rs);
    for (int i = 0; i < D; i++) rs[i][i] = 1;
}

M mulM(M &u, M &v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++)
            for (int k = 0; k < D; k++)
                rs[n][m] =
                    (rs[n][m] + 0ll + (u[n][k] * 1ll * v[k][m]) % mod) % mod;
    return rs;
}

M addM(M &u, M &v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++)
            rs[n][m] = (u[n][m] % mod + v[n][m] % mod) % mod;
    return rs;
}

M subM(M &u, M v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++)
            rs[n][m] = (u[n][m] % mod + 0ll - v[n][m] % mod + mod) % mod;
    return rs;
}

M poweM(M &u, ll v, int mod = MOD) {
    M ans;
    getIdentity(ans);
    M acc = u;
    while (v) {
        if (v % 2) ans = mulM(ans, acc, mod);
        acc = mulM(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

void showM(M &v) {
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

struct NTT {
    const int mod = MOD;
    int base, max_base;
    int root;
    vector<int> roots;

    vector<int> rev;

    void init() {
        int tmp = mod - 1;
        max_base = 0;
        while (tmp % 2 == 0) {
            tmp /= 2;
            max_base++;
        }
        root = 2;

        while (powe(root, (mod - 1) >> 1) == 1) {
            root++;
        };
        assert(powe(root, mod - 1) == 1);
        root = powe(root, (mod - 1) >> max_base);
        base = 1;
        rev = {0, 1};
        roots = {0, 1};
    }

    void ensure_base(int nbase) {
        if (roots.empty()) {
            init();
        }
        if (nbase <= base) return;
        assert(nbase <= max_base);
        rev.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = ((rev[i >> 1] >> 1) + 0ll + ((i & 1) << (nbase - 1))) % MOD;
        }
        roots.resize(1 << nbase);
        while (base < nbase) {
            int z = powe(root, 1 << (max_base - 1 - base));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                roots[(i << 1) + 1] = (roots[i] * 1ll * z) % MOD;
            }
            base++;
        }
    }

    void multiply(vector<int> const& a, vector<int> const& b, vector<int>& result) {
        vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int eq = fa == fb;
        int nbase = 0;
        int need = a.size() + b.size() - 1;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int n = 1 << nbase;
        fa.resize(n);
        fb.resize(n);

        fft(fa);
        if (eq)
            fb = fa;
        else
            fft(fb);
        int inv_sz = inv(n);
        for (int i = 0; i < n; i++) fa[i] = ((fa[i] * 1ll * fb[i]) % MOD * 1ll * inv_sz) % MOD;
        reverse(fa.begin() + 1, fa.end());
        fft(fa);
        result.resize(need);
        for (int i = 0; i < need; i++) result[i] = fa[i];
    }

    void fft(vector<int>& a) {
        int n = a.size();
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    int u = a[i + j], v = (1LL * a[i + j + k] * roots[j + k]) % MOD;
                    a[i + j] = (u + v) % MOD;
                    a[i + j + k] = (u + 0ll + MOD - v) % MOD;
                }
            }
        }
    }
} ntt;


const int P = 1e5 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int sieve_size;

    NumberTheory() { sieve_size = 0; }
    template <typename T>
    T gcd(T a, T b) {
        return (b == 0 ? a : gcd(b, a % b));
    }
    template <typename T>
    T lcm(T a, T b) {
        return a * (b / gcd(a, b));
    }
    template <typename T>
    bool issquare(T w) {
        T sq = round(sqrt(w));
        return sq * sq == w;
    }
    void sieve(int ub) {
        sieve_size = ub;
        primes.clear();
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            primes.pb(i);
            if (i * 1ll * i <= ub)
                for (int j = i * i; j <= ub; j += i) {
                    is_prime[j] = 0;
                }
        }
    }
    void mobius_sieve(int ub) {
        sieve_size = ub;
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        mob.assign(ub + 1, 1);
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            primes.pb(i);
            mob[i] = -1;
            for (int j = 2 * i; j <= ub; j += i) {
                is_prime[j] = 0;
                mob[j] *= -1;
                if ((j / i) % i == 0) mob[j] = 0;
            }
        }
    }

    bool isPrime(ll N) {
        if (N <= sieve_size) return is_prime[N];
        for (int i = 0; i < primes.size(); ++i)
            if (N % primes[i] == 0) return false;
        return true;
    }
    template <typename T>
    vector<T> primeFactors(T N) {
        vector<T> factors;
        int PF_idx = 0, PF = primes[PF_idx];
        while (N != 1 && (PF * 1ll * PF <= N)) {
            while (N % PF == 0) {
                N /= PF;
                factors.push_back(PF);
            }
            PF = primes[++PF_idx];
        }
        if (N != 1) factors.push_back(N);
        return factors;
    }
    template <typename T>
    int numPF(T N) {
        int PF_idx = 0, PF = primes[PF_idx], ans = 0;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            while (N % PF == 0) {
                N /= PF;
                ans++;
            }
            PF = primes[++PF_idx];
        }
        if (N != 1) ans++;
        return ans;
    }
    template <typename T>
    int numDiffPF(T N) {
        int PF_idx = 0, PF = primes[PF_idx], ans = 0;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            if (N % PF == 0) ans++;
            while (N % PF == 0) N /= PF;
            PF = primes[++PF_idx];
        }
        if (N != 1) ans++;
        return ans;
    }
    template <typename T>
    ll sumPF(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        ll ans = 0;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            while (N % PF == 0) {
                N /= PF;
                ans += PF;
            }
            PF = primes[++PF_idx];
        }
        if (N != 1) ans += N;
        return ans;
    }
    template <typename T>
    T numDiv(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        T ans = 1;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            int power = 0;
            while (N % PF == 0) {
                N /= PF;
                power++;
            }
            ans *= (power + 1);
            PF = primes[++PF_idx];
        }
        if (N != 1) ans *= 2;
        return ans;
    }
    template <typename T>
    ll sumDiv(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        ll ans = 1;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            int power = 0;
            T po = PF;
            while (N % PF == 0) {
                N /= PF;
                power++;
                po *= PF;
            }
            ans *= ((po - 1) / (PF - 1));
            PF = primes[++PF_idx];
        }
        if (N != 1) ans *= (N + 1);
        return ans;
    }
    template <typename T>
    T EulerPhi(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        T ans = N;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            if (N % PF == 0) ans -= ans / PF;
            while (N % PF == 0) N /= PF;
            PF = primes[++PF_idx];
        }
        if (N != 1) ans -= ans / N;
        return ans;
    }

} nt;


using ul = uint64_t;
using db = long double;

class Pollard {
   public:
    map<ul, int> cnt_primes;
    vector<ul> primes, divisors;
    ul modMul(ul a, ul b, const ul mod) {
        ll ret = a * b - mod * (ul)((db)a * b / mod);
        return ret + ((ret < 0) - (ret >= (ll)mod)) * mod;
    }
    ul modPow(ul a, ul b, const ul mod) {
        if (b == 0) return 1;
        ul res = modPow(a, b / 2, mod);
        res = modMul(res, res, mod);
        return b & 1 ? modMul(res, a, mod) : res;
    }

    bool rabin_miller(ul n) {  // not ll!
        if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
        ul A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
           s = __builtin_ctzll(n - 1), d = n >> s;
        for (auto a : A) {  // ^ count trailing zeroes
            ul p = modPow(a, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--) p = modMul(p, p, n);
            if (p != n - 1 && i != s) return 0;
        }
        return 1;
    }
    ul pollard(ul n) {  // return some nontrivial factor of n
        auto f = [n, this](ul x) { return modMul(x, x, n) + 1; };
        ul x = 0, y = 0, t = 30, prd = 2, i = 1, q;
        while (t++ % 40 ||
               __gcd(prd, n) == 1) {  /// speedup: don't take gcd every it
            if (x == y) x = ++i, y = f(x);
            if ((q = modMul(prd, max(x, y) - min(x, y), n))) prd = q;
            x = f(x), y = f(f(y));
        }
        return __gcd(prd, n);
    }
    void factor_rec(ul n, map<ul, int>& cnt) {
        if (n == 1) return;
        if (rabin_miller(n)) {
            ++cnt[n];
            return;
        }
        ul u = pollard(n);
        factor_rec(u, cnt), factor_rec(n / u, cnt);
    }
    void calcDivisorsRec(ul cur, int i) {
        if (i >= primes.size()) {
            divisors.pb(cur);
            return;
        }
        int r = cnt_primes[primes[i]];
        for (int j = 0; j <= r; j++) {
            calcDivisorsRec(cur, i + 1);
            cur = cur * primes[i];
        }
    }
    void calcDivisors(ul x) {
        cnt_primes.clear();
        primes.clear();
        divisors.clear();
        factor_rec(x, cnt_primes);
        for (auto& u : cnt_primes) {
            primes.pb(u.fi);
        }
        calcDivisorsRec(1, 0);
    }
} pollard;

// Modular calculation and combinatorics Mtaylor

template <typename T>
T inverse(T a, T m) {
    T u = 0, v = 1;
    while (a != 0) {
        T t = m / a;
        m -= t * a;
        swap(a, m);
        u -= t * v;
        swap(u, v);
    }
    assert(m == 1);
    return u;
}
template <typename T>
class Modular {
   public:
    using Type = typename decay<decltype(T::value)>::type;

    constexpr Modular() : value() {}
    template <typename U>
    Modular(const U& x) {
        value = normalize(x);
    }

    template <typename U>
    static Type normalize(const U& x) {
        Type v;
        if (-mod() <= x && x < mod())
            v = static_cast<Type>(x);
        else
            v = static_cast<Type>(x % mod());
        if (v < 0) v += mod();
        return v;
    }

    const Type& operator()() const { return value; }
    template <typename U>
    explicit operator U() const {
        return static_cast<U>(value);
    }
    constexpr static Type mod() { return T::value; }

    Modular& operator+=(const Modular& other) {
        if ((value += other.value) >= mod()) value -= mod();
        return *this;
    }
    Modular& operator-=(const Modular& other) {
        if ((value -= other.value) < 0) value += mod();
        return *this;
    }
    template <typename U>
    Modular& operator+=(const U& other) {
        return *this += Modular(other);
    }
    template <typename U>
    Modular& operator-=(const U& other) {
        return *this -= Modular(other);
    }
    Modular& operator++() { return *this += 1; }
    Modular& operator--() { return *this -= 1; }
    Modular operator++(int) {
        Modular result(*this);
        *this += 1;
        return result;
    }
    Modular operator--(int) {
        Modular result(*this);
        *this -= 1;
        return result;
    }
    Modular operator-() const { return Modular(-value); }

    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, int>::value,
                       Modular>::type&
    operator*=(const Modular& rhs) {
#ifdef _WIN32
        uint64_t x =
            static_cast<int64_t>(value) * static_cast<int64_t>(rhs.value);
        uint32_t xh = static_cast<uint32_t>(x >> 32),
                 xl = static_cast<uint32_t>(x), d, m;
        asm("divl %4; \n\t" : "=a"(d), "=d"(m) : "d"(xh), "a"(xl), "r"(mod()));
        value = m;
#else
        value = normalize(static_cast<int64_t>(value) *
                          static_cast<int64_t>(rhs.value));
#endif
        return *this;
    }
    template <typename U = T>
    typename enable_if<is_same<typename Modular<U>::Type, long long>::value,
                       Modular>::type&
    operator*=(const Modular& rhs) {
        long long q = static_cast<long long>(static_cast<long double>(value) *
                                             rhs.value / mod());
        value = normalize(value * rhs.value - q * mod());
        return *this;
    }
    template <typename U = T>
    typename enable_if<!is_integral<typename Modular<U>::Type>::value,
                       Modular>::type&
    operator*=(const Modular& rhs) {
        value = normalize(value * rhs.value);
        return *this;
    }

    Modular& operator/=(const Modular& other) {
        return *this *= Modular(inverse(other.value, mod()));
    }

    friend const Type& abs(const Modular& x) { return x.value; }

    template <typename U>
    friend bool operator==(const Modular<U>& lhs, const Modular<U>& rhs);

    template <typename U>
    friend bool operator<(const Modular<U>& lhs, const Modular<U>& rhs);

    template <typename V, typename U>
    friend V& operator>>(V& stream, Modular<U>& number);

   private:
    Type value;
};
template <typename T>
bool operator==(const Modular<T>& lhs, const Modular<T>& rhs) {
    return lhs.value == rhs.value;
}
template <typename T, typename U>
bool operator==(const Modular<T>& lhs, U rhs) {
    return lhs == Modular<T>(rhs);
}
template <typename T, typename U>
bool operator==(U lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) == rhs;
}

template <typename T>
bool operator!=(const Modular<T>& lhs, const Modular<T>& rhs) {
    return !(lhs == rhs);
}
template <typename T, typename U>
bool operator!=(const Modular<T>& lhs, U rhs) {
    return !(lhs == rhs);
}
template <typename T, typename U>
bool operator!=(U lhs, const Modular<T>& rhs) {
    return !(lhs == rhs);
}

template <typename T>
bool operator<(const Modular<T>& lhs, const Modular<T>& rhs) {
    return lhs.value < rhs.value;
}

template <typename T>
Modular<T> operator+(const Modular<T>& lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) += rhs;
}
template <typename T, typename U>
Modular<T> operator+(const Modular<T>& lhs, U rhs) {
    return Modular<T>(lhs) += rhs;
}
template <typename T, typename U>
Modular<T> operator+(U lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) += rhs;
}

template <typename T>
Modular<T> operator-(const Modular<T>& lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) -= rhs;
}
template <typename T, typename U>
Modular<T> operator-(const Modular<T>& lhs, U rhs) {
    return Modular<T>(lhs) -= rhs;
}
template <typename T, typename U>
Modular<T> operator-(U lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) -= rhs;
}

template <typename T>
Modular<T> operator*(const Modular<T>& lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) *= rhs;
}
template <typename T, typename U>
Modular<T> operator*(const Modular<T>& lhs, U rhs) {
    return Modular<T>(lhs) *= rhs;
}
template <typename T, typename U>
Modular<T> operator*(U lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) *= rhs;
}

template <typename T>
Modular<T> operator/(const Modular<T>& lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) /= rhs;
}
template <typename T, typename U>
Modular<T> operator/(const Modular<T>& lhs, U rhs) {
    return Modular<T>(lhs) /= rhs;
}
template <typename T, typename U>
Modular<T> operator/(U lhs, const Modular<T>& rhs) {
    return Modular<T>(lhs) /= rhs;
}

template <typename T, typename U>
Modular<T> power(const Modular<T>& a, const U& b) {
    assert(b >= 0);
    Modular<T> x = a, res = 1;
    U p = b;
    while (p > 0) {
        if (p & 1) res *= x;
        x *= x;
        p >>= 1;
    }
    return res;
}

template <typename T>
bool IsZero(const Modular<T>& number) {
    return number() == 0;
}

template <typename T>
string to_string(const Modular<T>& number) {
    return to_string(number());
}

// U == std::ostream? but done this way because of fastoutput
template <typename U, typename T>
U& operator<<(U& stream, const Modular<T>& number) {
    return stream << number();
}

// U == std::istream? but done this way because of fastinput
template <typename U, typename T>
U& operator>>(U& stream, Modular<T>& number) {
    typename common_type<typename Modular<T>::Type, long long>::type x;
    stream >> x;
    number.value = Modular<T>::normalize(x);
    return stream;
}
constexpr int MOD = (int)1e9 + 7;
using Mint = Modular<std::integral_constant<decay<decltype(MOD)>::type, MOD>>;
const int F = 3e6 + 5;
Mint fact[F];
Mint invfact[F];
Mint cnk(int n, int k) {
    if (k > n) return 0;
    if (n == 0) return 1;
    return fact[n] * invfact[k] * invfact[n - k];
}
void init_fact(int n) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++) fact[i] = (fact[i - 1] * i);
    for (int i = 0; i <= n; i++) invfact[i] = 1 / fact[i];
}

const int MOD = 998244353;
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

const int F = 1e6;
int fact[F];
int invfact[F];
int cnk(int n, int k, int mod = MOD) {
    if (k > n) return 0;
    if (n == 0) return 1;
    int ans = mul(fact[n], invfact[k], mod);
    ans = mul(ans, invfact[n - k], mod);
    return ans;
}
void init_fact(int n, int mod = MOD) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++) fact[i] = mul(i, fact[i - 1], mod);
    for (int i = 0; i <= n; i++) invfact[i] = powe(fact[i], mod - 2, mod);
}
int starsandbars(int n, int k) { return cnk(n + k - 1, n); }


// Geometry Mtaylor



//WRONG ANSWER
#include <bits/stdc++.h>
using namespace std;

typedef complex<double> point;
#define EPS 1e-9
#define OO 1e9
#define X real()
#define Y imag()
#define vec(a,b) ((b)-(a))
#define polar(r,t) ((r)*exp(point(0,(t))))
#define angle(v) (atan2((v).Y,(v).X))
#define length(v) ((double)hypot((v).Y,(v).X))
#define lengthSqr(v) (dot(v,v))
#define dot(a,b) ((conj(a)*(b)).real())
#define cross(a,b) ((conj(a)*(b)).imag())
#define rotate(v,t) (polar(v,t))
#define rotateabout(v,t,a)  (rotate(vec(a,v),t)+(a))
#define reflect(p,m) ((conj((p)/(m)))*(m))
#define normalize(p) ((p)/length(p))
#define same(a,b) (lengthSqr(vec(a,b))<EPS)
#define mid(a,b) (((a)+(b))/point(2,0))
#define perp(a) (point(-(a).Y,(a).X))
#define colliner pointOnLine
const double PI = 4*atan(1);

enum STATE
{
    IN, OUT, BOUNDRY
};

long double circleIntersectionArea(long double r1, long double r2,
                                   long double d) {
    // d is the distance between the 2 centers
    if (r1 < r2) swap(r1, r2);
    if (d >= r1 + r2) return 0;
    if (d <= r1 - r2) return PI * r2 * r2;
    long double alpha = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
    long double s = alpha * r2 * r2;
    long double t = r2 * r2 * sin(alpha) * cos(alpha);
    long double x = s - t;
    alpha = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
    s = alpha * r1 * r1;
    t = r1 * r1 * sin(alpha) * cos(alpha);
    long double y = s - t;
    return x + y;
}




bool intersect(const point &a, const point &b, const point &p, const point &q,
               point &ret)
{

    //handle degenerate cases (2 parallel lines, 2 identical lines,   line is 1 point)

    double d1 = cross(p - a, b - a);
    double d2 = cross(q - a, b - a);
    ret = (d1 * q - d2 * p) / (d1 - d2);
    if(fabs(d1 - d2) > EPS) return 1;
    return 0;
}

bool pointOnLine(const point& a, const point& b, const point& p)
{
    // degenerate case: line is a point
    return fabs(cross(vec(a,b),vec(a,p))) < EPS;
}

bool pointOnRay(const point& a, const point& b, const point& p)
{
    //IMP NOTE: a,b,p must be collinear
    //chech if it's in the same direction as the [a,b)
    return dot(vec(a,p), vec(a,b)) > -EPS;
}

bool pointOnSegment(const point& a, const point& b, const point& p)
{
    if (same(a,b))
        return same(a,p);
    if(!colliner(a,b,p)) return 0;
    return pointOnRay(a, b, p) && pointOnRay(b, a, p);
}

double pointLineDist(const point& a, const point& b, const point& p)
{
    // handle degenrate case: (a,b) is point

    return fabs(cross(vec(a,b),vec(a,p)) / length(vec(a,b)));
}

double pointSegmentDist(const point& a, const point& b, const point& p)
{
    if (dot(vec(a,b),vec(a,p)) < EPS)
        return length(vec(a,p));
    if (dot(vec(b,a),vec(b,p)) < EPS)
        return length(vec(b,p));
    return pointLineDist(a, b, p);
}

int segmentLatticePointsCount(int x1, int y1, int x2, int y2)
{
    return abs(__gcd(x1 - x2, y1 - y2)) + 1;
}

double triangleAreaBH(double b, double h)
{
    return b * h / 2;
}

double triangleArea2sidesAngle(double a, double b, double t)
{
    return fabs(a * b * sin(t) / 2);
}

double triangleArea2anglesSide(double t1, double t2,
                               double s)
{
    return fabs(s * s * sin(t1) * sin(t2) / (2 * sin(t1 + t2)));
}



double triangleArea3points(const point& a, const point& b, const point& c)
{
    return fabs(cross(a,b) + cross(b,c) + cross(c,a)) / 2;
}

//count interior Lattice points inside polygon (corner are already lattice points)
int picksTheorm(int a, int b)
{
    // a area
    // b nbr of lattice points on boundary
    return a - b / 2 + 1;
}

//get angle opposite to side a
double cosRule(double a, double b, double c)
{
    // Handle denom = 0
    double res = (b * b + c * c - a * a) / (2 * b * c);
    if ( fabs(res-1)<EPS)
        res = 1;
    if (fabs(res+1)<EPS)
        res = -1;
    return acos(res);
}

double sinRuleAngle(double s1, double s2, double a1)
{
    // Handle denom = 0
    double res = s2 * sin(a1) / s1;
    if ( fabs(res-1)<EPS)
        res = 1;
    if ( fabs(res+1)<EPS)
        res = -1;
    return asin(res);
}

double sinRuleSide(double s1, double a1, double a2)
{
    // Handle denom = 0
    double res = s1 * sin(a2) / sin(a1);
    return fabs(res);
}

int circleLineIntersection(const point& p0, const point& p1, const point& cen,
                           double rad, point& r1, point & r2)
{

    // handle degenerate case if p0 == p1
    double a, b, c, t1, t2;
    a = dot(p1-p0,p1-p0);
    b = 2 * dot(p1-p0,p0-cen);
    c = dot(p0-cen,p0-cen) - rad * rad;
    double det = b * b - 4 * a * c;
    int res;
    if (fabs(det) < EPS)
        det = 0, res = 1;
    else if (det < 0)
        res = 0;
    else
        res = 2;
    det = sqrt(det);
    t1 = (-b + det) / (2 * a);
    t2 = (-b - det) / (2 * a);
    r1 = p0 + t1 * (p1 - p0);
    r2 = p0 + t2 * (p1 - p0);
    return res;
}

int circleCircleIntersection(const point &c1, const double&r1,
                             const point &c2, const double&r2, point &res1, point &res2)
{
    if (same(c1,c2) && fabs(r1 - r2) < EPS)
    {
        res1 = res2 = c1;
        return fabs(r1) < EPS ? 1 : OO;
    }
    double len = length(vec(c1,c2));
    if (fabs(len - (r1 + r2)) < EPS || fabs(fabs(r1 - r2) - len) < EPS)
    {
        point d, c;
        double r;
        if (r1 > r2)
            d = vec(c1,c2), c = c1, r = r1;
        else
            d = vec(c2,c1), c = c2, r = r2;
        res1 = res2 = normalize(d) * r + c;
        return 1;
    }
    if (len > r1 + r2 || len < fabs(r1 - r2))
        return 0;
    double a = cosRule(r2, r1, len);
    point c1c2 = normalize(vec(c1,c2)) * r1;
    res1 = rotate(c1c2,a) + c1;
    res2 = rotate(c1c2,-a) + c1;
    return 2;
}

// P1P2 diameter
void circle2(const point& p1, const point& p2, point& cen, double& r)
{
    cen = mid(p1,p2);
    r = length(vec(p1,p2)) / 2;
}
// cercle circonscrit
bool circle3(const point& p1, const point& p2, const point& p3, point& cen,
             double& r)
{
    // li mel bara
    point m1 = mid(p1,p2);
    point m2 = mid(p2,p3);
    point perp1 = perp(vec(p1,p2));
    point perp2 = perp(vec(p2,p3));
    bool res = intersect(m1, m1 + perp1, m2, m2 + perp2, cen);
    r = length(vec(cen,p1));
    return res;
}
// point % cercle
STATE circlePoint(const point & cen, const double & r, const point& p)
{
    double lensqr = lengthSqr(vec(cen,p));
    if (fabs(lensqr - r * r) < EPS)
        return BOUNDRY;
    if (lensqr < r * r)
        return IN;
    return OUT;
}
//p is outside the circle
int tangentPoints(const point & cen, const double & r, const point& p,
                  point &r1, point &r2)
{
    STATE s = circlePoint(cen, r, p);
    if (s != OUT)
    {
        r1 = r2 = p;
        return s == BOUNDRY;
    }
    point cp = vec(cen,p);
    double h = length(cp);
    double a = acos(r / h);
    cp = normalize(cp) * r;
    r1 = rotate(cp,a) + cen;
    r2 = rotate(cp,-a) + cen;
    return 2;
}

typedef pair<point, point> segment;
// tangentes communes �?  deux cercles
void getCommonTangents(point c1, double r1, point c2, double r2, vector<segment> &res)
{
    if (r1 < r2) swap(r1, r2), swap(c1, c2);
    double d = length(c1 - c2);
    double theta = acos((r1 - r2) / d);
    point v = c2 - c1;
    v = v / hypot(v.imag(), v.real());
    point v1 = v * exp(point(0, theta));
    point v2 = v * exp(point(0, -theta));
    res.clear();
    res.push_back(segment(c1 + v1 * r1, c2 + v1 * r2));
    res.push_back(segment(c1 + v2 * r1, c2 + v2 * r2));
    theta = acos((r1 + r2) / d);
    v1 = v * exp(point(0, theta));
    v2 = v * exp(point(0, -theta));
    res.push_back(segment(c1 + v1 * r1, c2 - v1 * r2));
    res.push_back(segment(c1 + v2 * r1, c2 - v2 * r2));
}

// minimum enclosing circle
//init p array with the points and ps with the number of points
//cen and rad are result circle
//you must call random_shuffle(p,p+ps); before you call mec
#define MAXPOINTS 100000
point p[MAXPOINTS], r[3], cen;
int ps, rs;
double rad;

void mec()
{
    if (rs == 3)
    {
        circle3(r[0], r[1], r[2], cen, rad);
        return;
    }
    if (rs == 2 && ps == 0)
    {
        circle2(r[0], r[1], cen, rad);
        return;
    }
    if (!ps)
    {
        cen = r[0];
        rad = 0;
        return;
    }
    ps--;
    mec();
    if (circlePoint(cen, rad, p[ps]) == OUT)
    {
        r[rs++] = p[ps];
        mec();
        rs--;
    }
    ps++;

}

//to check if the points are sorted anti-clockwise or clockwise
//remove the fabs at the end and it will return -ve value if clockwise
double polygonArea(const vector<point>&p)
{
    double res = 0;
    for (int i = 0; i < sz(p); i++)
    {
        int j = (i + 1) % sz(p);
        res += cross(p[i],p[j]);
    }
    return fabs(res) / 2;
}

// return the centroid point of the polygon
// The centroid is also known as the "centre of gravity" or the "center of mass". The position of the centroid
// assuming the polygon to be made of a material of uniform density.
point polyginCentroid(vector<point> &polygon)
{

    double a = 0;
    double x=0.0,y=0.0;
    for (int i = 0; i < (int) polygon.size(); i++)
    {
        int j = (i + 1) % polygon.size();

        x += (polygon[i].X + polygon[j].X) * (polygon[i].X * polygon[j].Y
                                              - polygon[j].X * polygon[i].Y);

        y += (polygon[i].Y + polygon[j].Y) * (polygon[i].X * polygon[j].Y
                                              - polygon[j].X * polygon[i].Y);

        a += polygon[i].X * polygon[j].Y - polygon[i].Y * polygon[j].X;
    }

    a *= 0.5;
    x /= 6 * a;
    y /= 6 * a;

    return point(x,y);
}

int picksTheorm(vector<point>& p)
{
    double area = 0;
    int bound = 0;
    for (int i = 0; i < sz(p); i++)
    {
        int j = (i + 1) % sz(p);
        area += cross(p[i],p[j]);
        point v = vec(p[i],p[j]);
        bound += abs(__gcd((int) v.X, (int) v.Y));
    }
    area /= 2;
    area = fabs(area);
    return round(area - bound / 2 + 1);
}
//convex polygon [a , b) sens trigonom�?©trique
void polygonCut(const vector<point>& p, const point&a, const point&b, vector<
                point>& res)
{
    res.clear();
    for (int i = 0; i < sz(p); i++)
    {
        int j = (i + 1) % sz(p);
        bool in1 = cross(vec(a,b),vec(a,p[i])) > EPS;
        bool in2 = cross(vec(a,b),vec(a,p[j])) > EPS;
        if (in1)
            res.push_back(p[i]);
        if (in1 ^ in2)
        {
            point r;
            intersect(a, b, p[i], p[j], r);
            res.push_back(r);
        }
    }
}

//assume that both are anti-clockwise
void convexPolygonIntersect(const vector<point>& p, const vector<point>& q,
                            vector<point>& res)
{
    res = q;
    for (int i = 0; i < sz(p); i++)
    {
        int j = (i + 1) % sz(p);
        vector<point> temp;
        polygonCut(res, p[i], p[j], temp);
        res = temp;
        if (res.empty())
            return;
    }
}

void voronoi(const vector<point> &pnts, const vector<point>& rect, vector<
             vector<point> > &res)
{
    // y9assem region tq q point fi region wa7adha
    res.clear();
    for (int i = 0; i < sz(pnts); i++)
    {
        res.push_back(rect);
        for (int j = 0; j < sz(pnts); j++)
        {
            if (j == i)
                continue;
            point p = perp(vec(pnts[i],pnts[j]));
            point m = mid(pnts[i],pnts[j]);
            vector<point> temp;
            polygonCut(res.back(), m, m + p, temp);
            res.back() = temp;
        }
    }
}

STATE pointInPolygon(const vector<point>& p, const point &pnt)
{
    point p2 = pnt + point(1, 0);
    int cnt = 0;
    for (int i = 0; i < sz(p); i++)
    {
        int j = (i + 1) % sz(p);
        if (same(p[i],p[j]))
            continue;
        if (pointOnSegment(p[i], p[j], pnt))
            return BOUNDRY;
        point r;
        if(!intersect(pnt, p2, p[i], p[j], r))
            continue;
        if (!pointOnRay(pnt, p2, r))
            continue;
        if (same(r,p[i]) || same(r,p[j]))
            if (fabs(r.Y - min(p[i].Y, p[j].Y)) < EPS)
                continue;
        if (!pointOnSegment(p[i], p[j], r))
            continue;
        cnt++;
    }
    return cnt & 1 ? IN : OUT;
}

struct cmp
{
    point about;
    cmp(point c)
    {
        about = c;
    }
    bool operator()(const point& p, const point& q) const
    {
        double cr = cross(vec(about, p), vec(about, q));
        if (fabs(cr) < EPS)
            return make_pair(p.Y, p.X) < make_pair(q.Y, q.X);
        return cr > 0;
    }
};

void sortAntiClockWise(vector<point>& pnts)
{
    point mn(1 / 0.0, 1 / 0.0);
    for (int i = 0; i < sz(pnts); i++)
        if (make_pair(pnts[i].Y, pnts[i].X) < make_pair(mn.Y, mn.X))
            mn = pnts[i];

    sort(all(pnts), cmp(mn));
}

void convexHull(vector<point> pnts, vector<point> &convex)
{
    sortAntiClockWise(pnts);
    convex.clear();
    convex.push_back(pnts[0]);
    if (sz(pnts) == 1)
        return;
    convex.push_back(pnts[1]);
    if (sz(pnts) == 2)
    {
        if (same(pnts[0], pnts[1]))
            convex.pop_back();
        return;
    }
    for (int i = 2; i <= sz(pnts); i++)
    {
        point c = pnts[i % sz(pnts)];
        while (sz(convex) > 1)
        {
            point b = convex.back();
            point a = convex[sz(convex) - 2];
            if (cross(vec(b, a), vec(b, c)) < -EPS)
                break;
            convex.pop_back();
        }
        if (i < sz(pnts))
            convex.push_back(pnts[i]);
    }
}
