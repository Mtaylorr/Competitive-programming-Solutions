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
    int greatestSmallerThanOrEqual(ll x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    int greaterThanOrEqual(ll x) {
        return (lower_bound(all(values), x) - values.begin());
    }
    ll decompress(int p) { return values[p]; }
} compressor, c_compressor;

const int MAXRT = 2e7;
template <typename T>
class DynSegTree {
   public:
    vector<int> deleted;
    T vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    T defalt_value = 0;

    void init() {
        ndcnt = 0;
        deleted.clear();
    }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    T mrg(T u, T v) { return max(u, v); }

    T getval(int u) {
        if (u != -1) {
            return vals[u];
        }
        // define here the default value
        return defalt_value;
    }

    void delnode(int u) { deleted.pb(u); }

    int addnode() {
        int x = ndcnt;
        if (deleted.size()) {
            x = deleted.back();
            deleted.pop_back();
        } else {
            ndcnt++;
        }
        lch[x] = rch[x] = -1;
        vals[x] = defalt_value;
        return x;
    }
    void pull_up(int &id) { vals[id] = mrg(getval(lch[id]), getval(rch[id])); }

    void apply(int old_idx, int new_idx, T v) {
        vals[new_idx] = mrg(v, getval(old_idx));
    }

    template <typename... M>
    int modify(int cur, int p, ll l, ll r, bool inplace, const M &...v) {
        if (l == r) {
            int idx = cur;
            if (cur == -1 || !inplace) {
                idx = addnode();
            }
            apply(cur, idx, v...);
            return idx;
        }
        int md = l + (r - l) / 2;
        int idx = cur;
        if (cur == -1 || !inplace) {
            idx = addnode();
        }
        if (p <= md) {
            lch[idx] = modify(left(cur), p, l, md, inplace, v...);
            rch[idx] = right(cur);
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), p, md + 1, r, inplace, v...);
        }
        pull_up(idx);
        return idx;
    }

    T query(int nd, int qs, int qe, ll l, ll r) {
        // dbg(qs, qe, l, r, nd);
        if (nd == -1) return getval(-1);

        if (qs <= l && qe >= r) {
            return getval(nd);
        }
        int md = l + (r - l) / 2;
        if (qe <= md) {
            return query(left(nd), qs, qe, l, md);
        } else {
            if (qs > md) {
                return query(right(nd), qs, qe, md + 1, r);
            } else {
                return mrg(query(left(nd), qs, qe, l, md),
                           query(right(nd), qs, qe, md + 1, r));
            }
        }
    }
};
DynSegTree<ll> sg;

int p[N], a[N], c[N], x[N];
vector<int> stations[N];
int n, k;
int roots[2][N];
int lidx[N];
int lc[N], rc[N], cc[N];

void test_case() {
    compressor.init();
    c_compressor.init();
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < n; i++) {
        compressor.add(p[i] - a[i] - 1);
        compressor.add(p[i] + a[i]);
        c_compressor.add(c[i] + x[i]);
        c_compressor.add(c[i] - x[i]);
        c_compressor.add(c[i]);
    }
    compressor.run();
    c_compressor.run();
    for (int i = 0; i < compressor.n; i++) {
        stations[i].clear();
    }

    for (int i = 0; i < n; i++) {
        stations[compressor.compress(p[i] + a[i])].pb(i);
        lidx[i] = compressor.compress(p[i] - a[i] - 1);
        rc[i] = c_compressor.compress(c[i] + x[i]);
        lc[i] = c_compressor.compress(c[i] - x[i]);
        cc[i] = c_compressor.compress(c[i]);
    }

    sg.init();
    for (int i = 0; i < compressor.n; i++) {
        roots[0][i] = sg.addnode();
    }

    ll ans = 0;

    for (int j = 1; j <= k; j++) {
        int id = j & 1;
        for (int i = 0; i < compressor.n; i++) {
            if (i - 1 >= 0)
                roots[id][i] = roots[id][i - 1];
            else
                roots[id][i] = sg.addnode();
            for (auto u : stations[i]) {
                ll vall = sg.query(roots[id ^ 1][lidx[u]], 0, lc[u], 0,
                                   c_compressor.n-1);
                // dbg(i, j, u, lidx[u], c[u] + x[u], c[u] - x[u]);
                ll valr = sg.query(roots[id ^ 1][lidx[u]], rc[u],
                                   c_compressor.n-1, 0, c_compressor.n-1);
                // dbg(i, j, u, lidx[u]);
                vall += c[u];
                valr += c[u];
                vall = max(vall, valr);
                ans = max(ans, vall);
                roots[id][i] =
                    sg.modify(roots[id][i], cc[u], 0, c_compressor.n-1, 0, vall);
            }
        }
    }
    cout << ans << endl;
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
