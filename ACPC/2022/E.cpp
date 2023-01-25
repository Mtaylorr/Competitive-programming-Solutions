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
    int compress(ll x) {
        return (lower_bound(all(values), x) - values.begin()) + 1;
    }
    ll decompress(int p) { return values[p - 1]; }
} compressor;

const int MAXRT = N * 30;

struct DynSegTree {
    int vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    int defalt_value = 0;

    void init() { ndcnt = 0; }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    int mrg(int u, int v) { return (u + v); }

    int getval(int u) {
        if (u != -1) {
            return vals[u];
        }
        // define here the default value
        return defalt_value;
    }

    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = defalt_value;
        return ndcnt++;
    }
    void pull_up(int &id) { vals[id] = mrg(getval(lch[id]), getval(rch[id])); }

    void apply(int old_idx, int new_idx, int v) {
        vals[new_idx] = mrg(v, getval(old_idx));
    }

    template <typename... M>
    int modify(int cur, int p, int l, int r, const M &...v) {
        if (l == r) {
            int idx = addnode();
            apply(cur, idx, v...);
            return idx;
        }
        int md = l + (r - l) / 2;
        int idx = addnode();
        if (p <= md) {
            lch[idx] = modify(left(cur), p, l, md, v...);
            rch[idx] = right(cur);
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), p, md + 1, r, v...);
        }
        pull_up(idx);
        return idx;
    }

    int firstOnCondition(int nd, int k, int l, int r) {
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int sum = getval(left(nd));
        if (sum >= k) {
            return firstOnCondition(left(nd), k, l, md);
        }
        return firstOnCondition(right(nd), k, md + 1, r);
    }
} sg;

struct FenwickTree {
    vector<ll> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    int mrg(ll &x, ll &y) { return x + y; }

    void upd(int x, ll v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    ll getprefix(int x) {
        if (x <= 0) return 0;
        ll rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    ll getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
} ft[2];

int n, k, X;
int a[N], b[N];
int pref[N];
int suff[N];
ll calc(int u, int i) {
    if (u == 0) {
        return 0;
    }
    int left_pos = sg.firstOnCondition(pref[i], i - u + 1, 1, compressor.n);
    int right_pos =
        sg.firstOnCondition(suff[i + 1], n - i - u + 1, 1, compressor.n);
    ll lsm = ft[0].getrange(left_pos, compressor.n);
    ll rsm = ft[1].getrange(right_pos, compressor.n);
    return X * 1ll * u - lsm - rsm;
}

void test_case() {
    compressor.init();
    cin >> n >> k >> X;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        compressor.add(a[i]);
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
        compressor.add(b[i]);
    }
    compressor.run();
    ft[0].init(compressor.n + 1);
    ft[1].init(compressor.n + 1);
    sg.init();
    pref[0] = sg.addnode();
    for (int i = 1; i <= n; i++) {
        int x = compressor.compress(a[i]);
        pref[i] = sg.modify(pref[i - 1], x, 1, compressor.n, 1);
    }
    suff[n + 1] = sg.addnode();
    for (int i = n; i >= 1; i--) {
        int x = compressor.compress(b[i]);
        suff[i] = sg.modify(suff[i + 1], x, 1, compressor.n, 1);
        ft[1].upd(x, b[i]);
    }
    ll ans = 1e18;
    for (int i = 0; i <= n; i++) {
        int l = 0;
        int r = min(k, min(i, n - i));
        ll sm = calc(l, i);
        sm += ft[0].getprefix(compressor.n);
        sm += ft[1].getprefix(compressor.n);
        ll curans = sm;
        while (l < r) {
            int md = (l + r + 1) / 2;
            ll nsm = calc(md, i);
            if (nsm + sm < curans) {
                curans = nsm + sm;
                l = md;
            } else {
                r = md - 1;
            }
        }
        ans = min(ans, curans);
        if (i + 1 <= n) {
            ft[1].upd(compressor.compress(b[i + 1]), -b[i + 1]);
            ft[0].upd(compressor.compress(a[i + 1]), a[i + 1]);
        }
    }
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
