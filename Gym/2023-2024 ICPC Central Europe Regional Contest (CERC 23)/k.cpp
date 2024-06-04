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
const int E = 1e6 + 5;

#define neig(u, v, e, g) for (int e = g.head[u], v; ~e && ((v = g.to[e]), 1); e = g.nxt[e])

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

int n, m;
int par[N];
vector<int> keys[N];
int parkey[N];
bool vis[N];
int nxt[N];
bool inpath[N];
int intersection;
set<int> bobkeys;
bool isFirstPath[N];
bool isSecondPath[N];

void dfs(int u) {
    vis[u] = 1;
    neig(u, v, e, adj) {
        if (v == 1 && v != par[u]) {
            intersection = u;
            // dbg(intersection);
        }
        if (vis[v]) continue;
        par[v] = u;
        parkey[v] = adj.cst[e];
        dfs(v);
    }
}

void test_case() {
    cin >> n >> m;
    adj.init(n);
    for (int i = 0; i < m; i++) {
        int a, b;
        cin >> a >> b;
        adj.addBiEdge(a, b, i);
    }
    par[1] = -1;
    intersection = -1;
    dfs(1);
    if (intersection == -1 || !vis[0]) {
        cout << "No solution\n";
        return;
    }
    set<int> alicekeys;
    vector<int> alice;
    int t = 0;
    while (t != -1) {
        isFirstPath[t] = 1;
        t = par[t];
    }
    t = intersection;
    while (t != -1) {
        isSecondPath[t] = 1;
        t = par[t];
    }
    int cur = 0;
    set<int> to_drop;
    vector<int> bob;
    while (isFirstPath[cur] && !isSecondPath[cur] && cur != 1) {
        alice.pb(par[cur]);
        bob.pb(cur);
        to_drop.insert(parkey[cur]);
        cur = par[cur];
    }
    int md = cur;
    if (md == 1) {
        vector<int> path;
        cur = intersection;
        while (cur != 1) {
            path.pb(cur);
            cur = par[cur];
        }
        reverse(all(path));
        cur = intersection;
        while (cur != 1) {
            path.pb(par[cur]);
            cur = par[cur];
        }
        for (auto &u : path) {
            alice.pb(u);
        }
        path.clear();
        cur = intersection;
        bob.pb(1);
        bob.pb(intersection);
        // cur = intersection;
        // while (cur != 1) {
        //     path.pb(cur);
        //     cur = par[cur];
        // }
        // reverse(all(path));
        // for (auto &u : path) {
        //     bob.pb(u);
        // }
        reverse(all(bob));
        md = intersection;
    } else {
        while (cur != 1) {
            alice.pb(par[cur]);
            alicekeys.insert(parkey[cur]);
            cur = par[cur];
        }
        vector<int> path;
        cur = intersection;
        while (cur != md) {
            bobkeys.insert(parkey[cur]);
            path.push_back(cur);
            cur = par[cur];
        }
        bob.pb(md);
        reverse(all(path));
        for (auto &u : path) {
            bob.pb(u);
        }
        reverse(all(bob));
    }

    neig(1, v, e, adj) {
        if (v == intersection) {
            bobkeys.insert(adj.cst[e]);
        }
    }
    for (int i = 0; i < m; i++) {
        if (!bobkeys.count(i)) cout << i << " ";
    }
    cout << endl;
    for (auto &u : bobkeys) {
        cout << u << " ";
    }
    cout << endl;

    for (int i = 0; i < alice.size(); i++) {
        cout << "MOVE " << alice[i] << endl;
        if (alice[i] == md) {
            cout << "DROP ";
            for (auto &u : to_drop) {
                cout << u << " ";
            }
            cout << endl;
        }
    }
    cout << "DONE" << endl;
    for (auto &u : bob) {
        cout << "MOVE " << u << endl;
        if (u == md) {
            cout << "GRAB" << endl;
        }
    }

    cout << "DONE" << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
