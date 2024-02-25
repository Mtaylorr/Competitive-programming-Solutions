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
const int M = 2e7 + 1;
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

int fact[M];
ll n;

void preprocess() {
    fact[0] = 1;
    for (int i = 1; i <= 2e7; i++) {
        fact[i] = (fact[i - 1] * 1ll * i) % MOD;
    }
}

void test_case() {
    cin >> n;
    if (n == 1) {
        cout << -1 << endl;
        return;
    }
    if (n == 2) {
        cout << 2 << " " << 2 << " " << 2 << endl;
        return;
    }
    ll s = n - 2;
    ll mx = s * (s + 1) / 2;
    mx += (2 * (n - 1));

    ll mn = 0;
    ll l = __lg(n);
    while ((1 << l) < n) {
        l++;
    }
    l--;
    mn = l * n + 2 * (n - (1 << l));
    ll ans = fact[2 * (n - 1)];
    ans = (ans * inv(fact[n - 1])) % MOD;

    cout << ans << " " << mn << " " << mx << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    preprocess();
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
