//https://codeforces.com/problemset/problem/484/E

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
        int l, r, s, a;
        node() {
            // define initial values
            l = r = a = 0;
            s = 1;
        }
        void apply(int ns, int ne, int v) {
            // define apply operation
            l = r = a = v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.s = a.s + b.s;
        res.a = max(a.a, b.a);
        res.a = max(res.a, a.r + b.l);
        res.l = a.l;
        res.r = b.r;
        if (a.l == a.s) {
            res.l = a.l + b.l;
        }
        if (b.r == b.s) {
            res.r = b.r + a.r;
        }
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

int n, m;
int h[N];
vector<int> sh;
int lf[N], rg[N], w[N];
int ans[N];

void upd(int p, int c, segtree &sg) {
    if (c == 1) {
        sg.upd(sh[p], sh[p], 1);
    } else {
        sg.upd(sh[p], sh[p], 0);
    }
}

void rec(int l, int r, vector<int> &queries, segtree &sg, int &id) {
    if (queries.size() == 0) return;
    int md = (l + r) / 2;
    while (id < md) {
        upd(++id, +1, sg);
    }
    while (id > md) {
        upd(id--, -1, sg);
    }
    vector<int> left_queries, right_queries;
    for (auto u : queries) {
        int x = sg.get(lf[u], rg[u]).a;
        if (x >= w[u]) {
            ans[u] = h[sh[md]];
            left_queries.pb(u);
        } else {
            right_queries.pb(u);
        }
    }
    queries.clear();
    if (l == r) return;
    rec(l, md, left_queries, sg, id);
    rec(md+1, r, right_queries, sg, id);
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> h[i];
        sh.pb(i);
    }

    sort(all(sh), [](int &x, int &y) { return h[x] > h[y]; });
    vector<int> queries;
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> lf[i] >> rg[i] >> w[i];
        --lf[i], --rg[i];
        queries.pb(i);
    }
    segtree sg = segtree(n);
    int id = -1;
    rec(0, n - 1, queries, sg, id);
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
