//https://atcoder.jp/contests/abc446/tasks/abc446_f
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

int dist[N];
bool vis[N];
int n, m;

void test_case() {
    cin >> n >> m;
    adj.init(n);
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        adj.addEdge(u, v);
    }
    for (int i = 0; i < n; i++) {
        dist[i] = 1e9;
    }
    set<pair<int, int> > st;
    st.insert({0, 0});
    dist[0] = 0;
    pair<int, int> p;
    while (!st.empty()) {
        p = *st.begin();
        st.erase(st.begin());
        int u = p.second;
        int d = p.first;
        if (vis[u]) continue;
        vis[u] = 1;
        neig(u, v, e, adj) {
            if (vis[v]) continue;
            if (dist[v] > max(v, d)) {
                dist[v] = max(v, d);
                st.insert({dist[v], v});
            }
        }
    }
    int cur = 0;
    set<int> rem;
    int nextpossible = 0;
    for (int i = 0; i < n; i++) {
        neig(i, v, e, adj) {
            if (v > i) {
                rem.insert(v);
            }
        }
        if (rem.count(i)) {
            rem.erase(i);
        }
        nextpossible = max(nextpossible, dist[i]);
        if (nextpossible == i) {
            cout << rem.size() << "\n";
        } else {
            cout << -1 << "\n";
        }
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
