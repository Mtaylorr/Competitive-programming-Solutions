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

const int E = 2e6 + 5;

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

int n, x[N];
int st[N], en[N];
int col[N];
bool isbipartite = true;
bool vis[N];
void dfs(int u, int c = 0) {
    vis[u] = 1;
    col[u] = c;
    neig(u, v, e, adj) {
        if (vis[v]) {
            if (col[u] == col[v]) {
                isbipartite = false;
                break;
            }
            continue;
        }
        dfs(v, c ^ 1);
    }
}

void test_case() {
    memset(st, -1, sizeof(st));
    cin >> n;
    adj.init(n);
    for (int i = 0; i < 2 * n; i++) {
        char c;
        cin >> c;
        cin >> x[i];
        x[i]--;
        if (st[x[i]] == -1) {
            st[x[i]] = i;
        } else {
            en[x[i]] = i;
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = st[i] + 1; j < en[i]; j++) {
            if (st[x[j]] < st[i] || en[x[j]] > en[i]) adj.addBiEdge(i, x[j]);
        }
    }
    for (int i = 0; i < n; i++) {
        if (!vis[i]) {
            dfs(i);
        }
    }
    if (!isbipartite) {
        cout << "*";
        return;
    }
    for (int i = 0; i < n; i++) {
        cout << "GS"[col[i]];
    }
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
