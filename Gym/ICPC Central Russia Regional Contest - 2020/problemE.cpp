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

template <typename T>
class BSFenwickTree {
   public:
    vector<T> tree;
    int n;
    void init(int n, T v = 0) {
        this->n = 1 << (__lg(n) + !!(n & (n - 1)));
        tree.assign(this->n + 1, v);
    }
    T mrg(T &x, T &y) { return x + y; }

    void upd(int x, T v) {
        for (++x; x <= n; x += (x) & (-x)) tree[x - 1] = mrg(tree[x - 1], v);
    }
    T getprefix(int x) {
        if (x < 0) return 0;
        T rs = 0;
        for (++x; x; x -= (x) & (-x)) rs = mrg(rs, tree[x - 1]);
        return rs;
    }
    T getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }

    int lower_bound(T v) {
        int p = 0;
        if (tree[n - 1] < v) {
            return n;
        }
        for (int sz = n >> 1; sz; sz >>= 1) {
            if (tree[p + sz - 1] < v) {
                v -= tree[p + sz - 1];
                p += sz;
            }
        }
        return p;
    }
};

template <typename T>
class OrderedMultiSet {
   public:
    BSFenwickTree<T> ft;
    int len = 0;
    void init(int n) {
        ft.init(n);
        ft.upd(0, -1);
        len = 0;
    }
    void insert(int u) { ft.upd(u, 1), len++; }
    void erase(int u) { ft.upd(u, -1), len--; }
    int getByIdx(int u) { return ft.lower_bound(u); }
    void eraseByIdx(int idx) { erase(getByIdx(idx)); }
    int size() { return len; }
    bool empty() { return len == 0; };
};
OrderedMultiSet<int> st;

struct DSUArray {
    vector<int> id, l, r, sz;
    void init(int n) {
        id.assign(n, 0);
        l.assign(n, 0);
        r.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            l[i] = i;
            r[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        l[v] = min(l[v], l[u]);
        r[v] = max(r[v], r[u]);
        sz[v] += sz[u];
    }
} dsu;
int p[N];
int n, m;
void test_case() {
    cin >> n >> m;
    dsu.init(n);
    st.init(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        st.insert(i);
    }
    while (m--) {
        vector<int> tmp;
        int l, r;
        cin >> l >> r;
        l--;
        r--;
        int mx = -1;
        int bef = -1;
        for (int i = l; i <= r; i++) {
            int x = st.getByIdx(i);
            tmp.pb(x);
            if (mx < p[x]) {
                mx = p[x];
            }
            if (bef != -1) {
                dsu.uni(bef, x);
            }
            bef = x;
        }
        int id = dsu.getid(tmp[0]);
        p[id] = mx;
        for (auto &u : tmp) {
            if (u == id) continue;
            st.erase(u);
        }
    }
    for (int i = 0; i < n; i++) {
        if (dsu.getid(i) == i) {
            cout << p[i] << " ";
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
