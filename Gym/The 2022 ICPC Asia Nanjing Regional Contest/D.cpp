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
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    T getprefix(int x) {
        if (x <= 0) return 0;
        T rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    T getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
};
FenwickTree<int> ft[2];
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
} compressor[2];

ll n, k, m, c, d;
ll a[N];
ll b[N];

int cnt(ll u, ll i) {
    int p0 = compressor[0].compress(u + 1);
    ll ans = ft[0].getprefix(p0);
    int p1 = compressor[1].compress(u + i * d + 1);
    // dbg(ans);
    // dbg(u + c + i * d);
    ans += ft[1].getprefix(p1);
    // dbg(ans);
    return ans;
}

void addUpd(ll u, ll i) {
    ft[1].upd(1 + compressor[1].compress(u + c + i * d), 1);
}
void addReg(ll u, ll i) { ft[0].upd(1 + compressor[0].compress(u), 1); }

void remUpd(ll u, ll i) {
    ft[1].upd(1 + compressor[1].compress(u + c + i * d), -1);
}
void remReg(ll u, ll i) { ft[0].upd(1 + compressor[0].compress(u), -1); }

void test_case() {
    cin >> n >> k >> m >> c >> d;
    compressor[0].init();
    compressor[1].init();
    ft[0].init(n + 1);
    ft[1].init(n + 1);
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        b[i] = a[i];
        compressor[0].add(a[i]);
        compressor[1].add(a[i] + c + d * i);
    }
    compressor[0].run();
    compressor[1].run();
    sort(b, b + n);
    ll ans = b[n - k];
    for (int i = 0; i < m - 1; i++) {
        addUpd(a[i], i);
    }
    for (int i = m - 1; i < n; i++) {
        addReg(a[i], i);
    }
    for (int i = m - 1; i < n; i++) {
        remReg(a[i], i);
        addUpd(a[i], i);
        ll l = 0;
        ll r = 1e15;
        while (l < r) {
            ll md = (l + r) / 2;
            ll cn = cnt(md, i - m + 1);
            // dbg(md, cn, n - k + 1);
            if (cn < n - k + 1) {
                l = md + 1;
            } else {
                r = md;
            }
        }
        // dbg(l);
        ans = max(ans, l);
        remUpd(a[i - m + 1], i - m + 1);
        addReg(a[i - m + 1], i - m + 1);
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
