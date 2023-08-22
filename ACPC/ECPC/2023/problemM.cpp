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
const int MOD = 1e9 + 7;

int dp[2][1005][1005];
int dp2[105][105][105];
int n, k;

int solve(int p, int lt, int r) {
    if (p == n) {
        return r == k;
    }
    int &rs = dp2[p][lt][r];
    if (rs != -1) return rs;
    rs = 0;
    for (int i = 0; i < lt; i++) {
        rs = (rs + solve(p + 1, i, r + 1)) % MOD;
    }
    int rem = n - p;
    for (int i = lt; i < rem; i++) {
        rs = (rs + solve(p + 1, i, r)) % MOD;
    }
    return rs;
}

int solve2(int n, int k) {
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j <= n; j++) {
            for (int w = 0; w <= n; w++) {
                dp[i][j][w] = 0;
            }
        }
    }
    dp[(n & 1)][0][k] = 1;
    for (int p = n - 1; p >= 0; p--) {
        int rem = n - p;
        int id = p & 1;
        for (int lt = 0; lt <= rem; lt++) {
            for (int r = 0; r <= p; r++) {
                int &rs = dp[id][lt][r];
                rs = 0;
                if (lt >= 1) {
                    rs = (rs + dp[id ^ 1][lt - 1][r + 1]) % MOD;
                }
                if (lt < rem)
                    rs = (rs + 0ll + dp[id ^ 1][rem - 1][r] + MOD + 0ll -
                          (lt >= 1 ? dp[id ^ 1][lt - 1][r] : 0)) %
                         MOD;
                if (lt) rs = (rs + dp[id][lt - 1][r]) % MOD;
            }
        }
    }
    return dp[0][0][0];
}

void test_case() {
    // mx = 166666500
    /*for (n = 1; n <= 20; n++) {
        for (k = 0; k <= n - 1; k++) {
            memset(dp2, -1, sizeof(dp2));
            int x = solve(0, 0, 0);
            int y = solve2(n, k);
            if (x != y) dbg(n, k, x, y);
        }
    }*/
    cin >> n >> k;
    cout << solve2(n, k) << endl;
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
