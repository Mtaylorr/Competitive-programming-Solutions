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

int n, a[N];
int sum[N];
bool fix[N];

int dp[1005][1005];

int solve(int i, int j) {
    if (i < 0) return 0;
    if (j > n + 1) return 0;
    if (i == 0 && j == n + 1) {
        return 1;
    }
    int& rs = dp[i][j];
    if (rs != -1) return rs;
    rs = 0;
    if (i >= 1 && a[i] != 0) {
        if (a[i] == (j - i)) {
            return rs = (solve(i - 1, j)) % MOD;
        }
        if (a[i] > j - i && j <= n && (a[j] == 0 || a[j] == (j - i))) {
            return rs = (solve(i, j + 1)) % MOD;
        }
        return rs = 0;
    }
    if (j <= n && a[j] != 0) {
        if (a[j] == (j - i)) {
            return rs = (solve(i, j + 1)) % MOD;
        }
        if (a[j] > j - i && i >= 1 && a[i] == 0) {
            return rs = (solve(i - 1, j)) % MOD;
        }
        return rs = 0;
    }
    rs = (solve(i - 1, j) + 0ll + solve(i, j + 1)) % MOD;
    return rs;
}

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i <= n + 1; i++) {
        for (int j = i; j <= n + 1; j++) {
            dp[i][j] = -1;
        }
    }
    for (int i = 1; i <= n; i++) {
        if (a[i] == 0 || a[i] == 1) {
            ans = (ans + 0ll + solve(i - 1, i + 1)) % MOD;
        }
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
    init_fact(2e3);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
