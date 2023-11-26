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

const int E = 4e6 + 100;

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

const int B_TRIE = 26;
const int N_TRIE = N;

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

    void initGraph() {
        adj.init(ndcnt);
        buildGraph(0);
    }

    void buildGraph(int cur) {
        if (cur == -1) return;
        for (int i = 0; i < B_TRIE; i++) {
            int nx = nodes[cur].nxt[i];
            if (nx != -1) {
                nodes[nx].cnt += nodes[cur].cnt;
                adj.addBiEdge(cur, nx);
                buildGraph(nx);
            }
        }
    }

    int ins(string &s, int p = 1, int from = 0, int to = -1) {
        // s is the string to add to the trie
        // p is the index of the string if we want to get it after
        // from is where to start to the string from
        // to is the until when we need to add the string
        int cur = 0;
        if (to == -1) to = sz(s) - 1;
        for (int i = from; i <= to; i++) {
            // To change if the characters change
            int id = s[i] - 'a';
            int &nx = nodes[cur].nxt[id];
            if (nx == -1) {
                nx = addnode();
            }
            cur = nx;
        }
        nodes[cur].cnt++;
        nodes[cur].isEnd = p;
        return cur;
    }
} trie;
const int L = 21;

class LCABinaryLifting {
   public:
    int up[N][L];
    int dpth[N];
    int po[L];

    void run(int src, ADJ &adj) {
        for (int i = 0; i < L; i++) {
            po[i] = (1 << i);
        }
        dpth[src] = 0;
        dfs(src, src, adj);
    }
    void dfs(int u, int p, ADJ &adj) {
        up[u][0] = p;
        for (int i = 1; i < L; i++) {
            up[u][i] = up[up[u][i - 1]][i - 1];
        }
        neig(u, v, e, adj) {
            if (v == p) continue;
            dpth[v] = dpth[u] + 1;
            dfs(v, u, adj);
        }
    }
    int getlca(int u, int v) {
        if (dpth[u] < dpth[v]) {
            swap(u, v);
        }
        int l = dpth[u] - dpth[v];
        for (int i = L - 1; i >= 0; i--) {
            if (po[i] <= l) {
                l -= po[i];
                u = up[u][i];
            }
        }
        for (int i = L - 1; i >= 0; i--) {
            if (up[u][i] != up[v][i]) {
                u = up[u][i];
                v = up[v][i];
            }
        }
        if (u != v) {
            u = up[u][0];
        }
        return u;
    }

    int getkthpar(int u, int k) {
        for (int i = L - 1; i >= 0; i--) {
            if (k >= po[i]) {
                u = up[u][i];
                k -= po[i];
            }
        }
        return u;
    }
    int getkthonpath(int u, int v, int k) {
        int lc = getlca(u, v);
        int d = dpth[u] - dpth[lc];
        if (d >= k) return getkthpar(u, k);
        d = dpth[u] + dpth[v] - 2 * dpth[lc];
        return getkthpar(v, d - k);
    }

    int getdist(int u, int v) {
        int lc = getlca(u, v);
        return dpth[u] + dpth[v] - 2 * dpth[lc];
    }
} LCA;

string s;
int idx[N];
int n, q;
void test_case() {
    trie.init();
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> s;
        idx[i] = trie.ins(s);
    }
    trie.initGraph();
    LCA.run(0, adj);
    while (q--) {
        int a, b;
        cin >> a >> b;
        int lc = LCA.getlca(idx[--a], idx[--b]);
        cout << trie.nodes[lc].cnt << endl;
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
