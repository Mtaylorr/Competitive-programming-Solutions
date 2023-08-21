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

ll dist[3][10005];
int h, w;
int a[105][105];
set<int> adj[2][N];
bool vis[10005];
void bfs(int src, int b, int c) {
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i <= 10000; i++) {
        dist[b][i] = 1e9;
    }
    dist[b][src] = 0;
    queue<int> q;
    q.push(src);
    vis[src] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto &v : adj[c][u]) {
            if (vis[v]) continue;
            vis[v] = 1;
            dist[b][v] = dist[b][u] + 1;
            q.push(v);
        }
    }
}
void test_case() {
    cin >> h >> w;
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            cin >> a[i][j];
        }
    }
    for (int i = 0; i < h; i++) {
        for (int j = 0; j < w; j++) {
            if (a[i][j] != a[i + 1][j]) {
                adj[0][a[i][j]].insert(a[i + 1][j]);
                adj[1][a[i + 1][j]].insert(a[i][j]);
            }
        }
    }
    bfs(0, 0, 1);
    set<int> st;
    int x = -1, y = -1;
    for (int i = 0; i < w; i++) {
        st.insert(a[0][i]);
    }
    x = *st.begin();
    bfs(x, 1, 0);
    st.erase(st.begin());
    if (st.size()) {
        y = *st.begin();
        bfs(y, 2, 0);
        st.erase(st.begin());
    }
    if (y == -1) {
        cout << dist[0][x] << endl;
        return;
    }
    ll ans = 1e9;
    for (int i = 0; i < 10000; i++) {
        ans = min(ans, dist[0][i] + dist[1][i] + dist[2][i]);
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
