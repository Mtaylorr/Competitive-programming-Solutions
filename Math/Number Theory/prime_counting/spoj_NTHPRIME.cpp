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
const int MAXV = 20000010;

const int MAXP = 7;
const int MAXN = 50;
const int MAXM = 2 * 3 * 7 * 5 * 11 * 13 * 17;  /// Product of the first MAXP primes

vector<int> primes;
bitset<MAXV> is_prime;
int prod[MAXP], pi[MAXV], dp[MAXN][MAXM];

void sieve() {
    is_prime[2] = true;
    for (int i = 3; i < MAXV; i += 2) is_prime[i] = true;

    for (int i = 3; i * i < MAXV; i += 2) {
        for (int j = i * i; is_prime[i] && j < MAXV; j += (i << 1)) {
            is_prime[j] = false;
        }
    }

    for (int i = 1; i < MAXV; i++) {
        pi[i] = pi[i - 1] + is_prime[i];
        if (is_prime[i]) primes.push_back(i);
    }
}

void gen() {
    int i, j;
    assert(MAXN >= MAXP);

    sieve();
    for (prod[0] = primes[0], i = 1; i < MAXP; i++) {
        prod[i] = prod[i - 1] * primes[i];
    }

    for (i = 0; i < MAXM; i++) dp[0][i] = i;
    for (i = 1; i < MAXN; i++) {
        for (j = 1; j < MAXM; j++) {
            dp[i][j] = dp[i - 1][j] - dp[i - 1][j / primes[i - 1]];
        }
    }
}

uint64_t phi(long long m, int n) {
    if (!n) return m;
    if (n < MAXN && m < MAXM) return dp[n][m];
    if (n < MAXP) return dp[n][m % prod[n - 1]] + (m / prod[n - 1]) * dp[n][prod[n - 1]];

    long long p = primes[n - 1];
    if (m < MAXV && p * p >= m) return pi[m] - n + 1;
    if (p * p * p < m || m >= MAXV) return phi(m, n - 1) - phi((m / p), n - 1);

    int lim = pi[(int)sqrt(0.5 + m)];
    uint64_t res = pi[m] - (lim + n - 2) * (lim - n + 1) / 2;
    for (int i = n; i < lim; i++) {
        res += pi[(m / primes[i])];
    }

    return res;
}

uint64_t lehmer(long long n) {
    if (n < MAXV) return pi[n];

    int s = sqrt(0.5 + n), c = cbrt(0.5 + n);
    uint64_t res = phi(n, pi[c]) + pi[c] - 1;
    for (int i = pi[c]; i < pi[s]; i++) {
        res -= lehmer((n / primes[i])) - i;
    }

    return res;
}

int n;

void test_case() {
    gen();
    cin >> n;
    ll l = 2;
    ll r = 1e11;
    while (l < r) {
        ll md = (l + r) / 2;
        if (lehmer(md) >= n) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    cout << l << endl;
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
