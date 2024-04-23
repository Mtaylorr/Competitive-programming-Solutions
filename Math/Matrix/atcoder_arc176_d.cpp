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

typedef vector<vector<ll> > M;

const int MOD = 998244353;
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
            for (int k = 0; k < D; k++) rs[n][m] = (rs[n][m] + 0ll + (u[n][k] * 1ll * v[k][m]) % mod) % mod;
    return rs;
}

M addM(M &u, M &v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++) rs[n][m] = (u[n][m] % mod + v[n][m] % mod) % mod;
    return rs;
}

M subM(M &u, M v, int mod = MOD) {
    M rs;
    initM(rs);
    for (int n = 0; n < D; n++)
        for (int m = 0; m < D; m++) rs[n][m] = (u[n][m] % mod + 0ll - v[n][m] % mod + mod) % mod;
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

int n, m;
int p[N];
int pos[N];

void test_case() {
    cin >> n >> m;
    D = 3;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        pos[p[i]] = i;
    }
    M mat;
    initM(mat);
    // (0)=( (n-2)*(n-3)/2 +1 + 2*(zeros-2), zeros-1     ,      0) (0)
    // (1)=( 2*ones, (n-2)*(n-3)/2 +1 + zeros-1 + ones-1 , ones-1) (1)
    // (2)=( 0,  ones-1,           (n-2)*(n-3)/2 +1 + 2*(ones-2) ) (2)
    int zeros = 0;
    int ones = n;
    int zz = 0;
    int oo = n - 1;
    int zo = 0;
    int ans = 0;
    for (int i = 1; i < n; i++) {
        int po = pos[i];
        ones--;
        zeros++;
        if (po >= 1) {
            if (p[po - 1] > i) {
                oo--;
                zo++;
            } else {
                zo--;
                zz++;
            }
        }
        if (po + 1 < n) {
            if (p[po + 1] > i) {
                oo--;
                zo++;
            } else {
                zo--;
                zz++;
            }
        }
        initM(mat);
        mat[0][0] = ((n - 2) * 1ll * (n - 3) / 2 + 1 + 2 * (zeros - 2)) % MOD;
        mat[0][1] = (zeros - 1) % MOD;
        mat[0][2] = 0;
        mat[1][0] = (2 * ones) % MOD;
        mat[1][1] = ((n - 2) * 1ll * (n - 3) / 2 + 1 + zeros - 1 + ones - 1) % MOD;
        mat[1][2] = 2*(zeros);
        mat[2][0] = 0;
        mat[2][1] = ones - 1;
        mat[2][2] = ((n - 2) * 1ll * (n - 3) / 2 + 1 + 2 * (ones - 2)) % MOD;
        M rpo = poweM(mat, m);
        vector<int> tmp = {zz, zo, oo};
        int result = 0;
        for (int i = 0; i < 3; i++) {
            result = (result + (tmp[i] * 1ll * rpo[1][i]) % MOD) % MOD;
        }
        // dbg(i, result, zz, zo, oo, zeros, ones);
        ans = (ans + result) % MOD;
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
    while (T--) {
        test_case();
    }
    return 0;
}
