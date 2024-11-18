//https://atcoder.jp/contests/arc187/tasks/arc187_c
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
const int MOD = 998244353;
template <typename T, typename U>
int mul(T u, U v, int mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}
template <typename T, typename U>
int add(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}
template <typename T, typename U>
int sub(T u, U v, int mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}
template <typename T>
int powe(T u, ll v, int mod = MOD) {
    int ans = 1;
    int acc = u % mod;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}
template <typename T>
int inv(T u, int mod = MOD) {
    return powe(u, mod - 2, mod);
}

int n, q[N];
int pos[N];
int suff[5005][5005];
int dp[5005][5005][2];

int solve(int p, int mx, int ismx) {
    if (p >= n + 1) {
        return mx == n + 1 && ismx == 1;
    }
    if (mx > n) return 0;
    int& rs = dp[p][mx][ismx];
    if (rs != -1) return rs;
    rs = 0;
    if (ismx) {
        // case 1: increase the maximum
        rs = (rs + solve(p, mx + 1, ismx)) % MOD;
        // case 2 : go again to max in next position
        if ((pos[mx] == p || pos[mx] == 0) && (q[p] == -1 || q[p] == mx)) {
            rs = (rs + solve(p + 1, mx + 1, 1)) % MOD;
        }
    }
    if (p + 1 <= n) {
        // cyclic shift
        if (q[p] < mx && q[p] != -1) {
            rs = (rs + solve(p + 1, mx, 0)) % MOD;
        }
        if (q[p] == -1) {
            int cnt = mx - 1 - suff[p + 1][mx - 1] - (p - 1);
            if (cnt >= 1) rs = (rs + (cnt * 1ll * solve(p + 1, mx, 0)) % MOD) % MOD;
        }
    }
    if (!ismx) {
        // end the cyclic shift
        if ((pos[mx] == p || pos[mx] == 0) && (q[p] == -1 || q[p] == mx)) {
            rs = (rs + solve(p + 1, mx + 1, 1)) % MOD;
        }
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> q[i];
        if (q[i] != -1) {
            pos[q[i]] = i;
        }
    }
    for (int i = n; i >= 1; i--) {
        for (int j = 1; j <= n; j++) {
            suff[i][j] = suff[i + 1][j];
            if (q[i] != -1) {
                suff[i][j] = suff[i][j] + (q[i] <= j);
            }
        }
    }
    int ans = solve(1, 1, 1);

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
