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

int n, a[N];
int dp[2][N];

void test_case() {
    cin >> n;
    int nb = 0;
    a[0] = 1;
    a[n + 1] = 1;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) {
            dp[0][i] = 1 + dp[0][i - 1];
        } else {
            nb++;
            dp[0][i] = 0;
        }
    }
    if (!nb) {
        cout << -1;
        return;
    }
    for (int i = n; i >= 1; i--) {
        if (a[i] % 2 == 0) {
            dp[1][i] = 1 + dp[1][i + 1];
        } else {
            dp[1][i] = 0;
        }
    }
    int ans = 0;
    for (int i = 1; i <= n; i++) {
        if (a[i] % 2) {
            ans = max(ans, 1 + dp[1][i + 1] + dp[0][i - 1]);
        }
    }
    cout << ans;
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
