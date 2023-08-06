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
        ll add = 0;
        ll mn = 0;
        node() {
            // define initial values
            mn = add = 0;
        }
        void apply(int ns, int ne, ll v) {
            // define apply operation
            if (mn < 1e18) mn += v;
            add += v;
        }
        void apply(int ns, int ne, ll v, int k) {
            // define apply operation
            mn = v;
        }
    };

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

    int getFirstOnCondition(int qs, int qe, ll v, int id, int ns, int ne) {
        if (qs > ne || qe < ns) return -1;
        if (tree[id].mn != v) return -1;
        if (ns == ne) return ns;
        push(id, ns, ne);
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        int p = getFirstOnCondition(qs, qe, v, l, ns, md);
        if (p == -1) {
            p = getFirstOnCondition(qs, qe, v, r, md + 1, ne);
        }
        pull(id, l, r);
        return p;
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

    int getFirstOnCondition(int qs, int qe, ll v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        return getFirstOnCondition(qs, qe, v, 0, 0, n - 1);
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

ll h[N], s[N];
int bef[N];
int nxt[N];
int n;

void link(int u, int v) {
    nxt[u] = v;
    bef[v] = u;
}

void rem(int u, segtree &sg) {
    int b = bef[u];
    int nx = nxt[u];
    ll val = sg.get(nx, nx).mn;
    ll initial = (h[nx] + s[u] - 1) / s[u];
    h[nx] = max(0ll, h[nx] - (initial - val) * s[u]);
    link(b, nx);
    ll x = (h[nx] + s[bef[nx]] - 1) / s[bef[nx]];
    sg.upd(nx, nx, x, 1);
    sg.upd(u, u, 1e18, 1);
}

void test_case() {
    cin >> n;
    segtree sg = segtree(n);
    for (int i = 0; i < n; i++) {
        nxt[i] = (i + 1) % n;
        bef[i] = (i + n - 1) % n;
    }
    for (int i = 0; i < n; i++) {
        cin >> h[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    for (int i = 0; i < n; i++) {
        ll x = (h[i] + s[bef[i]] - 1) / s[bef[i]];
        sg.upd(i, i, x, 1);
    }
    int cur = 0;
    for (int i = 0; i < n; i++) {
        ll mn = sg.get(0, n - 1).mn;
        int p;
        if (sg.get(cur, cur).mn <= 0) {
            int nxp = nxt[cur];
            p = cur;
            sg.upd(nxp, nxp, -1);
            rem(cur, sg);
            cur = nxp;
        } else {
            cur = nxt[cur];
            p = sg.getFirstOnCondition(cur, n - 1, mn);
            if (p == -1) {
                p = sg.getFirstOnCondition(0, cur - 1, mn);
            }
            int nxp = nxt[p];
            if (mn > 1) {
                sg.upd(0, n - 1, -(mn - 1));
            }
            if (p >= cur) {
                sg.upd(cur, p, -1);
            } else {
                sg.upd(cur, n - 1, -1);
                sg.upd(0, p, -1);
            }
            sg.upd(nxp, nxp, -1);
            cur = nxp;
            rem(p, sg);
        }
        cout << p + 1 << " ";
    }
    cout << endl;
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
