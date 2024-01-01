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
struct node {
    // define states here
    bool has_lazy;
    int lazy = 0;
    int mx = 0, mn = 0;
    ll sm = 0;
    node() {
        // initialize states here
        has_lazy = false;
        lazy = 0;
        mx = mn = sm = 0;
    }

    void apply(int ns, int ne, int v) {
        // update value
        mn = mx = v;
        sm = v * 1ll * (ne - ns + 1);
        // update lazy
        has_lazy = 1;
        lazy = v;
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
        res.mx = max(l.mx, r.mx);
        res.mn = min(l.mn, r.mn);
        res.sm = l.sm + r.sm;
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
            if (tree[id].mn > k) return -1;
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

    void calcAns(int qs, int qe, int id, int ns, int ne, int &cur, int &ans) {
        if (qs > ne || qe < ns) return;
        if (qs <= ns && qe >= ne) {
            if (tree[id].mn > cur) return;
            if (tree[id].mn == tree[id].mx) {
                int k = cur / (tree[id].mx);
                k = min(ne - ns + 1, k);
                cur -= k * tree[id].mn;
                ans += k;
                return;
            }
            if (tree[id].sm <= cur) {
                cur -= tree[id].sm;
                ans += (ne - ns + 1);
                return;
            }
        }
        if (ns == ne) {
            return;
        }
        push(id, ns, ne);
        int p;
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        calcAns(qs, qe, l, ns, md, cur, ans);
        calcAns(qs, qe, r, md + 1, ne, cur, ans);
        pull(id, ns, ne);
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

    void calcAns(int qs, int qe, int &cur, int &ans) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        calcAns(qs, qe, 0, 0, n - 1, cur, ans);
    }
    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        update(qs, qe, 0, 0, n - 1, v...);
    }
};

int n, q;
vector<int> a;
int t, x, y;
void test_case() {
    cin >> n >> q;
    a.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    SegTree sg = SegTree(a);
    while (q--) {
        cin >> t >> x >> y;
        x--;
        if (t == 1) {
            int p = sg.getFirstOnCondition(0, n - 1, 0, y);
            if (p != -1 && p <= x) {
                sg.upd(p, x, y);
            }
        } else {
            int ans = 0;
            sg.calcAns(x, n - 1, y, ans);
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
