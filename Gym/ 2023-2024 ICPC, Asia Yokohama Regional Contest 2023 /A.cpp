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

int n, m;
string e = "YOKOHAMA";

ll dp[11][11][11];

string s[11];
int dx[] = {1, -1, 0, 0};
int dy[] = {0, 0, 1, -1};
ll solve(int i, int j, int c) {
    if (c == e.size() - 1) return 1;
    ll &rs = dp[i][j][c];
    if (rs != -1) return rs;

    rs = 0;
    for (int k = 0; k < 4; k++) {
        int nx = i + dx[k];
        int ny = j + dy[k];
        // dbg(nx, ny, e[c + 1], s[nx][ny]);
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && s[nx][ny] == e[c + 1]) {
            rs += solve(nx, ny, c + 1);
        }
    }
    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> s[i];
    }
    ll ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (s[i][j] == 'Y') {
                ans += solve(i, j, 0);
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
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
