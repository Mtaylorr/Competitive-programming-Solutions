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

ll dist[2][N];
bool vis[N];
int n, m;
int p, g;

void dijk(int src, int b, int skip) {
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
        dist[b][i] = 1e18;
    }
    set<pair<ll, int> > st;
    st.insert({0, p});
    dist[b][p] = 0;
    pair<ll, int> pa;
    while (!st.empty()) {
        pa = *st.begin();
        st.erase(st.begin());
        ll d = pa.fi;
        int u = pa.se;
        if (vis[u]) continue;
        vis[u] = 1;
        if (u == skip) continue;
        neig(u, v, e, adj) {
            if (vis[v]) continue;
            ll nd = d + adj.cst[e];
            if (nd < dist[b][v]) {
                dist[b][v] = nd;
                st.insert({nd, v});
            }
        }
    }
}

void test_case() {
    cin >> n >> m;

    cin >> p >> g;
    --p, --g;
    adj.init(n);
    for (int i = 0; i < m; i++) {
        int u, v, d;
        cin >> u >> v >> d;
        --u, --v;
        adj.addBiEdge(u, v, d);
    }
    dijk(0, 0, -1);
    dijk(1, 1, g);
    vector<int> ans;
    ll target = 2 * dist[0][g];
    for (int i = 0; i < n; i++) {
        if (dist[1][i] > dist[0][i] && dist[0][i] == target) {
            ans.pb(i);
        }
    }
    if (ans.size()) {
        for (auto &u : ans) {
            cout << u + 1 << " ";
        }
    } else {
        cout << "*";
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
