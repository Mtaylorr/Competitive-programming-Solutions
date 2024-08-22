/ Mtaylor
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
int msk[N];
int freq[1 << 26];
ll ans = 0;
int n;
 
struct SmallToBigMerge {
    int tin[N], tout[N], sz[N], bchd[N], nodes[N], ti;
 
    void init(int n) { ti = -1; }
    void dfs(int u, ADJ& adj, int pa = -1) {
        tin[u] = ++ti;
        sz[u] = 1;
        nodes[ti] = u;
        pair<int, int> p = {-1, -1};
        neig(u, v, e, adj) {
            if (v == pa) continue;
            msk[v] = adj.cst[e] ^ msk[u];
            dfs(v, adj, u);
            sz[u] += sz[v];
            p = max(p, mp(sz[v], v));
        }
        bchd[u] = p.se;
        tout[u] = ti;
    }
 
    void solve(int u, ADJ& adj, int p = -1, bool keep = 1) {
        neig(u, v, e, adj) {
            if (v == p || v == bchd[u]) continue;
            solve(v, adj, u, 0);
        }
        if (bchd[u] != -1) {
            solve(bchd[u], adj, u, 1);
        }
        // don't forget to handle or add the value for u
        ans += freq[msk[u]];
        for (int j = 0; j < 26; j++) {
            ans += freq[msk[u] ^ (1 << j)];
        }
        freq[msk[u]]++;
        neig(u, v, e, adj) {
            if (v == p || v == bchd[u]) continue;
            for (int i = tin[v]; i <= tout[v]; i++) {
                int nd = nodes[i];
                ans += freq[msk[nd]];
                for (int j = 0; j < 26; j++) {
                    ans += freq[msk[nd] ^ (1 << j)];
                }
            }
            for (int i = tin[v]; i <= tout[v]; i++) {
                int nd = nodes[i];
                freq[msk[nd]]++;
            }
        }
 
        if (!keep) {
            // clear data structure
            //  loop from tin to tout and undo
            for (int i = tin[u]; i <= tout[u]; i++) {
                int nd = nodes[i];
                freq[msk[nd]]--;
            }
            // use clear() if possible
 
        }
    }
 
    void run(ADJ& adj) {
        init(adj.n);
        dfs(0, adj);
        solve(0, adj);
    }
} stb;
 
void test_case() {
    cin >> n;
    adj.init(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        char c;
        cin >> u >> v >> c;
        --u, --v;
        int m = c - 'a';
        m = 1 << m;
        adj.addBiEdge(u, v, m);
    }
    stb.run(adj);
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
