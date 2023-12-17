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

ll k, n;

void test_case() {
    cin >> n >> k;
    // dbg(n, k);
    ll nb = n / (k * 2);
    ll ans = 0;
    if (nb == 0) {
        ans = 0;
        n -= k + 1;
        ll f = cnk(k - 1, n);
        cout << ans << " " << f << endl;
        return ;
    }

    for (int i = 0; i < 2 * (k); i++) {
        ans += (nb * (nb - 1)) / 2;
    }

    n -= (nb * (2 * (k)));
    ans += (nb * n);
    ll f = 0;
    if (n) {
        for (int i = 0; i <= k - 1; i++) {
            if (2 * i > n) break;
            int x = cnk(k - 1, i);
            int y = cnk(k + 1-i, n - 2 * i);
            f = (f + (x * 1ll * y) % MOD) % MOD;
        }
        cout << ans << " " << f << endl;
    } else {
        cout << ans << " " << 1 << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init_fact(5e5);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
