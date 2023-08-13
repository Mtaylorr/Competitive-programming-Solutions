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

ll CNK[55][55];
ll cnk(int n, int k) {
    if (k < 0) return 0;
    if (k > n) return 0;
    if (k == 0) return 1;
    if (CNK[n][k] != -1) return CNK[n][k];
    return CNK[n][k] = cnk(n - 1, k - 1) + cnk(n - 1, k);
}

double dp[20][20][20];

bool vis[20][20][20];
double tot;
map<int, int> freq;
int a[N], b[N];
int n, d, c;

double solve(int x, int y, int z) {
    if (x + z == 0) return 0;
    if (x + y == 0) return 0;
    if (vis[x][y][z]) return dp[x][y][z];
    vis[x][y][z] = 1;
    double &rs = dp[x][y][z];
    rs = 0;
    double p = cnk(n - x - y - z, d) / tot;
    for (int i = 0; i <= x; i++) {
        for (int j = 0; j <= y; j++) {
            for (int k = 0; k <= z; k++) {
                if (i + j + k > d) break;
                double prob = cnk(x, i) * cnk(y, j) * cnk(z, k) *
                              cnk(n - x - y - z, d - i - j - k);
                rs += prob * (solve(x - i, y - j, z - k));
            }
        }
    }
    rs /= tot;
    rs++;
    rs *= (1 / (1 - p));
    return rs;
}

void test_case() {
    memset(CNK, -1, sizeof(CNK));
    cin >> n >> d >> c;
    for (int i = 0; i < c; i++) {
        cin >> a[i];
        freq[a[i]]++;
    }
    for (int i = 0; i < c; i++) {
        cin >> b[i];
        freq[b[i]]++;
    }
    int x = 0;
    int y = 0;
    int z = 0;
    tot = cnk(n, d);
    for (int i = 0; i < c; i++) {
        if (freq[a[i]] == 2)
            x++;
        else
            y++;
    }
    for (int i = 0; i < c; i++) {
        if (freq[b[i]] == 1) z++;
    }

    cout << fixed << setprecision(10) << solve(x, y, z) << endl;
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
