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

template <typename node>
struct SegTree {
    vector<node> tree;
    vector<node> lazy;
    int n;

    void apply(int id, int ns, int ne, ll v) {  // define apply operation here
        tree[id] = v * (ne - ns + 1);
        lazy[id] = v;
    }
    node mrg(const node &l, const node &r) {
        node res;
        // merge nodes
        res = l + r;
        return res;
    }
    void pull(int id, int ns, int ne) {
        int l = 2 * id + 1;
        int r = l + 1;
        tree[id] = mrg(tree[l], tree[r]);
    }

    void push(int id, int ns, int ne) {
        if (lazy[id] && ns != ne) {
            int l = 2 * id + 1;
            int r = l + 1;
            int md = ns + (ne - ns) / 2;
            apply(l, ns, md, lazy[id]);
            apply(r, md + 1, ne, lazy[id]);
            lazy[id] = 0;
        }
    }
    template <typename M>
    void build(int id, int ns, int ne, const vector<M> &v) {
        if (ns == ne) {
            apply(id, ns, ne, v[ns]);
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

    int getFirstOnCondition(int qs, int qe, int dir, int id, int ns, int ne,
                            int k) {
        if (qs > ne || qe < ns) return -1;
        if (qs <= ns && qe >= ne) {
            // check condition on interval
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

    template <typename... M>
    void update(int qs, int qe, int id, int ns, int ne, const M &...v) {
        if (qs > ne || qe < ns) return;
        if (qs <= ns && qe >= ne) {
            apply(id, ns, ne, v...);
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
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(0, 0, n - 1);
    }
    SegTree(const vector<node> &v) {
        n = v.size();
        tree.assign(4 * n, 0);
        lazy.assign(4 * n, 0);
        build(0, 0, n - 1, v);
    }
    node query(int qs, int qe) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        return query(qs, qe, 0, 0, n - 1);
    }

    node query(int p) {
        assert(p >= 0 && p <= n - 1);
        return query(p, p, 0, 0, n - 1);
    }
    template <typename... M>
    int getFirstOnCondition(int qs, int qe, int dir, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1 && dir >= 0 && dir <= 1);
        return getFirstOnCondition(qs, qe, dir, 0, 0, n - 1, v...);
    }
    template <typename... M>
    void update(int qs, int qe, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        update(qs, qe, 0, 0, n - 1, v...);
    }
};

const int E = 1e6 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E];

    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }

    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;
using ul = uint64_t;
using db = long double;

class Pollard {
   public:
    map<ul, int> cnt_primes;
    vector<ul> primes, divisors;
    ul modMul(ul a, ul b, const ul mod) {
        ll ret = a * b - mod * (ul)((db)a * b / mod);
        return ret + ((ret < 0) - (ret >= (ll)mod)) * mod;
    }
    ul modPow(ul a, ul b, const ul mod) {
        if (b == 0) return 1;
        ul res = modPow(a, b / 2, mod);
        res = modMul(res, res, mod);
        return b & 1 ? modMul(res, a, mod) : res;
    }

    bool rabin_miller(ul n) {  // not ll!
        if (n < 2 || n % 6 % 4 != 1) return n - 2 < 2;
        ul A[] = {2, 325, 9375, 28178, 450775, 9780504, 1795265022},
           s = __builtin_ctzll(n - 1), d = n >> s;
        for (auto a : A) {  // ^ count trailing zeroes
            ul p = modPow(a, d, n), i = s;
            while (p != 1 && p != n - 1 && a % n && i--) p = modMul(p, p, n);
            if (p != n - 1 && i != s) return 0;
        }
        return 1;
    }
    ul pollard(ul n) {  // return some nontrivial factor of n
        auto f = [n, this](ul x) { return modMul(x, x, n) + 1; };
        ul x = 0, y = 0, t = 30, prd = 2, i = 1, q;
        while (t++ % 40 ||
               __gcd(prd, n) == 1) {  /// speedup: don't take gcd every it
            if (x == y) x = ++i, y = f(x);
            if ((q = modMul(prd, max(x, y) - min(x, y), n))) prd = q;
            x = f(x), y = f(f(y));
        }
        return __gcd(prd, n);
    }
    void factor_rec(ul n, map<ul, int> &cnt) {
        if (n == 1) return;
        if (rabin_miller(n)) {
            ++cnt[n];
            return;
        }
        ul u = pollard(n);
        factor_rec(u, cnt), factor_rec(n / u, cnt);
    }
    void calcDivisorsRec(ul cur, int i) {
        if (i >= primes.size()) {
            divisors.pb(cur);
            return;
        }
        int r = cnt_primes[primes[i]];
        for (int j = 0; j <= r; j++) {
            calcDivisorsRec(cur, i + 1);
            cur = cur * primes[i];
        }
    }
    void calcDivisors(ul x) {
        cnt_primes.clear();
        primes.clear();
        divisors.clear();
        factor_rec(x, cnt_primes);
        for (auto &u : cnt_primes) {
            primes.pb(u.fi);
        }
        calcDivisorsRec(1, 0);
    }
} pollard;

int n, a[N];
int tin[N], tout[N], ti = -1;
vector<ll> v;

void dfs(int u, int p = -1) {
    tin[u] = ++ti;
    v.pb(a[u]);
    neig(u, v, e, adj) {
        if (v == p) continue;
        dfs(v, u);
    }
    tout[u] = ti;
}
int t, u, val, q;
void test_case() {
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }

    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    dfs(0);
    SegTree<ll> sg = SegTree<ll>(v);
    cin >> q;
    while (q--) {
        cin >> t;
        if (t == 1) {
            cin >> u >> val;
            --u;
            sg.update(tin[u], tout[u], val);
        } else {
            cin >> u;
            --u;
            ll s = sg.query(tin[u], tout[u]);
            if (s % 2) {
                if (s <= 3) {
                    cout << "NO\n";
                } else if (pollard.rabin_miller(s - 2)) {
                    cout << "YES\n";
                } else {
                    cout << "NO\n";
                }
            } else {
                if (s <= 2) {
                    cout << "NO\n";
                } else {
                    cout << "YES\n";
                }
            }
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
