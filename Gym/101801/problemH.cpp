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

vector<int> adj[N];

int dist[N][2];
bool vis[N];
int n;
int a, b;
ll ans;
int dp[N];
ll rem;

void bfs(int src, int b) {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    vis[src] = 1;
    dist[src][b] = 0;
    q.push(src);
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            vis[v] = 1;
            dist[v][b] = dist[u][b] + 1;
            q.push(v);
        }
    }
}

void dfs(int u, int p = -1, int cur = 0) {
    dp[u] = 0;
    if (u == b) return;
    dp[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (dist[b][0] == dist[v][0] + dist[v][1]) {
            continue;
        }
        dfs(v, u);
        dp[u] += dp[v];
    }

    if (dist[b][0] == dist[u][0] + dist[u][1]) {
        //dbg(u, dp[u], (n - dp[u] - cur));
        ans += ((dp[u]) * 1ll * (n - dp[u] - cur));
    }
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (dist[b][0] == dist[v][0] + dist[v][1]) {
            dfs(v, u, dp[u]+cur);
        }
    }
}

void test_case() {
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++) {
        adj[i].clear();
    }
    --a, --b;
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    if (a == b) {
        cout << 0 << endl;
        return;
    }
    bfs(a, 0);
    bfs(b, 1);
    ans=0;
    dfs(a);
    cout << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
