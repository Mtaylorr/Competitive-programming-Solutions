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

int m, n, k, s;
double x[N];
double dp[2005][105];
double sum[2005];
double smsq[2005];

double solve(int i, int j) {
    double sm = sum[j] - sum[i - 1];
    double l = j - i + 1;
    double xt = sm / l;
    double ans = xt * xt * l;
    ans += smsq[j] - smsq[i - 1];
    ans -= 2 * sm * xt;
    return ans;
}
void test_case() {
    cin >> m >> n >> k >> s;
    n += m;
    for (int i = 1; i <= n; i++) {
        cin >> x[i];
    }
    sort(x + 1, x + (n + 1));
    for (int i = 1; i <= n; i++) {
        sum[i] = sum[i - 1] + x[i];
        smsq[i] = smsq[i - 1] + x[i] * x[i];
    }
    dp[0][0] = 0;
    for (int i = 1; i <= n; i++) {
        for (int e = 0; e <= k; e++) {
            dp[i][e] = 1e18;
        }
        for (int j = i; j >= 1; j--) {
            double cur = solve(j, i);
            for (int e = 1; e <= k; e++) {
                dp[i][e] = min(dp[i][e], cur + dp[j - 1][e - 1]);
            }
        }

    }
    double ans = n * (s * 0.5) * (s * 0.5) + dp[n][k];
    cout << fixed << setprecision(10) << ans << endl;
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
