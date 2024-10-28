//https://csacademy.com/ieeextreme18/task/halving/


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

const int F = 1e3;
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

int n, r[N], c[N], b[N];

bool done[N];

int dp[601][301][301];
int en[N], st[N];

int solve(int p, int pts, int rm) {
    if (p > 2 * n) {
        return pts == 0 && rm == 0;
    }
    // dbg(p, pts, rm, done[p]);
    int &rs = dp[p][pts][rm];
    if (rs != -1) return rs;
    rs = 1;
    int x = 1;
    int y = 0;
    rm += st[p];
    if (!done[p] && rm) {
        int rpts = pts;
        for (int j = 1; j <= en[p]; j++) {
            x = (x * 1ll * rpts) % MOD;
            rpts--;
        }
        x = (x * 1ll * solve(p + 1, rpts, rm - 1)) % MOD;
        x = (rm * 1ll * x) % MOD;
    } else {
        x = 0;
    }
    int npts = pts + !done[p];
    for (int j = 1; j <= en[p]; j++) {
        // dbg(npts);
        rs = (rs * 1ll * npts) % MOD;
        npts--;
    }
    rs = (rs * 1ll * solve(p + 1, npts, rm)) % MOD;
    rs = (rs + x) % MOD;
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    init_fact(1e3);
    cin >> n;
    for (int i = 0; i < 2 * n; i++) {
        cin >> c[i];
        done[c[i]] = 1;
    }
    for (int i = 0; i < n; i++) {
        cin >> r[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> b[i];
    }
    int multiplier = 1;
    vector<pair<int, int> > ranges;
    for (int i = 0; i < n; i++) {
        int lf = 2 * i;
        int rg = lf + 1;
        if (r[i] == 1) {
            if (c[lf] != -1 && c[rg] != -1) {
                if (max(c[lf], c[rg]) != b[i]) {
                    cout << 0 << endl;
                    return;
                }
            } else if (c[lf] == -1 && c[rg] == -1) {
                multiplier = (multiplier * 2ll) % MOD;
                if (done[b[i]]) {
                    cout << 0;
                    return;
                }
                done[b[i]] = 1;
                ranges.push_back({1, b[i] - 1});
            } else if (c[lf] == -1) {
                if (c[rg] > b[i]) {
                    cout << 0 << endl;
                    return;
                }
                if (c[rg] != b[i]) {
                    c[lf] = b[i];
                    if (done[b[i]]) {
                        cout << 0;
                        return;
                    }
                    done[b[i]] = 1;
                } else {
                    ranges.push_back({1, b[i] - 1});
                }
            } else {
                if (c[lf] > b[i]) {
                    cout << 0 << endl;
                    return;
                }
                if (c[lf] != b[i]) {
                    c[rg] = b[i];
                    if (done[b[i]]) {
                        cout << 0;
                        return;
                    }
                    done[b[i]] = 1;
                } else {
                    ranges.push_back({1, b[i] - 1});
                }
            }
        } else {
            if (c[lf] != -1 && c[rg] != -1) {
                if (min(c[lf], c[rg]) != b[i]) {
                    cout << 0 << endl;
                    return;
                }
            } else if (c[lf] == -1 && c[rg] == -1) {
                multiplier = (multiplier * 2ll) % MOD;
                if (done[b[i]]) {
                    cout << 0;
                    return;
                }
                done[b[i]] = 1;
                ranges.push_back({b[i] + 1, 2 * n});
            } else if (c[lf] == -1) {
                if (c[rg] < b[i]) {
                    cout << 0 << endl;
                    return;
                }
                if (c[rg] != b[i]) {
                    c[lf] = b[i];
                    if (done[b[i]]) {
                        cout << 0;
                        return;
                    }
                    done[b[i]] = 1;
                } else {
                    ranges.push_back({b[i] + 1, 2 * n});
                }
            } else {
                if (c[lf] < b[i]) {
                    cout << 0 << endl;
                    return;
                }
                if (c[lf] != b[i]) {
                    c[rg] = b[i];
                    if (done[b[i]]) {
                        cout << 0;
                        return;
                    }
                    done[b[i]] = 1;
                } else {
                    ranges.push_back({b[i] + 1, 2 * n});
                }
            }
        }
    }
    for (auto &u : ranges) {
        // dbg(u.fi, u.se);
        if (u.fi > u.se) {
            cout << 0;
            return;
        }
        if (u.fi == 1) {
            en[u.se]++;
        } else {
            st[u.fi]++;
        }
    }
    cout << (solve(1, 0, 0) * 1ll * multiplier) % MOD << endl;
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
