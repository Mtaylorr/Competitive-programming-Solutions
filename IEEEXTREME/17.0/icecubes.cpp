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

ll dp[1005][1005][25];
bool vis[1005][1005][25];
int v[1005][1005];
int K, B;
int n, m;

ll solve(int i, int j, int r) {
    int nr = r;
    if (v[i][j] < B) {
        nr--;
    } else {
        nr = K;
    }
    if (nr <= 0) return -1e18;
    if (i == n - 1 && j == m - 1) {
        return v[i][j];
    }
    if (vis[i][j][r]) return dp[i][j][r];
    vis[i][j][r] = 1;
    ll &rs = dp[i][j][r];
    rs = -1e18;
    if (i + 1 < n) {
        rs = max(rs, v[i][j] + solve(i + 1, j, nr));
    }
    if (j + 1 < m) {
        rs = max(rs, v[i][j] + solve(i, j + 1, nr));
    }
    return rs;
}

void test_case() {
    cin >> n >> m >> K >> B;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            cin >> v[i][j];
        }
    }

    memset(vis, 0, sizeof(vis));
    ll ans = solve(0, 0, K);
    if (ans < 0) {
        cout << "IMPOSSIBLE\n";
    } else {
        cout << ans << "\n";
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    int tt = 0;
    while (T--) {
        cout << "Case " << ++tt << ": ";
        test_case();
    }
    return 0;
}
