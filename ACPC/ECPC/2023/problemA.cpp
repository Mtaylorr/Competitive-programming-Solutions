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
const int M = 1e6 + 5;

const int MAXRT = N * 20;
template <typename T>
class DynSegTree {
   public:
    T vals[MAXRT];
    int lch[MAXRT], rch[MAXRT], ndcnt = 0;
    T defalt_value = 1e9;

    void init() { ndcnt = 0; }

    int left(int u) { return u == -1 ? u : lch[u]; }
    int right(int u) { return u == -1 ? u : rch[u]; }

    T mrg(T u, T v) { return min(u, v); }

    T getval(int u) {
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

    void apply(int old_idx, int new_idx, T v) {
        vals[new_idx] = mrg(v, getval(old_idx));
    }

    template <typename... M>
    int modify(int cur, int p, int l, int r, bool inplace, const M &...v) {
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

    int firstOnCondition(int nd, int qs, int qe, int l, int r,
                         function<bool(int)> ch) {
        if (qs > r || qe < l) return -1;
        if (qs <= l && qe >= r) {
            if (ch(getval(nd))) {
                return -1;
            }
        }
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int x = firstOnCondition(left(nd), qs, qe, l, md, ch);
        if (x == -1) {
            return firstOnCondition(right(nd), qs, qe, md + 1, r, ch);
        }
        return x;
    }

    T query(int nd, int qs, int qe, int l, int r) {
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
DynSegTree<int> sg;

int n, m, p, k;
ll lefts[N], rights[N];
ll a[N];
ll sum[N];
int l[N], r[N];
vector<int> pos[M];
int roots[M];

void test_case() {
    cin >> n >> m >> p >> k;
    for (int i = 1; i <= m; i++) {
        cin >> a[i];
        sum[i] = (sum[i - 1] + a[i]) % p;
        pos[a[i]].pb(i);
    }
    for (int i = m + 1; i <= n; i++) {
        a[i] = (sum[i - 1] + 0ll + p - sum[i - k - 1]) % p + 1;
        sum[i] = (sum[i - 1] + a[i]) % p;
        pos[a[i]].pb(i);
    }
    for (int i = 1; i <= n; i++) {
        cout << a[i] << " ";
    }
    cout << endl;

    sg.init();
    roots[1000001] = sg.addnode();
    for (int i = 1e6; i >= 0; i--) {
        roots[i] = roots[i + 1];
        for (int j = 0; j + i - 1 < pos[i].size(); j++) {
            roots[i] =
                sg.modify(roots[i], pos[i][j], 1, n, 0, pos[i][i + j - 1]);
        }
    }
    ll q, c, v, b;
    cin >> q >> c >> v >> b;
    ll ans = 0;
    for (int i = 1; i <= q; i++) {
        if (i > c) {
            l[i] = 1 + ((lefts[i - 1])) % n;
            r[i] = 1 + ((rights[i - 1])) % n;
            if (l[i] > r[i]) swap(l[i], r[i]);
        } else {
            cin >> l[i] >> r[i];
        }
        ll rs = 0;
        int lf = 0;
        int rg = 1e6;
        while (lf < rg) {
            int md = (lf + rg + 1) / 2;
            int x = sg.query(roots[md], l[i], r[i], 1, n);

            if (x <= r[i]) {
                lf = md;
            } else {
                rg = md - 1;
            }
        }
        rs = lf;
        ans += rs;
        ll g =
            (lefts[i - 1] - (i - 2 >= 0 ? lefts[i - 2] : 0) + l[i] * (rs + v)) %
            n;
        ll h = (rights[i - 1] - (i - 2 >= 0 ? rights[i - 2] : 0) +
                r[i] * (rs + b)) %
               n;
        lefts[i] = lefts[i - 1] + min(g, h);
        rights[i] = rights[i - 1] + max(g, h);
    }
    cout << ans << endl;
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
