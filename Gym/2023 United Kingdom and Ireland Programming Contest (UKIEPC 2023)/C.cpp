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
const double pi = acos(-1);
double dp[105][105][105];
bool vis[105][105][105];
int n, p;
double a[105];

double getval(int i, int j) {
    double ang = min(a[j] - a[i], a[i] + 2 * pi - a[j]);
    if (ang > pi) {
        ang = 2 * pi - ang;
        return -sin(ang / 2) * sin((pi - ang) / 2);
    }
    return sin(ang / 2) * sin((pi - ang) / 2);
}
double solve(int i, int r, int e) {
    if (i == e) {
        if (r == -1) return 0;
        return -1e9;
    }
    if (i > e) {
        return -1e9;
    }
    if (r <= -1) {
        return -1e9;
    }
    if (vis[i][r][e]) return dp[i][r][e];
    vis[i][r][e] = 1;
    double &rs = dp[i][r][e];
    rs = -1e9;

    for (int j = i + 1; j <= e; j++) {
        rs = max(rs, getval(i, j) + solve(j, r - 1, e));
    }
    return rs;
}

void test_case() {
    cin >> n >> p;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = pi / 180 * a[i];
    }
    double ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 2; j < n; j++) {
            ans = max(ans, getval(i, j) + solve(i, p - 2, j));
        }
    }
    ans = (ans * 1000 * 1000);
    cout << fixed << setprecision(10) << ans << endl;
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
