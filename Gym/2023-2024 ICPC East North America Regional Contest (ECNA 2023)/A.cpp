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
const int N = 1e6 + 5;

int n, a[N];
int dp[2][N];

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        dp[0][i] = max(dp[0][i - 1], a[i]);
    }
    dp[1][n + 1] = 1e9;
    for (int i = n; i >= 1; i--) {
        dp[1][i] = min(dp[1][i + 1], a[i]);
    }
    vector<int> ans;

    for (int i = 1; i <= n; i++) {
        if (dp[0][i - 1] <= a[i] && dp[1][i + 1] > a[i]) {
            ans.pb(a[i]);
        }
    }
    int m = ans.size();
    cout << m << " ";
    m = min(m, 100);
    for (int i = 0; i < m; i++) {
        cout << ans[i] << " ";
    }
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
