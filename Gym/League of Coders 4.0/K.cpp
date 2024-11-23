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
const int N = 1e6 + 5;

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

const int E = 1e6 + 5;

#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E];

    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }

    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;
struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;

int n, k;
int c[N];
vector<pair<int, int> > cnt[N];
int freq[N];
void test_case() {
    nt.mobius_sieve(1e6);
    cin >> n;
    dsu.init(n);
    adj.init(n);
    int a, b;
    for (int i = 0; i < n - 1; i++) {
        cin >> a >> b;
        --a, --b;
        adj.addBiEdge(a, b);
    }
    cin >> k;
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        freq[c[i]]++;
    }
    for (int u = 0; u < n; u++) {
        neig(u, v, e, adj) {
            if (v < u) continue;
            int x = __gcd(c[u], c[v]);
            if (x % k) continue;
            x /= k;
            cnt[x].pb({u, v});
        }
    }
    ll ans = 0;
    for (int i = 1; i <= 1e6; i++) {
        ll rs = 0;
        if (nt.mob[i] == 0) continue;
        for (int j = i; j <= 1e6; j += i) {
            for (auto& v : cnt[j]) {
                rs += dsu.sz[dsu.getid(v.fi)] * 1ll * dsu.sz[dsu.getid(v.se)];
                dsu.uni(v.fi, v.se);
            }
        }
        for (int j = i; j <= 1e6; j += i) {
            for (auto& v : cnt[j]) {
                dsu.sz[v.fi] = 1;
                dsu.id[v.fi] = v.fi;
                dsu.sz[v.se] = 1;
                dsu.id[v.se] = v.se;
            }
        }

        ans += rs * nt.mob[i];
    }
    cout << freq[k] + 2 * ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
