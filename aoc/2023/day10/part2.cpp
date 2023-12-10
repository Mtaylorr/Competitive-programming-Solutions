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
const int N = 1e3 + 5;

string g[N];
int dist[N][N];
bool vis[N][N];
bool done[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int n, m;
map<char, set<int> > coming = {
    {'|', {2, 3}}, {'-', {0, 1}}, {'L', {1, 2}}, {'J', {0, 2}}, {'7', {0, 3}}, {'F', {1, 3}}};
map<char, set<int> > going = {
    {'|', {2, 3}}, {'-', {0, 1}}, {'L', {0, 3}}, {'J', {1, 3}}, {'7', {1, 2}}, {'F', {0, 2}}};

void bfs(int x, int y) {
    queue<pair<int, int> > q;
    q.push({x, y});
    vis[x][y] = 1;
    pair<int, int> p;
    while (!q.empty()) {
        p = q.front();
        q.pop();
        x = p.fi;
        y = p.se;
        done[2 * x][2 * y] = 1;
        for (int k = 0; k < 4; k++) {
            int nx = x + dx[k];
            int ny = y + dy[k];
            // dbg(x, y, g[x][y], k, going[g[x][y]].count(k));
            // dbg(x, y, nx, ny, k, g[nx][ny], coming[g[nx][ny]].count(k));
            if (g[x][y] != 'S' && going[g[x][y]].count(k) == 0) continue;
            if (nx >= 0 && nx < n && ny >= 0 && ny < m && g[nx][ny] != '.' && coming[g[nx][ny]].count(k)) {
                done[2 * x + dx[k]][2 * y + dy[k]] = 1;
                if (!vis[nx][ny]) {
                    dist[nx][ny] = dist[x][y] + 1;
                    q.push({nx, ny});
                    vis[nx][ny] = 1;
                }
            }
        }
    }
}

struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;
void test_case() {
    n = 0;
    string s;
    while (cin >> s) {
        g[n++] = s;
    }
    int x = 0, y = 0;
    m = g[0].size();
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (g[i][j] == 'S') {
                x = i;
                y = j;
            }
        }
    }

    bfs(x, y);
    int ans = 0;
    n *= 2;
    m *= 2;
    dsu.init(n * m + 1);
    for (int i = 0; i < n * m + 1; i++) {
        dsu.sz[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (done[i][j]) continue;
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                dsu.uni(i * m + j, n * m);
            }
        }
    }
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m / 2; j++) {
            if (!done[(2 * i)][2*j]) {
                dsu.sz[(2 * i) * m + (2 * j)] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (done[i][j]) continue;
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && !done[ni][nj]) {
                    dsu.uni(i * m + j, ni * m + nj);
                }
            }
        }
    }
    set<int> st;
    int idout = dsu.getid(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (done[i][j]) continue;
            int p = i * m + j;
            int id = dsu.getid(p);
            if (st.count(id)) continue;
            st.insert(id);
            if (id != idout) {
                ans += dsu.sz[id];
            }
        }
    }
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m / 2; j++) {
            if (done[2 * i][2 * j]) {
                cout << g[i][j];
            } else {
                int p = (2 * i) * m + (2 * j);
                int id = dsu.getid(p);
                if (id == idout) {
                    cout << "0";
                } else {
                    cout << "I";
                }
            }
        }
        cout << endl;
    }
    cout << ans << endl;
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
