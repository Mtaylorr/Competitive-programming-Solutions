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
const int N = 2005 + 5;

ll s[N], p[N], e[N], a[N];
int n;
ll dp[N][N];

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> s[i] >> p[i] >> e[i] >> a[i];
    }
    for (int i = 0; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            dp[i][j] = -1e18;
        }
    }
    dp[0][0] = 0;
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        for (int j = 0; j <= n; j++) {
            if (dp[i - 1][j] >= 0) dp[i][j] = dp[i - 1][j] + s[i] - e[i - 1];

            if (j >= 1 && dp[i][j - 1] >= 0 &&
                dp[i - 1][j - 1] + s[i] - e[i - 1] >= a[i]) {
                dp[i][j] = max(dp[i][j], dp[i - 1][j - 1] + s[i] - e[i - 1] -
                                             a[i] + e[i] - p[i]);
            }
            if (dp[i][j] < 0) {
                dp[i][j] = -1e18;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (dp[n][i] >= 0) {
            ans = max(ans, i);
        }
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
