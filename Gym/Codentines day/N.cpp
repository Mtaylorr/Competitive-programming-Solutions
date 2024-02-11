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
int n;
ll k;
void test_case() {
    cin >> n >> k;
    int m = n - n % 2;
    // x = a -> a+1
    // y = a+1 -> a
    // k = x-y = (x-y)=> x-y = k;
    // x+y = m/2;
    if (abs(k + m / 2) % 2) {
        cout << 0 << endl;
        return;
    }
    ll x = (k + (m / 2)) / 2;
    ll y = x - k;
    if (x < 0 || y < 0) {
        cout << 0 << endl;
        return;
    }
    assert(x + y == m / 2);
    assert( (x - y) == k);
    ll c1 = cnk(m / 2, x);
    ll c2 = (fact[n] * 1ll * inv(powe(2, m / 2))) % MOD;
    for (int i = 1; i <= m / 2; i++) {
        ll together = i;
        ll whatever = n - 2 * i;
        ll similarwhatevr = m / 2 - i;
        ll r = (fact[together + whatever] * 1ll * inv(powe(2, similarwhatevr))) % MOD;
        r = (r * 1ll * cnk(m / 2, i)) % MOD;
        if (i % 2) {
            c2 = (c2 + 0ll + MOD - r) % MOD;
        } else {
            c2 = (c2 + 0ll + r) % MOD;
        }
    }
    ll ans = (c1 * 1ll * c2) % MOD;
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    init_fact(2e5);
    while (T--) {
        test_case();
    }
    return 0;
}
