// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
// #define mp make_pair
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
const int N = 50000 + 5, E = 2 * 505 * 505 + 5, M = N;
const int MOD = 1e9 + 7;

#define neig(u, v, e) for (int e = head[u], v; (~e) && (v = to[e], 1); e = nxt[e])
int head[N], nxt[E], to[E], edgcnt, n;
int vis[N], vid = 0, dist[N];
int l2r[N], r2l[M];

void addEdge(int a, int b) {
    nxt[edgcnt] = head[a];
    head[a] = edgcnt;
    to[edgcnt] = b;
    edgcnt++;
}

void init() {
    memset(head, -1, n * sizeof(head[0]));
    edgcnt = 0;
}

void bfs() {
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (l2r[i] == -1) {
            q.push(i);
            dist[i] = 0;
        } else {
            dist[i] = -1;
        }
    }
    while (q.size()) {
        int lid = q.front();
        q.pop();
        neig(lid, rid, e) {
            int newlid = r2l[rid];
            if (newlid != -1 && dist[newlid] == -1) {
                dist[newlid] = dist[lid] + 1;
                q.push(newlid);
            }
        }
    }
}

int dfs(int lid) {
    neig(lid, rid, e) {
        if (r2l[rid] != -1 && dist[r2l[rid]] != dist[lid] + 1) continue;
        if (r2l[rid] == -1 || dfs(r2l[rid])) {
            r2l[rid] = lid;
            l2r[lid] = rid;
            return 1;
        }
    }
    return 0;
}
int m, x, y;
int maxMatching() {
    int res = 0;
    memset(r2l, -1, m * sizeof(r2l[0]));
    memset(l2r, -1, n * sizeof(r2l[0]));
    bool bl = true;
    while (bl) {
        bl = false;
        bfs();
        for (int i = 0; i < n; i++) {
            if (dist[i] == 0 && dfs(i)) {
                res++;
                bl = true;
            }
        }
    }
    return res;
}

int n1, n2;
bool adj[505][505];
void test_case() {
    cin >> n1 >> n2;
    n = n1;
    m = n2;
    init();
    int q;
    cin >> q;
    for (int i = 0; i < q; i++) {
        int a, b;
        cin >> a >> b;
        --a, --b;
        b -= (n1);
        adj[a][b] = 1;
    }
    for (int i = 0; i < n1; i++) {
        for (int j = 0; j < n2; j++) {
            if (!adj[i][j]) {
                addEdge(i, j);
            }
        }
    }
    int rs = n1 + n2 - maxMatching();
    cout << rs << endl;
}

int main() {
    // #ifndef ONLINE_JUDGE
    //     freopen("in.txt", "r", stdin);
    // #endif
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
