//https://codeforces.com/problemset/problem/467/D
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

pair<int, int> val[N];

map<string, int> code;

string s, t;
int u[N], v[N];

string getlower(string t) {
    string ans = "";
    for (auto c : t) {
        ans += tolower(c);
    }
    return ans;
}
int nb = 0;
void add(string &s) {
    if (code.count(s)) {
        return;
    }
    int rs = 0, sze = 0;
    sze = s.size();
    for (auto &c : s) {
        rs += c == 'r';
    }
    val[nb] = {rs, sze};
    code[s] = nb++;
}

const int E = 1e6 + 5;

#define neig(u, v, e, g) \
    for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

class ADJ {
   public:
    int head[E], to[E], nxt[E], n, edgcnt = 0;
    ll cst[E];

    void addEdge(int a, int b, int c = 0) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        cst[edgcnt] = c;
        edgcnt++;
    }

    void addBiEdge(int a, int b, int c = 0) {
        addEdge(a, b, c);
        addEdge(b, a, c);
    }
    void init(int _n) {
        n = _n;
        memset(head, -1, n * sizeof(head[0]));
        edgcnt = 0;
    }
} adj;

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
pair<int, int> sccval[N];
int n, m;
string essai[N];
bool vis[N];

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    neig(u, v, e, adj) {
        dfs(v);
        sccval[u] = min(sccval[u], sccval[v]);
    }
}
void test_case() {
    cin >> m;
    for (int i = 0; i < m; i++) {
        cin >> essai[i];
        essai[i] = getlower(essai[i]);
        add(essai[i]);
    }
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s >> t;
        s = getlower(s);
        t = getlower(t);
        add(s);
        add(t);
        u[i] = code[s];
        v[i] = code[t];
    }
    scc.init(nb);
    for (int i = 0; i < n; i++) {
        scc.addEdge(u[i], v[i]);
    }
    scc.getSCC();
    adj.init(scc.scccnt);
    for (int i = 0; i < scc.scccnt; i++) {
        sccval[i] = {1e9, 1e9};
    }
    for (int i = 0; i < nb; i++) {
        int id = scc.sccid[i];
        sccval[id] = min(sccval[id], val[i]);
    }
    for (int i = 0; i < n; i++) {
        int pu = scc.sccid[u[i]];
        int pv = scc.sccid[v[i]];
        if (pu == pv) continue;
        adj.addEdge(pu, pv);
    }
    for (int i = 0; i < scc.scccnt; i++) {
        if (!vis[i]) dfs(i);
    }

    ll r = 0;
    ll l = 0;
    for (int i = 0; i < m; i++) {
        int p = code[essai[i]];
        pair<int, int> pa = sccval[scc.sccid[p]];
        r += pa.fi;
        l += pa.se;
    }
    cout << r << " " << l;
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
