//https://codeforces.com/contest/1710/problem/B
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
        ll mx = 0;
        node() {
            // define initial values
            mx = 0;
        }
        void apply(int ns, int ne, ll v) {
            // define apply operation
            mx = v;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.mx = max(a.mx, b.mx);
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
    segtree() {}

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
        return get(p, p, 0, 0, n - 1);
    }

    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, v...);
    }
};

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    ll decompress(int p) { return values[p]; }
} compressor;

int n, m;
ll initial[N];
ll add[2][N], rem[N];
ll x[N], p[N];

void solve() {
    cin >> n >> m;
    compressor.init();
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> p[i];
        compressor.add(x[i]);
        compressor.add(x[i] + p[i]);
        compressor.add(x[i] - p[i]);
    }
    compressor.run();
    vector<segtree> sg;
    for (int i = 0; i < 3; i++) {
        sg.pb(segtree(compressor.n));
    }
    for (int i = 0; i < compressor.n; i++) {
        initial[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        int pos = compressor.compress(x[i]);
        int nxpos = compressor.compress(x[i] + p[i]);
        add[0][pos]++;
        add[1][pos] += p[i];
        rem[nxpos]++;
    }
    ll cursum = 0;
    ll curcnt = 0;
    int bef = -1;
    for (int i = 0; i < compressor.n; i++) {
        ll x_decompressed = compressor.decompress(i);
        cursum -= curcnt * (x_decompressed - bef);
        cursum += add[1][i];
        curcnt += add[0][i];
        initial[i] += cursum;
        curcnt -= rem[i];
        add[1][i] = add[0][i] = rem[i] = 0;
        bef = x_decompressed;
    }
    for (int i = 0; i < n; i++) {
        int pos = compressor.compress(x[i]);
        int nxpos = compressor.compress(x[i] - p[i]);
        add[0][pos]++;
        add[1][pos] += p[i];
        rem[nxpos]++;
    }
    cursum = 0;
    curcnt = 0;
    bef = -1;
    for (int i = compressor.n - 1; i >= 0; i--) {
        ll x_decompressed = compressor.decompress(i);
        cursum -= curcnt * (bef - x_decompressed);
        cursum += add[1][i];
        curcnt += add[0][i];
        initial[i] += cursum;
        curcnt -= rem[i];
        add[1][i] = add[0][i] = rem[i] = 0;
        bef = x_decompressed;
    }
    for (int i = 0; i < n; i++) {
        int pos = compressor.compress(x[i]);
        initial[pos] -= p[i];
    }
    for (int i = 0; i < compressor.n; i++) {
        int x_decompressed = compressor.decompress(i);
        sg[0].upd(i, i, initial[i]);
        sg[1].upd(i, i, initial[i] + x_decompressed);
        sg[2].upd(i, i, initial[i] - x_decompressed);
    }
    for (int i = 0; i < n; i++) {
        int pos = compressor.compress(x[i]);
        int l = compressor.compress(x[i] - p[i]);
        int r = compressor.compress(x[i] + p[i]);
        ll ans = 0;
        if (r < compressor.n - 1) {
            ans = max(ans, sg[0].get(r + 1, compressor.n - 1).mx);
        }
        if (l > 0) {
            ans = max(ans, sg[0].get(0, l - 1).mx);
        }
        ans = max(ans, sg[1].get(pos, r).mx - (p[i] + x[i]));
        ans = max(ans, sg[2].get(l, pos).mx - (p[i] - x[i]));
        if (ans > m) {
            cout << 0;
        } else {
            cout << 1;
        }
    }
    cout << "\n";
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        solve();
    }
    return 0;
}
