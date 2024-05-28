//https://codeforces.com/problemset/problem/1065/E
// Mtaylor
#include <bitset>
#include <iostream>
#include <vector>
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

int n, m, a;
int b[N];
struct PolyaEnumeration {
    ll solve(int n, int m, int a) {
        int bef = 0;
        int ans = 1;
        int inv2 = inv(2);
        for (int i = 0; i < m; i++) {
            int sz = b[i] - bef;
            int x = powe(a, 2 * sz);
            int y = powe(a, sz);
            x = ((x + y) * 1ll * inv2) % MOD;
            bef = b[i];
            ans = (ans * 1ll * x) % MOD;
        }
        ans = (ans * 1ll * powe(a, n - 2 * b[m - 1])) % MOD;
        return ans;
    }
} pe;

void test_case() {
    cin >> n >> m >> a;
    for (int i = 0; i < m; i++) {
        cin >> b[i];
    }
    cout << pe.solve(n, m, a) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
