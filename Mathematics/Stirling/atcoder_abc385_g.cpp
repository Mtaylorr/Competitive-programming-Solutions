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

struct NTT {
    const int mod = MOD;
    int base, max_base;
    int root;
    vector<int> roots;

    vector<int> rev;

    void init() {
        int tmp = mod - 1;
        max_base = 0;
        while (tmp % 2 == 0) {
            tmp /= 2;
            max_base++;
        }
        root = 2;

        while (powe(root, (mod - 1) >> 1) == 1) {
            root++;
        };
        assert(powe(root, mod - 1) == 1);
        root = powe(root, (mod - 1) >> max_base);
        base = 1;
        rev = {0, 1};
        roots = {0, 1};
    }

    void ensure_base(int nbase) {
        if (roots.empty()) {
            init();
        }
        if (nbase <= base) return;
        assert(nbase <= max_base);
        rev.resize(1 << nbase);
        for (int i = 0; i < (1 << nbase); i++) {
            rev[i] = ((rev[i >> 1] >> 1) + 0ll + ((i & 1) << (nbase - 1))) % MOD;
        }
        roots.resize(1 << nbase);
        while (base < nbase) {
            int z = powe(root, 1 << (max_base - 1 - base));
            for (int i = 1 << (base - 1); i < (1 << base); i++) {
                roots[i << 1] = roots[i];
                roots[(i << 1) + 1] = (roots[i] * 1ll * z) % MOD;
            }
            base++;
        }
    }

    void multiply(vector<int> const& a, vector<int> const& b, vector<int>& result) {
        vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());
        int eq = fa == fb;
        int nbase = 0;
        int need = a.size() + b.size() - 1;
        while ((1 << nbase) < need) nbase++;
        ensure_base(nbase);
        int n = 1 << nbase;
        fa.resize(n);
        fb.resize(n);

        fft(fa);
        if (eq)
            fb = fa;
        else
            fft(fb);
        int inv_sz = inv(n);
        for (int i = 0; i < n; i++) fa[i] = ((fa[i] * 1ll * fb[i]) % MOD * 1ll * inv_sz) % MOD;
        reverse(fa.begin() + 1, fa.end());
        fft(fa);
        result.resize(need);
        for (int i = 0; i < need; i++) result[i] = fa[i];
    }

    void fft(vector<int>& a) {
        int n = a.size();
        int zeros = __builtin_ctz(n);
        ensure_base(zeros);
        int shift = base - zeros;
        for (int i = 0; i < n; i++) {
            if (i < (rev[i] >> shift)) {
                swap(a[i], a[rev[i] >> shift]);
            }
        }
        for (int k = 1; k < n; k <<= 1) {
            for (int i = 0; i < n; i += 2 * k) {
                for (int j = 0; j < k; j++) {
                    int u = a[i + j], v = (1LL * a[i + j + k] * roots[j + k]) % MOD;
                    a[i + j] = (u + v) % MOD;
                    a[i + j + k] = (u + 0ll + MOD - v) % MOD;
                }
            }
        }
    }
} ntt;

struct StirlingNumber {
    // S(0,0) = 1;
    // S(n,0) = S(0,n) = 0;
    // S(n,k) = (n-1) * S(n-1, k) + S(n-1, k-1);
    // (x)*(x+1)*....*(x+n-1) = Sum(S(n,k) x**k);

    // Using NTT
    void computeN(int n, vector<int>& ans) {
        vector<vector<int> > polys;
        for (int i = 0; i < n; i++) {
            polys.push_back({i, 1});
        }
        calculateRecursive(0, polys.size() - 1, polys);
        ans = polys[0];
    }
    void calculateRecursive(int l, int r, vector<vector<int> >& polys) {
        if (l == r) return;
        int md = (l + r) / 2;
        calculateRecursive(l, md, polys);
        calculateRecursive(md + 1, r, polys);
        ntt.multiply(polys[l], polys[md + 1], polys[l]);
    }
    int dp[3005][3005];
    void computeIterative(int n) {
        memset(dp, 0, sizeof(dp));
        dp[0][0] = 1;
        for (int i = 1; i <= n; i++) {
            for (int j = 0; j <= i; j++) {
                if (j == 0) {
                    dp[i][j] = 0;
                } else {
                    dp[i][j] = (((i - 1) * 1ll * dp[i - 1][j]) % MOD + dp[i - 1][j - 1]) % MOD;
                }
            }
        }
    }

    void assertN(int n) {
        computeIterative(n);
        vector<int> iterAns;
        for (int i = 0; i <= n; i++) {
            iterAns.push_back(dp[n][i]);
        }
        vector<int> ans;
        computeN(n, ans);
        assert(ans == iterAns);
        // for (auto& u : iterAns) {
        //     cout << u << " ";
        // }
        // cout << endl;
        // for (auto& u : ans) {
        //     cout << u << " ";
        // }
        // cout << endl;
    }

} SN;

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
void test_case() {
    cin >> n >> k;
    vector<int> ans;
    init_fact(n);
    if (n == 1) {
        cout << 1 << endl;
        return;
    }
    SN.computeN(n - 1, ans);
    int res = 0;
    for (int sm = 2; sm <= n + 1; sm++) {
        if ((sm % 2) == abs(k) % 2) {
            int x = (sm + k) / 2;
            int y = x - k;
            if (x >= 1 && y >= 1) {
                res = (res + (ans[sm - 2] * 1ll * cnk(sm - 2, x - 1)) % MOD) % MOD;
            }
        }
    }
    cout << res;
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
