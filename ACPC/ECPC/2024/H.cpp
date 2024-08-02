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
const int B = 17;

struct node {
    // define states here
    bool has_lazy;
    int lazy = 0;
    vector<int> b;
    int o;
    node() {
        // initialize states here
        has_lazy = false;
        lazy = 0;
        b.resize(B);
        o = 0;
    }

    void apply(int ns, int ne, int v) {
        // update value
        b.assign(B, 0);
        b[__lg(v)] = v;
        o = v;
        // update lazy
        has_lazy = 0;
    }
    void apply(int ns, int ne, int v, int t) {
        // update value
        o &= v;
        b.assign(B, 0);
        if (o) b[__lg(o)] = o;
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
        res.o = l.o | r.o;
        res.b = l.b;
        for (auto &x : r.b) {
            if (x == 0) continue;
            int y = x;
            for (int j = B - 1; j >= 0; j--) {
                if (y & (1 << j)) {
                    if (res.b[j] == 0) {
                        res.b[j] = y;
                        break;
                    } else {
                        y ^= res.b[j];
                    }
                }
            }
        }
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

    void update(int qs, int qe, int id, int ns, int ne, int v, int t) {
        if (qs > ne || qe < ns) return;
        if ((tree[id].o & v) == tree[id].o) {
            return;
        }
        if (ns == ne) {
            tree[id].apply(ns, ne, v, t);
            return;
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        update(qs, qe, l, ns, md, v, t);
        update(qs, qe, r, md + 1, ne, v, t);
        pull(id, ns, ne);
    }

    void update(int qs, int qe, int id, int ns, int ne, int v) {
        if (qs > ne || qe < ns) return;
        if (qs <= ns && qe >= ne) {
            tree[id].apply(ns, ne, v);
            return;
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        update(qs, qe, l, ns, md, v);
        update(qs, qe, r, md + 1, ne, v);
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

int n, q;
vector<int> a;

int t, l, r, x;
void test_case() {
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegTree sg = SegTree(a);
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> l >> r >> x;
            --l, --r;
            sg.upd(l, r, x, 1);
        } else if (t == 2) {
            cin >> l >> x;
            --l;
            sg.upd(l, l, x);
        } else {
            cin >> l >> r;
            --l, --r;
            auto ans = sg.get(l, r);
            int rs = 0;
            for (int i = B - 1; i >= 0; i--) {
                if (ans.b[i] && (rs & (1 << i)) == 0) {
                    rs = ans.b[i] ^ rs;
                }
            }
            cout << rs << endl;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
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
