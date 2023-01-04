//https://codeforces.com/problemset/problem/949/C
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

struct SCC {
    int n;
    vector<int> adj[N], radj[N], topSort, vis, scc, sccid, sccsz;
    int scccnt;
    int ans;
    void init(int n) {
        this->n = n;
        for (int i = 0; i < n; i++) {
            adj[i].clear();
            radj[i].clear();
        }
        vis.assign(n, 0);
        scc.assign(n, 0);
        topSort.clear();
        sccid.assign(n, -1);
        sccsz.assign(n, 0);
        ans = 0;
        scccnt = 0;
    }
    void addEdge(int u, int v) {
        adj[u].pb(v);
        radj[v].pb(u);
    }

    void dfsSort(int u) {
        if (vis[u]) return;
        vis[u] = 1;
        for (auto v : adj[u]) {
            dfsSort(v);
        }
        topSort.pb(u);
    }

    void rdfs(int u, int id) {
        if (vis[u]) return;
        vis[u] = 1;
        scc.pb(u);
        sccsz[id]++;
        sccid[u] = id;
        for (auto v : radj[u]) {
            rdfs(v, id);
        }
    }

    void topoSort() {
        vis.assign(n, 0);
        for (int i = 0; i < n; i++) {
            if (!vis[i]) dfsSort(i);
        }
    }

    void getSCC() {
        topoSort();
        reverse(all(topSort));
        vis.assign(n, 0);
        for (auto u : topSort) {
            if (vis[u]) continue;
            scc.clear();
            rdfs(u, scccnt);
            scccnt++;
        }
    }
} scc;

int n, m, h, u[N];
bool vis[N];
int notleaf[N];

void showans(int u) {
    vis[u] = 1;
    cout << u + 1 << " ";

    for (auto v : scc.adj[u]) {
        if (!vis[v]) {
            showans(v);
        }
    }
}

void test_case() {
    cin >> n >> m >> h;
    scc.init(n);
    for (int i = 0; i < n; i++) {
        cin >> u[i];
    }
    for (int i = 0; i < m; i++) {
        int x, y;
        cin >> x >> y;
        --x, --y;
        if ((u[x] + 1) % h == u[y]) {
            scc.addEdge(x, y);
        }
        if ((u[y] + 1) % h == u[x]) {
            scc.addEdge(y, x);
        }
    }
    scc.getSCC();
    for (int i = 0; i < n; i++) {
        for (auto v : scc.adj[i]) {
            if (scc.sccid[i] != scc.sccid[v]) {
                notleaf[scc.sccid[i]] = 1;
            }
        }
    }
    int ans = n + 1;
    int sccid = -1;
    for (int i = 0; i < scc.scccnt; i++) {
        if (notleaf[i] == 0) {
            if (scc.sccsz[i] < ans) {
                ans = min(ans, scc.sccsz[i]);
                sccid = i;
            }
        }
    }
    cout << ans << endl;
    for(int i=0;i<n;i++){
        if(scc.sccid[i]==sccid){
            showans(i);
            break;
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >> T;
    T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}

