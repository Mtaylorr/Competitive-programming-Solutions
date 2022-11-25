//https://codeforces.com/problemset/problem/846/D
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
const int N = 505;
int n, m, k, q;
int x, y, t[N][N];

int tree[4 * N][4 * N];

void buildy(int idx = 0, int lx = 0, int rx = n - 1, int idy = 0, int ly = 0,
            int ry = m - 1) {
    if (ly == ry) {
        tree[idx][idy] = 0;
        for (int i = lx; i <= rx; i++) {
            tree[idx][idy] = max(tree[idx][idy], t[i][ly]);
        }
        return;
    }
    int l = 2 * idy + 1;
    int r = l + 1;
    int md = ly + (ry - ly) / 2;
    buildy(idx, lx, rx, l, ly, md);
    buildy(idx, lx, rx, r, md + 1, ry);
    tree[idx][idy]=max(tree[idx][l], tree[idx][r]);
}

void buildx(int idx = 0, int lx = 0, int rx = n - 1) {
    buildy(idx, lx, rx, 0, 0, m - 1);
    if (lx == rx) {
        return;
    }
    int l = 2 * idx + 1;
    int r = l + 1;
    int md = lx + (rx - lx) / 2;
    buildx(l, lx, md);
    buildx(r, md + 1, rx);
}
int queryy(int qyl, int qyr, int idx, int idy = 0, int ly = 0, int ry = m - 1) {
    if (qyl > ry || qyr < ly) {
        return 0;
    }
    if (qyl <= ly && qyr >= ry) {
        return tree[idx][idy];
    }
    int l = 2 * idy + 1;
    int r = l + 1;
    int md = ly + (ry - ly) / 2;
    return max(queryy(qyl, qyr, idx, l, ly, md),
               queryy(qyl, qyr, idx, r, md + 1, ry));
}

int queryx(int qxl, int qxr, int qyl, int qyr, int idx = 0, int lx = 0,
           int rx = n - 1) {
    if (qxl > rx || qxr < lx) {
        return 0;
    }
    if (qxl <= lx && qxr >= rx) {
        return queryy(qyl, qyr, idx);
    }
    int l = 2 * idx + 1;
    int r = l + 1;
    int md = lx + (rx - lx) / 2;
    return max(queryx(qxl, qxr, qyl, qyr, l, lx, md),
               queryx(qxl, qxr, qyl, qyr, r, md + 1, rx));
}

void solve() {
    cin >> n >> m >> k >> q;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            t[i][j] = 2e9;
        }
    }
    for (int i = 0; i < q; i++) {
        cin >> x >> y;
        --x, --y;
        cin >> t[x][y];
    }
    buildx();
    int ans = 2e9;
    for (int i = 0; i + k <= n; i++) {
        for (int j = 0; j + k <= m; j++) {
            ans = min(ans, queryx(i, i + k - 1, j, j + k - 1));
        }
    }
    if (ans < 2e9) {
        cout << ans;
    } else {
        cout << -1;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    // cin >>T;
    T = 1;
    while (T--) {
        solve();
    }
    return 0;
}

