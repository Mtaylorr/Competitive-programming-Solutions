//https://csacademy.com/ieeextreme18/task/this-is-not-an-optimization-problem/
// 52%
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

const int MOD = 1e9 + 99999;
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

int n;
ll w[N];
ll dp[3005][3005];
int sb[N];
int tmp[3005];
ll sum[N];
int ans[N];
void dfs(int u, int p = -1) {
    dp[u][0] = 0;
    sb[u] = 1;
    neig(u, v, e, adj) {
        if (v == p) continue;
        dfs(v, u);
        sb[u] += sb[v];

        for (int i = 1; i <= sb[u]; i++) {
            tmp[i] = 0;
        }
        for (int i = 1; i <= sb[u]; i++) {
            for (int j = 0; j <= min(i, sb[v]); j++) {
                tmp[i] = (tmp[i] + (dp[v][j] * 1ll * cnk(sb[u] - sb[v], i - j)) % MOD) % MOD;
                tmp[i] = (tmp[i] + (dp[u][i - j] * 1ll * cnk(sb[v], j)) % MOD) % MOD;
            }
        }
        for (int i = 1; i <= sb[u]; i++) {
            dp[u][i] = tmp[i];
        }
    }
    for (int i = 1; i <= sb[u]; i++) {
        sum[i] = 0;
    }
    neig(u, v, e, adj) {
        if (v == p) continue;
        for (int i = 1; i <= sb[u]; i++) {
            dp[u][i] = (dp[u][i] + +0ll + MOD - dp[v][i]) % MOD;
            // dbg(u, i, dp[u][i], w[u], sb[u]);
            sum[i] += cnk(sb[v], i);
        }
    }
    for (int i = 1; i <= sb[u]; i++) {
        dp[u][i] = (dp[u][i] + (((cnk(sb[u], i) + 0ll + MOD - sum[i])) * 1ll * w[u]) % MOD) % MOD;
        ans[i] = (ans[i] + dp[u][i]) % MOD;
        // dbg(u, i, dp[u][i]);
    }
    neig(u, v, e, adj) {
        if (v == p) continue;
        for (int i = 1; i <= sb[u]; i++) {
            dp[u][i] = (dp[u][i] + dp[v][i] + 0ll + (w[u] * 1ll * cnk(sb[v], i)) % MOD) % MOD;
        }
    }
}

void test_case() {
    init_fact(2e5);
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n; i++) {
        cin >> w[i];
    }
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addBiEdge(u, v);
    }
    dfs(0);
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << "\n";
    }
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
