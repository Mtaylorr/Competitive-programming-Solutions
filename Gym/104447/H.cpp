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

class segtree {
   public:
    struct node {
        // define the variables
        int add = 0;
        int lazy = 0;
        int val = 0;
        node() {
            // define initial values
            lazy = add = 0;
            val = 0;
        }
        void apply(int ns, int ne, int v) {
            // define apply operation
            val = v;
            add = 1;
            lazy = v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.val = a.val;
        return res;
    }

    inline void push(int id, int ns, int ne) {
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        if (tree[id].add != 0) {
            tree[l].apply(ns, md, tree[id].lazy);
            tree[r].apply(md + 1, ne, tree[id].lazy);
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

    node get(int qs, int qe) { return get(qs + 4, qe + 4, 0, 0, n - 1); }
    node get(int p) { return get(p + 4, p + 4, 0, 0, n - 1); }

    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        modify(qs + 4, qe + 4, 0, 0, n - 1, v...);
    }
};

int x[N], y[N];
int n, q;
int valid[N];
vector<pair<int, int> > lines[N][2];
vector<int> pts[N][2];
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i = 0; i < n; i++) {
        int j = (i + 1) % n;
        if (x[i] == x[j]) {
            lines[x[i]][0].pb({min(y[i], y[j]), max(y[i], y[j])});
        } else {
            lines[y[i]][1].pb({min(x[i], x[j]), max(x[i], x[j])});
        }
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> x[i] >> y[i];
        pts[x[i]][0].pb(i);
        pts[y[i]][1].pb(i);
    }
    for (int j = 0; j < 2; j++) {
        segtree sg = segtree(4e6 + 30);
        for (int i = 0; i <= 1e6; i++) {
            vector<pair<int, int> > to_add, to_rem;
            sort(all(lines[i][j]));
            for (auto u : lines[i][j]) {
                int l = u.fi;
                int r = u.se;
                int val = sg.get(4 * l + 1, 4 * l + 1).val;
                val = 1 - val;
                if (val == 1) {
                    to_add.pb({4 * l + 1, 4 * r - 1});
                } else {
                    to_rem.pb({4 * l + 1, 4 * r - 1});
                }
            }
            for (auto u : to_add) {
                if (u.fi <= u.se) sg.upd(u.fi, u.se, 1);
            }
            sort(all(pts[i][j]), [](int &a, int &b) {
                return mp(x[a], y[a]) < mp(x[b], y[b]);
            });
            for (auto u : pts[i][j]) {
                int v = x[u] + y[u] - i;
                int val = sg.get(4 * v + 1, 4 * v + 3).val;
                if (val) {
                    valid[u]++;
                }
            }
            for (auto u : to_rem) {
                if (u.fi <= u.se) sg.upd(u.fi, u.se, 0);
            }
            int idx = 0;
            for (auto u : lines[i][j]) {
                while (idx < pts[i][j].size()) {
                    int p = pts[i][j][idx];
                    int c = x[p] + y[p] - i;
                    if (c < u.fi) {
                        idx++;
                        continue;
                    }
                    if (c <= u.se) {
                        valid[p] = 2;
                        idx++;
                    } else {
                        break;
                    }
                }
            }
        }
    }
    for (int i = 0; i < q; i++) {
        if (valid[i] >= 2) {
            cout << "YES\n";
        } else {
            cout << "NO\n";
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
