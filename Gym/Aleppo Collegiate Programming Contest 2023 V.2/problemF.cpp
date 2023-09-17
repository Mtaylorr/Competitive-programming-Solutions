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

int n, a[N], m, k;
template <typename T>
class FenwickTree {
   public:
    vector<T> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    T mrg(T &x, T &y) { return x + y; }

    void upd(int x, T v) {
        x++;
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    T getprefix(int x) {
        x++;
        if (x <= 0) return 0;
        T rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    T getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
};
FenwickTree<ll> ftsum, ftcnt;
ll cursum;

void solve(int cur, ll curval, int lf, int rg, ll &cnt, ll &cursum) {
    ll c = ftcnt.getrange(lf, rg);
    ll sm = ftsum.getrange(lf, rg);
    cnt += c;
    cursum += sm + c * curval;
    // dbg(cur, curval, lf, rg, sm, c, cursum);
}

void solveAns(int cur, int lf, int rg, ll &cnt, ll &cursum) {
    if (rg <= cur) {
        solve(cur, cur, lf, rg, cnt, cursum);
    } else if (lf >= cur) {
        solve(cur, cur + m, lf, rg, cnt, cursum);
    } else {
        solve(cur, cur, lf, cur, cnt, cursum);
        solve(cur, cur + m, cur + 1, rg, cnt, cursum);
    }
}

ll calc(int u) {
    if (u >= m) {
        cursum = 0;
        return 0;
    }
    int l = u;
    int r = m - 1;

    int cur = 0;
    ll cnt = 0;
    cursum = 0;
    ftcnt.upd(0, 1);
    for (int i = 0; i < n; i++) {
        cur += a[i];
        cur %= m;
        int lf = cur - r;
        int rg = cur - l;
        // dbg(cur, lf, rg);
        if (lf < 0 && rg < 0) {
            solveAns(cur, lf + m, rg + m, cnt, cursum);

        } else if (lf >= 0 && rg >= 0) {
            solveAns(cur, lf, rg, cnt, cursum);
        } else {
            solveAns(cur, lf + m, m - 1, cnt, cursum);
            solveAns(cur, 0, rg, cnt, cursum);
        }
        ftcnt.upd(cur, 1);
        ftsum.upd(cur, -cur);
    }
    cur = 0;
    for (int i = 0; i < n; i++) {
        cur += a[i];
        cur %= m;
        ftcnt.upd(cur, -1);
        ftsum.upd(cur, +cur);
    }
    ftcnt.upd(0, -1);
    return cnt;
}

void test_case() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] %= m;
    }
    /* vector<int> tmp;
     for (int i = 0; i < n; i++) {
         int sm = 0;
         for (int j = i; j < n; j++) {
             sm += a[j];
             sm %= m;
             tmp.pb(sm);
         }
     }
     sort(all(tmp));
     for (auto &u : tmp) {
         cout << u << " ";
     }
     cout << endl;*/
    int l = 0;
    int r = m - 1;

    while (l < r) {
        int md = (l + r) / 2;
        ll x = calc(md);
        // dbg(md, x);
        if (x <= k) {
            r = md;
        } else {
            l = md + 1;
        }
    }

    ll x = calc(r);
    ll sm = cursum;
    // dbg(x, sm);
    if (k > x) {
        ll y = calc(r - 1);
        sm += (k - x) * (r - 1);
    }
    cout << sm << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    ftcnt.init(1e5 + 7);
    ftsum.init(1e5 + 7);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
