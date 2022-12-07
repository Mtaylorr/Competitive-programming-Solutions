//https://codeforces.com/contest/1559/problem/E
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
const int N = 1e5 + 5;

#define MODDtype int

const int MOD = 998244353;

MODDtype mul(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) * 1ll * (v % mod)) % mod;
}

MODDtype add(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll + (v % mod) + mod) % mod;
}

MODDtype sub(MODDtype u, MODDtype v, MODDtype mod = MOD) {
    return ((u % mod) + 0ll - (v % mod) + mod) % mod;
}

MODDtype powe(MODDtype u, ll v, MODDtype mod = MOD) {
    MODDtype ans = 1;
    MODDtype acc = u;
    while (v) {
        if (v % 2) ans = mul(ans, acc, mod);
        acc = mul(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

MODDtype inv(MODDtype u, MODDtype mod = MOD) { return powe(u, mod - 2, mod); }

const int P = 1e5 + 5;
class NumberTheory {
   public:
    bitset<P> is_prime;
    vector<int> primes;
    vector<int> mob;
    int sieve_size;
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
} nt;

int n, l[N], r[N], ln[N], rn[N], m, nm;
int nb[N];
int dp[51][N];

int calc(int p, int rem) {
    if (p >= n) return 1;

    if (dp[p][rem] != -1) return dp[p][rem];
    int rs = 0;
    for (int i = 0; i <= min(rem, nb[p]); i++) {
        rs = add(rs, calc(p + 1, rem - i));
    }
    return dp[p][rem] = rs;
}

void solve() {
    nt.mobius_sieve(100000);
    cin >> n >> m;
    for (int i = 1; i <= n; i++) {
        cin >> l[i] >> r[i];
    }
    int ans = 0;
    for (int i = 1; i <= m; i++) {
        if (nt.mob[i] == 0) continue;
        bool cond = true;
        for (int j = 1; j <= n; j++) {
            ln[j] = (l[j] + i - 1) / i;
            rn[j] = (r[j]) / i;
            if (ln[j] > rn[j]) cond = false;
        }
        if (!cond) continue;
        nm = m / i;
        for (int j = 1; j <= n; j++) {
            nm -= ln[j];
            nb[j] = rn[j] - ln[j];
        }
        if (nm < 0) {
            continue;
        }
        for (int j = 0; j <= nm; j++) {
            dp[0][j] = 1;
        }
        for (int j = 1; j <= n; j++) {
            for (int k = 0; k <= nm; k++) {
                int x = max(0, k - nb[j]);
                int y = k;
                dp[j][k]=sub(dp[j-1][y],(x>0?dp[j-1][x-1]:0));
            }
            for (int k = 1; k <= nm; k++) {
                dp[j][k] = add(dp[j][k - 1], dp[j][k]);
            }
        }

        int rs= dp[n][nm];
        if (nt.mob[i] == 1) {
            ans = add(ans, rs);
        } else {
            ans = sub(ans, rs);
        }
    }
    cout << ans;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}
