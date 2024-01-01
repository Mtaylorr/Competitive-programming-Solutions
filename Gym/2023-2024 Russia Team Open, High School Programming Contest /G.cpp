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

const int MOD = 1e9+7;
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

int starsandbars(int n, int k) {
    return cnk(n + k - 1, n);
}

int n;
int a;
int f[3];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a;
        f[a % 3]++;
    }
    int ans = (fact[f[1]] * 1ll * fact[f[2]]) % MOD;
    ans = (ans * 1ll * fact[f[0]]) % MOD;
    int res = 0;
    // dbg(f[1], f[2], f[0]);
    if (f[1] == 0 && f[2] == 0) {
        cout << 0 << endl;
        return;
    }
    for (int i = 0; i < 2; i++) {
        int x = f[1];
        int y = f[2];
        if (i) swap(x, y);
        int ty = 0;
        bool valid = true;
        if (x == 0) continue;
        x--;
        while (1) {
            if (ty == 0) {
                if (x == 0 && y) {
                    valid = false;
                }
                if (x == 0) break;
                x--;
            } else {
                if (y == 0 && x) {
                    valid = false;
                }
                if (y == 0) break;
                y--;
            }
            ty = 1 - ty;
        }
        if (valid) {
            res++;
        }
    }
    ans = (ans * 1ll * res) % MOD;
    ans = (ans * 1ll * starsandbars(f[0], n - f[0])) % MOD;
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
