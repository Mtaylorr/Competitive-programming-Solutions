//https://codeforces.com/problemset/problem/1239/D
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
const int N = 1e6 + 5;

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
int n, m;
int outdeg[N];
int a[N], b[N];

void test_case() {
    cin >> n >> m;
    scc.init(n);
    for (int i = 0; i < m; i++) {
        cin >> a[i] >> b[i];
        --a[i], --b[i];
        scc.addEdge(a[i], b[i]);
    }

    scc.getSCC();
    for (int i = 0; i < n; i++) {
        outdeg[i] = 0;
    }
    for (int i = 0; i < m; i++) {
        if (scc.sccid[a[i]] != scc.sccid[b[i]]) {
            outdeg[scc.sccid[a[i]]] = 1;
        }
    }
    int id0 = -1;
    for (int i = 0; i < scc.scccnt; i++) {
        if (scc.sccsz[i] != n && outdeg[i] == 0) {
            id0 = i;
            break;
        }
    }
    if (id0==-1) {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
    cout << scc.sccsz[id0] << " " << n - scc.sccsz[id0] << endl;

    for (int i = 0; i < n; i++) {
        if (scc.sccid[i] == id0) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    for (int i = 0; i < n; i++) {
        if (scc.sccid[i] != id0) {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
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
