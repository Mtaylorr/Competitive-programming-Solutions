//https://atcoder.jp/contests/abc446/tasks/abc446_e
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

int a, b, m;
bool vis[1005][1005];
int dp[1005][1005];
int solve(int x, int y) {
    if (x == 0 || y == 0) {
        return dp[x][y] = 0;
    }
    if (vis[x][y]) {
        return dp[x][y];
    }

    vis[x][y] = 1;
    dp[x][y] = 1;
    dp[x][y] = solve(y, (a * y + b * x) % m);
    return dp[x][y];
}
void test_case() {
    cin >> m >> a >> b;
    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int r = solve(i, j);
            if (r == 1) {
                ans++;
            }
        }
    }
    cout << ans << endl;
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
