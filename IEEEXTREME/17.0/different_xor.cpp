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

const int B = 21;
int n, a[N];
int base[B];
int pos[B];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    memset(base, -1, sizeof(base));
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        int x = a[i];
        int p = i;
        for (int j = B - 1; j >= 0; j--) {
            if (x & (1 << j)) {
                if (base[j] == -1) {
                    base[j] = x;
                    pos[j] = p;
                    break;
                } else if (pos[j] < p) {
                    swap(base[j], x);
                    swap(pos[j], p);
                    x ^= base[j];
                } else {
                    x ^= base[j];
                }
            }
        }
        vector<int> tmp;
        for (int i = 0; i < B; i++) {
            if (base[i] != -1) {
                tmp.pb(pos[i]);
            }
        }
        tmp.pb(-1);
        sort(rall(tmp));
        for (int i = 1; i < tmp.size(); i++) {
            int d = tmp[i - 1] - tmp[i];
            ll x = (1 << i) - 1;
            ans = (ans + (x * 1ll * d) % MOD) % MOD;
        }
    }
    ans += (n * 1ll * (n + 1) / 2);
    ans %= MOD;
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
