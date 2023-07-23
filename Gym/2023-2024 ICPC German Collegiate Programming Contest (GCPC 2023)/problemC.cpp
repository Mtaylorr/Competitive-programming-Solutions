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
int n, m, k;
vector<int> holes;
ll dist[2][N];
bool vis[N];
void bfs(int u, int b) {
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    queue<int> q;
    dist[b][u] = 0;
    vis[u] = 1;
    q.push(u);
    while (!q.empty()) {
        u = q.front();
        q.pop();
        for (auto v : adj[u]) {
            if (vis[v]) continue;
            q.push(v);
            dist[b][v] = dist[b][u] + 1;
            vis[v] = 1;
        }
    }
}

void test_case() {
    cin >> n >> m >> k;
    for (int i = 0; i < k; i++) {
        int x;
        cin >> x;
        holes.pb(--x);
    }
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        adj[a].pb(b);
        adj[b].pb(a);
    }
    bfs(0, 0);
    bfs(n - 1, 1);
    ll sumdist = 0;
    for (auto u : holes) {
        sumdist += dist[1][u];
    }
    ll ans = 1e18;
    for (auto u : holes) {
        ans = min(ans, (k - 1) * dist[0][u] + sumdist - dist[1][u]);
    }
    ll d = __gcd(ans, (ll)(k - 1));
    if (dist[0][n - 1] * (k-1) <= ans) {
        cout << dist[0][n - 1] << "/" << 1 << endl;
        return;
    }
    cout << ans / d << "/" << (k - 1) / d << endl;
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
