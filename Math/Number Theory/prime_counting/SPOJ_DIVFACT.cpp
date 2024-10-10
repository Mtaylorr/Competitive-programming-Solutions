//https://www.spoj.com/problems/DIVFACT/
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

const int P = 2e6 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int sieve_size;

    NumberTheory() { sieve_size = 0; }
    template <typename T>
    T gcd(T a, T b) {
        return (b == 0 ? a : gcd(b, a % b));
    }
    template <typename T>
    T lcm(T a, T b) {
        return a * (b / gcd(a, b));
    }
    template <typename T>
    bool issquare(T w) {
        T sq = round(sqrt(w));
        return sq * sq == w;
    }

    vector<int> spf;
    void linearSieve(int ub) {
        sieve_size = ub;
        primes.clear();
        spf.assign(ub + 1, -1);
        for (int i = 2; i <= ub; i++) {
            if (spf[i] == -1) {
                spf[i] = primes.size();
                primes.push_back(i);
            }
            for (int j = 0; j < primes.size(); j++) {
                int p = primes[j];
                if (i * p > ub) break;
                spf[i * p] = j;
                if (i % p == 0) break;
            }
        }
    }

    void sieve(int ub) {
        sieve_size = ub;
        primes.clear();
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            primes.pb(i);
            if (i * 1ll * i <= ub)
                for (int j = i * i; j <= ub; j += i) {
                    is_prime[j] = 0;
                }
        }
    }

} nt;

struct CountPrimesN3_4 {
    // https://codeforces.com/blog/entry/91632
    vector<ll> dp;
    vector<ll> v;
    ll sq;
    ll n;
    int geti(ll x) {
        if (x <= sq)
            return (int)x - 1;
        else
            return (int)(v.size() - (n / x));
    };
    ll run(ll _n) {
        n = _n;
        // ll y = pow(n, 0.25) * pow(log(n), 0.5);
        // nt.linearSieve(y);
        v.clear();
        for (ll k = 1; k * k <= n; ++k) {
            v.pb(k);
            v.pb(n / k);
        }
        sort(all(v));
        v.erase(unique(v.begin(), v.end()), v.end());

        sq = sqrt(n);
        dp.resize(v.size());
        // S(n,0)
        for (int i = 0; i < v.size(); i++) {
            dp[i] = v[i];
        }
        int a = 0;
        for (ll p = 2; p * p <= n; p++) {
            // if p is prime
            if (dp[geti(p)] != dp[geti(p - 1)]) {
                ++a;
                for (int i = v.size() - 1; i >= 0; i--) {
                    if (v[i] < p * p) break;
                    dp[i] -= dp[geti(v[i] / p)] - a;
                }
            }
        }
        return dp[geti(n)] - 1;
    }

    ll getdp(ll x) { return dp[geti(x)] - 1; }
} cp;
ll mul(ll u, ll v, ll mod) { return ((u % mod) * (__int128)(1) * (v % mod)) % mod; }
ll powe(ll u, ll v, ll mod) {
    ll ans = 1;
    ll acc = u % mod;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

ll n, m;
void test_case() {
    cin >> n;
    m=1e9+7;
    ll ans = 1;
    cp.run(n);
    ll r = n;
    for (ll i = 1; i * i <= n; i++) {
        if (nt.is_prime[i]) {
            ll x = i;
            ll nb = 0;
            ll cur = 0;
            while (x <= n) {
                cur++;
                nb = (nb + cur * (__int128)(1) * (((n / x) % m + 0ll + m - (n / (x * i)) % m) % m) % m) % m;
                x *= i;
            }
            ans = (ans * (__int128)(1) * (nb + 1)) % m;
        }
        ll l = n / (i + 1);
        l = max(l, i);
        ans = (ans * (__int128)(1) * powe(i + 1, cp.getdp(r) - cp.getdp(l), m)) % m;
        r = l;
    }

    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    nt.sieve(2e6);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
