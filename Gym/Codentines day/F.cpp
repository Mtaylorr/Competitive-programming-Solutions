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
int c;
int k;
int mixture[7][7];
int mixturet[7][7];
int mixd[1 << 7][1 << 7];
int dist[101][101][1 << 7];
bool vis[101][101][1 << 7];
string grid[101];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
void test_case() {
    memset(mixture, -1, sizeof(mixture));
    cin >> n >> m >> c >> k;
    for (int i = 0; i < n; i++) {
        cin >> grid[i];
    }
    for (int i = 0; i < k; i++) {
        int c1, c2, c3, t;
        cin >> c1 >> c2 >> c3 >> t;
        c1--, c2--, c3--;
        mixture[c1][c2] = mixture[c2][c1] = c3;
        mixturet[c1][c2] = mixturet[c2][c1] = t;
    }
    for (int i = 0; i < (1 << c); i++) {
        for (int j = 0; j < (1 << c); j++) {
            mixd[i][j] = 1e9;
        }
    }
    for (int mask = (1 << c) - 1; mask >= 0; mask--) {
        mixd[mask][mask] = 0;
        for (int i = 0; i < c; i++) {
            if (!(mask & (1 << i))) continue;
            for (int j = i + 1; j < c; j++) {
                if (!(mask & (1 << j))) continue;
                if (mixture[i][j] == -1) continue;
                if (mask & (1 << mixture[i][j])) continue;
                int nmask = mask + (1 << mixture[i][j]);
                int d = mixturet[i][j];
                for (int _mask = 0; _mask < (1 << c); _mask++) {
                    mixd[mask][_mask] = min(mixd[mask][_mask], d + mixd[nmask][_mask]);
                }
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < (1 << c); k++) {
                dist[i][j][k] = 1e9;
            }
        }
    }
    int stmask = 0;
    if (grid[0][0] != '0') {
        stmask = (1 << ((grid[0][0] - '0') - 1));
    }
    dist[0][0][stmask] = 0;
    vis[0][0][stmask] = 1;
    queue<pair<pair<int, int>, int> > q;
    q.push({{0, 0}, stmask});
    pair<pair<int, int>, int> p;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        int x = p.fi.fi;
        int y = p.fi.se;
        int msk = p.se;

        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            if (nx >= 0 && nx < n && ny >= 0 && ny < m) {
                int nmsk = msk;
                if (grid[nx][ny] >= '1') {
                    nmsk = nmsk | (1 << ((grid[nx][ny] - '0') - 1));
                }
                if (vis[nx][ny][nmsk]) continue;
                vis[nx][ny][nmsk] = 1;
                dist[nx][ny][nmsk] = 1 + dist[x][y][msk];
                q.push({{nx, ny}, nmsk});
            }
        }
    }
    int tot = (1 << c) - 1;
    int ans = 1e9;
    for (int i = 0; i < (1 << c); i++) {
        ans = min(ans, dist[n - 1][m - 1][i] + mixd[i][tot]);
    }
    if(ans<1e9){
        cout << ans << endl;
    }else{
        cout << -1 << endl;
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
