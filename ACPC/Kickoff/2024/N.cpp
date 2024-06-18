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
const int N = 5e4 + 5;

const int MOD = 1e9+7;
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

int n, m;
string s[3];

int nxt[55][55];

int getFirstPrefix(string &cur, string &tmp) {
    for (int i = tmp.size(); i >= 1; i--) {
        if (i <= cur.size() && cur.substr(0, i) == tmp.substr(tmp.size() - i, i)) {
            return i;
        }
    }
    return 0;
}

void preprocess(string &s) {
    string cur = "";
    for (int i = 0; i <= m; i++) {
        for (int j = 0; j < 26; j++) {
            string tmp = cur + char('a' + j);
            nxt[i][j] = getFirstPrefix(s, tmp);
        }
        cur += s[i];
    }
}

int dp[N][2][2][52];

int solve(int p, int ea, int eb, int l) {
    if (l == m) return 0;
    if (p == n) {
        return 1;
    }
    int &rs = dp[p][ea][eb][l];
    if (rs != -1) return rs;
    rs = 0;
    int lb = 0;
    if (ea) {
        lb = s[0][p] - 'a';
    }
    int ub = 25;
    if (eb) {
        ub = s[1][p] - 'a';
    }
    for (int i = lb; i <= ub; i++) {
        rs = (rs + solve(p + 1, ea && (i == lb), eb && (i == ub), nxt[l][i])) % MOD;
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    cin >> s[0] >> s[1] >> s[2];
    preprocess(s[2]);
    cout << solve(0, 1, 1, 0) << endl;
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
