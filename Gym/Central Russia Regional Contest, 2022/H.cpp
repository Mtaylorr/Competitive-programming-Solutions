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

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};
int dist[1005][1005][4];
bool vis[1005][1005][4];
int n, m, l, r, f, t;
string g[1005];

int bfs(int x, int y, int b) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            for (int k = 0; k < 4; k++) {
                dist[i][j][k] = 1e9;
            }
        }
    }
    set<pair<ll, vector<int> > > q;
    q.insert({0, {x, y, b}});
    vis[x][y][b] = 1;
    dist[x][y][b]=0;
    pair<ll, vector<int> > p;
    ll ans = 1e9;
    while (!q.empty()) {
        p = *q.begin();
        q.erase(q.begin());
        x = p.se[0];
        y = p.se[1];
        int z = p.se[2];
        if (g[x][y] == '*') {
            ans = min(ans, p.fi - f);
            continue;
        }
        int nx = x + dx[z];
        int ny = y + dy[z];
        if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] != '#') {
            if (vis[nx][ny][z] == 0 && dist[nx][ny][z] > dist[x][y][z] + f) {
                dist[nx][ny][z] = dist[x][y][z] + f;
                q.insert({dist[nx][ny][z], {nx, ny, z}});
            }
        }
        int b = (z + 3) % 4;
        if (vis[x][y][b] == 0 && dist[x][y][b] > dist[x][y][z] + l) {
            dist[x][y][b] = dist[x][y][z] + l;
            q.insert({dist[x][y][b], {x, y, b}});
        }
        b = (z + 1) % 4;
        if (vis[x][y][b] == 0 && dist[x][y][b] > dist[x][y][z] + r) {
            dist[x][y][b] = dist[x][y][z] + r;
            q.insert({dist[x][y][b], {x, y, b}});
        }
    }
    return ans;
}

void test_case() {
    cin >> n >> m >> l >> r >> f >> t;
    for (int i = 0; i < n; i++) {
        cin >> g[i];
    }
    int x, y;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'V') {
                x = i;
                y = j;
            }
        }
    }
    int ans = bfs(x, y, 1);
    if (ans <= t) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
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
