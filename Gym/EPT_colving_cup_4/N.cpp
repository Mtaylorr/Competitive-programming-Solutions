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

typedef vector<vector<ll> > M;

int D = 3;
void initM(M &v) {
    v.resize(D);
    for (int i = 0; i < D; i++) {
        v[i].assign(D, 0);
    }
}

void getIdentity(M &rs) {
    initM(rs);
    for (int i = 0; i < D; i++) rs[i][i] = 1;
}

M mulM(M &u, M &v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++)
            for (int k = 0; k < D; k++)
                rs[n][m] =
                    (rs[n][m] + 0ll + (u[n][k] * 1ll * v[k][m]) % mod) % mod;
    return rs;
}

M addM(M &u, M &v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++)
            rs[n][m] = (u[n][m] % mod + v[n][m] % mod) % mod;
    return rs;
}

M subM(M &u, M v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++)
            rs[n][m] = (u[n][m] % mod + 0ll - v[n][m] % mod + mod) % mod;
    return rs;
}

M poweM(M &u, ll v, int mod = MOD) {
    M ans;
    getIdentity(ans);
    M acc = u;
    while (v) {
        if (v % 2) ans = mulM(ans, acc, mod);
        acc = mulM(acc, acc, mod);
        v /= 2;
    }
    return ans;
}

void showM(M &v) {
    for (int i = 0; i < D; i++) {
        for (int j = 0; j < D; j++) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

ll n, k;

void test_case() {
    cin >> n >> k;
    if (k < n) {
        cout << 0 << endl;
        return;
    }
    D = n + 2;
    M mat;
    initM(mat);
    mat[0][0] = 26;
    for (int i = 1; i <= n; i++) {
        mat[i][i] = 26;
        mat[i][i - 1] = 1;
    }
    mat[n + 1][n] = 1;
    mat[n + 1][n + 1] = 1;
    M ans = poweM(mat, k + 1);
    cout << ans[n + 1][0] << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
