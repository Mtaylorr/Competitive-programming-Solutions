//https://codeforces.com/problemset/problem/1423/B
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
const int M = N;

class MaxMatching {
   public:
    MaxMatching(){};
    int head[N], nxt[E], to[E], edgcnt, n, m;
    int vis[N], vid = 0, dist[N];
    int l2r[N], r2l[M];

    void addEdge(int a, int b) {
        nxt[edgcnt] = head[a];
        head[a] = edgcnt;
        to[edgcnt] = b;
        edgcnt++;
    }
    void init(int n, int m) {
        this->n = n;
        this->m = m;
        memset(head, -1, n * sizeof(head[0]));
        memset(vis, -1, n * sizeof(vis[0]));
        edgcnt = 0;
        vid = 0;
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
            for (int e = head[lid], rid; (~e) && (rid = to[e], 1); e = nxt[e]) {
                int newlid = r2l[rid];
                if (newlid != -1 && dist[newlid] == -1) {
                    dist[newlid] = dist[lid] + 1;
                    q.push(newlid);
                }
            }
        }
    }
    int dfs(int lid) {
        for (int e = head[lid], rid; (~e) && (rid = to[e], 1); e = nxt[e]) {
            if (r2l[rid] != -1 && dist[r2l[rid]] != dist[lid] + 1) continue;
            if (r2l[rid] == -1 || dfs(r2l[rid])) {
                r2l[rid] = lid;
                l2r[lid] = rid;
                return 1;
            }
        }
        return 0;
    }

    int run() {
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
} maxmatching;

int n, m;
int u[N], v[N], d[N];

bool ok(int x) {
    maxmatching.init(n, n);
    for (int i = 0; i < m; i++) {
        if (d[i] <= x) {
            maxmatching.addEdge(u[i], v[i]);
        }
    }
    int rs = maxmatching.run();
    return rs == n;
}

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < m; i++) {
        cin >> u[i] >> v[i] >> d[i];
        --u[i], --v[i];
    }
    int l = 1;
    int r = 1e9 + 5;
    while (l < r) {
        int md = (l + r) / 2;
        if (ok(md)) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    if (l <= 1e9) {
        cout << l << endl;
    } else {
        cout << -1;
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
