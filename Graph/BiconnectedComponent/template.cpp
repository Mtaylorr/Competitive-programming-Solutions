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
