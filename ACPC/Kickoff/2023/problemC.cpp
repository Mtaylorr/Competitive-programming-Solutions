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
const int N = 5e5 + 5;

string a[N];
string b[N];
int n, m;
int nb = 0;
vector<bool> vis[N];
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};

bool ingrid(int x, int y) {
    return x >= 0 && x < n - 1 && y >= 0 && y < m - 1 && b[x][y] != '#';
}

void dfs(int i, int j) {
    if (vis[i][j]) return;
    vis[i][j] = 1;
    nb++;
    for (int k = 0; k < 4; k++) {
        int ni = i + dx[k];
        int nj = j + dy[k];
        if (ingrid(ni, nj)) dfs(ni, nj);
    }
}

void test_case() {
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (a[i][j] == '.' && a[i + 1][j] == '.' && a[i][j + 1] == '.' &&
                a[i + 1][j + 1] == '.') {
                b[i] += '.';
            } else {
                b[i] += '#';
            }
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i].assign(m, 0);
    }
    int mx = 0;
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < m - 1; j++) {
            if (b[i][j] == '#') continue;
            if (vis[i][j]) continue;
            nb = 0;
            dfs(i, j);
            mx = max(mx, nb);
        }
    }
    cout << mx << endl;
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
