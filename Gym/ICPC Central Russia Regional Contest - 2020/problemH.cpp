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

int idx[1005][1005];
int dp[100][25][5];
int n, m;
int xp[N], yp[N];
int dx[] = {1, 1, -1, -1, 2, 2, -2, -2};
int dy[] = {2, -2, 2, -2, 1, -1, 1, -1};

bool _in(int x, int y, int i) {
    i %= 4;
    switch (i) {
        case 0:
            return (x < 2);
        case 1:
            return y < 2;
        case 2:
            return x >= n - 2;
    }
    return y >= m - 2;
}

bool inSpace(int x, int y, int i) {
    i %= 4;
    return _in(x, y, i) || _in(x, y, (i + 1) % 4);
}

int solve(int p, int steps, int c) {
    if (p == 0) return 1e9;
    if (steps > 25) return 1e9;

    if (p == 1 && c == 4) {
        return 0;
    }

    if (steps >= 100) return 1e9;

    int &rs = dp[p][steps][c];
    if (rs != -1) return rs;

    rs = 1e9;
    int x = xp[p];
    int y = yp[p];
    // dbg(x, y, steps, c);

    if (c + 1 < 5 && inSpace(x, y, c + 1)) {
        rs = min(rs, solve(p, steps, c + 1));
    }
    for (int k = 0; k < 8; k++) {
        int nx = x + dx[k];
        int ny = y + dy[k];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && idx[nx][ny] &&
            inSpace(nx, ny, c)) {
            rs = min(rs, 1 + solve(idx[nx][ny], steps + 1, c));
        }
    }
    int d = 0;
    int cc = 0;
    int ny;
    int nx;
    for (int cc = 0; cc < 4; cc++) {
        if (_in(x, y, cc)) {
            switch (cc) {
                case 0:
                    ny = 3;
                    if (ny % 2 != y % 2) ny--;
                    if (ny < y) {
                        d = (y - ny) / 2;
                        assert(ny % 2 == y % 2);
                        int nx = x;
                        if (d % 2) nx = x == 0 ? 1 : 0;
                        // dbg(nx, ny, idx[nx][ny], d);
                        rs = min(rs, d + solve(idx[nx][ny], steps, c));
                    }
                    break;
                case 3:
                    nx = 3;
                    if (nx % 2 != x % 2) nx--;
                    if (nx < x) {
                        d = (x - nx) / 2;
                        assert(nx % 2 == x % 2);
                        int ny = y;
                        if (d % 2) ny = y == m - 1 ? m - 2 : m - 1;
                        // dbg(nx, ny, idx[nx][ny], d);
                        rs = min(rs, d + solve(idx[nx][ny], steps, c));
                    }
                    break;
                case 2:
                    ny = m - 4;
                    if (ny % 2 != y % 2) ny++;
                    if (ny > y) {
                        d = (ny - y) / 2;
                        assert(ny % 2 == y % 2);
                        int nx = x;
                        if (d % 2) nx = x == n - 1 ? n - 2 : n - 1;
                        // dbg(nx, ny, idx[nx][ny], d);
                        rs = min(rs, d + solve(idx[nx][ny], steps, c));
                    }
                    break;
                case 1:
                    nx = n - 4;
                    if (nx % 2 != x % 2) nx++;
                    if (nx > x) {
                        d = (nx - x) / 2;
                        assert(nx % 2 == x % 2);
                        int ny = y;
                        if (d % 2) ny = y == 0 ? 1 : 0;
                        rs = min(rs, d + solve(idx[nx][ny], steps, c));
                    }
                    break;
            }
        }
    }
    return rs;
}
void test_case() {
    memset(dp, -1, sizeof(dp));
    cin >> n >> m;
    int cnt = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (i >= 2 && i < n - 2 && j >= 2 && j < m - 2) continue;
            if (i - 2 >= 2 && i + 2 < n - 2) continue;
            if (j - 2 >= 2 && j + 2 < m - 2) continue;
            idx[i][j] = cnt;
            xp[cnt] = i;
            yp[cnt] = j;
            cnt++;
        }
    }
    int ans = solve(1, 0, 0);
    if (ans < 1e9) {
        cout << ans << endl;
    } else {
        cout << 0 << endl;
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
