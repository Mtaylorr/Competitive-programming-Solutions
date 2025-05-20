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
    if (n < 0) return 0;
    if (k > n) return 0;
    if (k < 0) return 0;
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

ll n, k;

void test_case() {
    cin >> n >> k;
    int tot = (n * (n + 1)) / 2;
    ll ans = 0;
    for (int j = k; j <= n; j++) {
        int x = cnk(n, j);
        int y = cnk(tot - n, n - j);
        int w = cnk(tot - n, n);
        x = (x * 1ll * y) % MOD;
        x = (x * 1ll * w) % MOD;
        ans = (ans + x) % MOD;
    }
    ans = (ans * 1ll * n) % MOD;
    ans = (ans * 2ll) % MOD;
    ll x = 0;
    // first case  01  in left
    for (int i = k; i <= n; i++) {
        for (int j = k; j <= n; j++) {
            for (int p = 0; p <= n; p++) {
                ll lf = cnk(n - 1, i - 1);
                ll rg = cnk(n - 1, j);
                lf = (lf * 1ll * cnk(n - 1 - j, p) % MOD) % MOD;
                lf = (lf * 1ll * cnk(tot - 2 * n + 1, n - i - p)) % MOD;
                rg = (rg * 1ll * cnk(tot - n - (i - 1) - (n - i - p), n - j)) % MOD;
                x = (x + 0ll + (lf * 1ll * rg) % MOD) % MOD;
            }
        }
    }

    x = (x * 2ll) % MOD;

    for (int i = k; i <= n; i++) {
        for (int j = k; j <= n; j++) {
            for (int p = 0; p <= n; p++) {
                ll lf = cnk(n - 1, i);
                ll rg = cnk(n - 1, j);
                lf = (lf * 1ll * cnk(n - 1 - j, p) % MOD) % MOD;
                lf = (lf * 1ll * cnk(tot - 2 * n + 1, n - i - p)) % MOD;
                rg = (rg * 1ll * cnk(tot - n - (i) - (n - i - p), n - j)) % MOD;
                x = (x + 0ll + (lf * 1ll * rg) % MOD) % MOD;
            }
        }
    }

    x = (x * 2ll) % MOD;
    ll p = ((n * 1ll * (n - 1)) / 2) % MOD;
    x = (x * 1ll * p) % MOD;
    // dbg(ans, x);
    ans = (ans + 0ll + MOD - x) % MOD;
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init_fact(1e6);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
