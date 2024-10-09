//https://codeforces.com/contest/665/problem/F


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
ll ans = 0;

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
} nt;

struct CountPrimesN3_4 {
    // https://codeforces.com/blog/entry/91632
    vector<ll> v;
    vector<ll> dp;
    ll n;
    ll sq;
    int geti(ll x) {
        if (x <= sq)
            return (int)x - 1;
        else
            return (int)(v.size() - (n / x));
    };
    void run(ll _n) {
        n = _n;
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
            if (p * p * p <= n && p == nt.primes[nt.spf[p]]) {
                ans++;
            }
            if (dp[geti(p)] != dp[geti(p - 1)]) {
                ++a;
                for (int i = v.size() - 1; i >= 0; i--) {
                    if (v[i] < p * p) break;
                    dp[i] -= dp[geti(v[i] / p)] - a;
                }
            }
        }
    }
} cp;
ll n;
void test_case() {
    cin >> n;
    ans = 0;
    nt.linearSieve(2e6);
    cp.run(n);
    int nb = 0;
    for (auto &u : nt.primes) {
        if (u * 1ll * u <= n) {
            nb++;
            ans += cp.dp[cp.geti(n / u)] - 1 - nb;
        } else {
            break;
        }
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
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
