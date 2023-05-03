//https://codeforces.com/problemset/problem/1194/E
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
} compressor;

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
FenwickTree<int> ft;

int x[2][N], y[2][N];
vector<int> v[2];
int n;

int getsum(int x) { return x * (x - 1) / 2; }

void test_case() {
    compressor.init();
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[0][i] >> y[0][i] >> x[1][i] >> y[1][i];
        if (x[0][i] == x[1][i]) {
            if (y[0][i] > y[1][i]) {
                swap(y[0][i], y[1][i]);
            }
            v[0].pb(i);
        } else {
            if (x[0][i] > x[1][i]) {
                swap(x[0][i], x[1][i]);
            }
            v[1].pb(i);
        }
        compressor.add(y[0][1]);
        compressor.add(y[1][i]);
    }
    compressor.run();
    ft.init(compressor.n + 1);
    sort(all(v[0]), [](int &a, int &b) { return x[0][a] < x[0][b]; });
    sort(all(v[1]), [](int &a, int &b) { return x[1][a] < x[1][b]; });
    ll ans = 0;
    vector<int> tmp;
    for (int i = 0; i < v[0].size(); i++) {
        int a = v[0][i];
        int k = 0;
        tmp.clear();
        ft.init(compressor.n + 1);
        for (auto u : v[1]) {
            if (x[0][u] <= x[0][a]) {
                tmp.pb(u);
                ft.upd(compressor.compress(y[0][u]) + 1, 1);
            }
        }
        for (int j = i + 1; j < v[0].size(); j++) {
            int b = v[0][j];
            while (k < tmp.size() && x[1][tmp[k]] < x[0][b]) {
                ft.upd(compressor.compress(y[0][tmp[k]]) + 1, -1);
                k++;
            }
            int lf = max(y[0][a], y[0][b]);
            int rg = min(y[1][a], y[1][b]);
            if (lf <= rg) {
                ans += getsum(ft.getrange(compressor.compress(lf) + 1,
                                          compressor.compress(rg) + 1));
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
    while (T--) {
        test_case();
    }
    return 0;
}
