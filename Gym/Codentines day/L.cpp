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

ll l;
int k;
//  case k = 3
//  sumdp(i-1)    1 0 0 0 1     sumdp(i-2)
//  1             0 1 0 0 0     1
//  dp(i-2)    =  0 0 0 1 0  *  dp(i-3)
//  dp(i-1)       0 0 0 0 1     dp(i-2)
//  dp(i)         0 1 1 1 1     dp(i-1)

void test_case() {
    cin >> l >> k;
    D = k + 2;
    M mat;
    initM(mat);
    mat[0][0] = 1;
    mat[0][D - 1] = 1;
    mat[1][1] = 1;
    for (int i = 2; i < D - 1; i++) {
        mat[i][i + 1] = 1;
    }
    for (int i = 1; i < D; i++) {
        mat[D - 1][i] = 1;
    }
    M ans = poweM(mat, l + 1);
    cout << ans[0][1] << endl;
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
