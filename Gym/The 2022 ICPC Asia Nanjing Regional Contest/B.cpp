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
    int n;
    vector<ll> tree;

    void build(int id, int ns, int ne) {
        if (ns == ne) {
            tree[id] = 1e18;
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        build(l, ns, md);
        build(r, md + 1, ne);
        tree[id] = min(tree[l], tree[r]);
    }
    ll get(int qs, int qe, int id, int ns, int ne) {
        if (qs <= ns && qe >= ne) {
            return tree[id];
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        if (qe <= md) {
            return get(qs, qe, l, ns, md);
        } else {
            if (qs > md) {
                return get(qs, qe, r, md + 1, ne);
            } else {
                return min(get(qs, qe, l, ns, md), get(qs, qe, r, md + 1, ne));
            }
        }
    }

    void modify(int qs, int qe, int id, int ns, int ne, const ll &v) {
        if (qs <= ns && qe >= ne) {
            tree[id] = v;
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        if (qs <= md) {
            modify(qs, qe, l, ns, md, v);
        }
        if (qe > md) {
            modify(qs, qe, r, md + 1, ne, v);
        }
        tree[id] = min(tree[l], tree[r]);
    }

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    ll get(int qs, int qe) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        return get(qs, qe, 0, 0, n - 1);
    }
    ll get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(p, p, 0, 0, n - 1);
    }

    void upd(int qs, int qe, const ll &v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, v);
    }
};

const int LOGSPT = 17;
template <typename T>
class SPT {
   public:
    vector<T> spt[LOGSPT];
    int po[LOGSPT];
    vector<int> lg;
    int n;

    T mrg(T &x, T &y) { return min(x, y); }

    void init(vector<T> &v) {
        n = v.size();
        lg.assign(n + 1, 0);
        po[0] = 1;
        for (int i = 0; i < LOGSPT; i++) {
            spt[i].assign(n, 0);
            if (i > 0) po[i] = 2 * po[i - 1];
        }
        for (int i = 2; i <= n; i++) {
            lg[i] = 1 + lg[i / 2];
        }
        for (int i = 0; i < n; i++) {
            spt[0][i] = v[i];
        }
        for (int b = 1; po[b] <= n; b++) {
            for (int i = 0; i + po[b] <= n; i++) {
                spt[b][i] = min(spt[b - 1][i], spt[b - 1][i + po[b - 1]]);
            }
        }
    }
    T getLog(int l, int r) {
        int d = r - l + 1;
        T rs = 1e9;
        for (int i = LOGSPT - 1; i >= 0; i--) {
            if (po[i] <= d) {
                rs = mrg(rs, spt[i][l]);
                d -= po[i];
                l += po[i];
            }
        }
        return rs;
    }

    T get(int l, int r) {
        if (l > r) return 1e18;
        int lg2 = lg[r - l + 1];
       // dbg(l, r, lg2, spt[lg2][l], spt[lg2][r - po[lg2] + 1]);
        return min(spt[lg2][l], spt[lg2][r - po[lg2] + 1]);
    }
};
SPT<ll> spt[2];

int n, k;
int a[N];
string s;
int bef[N], aft[N];
void test_case() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    a[0] = a[n + 1] = 0;
    cin >> s;
    bef[0] = 0;
    for (int i = 1; i <= n; i++) {
        bef[i] = (s[i - 1] == '0') ? bef[i - 1] : i;
    }
    aft[n + 1] = n + 1;
    for (int i = n; i >= 1; i--) {
        aft[i] = (s[i - 1] == '0') ? aft[i + 1] : i;
    }

    segtree sgleft = segtree(n + 2);
    vector<ll> dpl, dpr;
    sgleft.upd(0, 0, 0);
    dpl.pb(0);
    ll mnans = 0;
    for (int i = 1; i <= n + 1; i++) {
        int b = max(i - k, bef[i - 1]);
        ll dp = a[i] + sgleft.get(b, i - 1);
        sgleft.upd(i, i, dp);
        mnans = dp;
        dpl.pb(dp);
    }
    segtree sgright = segtree(n + 2);
    dpr.pb(0);
    sgright.upd(n + 1, n + 1, 0);
    for (int i = n; i >= 0; i--) {
        int b = min(i + k, aft[i + 1]);
        ll dp = a[i] + sgright.get(i + 1, b);
        sgright.upd(i, i, dp);
        dpr.pb(dp);
    }
    reverse(all(dpr));
    spt[0].init(dpl);
    spt[1].init(dpr);
    int q;
    cin >> q;
    while (q--) {
        int u, v;
        cin >> u >> v;
        if (bef[u] == u) {
            cout << mnans - a[u] + v << endl;
            continue;
        }
        ll cdpl = 0;
        ll cdpr = 0;
        {
            int b = max(u - k, bef[u - 1]);
            cdpl = v + spt[0].get(b, u - 1);
        }
        {
            int b = min(u + k, aft[u + 1]);
            cdpr = v + spt[1].get(u + 1, b);
        }
        ll ans = 1e18;
        for (int i = u; i >= max(0, u - k); i--) {
            ll rs = i != u ? dpl[i] : cdpl;
            rs += min(cdpr, spt[1].get(u + 1, min(aft[u], i + k)));
            ans = min(ans, rs);
            if (bef[i] == i) break;
        }

        for (int i = u; i <= min(n + 1, u + k); i++) {
            ll rs = i != u ? dpr[i] : cdpr;
            rs += min(cdpl, spt[0].get(max(bef[u], i - k), u - 1));
            ans = min(ans, rs);
            if (aft[i] == i) break;
        }
        cout << ans << endl;
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
