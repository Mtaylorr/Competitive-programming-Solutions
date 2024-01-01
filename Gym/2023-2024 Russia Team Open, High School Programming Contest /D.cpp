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
int dp[5005][5005];
int n;
int solve(int c, int p) {
    if (c == 0) {
        return p >= 0;
    }
    if (p <= 0) {
        return 0;
    }
    int &rs = dp[c][p];
    if (rs != -1) return rs;
    rs = solve(c, p - 1);
    rs = (rs + solve(c - 1, p - 1)) % MOD;
    if (c >= 2) {
        rs = (rs + solve(c - 2, p - 1)) % MOD;
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n;
    int ans = 1;
    for (int i = 2; i <= n; i++) {
        ans = (ans * 1ll * solve(i, i - 1)) % MOD;
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
