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
const int B = 31;
const int invB = inv(B);
int n;
string s[N];
string t;
int h[N];
int th[N];
int po[N], invpo[N];
int dp[N];
int gethash(int l, int r) {
    int d = (th[r] + MOD + 0ll - th[l - 1]);
    return (d * 1ll * invpo[l]) % MOD;
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    po[0] = invpo[0] = 1;
    for (int i = 1; i <= 1e5; i++) {
        po[i] = (po[i - 1] * 1ll * B) % MOD;
        invpo[i] = (invpo[i - 1] * 1ll * invB) % MOD;
    }
    for (int i = 0; i < n; i++) {
        h[i] = 0;
        for (int j = 0; j < s[i].size(); j++) {
            h[i] = (h[i] + (((s[i][j] - 'a') + 1) * 1ll * po[j]) % MOD) % MOD;
        }
    }
    cin >> t;
    th[0] = 0;
    for (int i = 1; i <= t.size(); i++) {
        th[i] = (th[i - 1] + (((t[i - 1] - 'a') + 1) * 1ll * po[i]) % MOD) % MOD;
    }
    dp[t.size()] = 1;
    for (int i = t.size() - 1; i >= 0; i--) {
        for (int j = 0; j < n; j++) {
            if (i + s[j].size() <= t.size()) {
                int ch = gethash(i + 1, i + s[j].size());

                if (ch == h[j]) {
                    dp[i] = max(dp[i], dp[i + s[j].size()]);
                }
            }
        }
    }
    if (dp[0]) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
