//https://codeforces.com/problemset/problem/1093/G

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
int n, k;
int po[10];
class segtree {
   public:
    struct node {
        // define the variables
        int add = 0;
        vector<int> mx, mn;
        node() {
            // define initial values
            mx.assign(po[k], -1e9);
            mn.assign(po[k], 1e9);
        }
        void apply(int ns, int ne, vector<int> v) {
            // define apply operation
            for (int i = 0; i < po[k]; i++) {
                int rs = 0;
                for (int j = 0; j < k; j++) {
                    if (i & (po[j])) {
                        rs += v[j];
                    } else {
                        rs -= v[j];
                    }
                }
                mx[i] = rs;
                mn[i] = rs;
            }
        }
    };

    void unite(const node &a, const node &b, node &res) const {
        // define the union operation
        for (int i = 0; i < po[k]; i++) {
            res.mx[i] = max(a.mx[i], b.mx[i]);
            res.mn[i] = min(a.mn[i], b.mn[i]);
        }
    }

    inline void pull(int id, int l, int r) {
        tree[id] = {};
        unite(tree[l], tree[r], tree[id]);
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
    void get(int qs, int qe, int id, int ns, int ne, node &res) {
        if (qs <= ns && qe >= ne) {
            return unite(tree[id], res, res);
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        if (qe <= md) {
            get(qs, qe, l, ns, md, res);
        } else {
            if (qs > md) {
                get(qs, qe, r, md + 1, ne, res);
            } else {
                get(qs, qe, l, ns, md, res);
                get(qs, qe, r, md + 1, ne, res);
            }
        }
        pull(id, l, r);
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
        node res = {};
        get(qs, qe, 0, 0, n - 1, res);
        return res;
    }
    node get(int p) {
        assert(0 <= p && p <= n - 1);
        node res = {};
        get(p, p, 0, 0, n - 1, res);
        return res;
    }

    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, v...);
    }
};

vector<vector<int> > a;
void test_case() {
    cin >> n >> k;
    for (int i = 0; i < 10; i++) {
        po[i] = 1 << i;
    }
    for (int i = 0; i < n; i++) {
        a.emplace_back();
        for (int j = 0; j < k; j++) {
            int x;
            cin >> x;
            a[i].pb(x);
        }
    }
    segtree sg = segtree(a);
    int q;
    cin >> q;
    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int p;
            cin >> p;
            --p;
            vector<int> tmp;
            for (int i = 0; i < k; i++) {
                int x;
                cin >> x;
                tmp.pb(x);
            }
            sg.upd(p, p, tmp);
        } else {
            int l, r;
            cin >> l >> r;
            --l, --r;
            auto rs = sg.get(l, r);
            int ans = -1e9;
            for (int i = 0; i < po[k]; i++) {
                ans = max(ans, rs.mx[i] - rs.mn[i]);
            }
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
