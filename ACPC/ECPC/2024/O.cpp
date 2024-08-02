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

const int B_TRIE = 2;
const int L_TRIE = 60;  // only for binary trie, L is the maximum bit +1
const int N_TRIE = N * L_TRIE;

struct TrieNode {
    int nxt[B_TRIE];
    int isEnd;
    int cnt;
    void init() {
        memset(nxt, -1, sizeof(nxt));
        cnt = 0;
        isEnd = -1;
    }
    TrieNode() { init(); }
};

class Trie {
   public:
    TrieNode nodes[N_TRIE];
    int ndcnt = 0;
    int addnode() {
        nodes[ndcnt].init();
        return ndcnt++;
    }
    void init() {
        ndcnt = 0;
        addnode();
    }
    void ins(ll x) {
        // x is the number to add to the trie
        int cur = 0;
        for (int i = L_TRIE - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            int &nx = nodes[cur].nxt[id];
            if (nx == -1) {
                nx = addnode();
            }
            nodes[nx].cnt++;
            cur = nx;
        }
    }
    void erase(ll x) {
        // x is the number to add to the trie
        int cur = 0;
        for (int i = L_TRIE - 1; i >= 0; i--) {
            int id = (x >> i) & 1;
            int &nx = nodes[cur].nxt[id];
            if (nx == -1) {
                nx = addnode();
            }
            nodes[nx].cnt--;
            cur = nx;
            if (nodes[nx].cnt == 0) {
                nx = -1;
            }
        }
    }

    ll srch(int cur, int b, ll x) {
        if (b == -1) {
            return 0;
        }
        int id = (x >> b) & 1;
        if (nodes[cur].nxt[id] != -1) {
            return srch(nodes[cur].nxt[id], b - 1, x);
        }
        return (1ll << b) + srch(nodes[cur].nxt[id ^ 1], b - 1, x);
    }
} trie;
int n;
ll a[N];
int q;
ll val[N];
ll dp[N];
void dfs(int u, int p = -1) {
    if (u) {
        val[u] = trie.srch(0, 59, a[u]);
    }
    trie.ins(a[u]);
    dp[u] = val[u];
    neig(u, v, e, adj) {
        if (v == p) continue;
        dfs(v, u);
        dp[u] = min(dp[u], dp[v]);
    }
    trie.erase(a[u]);
}

void test_case() {
    trie.init();
    cin >> n;
    adj.init(n);
    for (int i = 1; i < n; i++) {
        int p;
        cin >> p;
        --p;
        adj.addBiEdge(i, p);
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    dfs(0);
    cin >> q;
    for (int i = 0; i < q; i++) {
        int u;
        cin >> u;
        --u;
        cout << dp[u] << endl;
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
