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

int n;
int a[N];
ll dp[N];
ll sum[N];

void preprocess() {
    for (int i = 1; i <= 2e5; ++i) {
        sum[i] = sum[i - 1] + (int)sqrt(i);
    }
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; ++i) {
        ll mx = 0;
        for (int j = 1; j <= 447; ++j) {
            int x = j * j;
            if (x >= a[i] + 1 && x - a[i] <= 1e5 && dp[x - a[i]] >= 0) {
                int y = x - a[i];
                mx = max(mx, sum[x] - sum[y] - sum[a[i]] + dp[y]);
            }
        }
        dp[a[i]] = max(dp[a[i]], mx);
        ans = max(ans, mx);
    }
    cout << ans << endl;

    for (int i = 0; i < n; i++) {
        dp[a[i]] = -1e18;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    preprocess();
    for (int i = 0; i <= 2e5; i++) {
        dp[i] = -1e18;
    }
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
