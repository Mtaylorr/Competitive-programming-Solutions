//https://codeforces.com/contest/570/problem/E
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
vector<pair<int, int> > pos[1005];
int dp[2][501][501];
char grid[505][505];
int n, m;

bool adj(pair<int, int> &x, pair<int, int> &y) {
    return abs(x.fi - y.fi) + abs(x.se - y.se) <= 1;
}
void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
        for (int j = 0; j < m; j++) {
            pos[i + j].pb({i, j});
        }
    }
    int st = 1;
    if ((n + m - 1) % 2) {
        int x = (n + m - 1) / 2;
        st = x - 1;
        int id = x % 2;
        for (int i = 0; i < pos[x].size(); i++) {
            dp[id][i][i] = 1;
        }
    } else {
        int l = 0;
        int x = (n + m - 1) / 2 - 1;
        int y = n + m - 1 - 1 - x;
        int id = x % 2;
        st = x - 1;
        for (int i = 0; i < pos[x].size(); i++) {
            for (int j = 0; j < pos[y].size(); j++) {
                dp[id][i][j] = 0;
                if (grid[pos[x][i].fi][pos[x][i].se] ==
                        grid[pos[y][j].fi][pos[y][j].se] &&
                    adj(pos[x][i], pos[y][j])) {
                    dp[id][i][j] = 1;
                }
            }
        }
    }
    for (int i = st; i >= 0; i--) {
        int x = i;
        int y = n + m - 1 - x - 1;
        int id = i % 2;
        for (int i = 0; i < pos[x].size(); i++) {
            for (int j = 0; j < pos[y].size(); j++) {
                dp[id][i][j] = 0;
                if (grid[pos[x][i].fi][pos[x][i].se] !=
                    grid[pos[y][j].fi][pos[y][j].se])
                    continue;

                for (int k = -1; k <= 1; k++) {
                    if (i + k >= pos[x + 1].size() || i + k < 0) continue;
                    if (!adj(pos[x][i], pos[x + 1][i + k])) continue;
                    for (int o = -1; o <=1; o++) {
                        if (j + o >= pos[y - 1].size() || j + o < 0) continue;
                        if (!adj(pos[y][j], pos[y - 1][j + o])) continue;
                        dp[id][i][j] =
                            (dp[id][i][j] + dp[id ^ 1][i + k][j + o]) % MOD;
                    }
                }
            }
        }
    }
    cout << dp[0][0][0] << endl;
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
