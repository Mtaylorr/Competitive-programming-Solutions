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

#define left(x) (2 * (x) + 1)
#define right(x) (2 * (x) + 2)
#define mid(ns, ne) ((ns) + ((ne) - (ns)) / 2)

struct node {
    // define the variables
    int add = 0;
    ll sm = 0;
    node() {
        // define initial values
        sm = 0;
    }
    void apply(int ns, int ne, ll v) {
        // define apply operation
        sm = v;
    }
};
class segTreeHLD {
   public:
    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.sm = a.sm + b.sm;
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

int n;
int q;
vector<ll> val;

void dfs(int u, int p = -1) {
    neig(u, v, e, adj) {
        if (v == p) continue;
        val[v] = adj.cst[e];
        dfs(v, u);
    }
}
int u[N], v[N];

void test_case() {
    cin >> n;
    adj.init(n);
    val.assign(n, 0);
    for (int i = 0; i < n - 1; i++) {
        int a, b, c;
        cin >> a >> b >> c;
        a--, b--;
        u[i] = a;
        v[i] = b;
        adj.addBiEdge(a, b, c);
    }

    dfs(0);
    hld.run(adj);
    hld.initSegmentTree(val);

    cin >> q;
    while (q--) {
        int a, b, c;
        cin >> a >> b >> c;
        if (a == 1) {
            b--;
            if (hld.par[u[b]] == v[b]) {
                hld.update(u[b], u[b], c);
            } else {
                hld.update(v[b], v[b], c);
            }
        } else {
            b--, c--;
            ll ans = hld.query(b, c);
            cout << ans << "\n";
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
