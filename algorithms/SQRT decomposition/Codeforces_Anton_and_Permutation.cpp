//https://codeforces.com/problemset/problem/785/E
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

FenwickTree<int> ft[500];
FenwickTree<int> ft0;

int n, q;
int l, r, a[N];
int B, mxB;

int getsum(int l, int r, int x) {
    if (l > r) return 0;
    if (x == 0) return 0;
    int s = l / B;
    int e = r / B;
    if (s == e) {
        int ans = 0;
        for (int i = l; i <= r; i++) {
            ans += a[i] <= x;
        }
        return ans;
    } else {
        int lb = (s + 1) * B - 1;
        int ub = e * B;
        int ans = 0;
        for (int i = l; i <= lb; i++) {
            ans += a[i] <= x;
        }
        for (int i = ub; i <= r; i++) {
            ans += a[i] <= x;
        }
        for (int i = s + 1; i <= e - 1; i++) {
            ans += ft[i].getprefix(x);
        }
        return ans;
    }
}

void test_case() {
    cin >> n >> q;
    B = sqrt(n);
    mxB = (n - 1) / B;
    ft0.init(n);
    ll ans = 0;
    for (int i = 0; i <= mxB; i++) {
        ft[i].init(n);
    }
    for (int i = 0; i < n; i++) {
        a[i] = i + 1;
        ft[i / B].upd(a[i], 1);
        if (a[i] < n) ans += ft0.getrange(a[i] + 1, n);
    }
    while (q--) {
        cin >> l >> r;
        l--;
        r--;
        if (l > r) swap(l, r);
        if (l == r) {
            cout << ans << endl;
            continue;
        }

        if (a[l] > a[r]) ans--;
        int x = getsum(l + 1, r - 1, a[l] - 1);
        int y = getsum(l + 1, r - 1, a[r] - 1);
        int sz = r - l - 1;
        ans += (sz - x) - x;
        ans += y - (sz - y);
        ft[l / B].upd(a[l], -1);
        ft[r / B].upd(a[r], -1);
        swap(a[l], a[r]);
        ft[l / B].upd(a[l], +1);
        ft[r / B].upd(a[r], +1);
        if (a[l] > a[r]) ans++;
        cout << ans << endl;
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
