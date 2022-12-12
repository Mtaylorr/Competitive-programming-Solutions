//https://www.spoj.com/problems/METEORS/
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
        ll add = 0;
        ll sm = 0;
        node() {
            // define initial values
            sm = 0;
        }
        void apply(int ns, int ne, int v) {
            // define apply operation
            sm += v;
        }
    };

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
        return ;
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

    node get(int qp, int id, int ns, int ne) {
        node res{};
        if (qp >= ns && qp <= ne) {
            res = tree[id];
        }
        if (ns == ne) {
            return res;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        push(id, ns, ne);
        if (qp <= md) {
            res = unite(res, get(qp, l, ns, md));
        } else {
            res = unite(res, get(qp, r, md + 1, ne));
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
        tree.resize(2 * n - 1);
        build(0, 0, n - 1, v);
    }

    node get(int qs, int qe) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        return get(qs, qe, 0, 0, n - 1);
    }
    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(p, 0, 0, n - 1);
    }

    template <typename... M>
    void modify(int qs, int qe, const M &...v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, v...);
    }
};

int n, m;
vector<int> owns[N];
int intend[N];
int k, ql[N], qr[N], qa[N];
int ans[N];

void add_query(int id, int c, segtree &sg) {
    if (ql[id] <= qr[id]) {
        sg.modify(ql[id], qr[id], c * qa[id]);
    } else {
        sg.modify(0, qr[id], c * qa[id]);
        sg.modify(ql[id], m - 1, c * qa[id]);
    }
    int x = sg.get(0).sm;
}

void rec(int low, int high, vector<int> &owners, int &q_idx, segtree &sg) {
    if (owners.size() == 0) return;
    int md = low + (high - low) / 2;
    while (q_idx < md) {
        add_query(++q_idx, 1, sg);
    }
    while (q_idx > md) {
        add_query(q_idx--, -1, sg);
    }
    vector<int> left_owners, right_owners;
    for (auto o : owners) {
        ll sm = 0;
        for (auto s : owns[o]) {
            sm += sg.get(s).sm;
            if (sm >= intend[o]) break;
        }
        if (sm >= intend[o]) {
            ans[o] = high + 1;
            left_owners.pb(o);
        } else {
            right_owners.pb(o);
        }
    }
    owners.clear();
    if (low == high) return;
    rec(low, md, left_owners, q_idx, sg);
    rec(md + 1, high, right_owners, q_idx, sg);
}

void solve() {
    cin >> n >> m;
    segtree sg = segtree(m);
    for (int i = 0; i < m; i++) {
        int x;
        cin >> x;
        --x;
        owns[x].pb(i);
    }
    vector<int> owners;
    for (int i = 0; i < n; i++) {
        cin >> intend[i];
        ans[i] = 1e9;
        owners.pb(i);
    }
    cin >> k;
    for (int i = 0; i < k; i++) {
        cin >> ql[i] >> qr[i] >> qa[i];
        ql[i]--;
        qr[i]--;
    }
    int q_idx = -1;
    rec(0, k - 1, owners, q_idx, sg);
    for (int i = 0; i < n; i++) {
        if (ans[i] < 1e9) {
            cout << ans[i] << "\n";
        } else {
            cout << "NIE\n";
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
