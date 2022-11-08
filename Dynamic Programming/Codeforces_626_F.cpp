//https://codeforces.com/problemset/problem/626/F
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
#define MODDtype int

const int MOD = 1e9 + 7;

MODDtype mul(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}

MODDtype add(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}

MODDtype sub(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}

MODDtype powe(MODDtype u, ll v, MODDtype mod = MOD) {
    MODDtype ans = 1;
    MODDtype acc = u;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

MODDtype inv(MODDtype u, MODDtype mod = MOD) { return powe(u, mod - 2, mod); }
int n, k;
int a[N];
int dp[2][205][1004];
void solve() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    if (n == 1) {
        cout << 1;
        return;
    }
    sort(a, a + n);
    a[n] = a[n - 1];
    int id = (n)&1;
    for (int nb = 0; nb <= n; nb++) {
        for (int sm = 0; sm <= k; sm++) {
            dp[id][nb][sm] = (nb == 0);
        }
    }
    for (int p = n - 1; p >= 0; p--) {
        int id = p & 1;
        for (int nb = 0; nb <= n; nb++) {
            for (int sm = 0; sm <= k; sm++) {
                int rs = 0;
                if (sm + (a[p + 1] - a[p]) * nb <= k)
                    rs = add(
                        rs,
                        mul(nb + 1,
                            dp[id ^ 1][nb][sm + (a[p + 1] - a[p]) * nb]));
                if (nb >= 1 && sm + (a[p + 1] - a[p]) * (nb - 1) <= k) {
                    rs =
                        add(rs, mul(nb, dp[id ^ 1][nb - 1]
                                          [sm + (a[p + 1] - a[p]) * (nb - 1)]));
                }
                if(sm + (a[p+1]-a[p]) * (nb + 1) <= k)
                        rs = add(rs,
                                 dp[id ^ 1][nb + 1][sm + (a[p+1]-a[p]) * (nb + 1)]);
                dp[id][nb][sm] = rs;
            }
        }
    }
    cout << dp[0][0][0];
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
        solve();
    }
    return 0;
}
