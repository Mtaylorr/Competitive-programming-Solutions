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
int n;
int dp[2][1005][1005];

int solve0(int i, int r) {
    if (i <= 0) {
        return r == 0;
    }
    int &rs = dp[0][i][r];
    if (rs != -1) return rs;
    rs = 0;
    for (int j = 1; j <= r / i; j++) {
        rs = (rs + solve0(i - 1, r - j * i)) % MOD;
    }
    return rs;
}

int solve1(int i, int r) {
    if (i >= n + 1) {
        return r == 0;
    }
    int &rs = dp[1][i][r];
    if (rs != -1) return rs;
    rs = 0;
    for (int j = 0; j <= r / i; j++) {
        rs = (rs + solve1(i + 1, r - j * i)) % MOD;
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n;
    int ans = 0;
    for (int i = 1; i <= n + 1; i++) {
        int r = 0;
        for (int j = 0; j <= n; j++) {
          //  dbg(i, j, solve0(i - 1, j), solve1(i + 1, n - j));
            r = (r + (solve0(i - 1, j) * 1ll * solve1(i + 1, n - j)) % MOD) % MOD;
        }
        //dbg(i, r);
        ans = (ans + (r * 1ll * i) % MOD) % MOD;
    }
    cout << ans << endl;
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
