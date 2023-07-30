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
const int MOD = 1e9 + 7;
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
const int F = 1e6;
int fact[F];
int invfact[F];
int cnk(int n, int k, int mod = MOD) {
    if (k > n) return 0;
    if (n == 0) return 1;
    int ans = mul(fact[n], invfact[k], mod);
    ans = mul(ans, invfact[n - k], mod);
    return ans;
}
void init_fact(int n, int mod = MOD) {
    fact[0] = fact[1] = 1;
    for (int i = 2; i <= n; i++) fact[i] = mul(i, fact[i - 1], mod);
    for (int i = 0; i <= n; i++) invfact[i] = powe(fact[i], mod - 2, mod);
}

int starsandbars(int n, int k) { return cnk(n + k - 1, n); }

int n[2];
int l[2], r[2];
int dp[2][N];

void calc(int j, int i) {
    int needed = l[j] * i;
    int rem = n[j] - needed;
    if (rem < 0) {
        dp[j][i] = 0;
        return;
    }
    int diff = r[j] - l[j] + 1;
    dp[j][i] = 0;
    for (int k = 0; (k * diff <= rem) && (k <= i); k++) {
        int x = cnk(i, k);
        int y = starsandbars(rem - k * diff, i);
        x = (x * 1ll * y) % MOD;
        if (k & 1) {
            dp[j][i] = (dp[j][i] + x) % MOD;
        } else {
            dp[j][i] = (dp[j][i] + 0ll + MOD - x) % MOD;
        }
    }
}
void test_case() {
    for (int j = 0; j < 2; j++) {
        cin >> n[j];
    }
    for (int j = 0; j < 2; j++) {
        cin >> l[j] >> r[j];
    }

    int m = n[0] + n[1];
    for (int i = 1; i <= m; i++) {
        for (int j = 0; j < 2; j++) {
            calc(j, i);
        }
    }
    int ans = 0;

    for (int i = 1; i <= m; i++) {
        ans = (ans + (dp[0][i] * 2ll * dp[1][i]) % MOD) % MOD;
        ans = (ans + (dp[0][i] * 1ll * dp[1][i - 1]) % MOD) % MOD;
        ans = (ans + (dp[0][i - 1] * 1ll * dp[1][i]) % MOD) % MOD;
    }
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    init_fact(4e5);
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
