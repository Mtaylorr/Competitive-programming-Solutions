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
    T mrg(T &x, T &y) { return max(x, y); }

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

int grid[1005][1005];
int n, m;
void test_case() {
    cin >> n >> m;
    vector<pair<int, int> > v;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> grid[i][j];
            if (grid[i][j]) {
                v.pb({-i, -j});
            }
        }
    }
    sort(all(v));
    ft.init(m + 1);
    int ans = 0;
    for (auto &u : v) {
        int y = -u.se;
        int r = 1 + ft.getprefix(y);
        ans = max(ans, r);
        ft.upd(y + 1, r);
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
