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
const int B = 37;
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
const int invB = inv(B);
int po[N];
int invpo[N];
int h[2][N];
int n;
string s;

int gethashleft(int i, int j) {
    int ha = (h[1][i] + 0ll + MOD - h[1][j + 1]) % MOD;
    ha = (ha * 1ll * invpo[n - j + 1]) % MOD;
    return ha;
}

int gethashright(int i, int j) {
    int ha = (h[0][j] + 0ll + MOD - h[0][i - 1]) % MOD;
    ha = (ha * 1ll * invpo[i]) % MOD;
    return ha;
}

int get(int i, int j) {
    int l = 0;
    int r = min(i, n - j + 1);
    while (l < r) {
        int md = (l + r + 1) / 2;
        int hl = gethashleft(i - md + 1, i);
        int hr = gethashright(j, j + md - 1);
        // dbg(i, j, md, hl, hr);
        if (hl == hr) {
            l = md;
        } else {
            r = md - 1;
        }
    }
    return l;
}
void test_case() {
    cin >> n;
    invpo[0] = po[0] = 1;
    for (int i = 1; i <= n; i++) {
        po[i] = (B * 1ll * po[i - 1]) % MOD;
        invpo[i] = (invB * 1ll * invpo[i - 1]) % MOD;
    }
    cin >> s;
    for (int i = 1; i <= n; i++) {
        h[0][i] =
            (h[0][i - 1] + 0ll + (po[i] * 1ll * (s[i - 1] - 'a' + 1)) % MOD) %
            MOD;
    }
    for (int i = n; i >= 1; i--) {
        h[1][i] = (h[1][i + 1] + 0ll +
                   (po[n - i + 1] * 1ll * (s[i - 1] - 'a' + 1)) % MOD) %
                  MOD;
    }
    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        int s = get(i, i);
        ans += s;
        if (i - s >= 1 && i + s <= n) {
            ans++;
            if (i - s - 1 >= 1 && i + s + 1 <= n) {
                int r = get(i - s - 1, i + s + 1);
                ans += r;
            }
        }
        if (i + 1 <= n) {
            s = get(i, i + 1);
            ans += s;
            if (i - s >= 1 && i + s + 1 <= n) {
                ans++;
                if (i - s - 1 >= 1 && i + s + 2 <= n) {
                    int r = get(i - s - 1, i + s + 2);
                    ans += r;
                }
            }
        }
    }
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
