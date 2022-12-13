//https://www.hackerearth.com/fr/challenges/competitive/may-circuits/algorithm/make-n00b_land-great-again-circuits/description/
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
const int N = 5e5 + 5;

#define left(x) (2 * (x) + 1)
#define right(x) (2 * (x) + 2)
#define mid(ns, ne) ((ns) + ((ne) - (ns)) / 2)

class segtree {
   public:
    struct node {
        // define the variables
        int add = 0;
        ll X;
        ll D;
        node() {
            // define initial values
            X = D  = 0;
        }

        void apply(int ns, int ne, ll x, ll d, int dpth) {
            // define apply operation
            X += x-d*1ll*dpth;
            D += d;
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.X = a.X + b.X;
        res.D = a.D + b.D;
        return res;
    }

    inline void push(int id, int ns, int ne) { return; }

    inline void pull(int id, int l, int r) {
        return;
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

    node get(int p, int id, int ns, int ne) {
        node res{};
        if (ns <= p && ne >= p) {
            res = unite(res, tree[id]);
        }
        if (ns == ne) return res;
        int md = mid(ns, ne);
        int l = left(id);
        int r = right(id);
        if (p <= md) {
            res = unite(res, get(p, l, ns, md));
        } else {
            res = unite(res, get(p, r, md + 1, ne));
        }
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
    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(p, 0, 0, n - 1);
    }

    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, v...);
    }
};

vector<int> adj[N];
vector<int> owns[N];
int ans[N];
ll th[N];
int n, m, q;
ll F[N], X[N], D[N];
int tin[N], tout[N], timer;
ll dpth[N];

void add_query(int id, int mul, segtree &sg) {
    int u = F[id];
    sg.upd(tin[u], tout[u], X[id] * mul, D[id] * mul, dpth[u]);
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
        for (auto c : owns[o]) {
            auto r = sg.get(tin[c]);
            sm += r.X;
            sm += r.D * 1ll * dpth[c];
            if (sm >= th[o]) break;
        }
        if (sm >= th[o]) {
            ans[o] = high + 1;
            left_owners.pb(o);
        } else {
            right_owners.pb(o);
        }
    }
    owners.clear();
    if (high == low) return;
    rec(low, md, left_owners, q_idx, sg);
    rec(md + 1, high, right_owners, q_idx, sg);
}

void dfs(int u) {
    tin[u] = timer++;
    for (auto v : adj[u]) {
        dpth[v] = dpth[u] + 1;
        dfs(v);
    }
    tout[u] = timer - 1;
}

void solve() {
    cin >> n >> m;
    segtree sg = segtree(n);
    for (int i = 1; i < n; i++) {
        int x;
        cin >> x;
        x--;
        adj[x].pb(i);
    }
    dfs(0);
    for (int i = 0; i < n; i++) {
        int x;
        cin >> x;
        --x;
        owns[x].pb(i);
    }
    vector<int> owners;
    for (int i = 0; i < m; i++) {
        ans[i] = 1e9;
        cin >> th[i];
        owners.pb(i);
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> F[i] >> X[i] >> D[i];
        F[i]--;
    }
    int q_idx = -1;
    rec(0, q - 1, owners, q_idx, sg);
    for (int i = 0; i < m; i++) {
        if (ans[i] < 1e9) {
            cout << ans[i] << "\n";
        } else {
            cout << "rekt\n";
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
