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
const int N = 3e3 + 5;

char g[N][N];
bool done[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int n, m;

struct DSUGraph {
    vector<int> id, sz;
    void init(int n) {
        id.assign(n, 0);
        sz.assign(n, 0);
        for (int i = 0; i < n; i++) {
            id[i] = i;
            sz[i] = 1;
        }
    }
    int getid(int u) { return (u == id[u] ? u : id[u] = getid(id[u])); }
    bool sameSet(int u, int v) { return getid(u) == getid(v); }
    void uni(int u, int v) {
        v = getid(v);
        u = getid(u);
        if (u == v) return;
        id[u] = v;
        sz[v] += sz[u];
    }
} dsu;
char c;
int d;
string s;
map<char, int> code = {{'R', 0}, {'L', 1}, {'U', 3}, {'D', 2}};
void test_case() {
    n = 0;
    m = 0;
    int x = 1000;
    int y = 1000;
    n = 1001;
    m = 1001;
    string s;
    done[2 * x][2 * y] = 1;
    int ans = 0;

    while (cin >> c) {
        cin >> d >> s;
        int k = code[c];
        while (d--) {
            done[2 * x + dx[k]][2 * y + dy[k]] = 1;
            x += dx[k];
            y += dy[k];
            done[2 * x][2 * y] = 1;
            n = max(n, x + 1);
            m = max(m, y + 1);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = '.';
            if (done[2 * i][2 * j]) {
                ans++;
                g[i][j] = '#';
            }
        }
    }
    n *= 2;
    m *= 2;
    dsu.init(n * m + 1);
    for (int i = 0; i < n * m + 1; i++) {
        dsu.sz[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (done[i][j]) continue;
            if (i == 0 || i == n - 1 || j == 0 || j == m - 1) {
                dsu.uni(i * m + j, n * m);
            }
        }
    }
    for (int i = 0; i < n / 2; i++) {
        for (int j = 0; j < m / 2; j++) {
            if (!done[(2 * i)][2 * j]) {
                dsu.sz[(2 * i) * m + (2 * j)] = 1;
            }
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (done[i][j]) continue;
            for (int k = 0; k < 4; k++) {
                int ni = i + dx[k];
                int nj = j + dy[k];
                if (ni >= 0 && ni < n && nj >= 0 && nj < m && !done[ni][nj]) {
                    dsu.uni(i * m + j, ni * m + nj);
                }
            }
        }
    }
    set<int> st;
    int idout = dsu.getid(n * m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (done[i][j]) continue;
            int p = i * m + j;
            int id = dsu.getid(p);
            if (st.count(id)) continue;
            st.insert(id);
            if (id != idout) {
                ans += dsu.sz[id];
            }
        }
    }
    // for (int i = 0; i < n / 2; i++) {
    //     for (int j = 0; j < m / 2; j++) {
    //         if (done[2 * i][2 * j]) {
    //             cout << g[i][j];
    //         } else {
    //             int p = (2 * i) * m + (2 * j);
    //             int id = dsu.getid(p);
    //             if (id == idout) {
    //                 cout << "0";
    //             } else {
    //                 cout << "I";
    //             }
    //         }
    //     }
    //     cout << endl;
    // }
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
