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
const int N = 4e3 + 5;

char g[N][N];
bool done[N][N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
int n, m;

struct DSUGraph {
    vector<ll> id, sz;
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

struct Compressor {
    vector<ll> values;
    int n;
    void init() {
        values.clear();
        n = 0;
    }
    void add(ll x) { values.pb(x); }
    void run() {
        sort(all(values));
        values.resize(unique(all(values)) - values.begin());
        n = values.size();
    }
    int compress(ll x) { return lower_bound(all(values), x) - values.begin(); }
    int greatestSmallerThanOrEqual(ll x) {
        return (upper_bound(all(values), x) - values.begin()) - 1;
    }
    int greaterThanOrEqual(ll x) {
        return (lower_bound(all(values), x) - values.begin());
    }
    ll decompress(int p) { return values[p]; }
} compressor;

int _k[N], _x[2][N], _y[2][N];
ll val[N];

void test_case() {
    n = 0;
    m = 0;
    int x = 0;
    int y = 0;
    n = 0;
    m = 0;
    string s;
    ll ans = 0;
    int id = 0;
    while (cin >> c) {
        cin >> d >> s;
        s = s.substr(1, s.size() - 2);
        c = s.back();

        if (c == '0')
            c = 'R';
        else if (c == '1')
            c = 'D';
        else if (c == '2')
            c = 'L';
        else
            c = 'U';
        s.pop_back();
        s = s.substr(1);
        std::stringstream ss;
        ss << std::hex << s;
        ss >> d;
        int k = code[c];
        int nx = x + d * dx[k];
        int ny = y + d * dy[k];
        _x[0][id] = x;
        _y[0][id] = y;
        _x[1][id] = nx;
        _y[1][id] = ny;
        _k[id] = k;
        ans += d;
        id++;
        compressor.add(x);
        compressor.add(y);
        compressor.add(nx);
        compressor.add(ny);
        compressor.add(x - 1);
        compressor.add(x + 1);
        compressor.add(y + 1);
        compressor.add(y - 1);
        compressor.add(nx + 1);
        compressor.add(ny + 1);
        compressor.add(nx - 1);
        compressor.add(ny - 1);
        x = nx;
        y = ny;
    }

    compressor.run();
    n = compressor.n;
    m = compressor.n;
    int bef = compressor.values[0];
    for (int i = 0; i < n; i++) {
        val[i] = compressor.values[i] - bef;
        bef = compressor.values[i];
    }
    for (int i = 0; i < id; i++) {
        for (int j = 0; j < 2; j++) {
            _x[j][i] = compressor.compress(_x[j][i]);
            _y[j][i] = compressor.compress(_y[j][i]);
        }
        int x = _x[0][i];
        int y = _y[0][i];
        done[2 * x][2 * y] = 1;
        while (x != _x[1][i] || y != _y[1][i]) {
            done[2 * x + dx[_k[i]]][2 * y + dy[_k[i]]] = 1;
            x += dx[_k[i]];
            y += dy[_k[i]];
            done[2 * x][2 * y] = 1;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            g[i][j] = '.';
            if (done[2 * i][2 * j]) {
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
                // dbg(i, j, val[i], val[j]);
                dsu.sz[(2 * i) * m + (2 * j)] = val[i] * val[j];
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
