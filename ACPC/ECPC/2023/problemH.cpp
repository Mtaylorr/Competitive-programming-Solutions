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
const int B = 31;
const int MOD = 1e9 + 7;
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
const int invB = inv(B);

/*
1
ab
7
1 a
1 b
3 2
4 1
1 a
2 b
4 3
*/

int l[N];
int lh[1055][1055], rh[1055][1055];
int po[1055];
int invpo[1055];
string p;
int dp[N];
int m;
int hp;
int idx[26];

void update(int r, int i, int j) {
    dp[r] = (dp[i] + dp[j]) % MOD;
    l[r] = l[i] + l[j];
    l[r] = min(l[r], m + 1);
    for (int k = 1; k <= m - 1; k++) {
        if (k <= l[i] && m - k <= l[j]) {
            int h = (rh[i][k] + (po[k] * 1ll * lh[j][m - k]) % MOD) % MOD;
            dp[r] = (dp[r] + (h == hp)) % MOD;
        }
    }
    for (int k = 1; k <= l[r]; k++) {
        if (k <= l[i]) {
            lh[r][k] = lh[i][k];
        } else {
            lh[r][k] =
                (lh[i][l[i]] + (po[l[i]] * 1ll * lh[j][k - l[i]]) % MOD) % MOD;
        }
    }
    for (int k = 1; k <= l[r]; k++) {
        if (k <= l[j]) {
            rh[r][k] = rh[j][k];
        } else {
            rh[r][k] =
                (rh[i][k - l[j]] + (po[k - l[j]] * 1ll * rh[j][l[j]]) % MOD) %
                MOD;
        }
    }

}

void test_case() {
    po[0] = invpo[0] = 1;
    for (int i = 1; i <= 1002; i++) {
        po[i] = (po[i - 1] * 1ll * B) % MOD;
        invpo[i] = (invpo[i - 1] * 1ll * invB) % MOD;
    }
    cin >> p;
    hp = 0;
    m = p.size();
    for (int i = 0; i < p.size(); i++) {
        hp = (hp + (po[i] * 1ll * ((p[i] - 'a') + 1)) % MOD) % MOD;
    }
    for (int i = 0; i < 26; i++) {
        idx[i] = 1003 + i;
        l[idx[i]] = 1;
        dp[idx[i]] = (p.size() == 1 && (p[0] - 'a') == i);
        lh[idx[i]][1] = i + 1;
        rh[idx[i]][1] = i + 1;
    }
    int q;
    cin >> q;
    for (int i = 1; i <= q; i++) {
        int ty;
        cin >> ty;
        char c;
        int j;
        switch (ty) {
            case 1:
                cin >> c;
                update(i, i - 1, idx[c - 'a']);
                break;
            case 2:
                cin >> c;
                update(i, idx[c - 'a'], i - 1);
                break;
            case 3:
                cin >> j;
                update(i, i - 1, j);
                break;
            case 4:
                cin >> j;
                update(i, j, i - 1);
                break;
        }
        cout << dp[i] << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
