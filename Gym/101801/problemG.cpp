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
        int add1 = 0;
        int add2 = 0;
        ll sum1 = 0;
        ll sum2 = 0;
        ll lazy_cnt_1 = 0;
        ll lazy_cnt_2 = 0;
        ll lazy_st_1 = 0;
        ll lazy_st_2 = 0;
        node() {
            // define initial values
        }
        void apply(int ns, int ne, int v) {
            // define apply operation
        }
        void apply(int ns, int ne, ll v, int cnt, int t) {
            // define apply operation
            ll sz = ne - ns + 1;
            if (t == 1) {
                sum1 += v * sz + cnt * (sz * (sz + 1)) / 2;
                add1 = 1;
                lazy_st_1 += v;
                lazy_cnt_1 += cnt;
            } else {
                sum2 += v * sz + cnt * (sz * (sz + 1)) / 2;
                add2 = 1;
                lazy_st_2 += v;
                lazy_cnt_2 += cnt;
            }
        };
    };

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.sum1 = a.sum1 + b.sum1;
        res.sum2 = a.sum2 + b.sum2;
        return res;
    }

    inline void push(int id, int ns, int ne) {
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        ll lsz = md - ns + 1;
        ll rsz = ne - md;
        if (tree[id].add1 != 0) {
            tree[l].apply(ns, md, tree[id].lazy_st_1, tree[id].lazy_cnt_1, 1);
            tree[r].apply(md + 1, ne,
                          tree[id].lazy_st_1 + lsz * tree[id].lazy_cnt_1,
                          tree[id].lazy_cnt_1, 1);
            tree[id].add1 = 0;
            tree[id].lazy_cnt_1 = 0;
            tree[id].lazy_st_1 = 0;
        }
        if (tree[id].add2 != 0) {
            tree[l].apply(ns, md,
                          tree[id].lazy_st_2 + rsz * tree[id].lazy_cnt_2,
                          tree[id].lazy_cnt_2, 2);
            tree[r].apply(md + 1, ne, tree[id].lazy_st_2, tree[id].lazy_cnt_2,
                          2);

            tree[id].add2 = 0;
            tree[id].lazy_cnt_2 = 0;
            tree[id].lazy_st_2 = 0;
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
    void modify(int qs, int qe, int id, int ns, int ne, int t) {
        if (qs <= ns && qe >= ne) {
            if (t == 1)
                tree[id].apply(ns, ne, ns - qs, 1, 1);
            else {
                tree[id].apply(ns, ne, qe - ne, 1, 2);
            }
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        push(id, ns, ne);
        if (qs <= md) {
            modify(qs, qe, l, ns, md, t);
        }
        if (qe > md) {
            modify(qs, qe, r, md + 1, ne, t);
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

    void upd(int qs, int qe, int t) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, t);
    }
};

int q, t, l, r;
void test_case() {
    cin >> q;
    segtree sg = segtree((int)1e5 + 2);
    ll tot = 0;
    while (q--) {
        cin >> t >> l >> r;
        if (t == 1) {
            tot += (r - l + 1) * 1ll * (r - l + 2) / 2;
            sg.upd(l, r, 1);
            sg.upd(l, r, 2);
        } else {
            ll lf = sg.get(0, l - 1).sum1;
            ll rg = sg.get(r + 1, 1e5 + 1).sum2;
            cout << tot - lf - rg << endl;
        }
    }
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
