//http://poj.org/problem?id=2409
// Mtaylor
#include <iostream>
#include <vector>
#include <bitset>
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

const int P = 1e6 + 5;
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
    void mobius_sieve(int ub) {
        sieve_size = ub;
        is_prime.set();
        is_prime[0] = is_prime[1] = 0;
        mob.assign(ub + 1, 1);
        for (int i = 2; i <= ub; i++) {
            if (is_prime[i] == 0) continue;
            primes.pb(i);
            mob[i] = -1;
            for (int j = 2 * i; j <= ub; j += i) {
                is_prime[j] = 0;
                mob[j] *= -1;
                if ((j / i) % i == 0) mob[j] = 0;
            }
        }
    }

    bool isPrime(ll N) {
        if (N <= sieve_size) return is_prime[N];
        for (int i = 0; i < primes.size(); ++i)
            if (N % primes[i] == 0) return false;
        return true;
    }
    template <typename T>
    vector<T> primeFactors(T N) {
        vector<T> factors;
        int PF_idx = 0, PF = primes[PF_idx];
        while (N != 1 && (PF * 1ll * PF <= N)) {
            while (N % PF == 0) {
                N /= PF;
                factors.push_back(PF);
            }
            PF = primes[++PF_idx];
        }
        if (N != 1) factors.push_back(N);
        return factors;
    }
    template <typename T>
    int numPF(T N) {
        int PF_idx = 0, PF = primes[PF_idx], ans = 0;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            while (N % PF == 0) {
                N /= PF;
                ans++;
            }
            PF = primes[++PF_idx];
        }
        if (N != 1) ans++;
        return ans;
    }
    template <typename T>
    int numDiffPF(T N) {
        int PF_idx = 0, PF = primes[PF_idx], ans = 0;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            if (N % PF == 0) ans++;
            while (N % PF == 0) N /= PF;
            PF = primes[++PF_idx];
        }
        if (N != 1) ans++;
        return ans;
    }
    template <typename T>
    ll sumPF(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        ll ans = 0;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            while (N % PF == 0) {
                N /= PF;
                ans += PF;
            }
            PF = primes[++PF_idx];
        }
        if (N != 1) ans += N;
        return ans;
    }
    template <typename T>
    T numDiv(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        T ans = 1;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            int power = 0;
            while (N % PF == 0) {
                N /= PF;
                power++;
            }
            ans *= (power + 1);
            PF = primes[++PF_idx];
        }
        if (N != 1) ans *= 2;
        return ans;
    }
    template <typename T>
    ll sumDiv(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        ll ans = 1;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            int power = 0;
            T po = PF;
            while (N % PF == 0) {
                N /= PF;
                power++;
                po *= PF;
            }
            ans *= ((po - 1) / (PF - 1));
            PF = primes[++PF_idx];
        }
        if (N != 1) ans *= (N + 1);
        return ans;
    }
    template <typename T>
    T EulerPhi(T N) {
        int PF_idx = 0, PF = primes[PF_idx];
        T ans = N;
        while (N != 1 && (PF * 1ll * PF <= N)) {
            if (N % PF == 0) ans -= ans / PF;
            while (N % PF == 0) N /= PF;
            PF = primes[++PF_idx];
        }
        if (N != 1) ans -= ans / N;
        return ans;
    }

} nt;

struct PolyaEnumeration {
    ll solve(int n, int k) {
        vector<ll> po(n + 1);
        po[0] = 1;
        for (int i = 1; i <= n; i++) {
            po[i] = (k * 1ll * po[i - 1]);
        }
        vector<int> divs;
        for (int i = 1; i * i <= n; i++) {
            if (n % i == 0) {
                divs.push_back(i);
                if (n != i * i) {
                    divs.pb(n / i);
                }
            }
        }
        ll ans = 0;
        for (auto &u : divs) {
            ans += po[u] * nt.EulerPhi(n / u);
        }
        if (n & 1) {
            ans += n * po[(n - 1) / 2 + 1];
        } else {
            ans += n / 2 * po[n / 2] + n / 2 * po[(n - 2) / 2 + 2];
        }
        ans = (ans / (2 * n));
        return ans;
    }
} pe;
int n, k;
void test_case() {
    cin >> k >> n;
    if (n == 0 && k == 0) exit(0);
    cout << pe.solve(n, k) << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    nt.sieve(1e6);
    int T = 1;
    while (true) {
        test_case();
    }
    return 0;
}
