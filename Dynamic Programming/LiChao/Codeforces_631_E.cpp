//https://codeforces.com/contest/631/problem/E
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
const int N = 2e5 + 5;

const int MAXND_LI_CHAO = N * 30;

typedef long long ftype;
typedef complex<ftype> point;
#define x real
#define y imag

struct LiChaoTree {
    point vals[MAXND_LI_CHAO];
    point initial_pt = {0, (long long)1e18};
    int lch[MAXND_LI_CHAO], rch[MAXND_LI_CHAO], ndcnt = 0;
    bool is_min;
    ftype lb, ub;
    ftype dot(point a, point b) { return (conj(a) * b).x(); }
    ftype f(point a, ftype x) { return dot(a, {x, 1}); }
    int init(ftype _lb, ftype _ub, bool _min = true) {
        lb = _lb;
        ub = _ub;
        ndcnt = 0;
        is_min = _min;
        if (is_min) {
            initial_pt = {0, (ll)1e18};
        } else {
            initial_pt = {0, (ll)-1e18};
        }
        return addnode();
    }
    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }
    int addnode() {
        lch[ndcnt] = rch[ndcnt] = -1;
        vals[ndcnt] = initial_pt;
        return ndcnt++;
    }
    int addnode(int p) {
        int np = addnode();
        if (p != -1) vals[np] = vals[p];
        return np;
    }

    int modify(int cur, int l, int r, point nw) {
        if (cur == -1) {
            int idx = addnode();
            vals[idx] = nw;
            return idx;
        }
        int idx = addnode(cur);
        int md = (l + r) / 2;
        bool lef =
            is_min ? f(nw, l) < f(vals[idx], l) : f(nw, l) > f(vals[idx], l);
        bool mid = is_min ? f(nw, md) < f(vals[idx], md)
                          : f(nw, md) > f(vals[idx], md);
        if (mid) {
            swap(vals[idx], nw);
        }
        if (r - l == 1) {
            return idx;
        } else if (lef != mid) {
            lch[idx] = modify(left(cur), l, md, nw);
            rch[idx] = right(cur);
            return idx;
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), md, r, nw);
            return idx;
        }
    }
    ftype query(int nd, ftype x, int l, int r) {
        if (nd == -1) {
            return f(initial_pt, x);
        }
        int md = (l + r) / 2;
        if (r - l + 1 == 1) {
            return f(vals[nd], x);
        } else if (x < md) {
            return is_min ? min(f(vals[nd], x), query(left(nd), x, l, md))
                          : max(f(vals[nd], x), query(left(nd), x, l, md));
        } else {
            return is_min ? min(f(vals[nd], x), query(right(nd), x, md, r))
                          : max(f(vals[nd], x), query(right(nd), x, md, r));
        }
    }

    int modify(int cur, point nw) { return modify(cur, lb, ub, nw); }

    ftype query(int nd, ftype x) { return query(nd, x, lb, ub); }
} lichao;

int n, a[N];
ll sm[N];
ll sm2[N];

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        sm[i] = sm[i - 1] + a[i];
        sm2[i] = sm2[i - 1] + i * 1ll * a[i];
    }
    int src = lichao.init(-1e6, 1e6, 0);
    ll ans = sm2[n];
    for (int i = 1; i <= n; i++) {
        src = lichao.modify(src, {i, -sm[i - 1]});
        ll r = lichao.query(src, a[i]);
        ll rs = sm2[n] + sm[i - 1] - i *1ll* a[i] + r;
        ans = max(ans, rs);
    }
    src = lichao.init(-1e6,1e6,0);
    for (int i = n; i >= 1; i--) {
        src = lichao.modify(src, {i, -sm[i]});
        ll r = lichao.query(src, a[i]);
        ll rs = sm2[n] + sm[i] - i *1ll* a[i] + r;
        ans = max(ans, rs);
    }
    cout << ans;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    T = 1;  // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
