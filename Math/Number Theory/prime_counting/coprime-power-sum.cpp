//https://www.hackerrank.com/challenges/coprime-power-sum
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
int starsandbars(int n, int k) { return cnk(n + k - 1, n); }

int n, k;
ll m;
vector<ll> s;

struct Interpolation {
    vector<int> yi;
    vector<int> dp[2];
    vector<int> xi;
    vector<int> denom;
    template <typename... M>
    void init(int d, const M &...v) {
        yi.clear();
        yi.assign(d + 1, 0);
        xi.clear();
        denom.assign(d + 1, 0);
        for (int i = 1; i <= d + 1; i++) {
            xi.pb(i);
        }
        for (int i = 0; i < xi.size(); i++) {
            yi[i] = f(xi[i], v...);
            if (i) {
                yi[i] = (yi[i] + yi[i - 1]) % MOD;
            }
        }
        int cur = 1;
        for (int i = xi.size() - 1; i >= 0; i--) {
            denom[i] = mul(cur, mul(invfact[xi.size() - xi[i]], invfact[xi[i] - 1]));
            cur *= -1;
        }
    }

    int f(int x) {
        // define here brute force solution
        int rs = 0;
        rs = powe(x, k);
        return rs;
    }

    int interpolate(int x) {
        dp[0].assign(xi.size(), 0);
        dp[1].assign(xi.size(), 0);
        int bef = 1;
        for (int i = 0; i < xi.size(); i++) {
            dp[0][i] = bef;
            bef = (bef * 1ll * ((x + 0ll + MOD - xi[i]) % MOD)) % MOD;
        }
        bef = 1;
        for (int i = xi.size() - 1; i >= 0; i--) {
            dp[1][i] = bef;
            bef = (bef * 1ll * ((x + 0ll + MOD - xi[i]) % MOD)) % MOD;
        }
        int ans = 0;
        for (int i = 0; i < xi.size(); i++) {
            int rs = (yi[i] * 1ll * dp[0][i]) % MOD;
            rs = (rs * 1ll * dp[1][i]) % MOD;
            rs = (rs * 1ll * denom[i]) % MOD;
            ans = (ans + rs) % MOD;
        }
        return ans;
    }

} interploator;

ll getsum(ll u) { return interploator.interpolate(u % MOD); }

struct CountPrimesN3_4 {
    // https://codeforces.com/blog/entry/91632
    ll run(ll n) {
        // ll y = pow(n, 0.25) * pow(log(n), 0.5);
        // nt.linearSieve(y);
        vector<ll> v;
        for (ll k = 1; k * k <= n; ++k) {
            v.pb(k);
            v.pb(n / k);
        }
        sort(all(v));
        v.erase(unique(v.begin(), v.end()), v.end());

        ll sq = sqrt(n);
        auto geti = [&](ll x) {
            if (x <= sq)
                return (int)x - 1;
            else
                return (int)(v.size() - (n / x));
        };
        vector<ll> dp(v.size());
        // S(n,0)
        for (int i = 0; i < v.size(); i++) {
            dp[i] = getsum(v[i]);
        }
        for (auto &p : s) {
            // if p is prime
            ll cur = powe(p, k);

            for (int i = v.size() - 1; i >= 0; i--) {
                if (v[i] < p) continue;
                dp[i] = (dp[i] + 0ll + MOD - ((cur * dp[geti(v[i] / p)]) % MOD)) % MOD;

            }
        }
        return dp[geti(n)];
    }
} cp;

void test_case() {
    cin >> n >> k >> m;
    interploator.init(k + 1);
    s.clear();
    for (int i = 0; i < n; i++) {
        ll x;
        cin >> x;
        s.push_back(x);
    }
    sort(all(s));
    cout << (cp.run(m)) % MOD << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    init_fact(20);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
