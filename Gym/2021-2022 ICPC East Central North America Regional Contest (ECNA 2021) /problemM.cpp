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

int dp[55][55][3][55][55];
int m, n, k;
char grid[55][55];
string s[55];
vector<int> st[55];

int solve(int i, int j, int d, int wd, int idx) {
    if (i == m && idx == 0) return 0;
    if (i == m) return 1e9;
    int& rs = dp[i][j][d][wd][idx];
    if (rs != -1) {
        return rs;
    }
    rs = 1e9;
    if (idx == 0) {
        for (auto& w : st[grid[i][j] - 'A']) {
            rs = min(rs, 1 + solve(i + 1, j, 0, w, (idx + 1) % s[w].size()));
            if (d != 2 && j - 1 >= 0) {
                rs =
                    min(rs, 1 + solve(i, j - 1, 1, w, (idx + 1) % s[w].size()));
            }
            if (d != 1 && j + 1 < n) {
                rs =
                    min(rs, 1 + solve(i, j + 1, 2, w, (idx + 1) % s[w].size()));
            }
        }
    } else {
        if (grid[i][j] == s[wd][idx]) {
            rs = min(rs, 1 + solve(i + 1, j, 0, wd, (idx + 1) % s[wd].size()));

            if (d != 2 && j - 1 >= 0) {
                rs = min(rs,
                         1 + solve(i, j - 1, 1, wd, (idx + 1) % s[wd].size()));
            }
            if (d != 1 && j + 1 < n) {
                rs = min(rs,
                         1 + solve(i, j + 1, 2, wd, (idx + 1) % s[wd].size()));
            }
        }
    }

    return rs;
}

void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> m >> n >> k;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            cin >> grid[i][j];
        }
    }
    for (int i = 0; i < k; i++) {
        cin >> s[i];
        st[s[i][0] - 'A'].pb(i);
    }

    int ans = 1e9;
    for (int i = 0; i < n; i++) {
        ans = min(ans, solve(0, i, 0, 0, 0));
    }

    if (ans < 1e9) {
        cout << ans << endl;
    } else {
        cout << "impossible";
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
