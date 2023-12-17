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

int n, dp[2][3];
int a[N];

void test_case() {
    cin >> n;
    int nb = 0;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        nb += (a[i] % 2 == 0);
    }
    int ans = powe(2, nb);
    ans = sub(ans, 1);
    ans = sub(ans, nb);
    ans = sub(ans, (nb * 1ll * (nb - 1)) / 2);
    // dbg(ans);
    for (int i = 1; i <= n; i++) {
        int id = i & 1;
        for (int j = 0; j < 3; j++) {
            dp[id][j] = dp[id ^ 1][j];
        }
        if (a[i] % 2 == 0) {
            dp[id][0] = (dp[id][0] + 1 + dp[id ^ 1][2]) % MOD;
        } else {
            dp[id][1] = (dp[id][1] + 1 + dp[id ^ 1][0]) % MOD;
            dp[id][2] = (dp[id][2] + 1 + dp[id ^ 1][1]) % MOD;
        }
    }
    for (int j = 0; j < 3; j++) {
        ans = (ans + dp[n & 1][j]) % MOD;
    }
    //dbg(ans);
    ans = sub(ans, nb);
    nb = n - nb;
    ans = sub(ans, 2 * (nb));
    ans = sub(ans, (nb * 1ll * (nb - 1)) / 2);
    ans = sub(ans, nb * 1ll * (n - nb));
    cout << ans << endl;
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
