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

double xs[2], ys[2];
double v[2];
double x[N], y[N];
double dist[2][N];
double distb[20][20];

double calcdist(double a, double b, double c, double d) {
    return sqrt((a - c) * (a - c) + (b - d) * (b - d));
}

void calc(int j, int i) {
    double l = -1e6;
    double r = 1e6;
    for (int k = 0; k < 100; k++) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double v1 = calcdist(xs[j], ys[j], m1, 0) / v[0] + calcdist(x[i], y[i], m1, 0) / v[1];
        double v2 = calcdist(xs[j], ys[j], m2, 0) / v[0] + calcdist(x[i], y[i], m2, 0) / v[1];
        if (v1 > v2) {
            l = m1;
        } else {
            r = m2;
        }
    }
    dist[j][i] = calcdist(xs[j], ys[j], l, 0) / v[0] + calcdist(x[i], y[i], l, 0) / v[1];
}

void calcbetween(int i, int j) {
    double l = -1e6;
    double r = 1e6;
    distb[i][j] = calcdist(x[i], y[i], x[j], y[j])/v[1];
    for (int k = 0; k < 100; k++) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double v1 = calcdist(x[i], y[i], m1, 0) / v[1] + calcdist(m1, 0, x[j], 0) / v[0];
        double v2 = calcdist(x[i], y[i], m2, 0) / v[1] + calcdist(m2, 0, x[j], 0) / v[0];
        if (v1 > v2) {
            l = m1;
        } else {
            r = m2;
        }
    }
    double _x = l;
    l=-1e6;
    r=1e6;
    for (int k = 0; k < 100; k++) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double v1 = calcdist(x[j], y[j], m1, 0) / v[1] + calcdist(m1, 0, _x, 0) / v[0];
        double v2 = calcdist(x[j], y[j], m2, 0) / v[1] + calcdist(m2, 0, _x, 0) / v[0];
        if (v1 > v2) {
            l = m1;
        } else {
            r = m2;
        }
    }
    double cd = calcdist(x[i], y[i], _x, 0) / v[1] +
                calcdist(_x, 0, l, 0) / v[0] +
                calcdist(x[j], y[j], l, 0) / v[1];
    distb[i][j] = min(distb[i][j], cd);
    distb[j][i] = distb[i][j];
}
int n, s;
double dp[1 << 15][15][16];

bool vis[1 << 15][15][16];
int tot;
double solve(int msk, int lst, int c) {
    // dbg(msk, lst, c);
    if(c>s){
        return 1e18;
    }
    if (msk == tot && c == 0) {
        return 0;
    }
    double &ans = dp[msk][lst][c];
    if (vis[msk][lst][c]) return ans;
    vis[msk][lst][c] = 1;
    ans = 1e18;
    if (c) {
        ans = min(ans, dist[1][lst] + solve(msk, 0, 0));
    }
    if (c == 0) {
        int _from = msk != 0;
        for (int i = 0; i < n; i++) {
            if (msk & (1 << i)) continue;
            ans = min(ans, dist[_from][i] + solve(msk + (1 << i), i, 1));
        }
    } else {
        for (int i = 0; i < n; i++) {
            if (msk & (1 << i)) continue;
            ans = min(ans, distb[lst][i] + solve(msk + (1 << i), i, c + 1));
        }
    }
    return ans;
}

void test_case() {
    for (int i = 0; i < 2; i++) {
        cin >> xs[i] >> ys[i];
    }
    cin >> v[0] >> v[1];
    cin >> n >> s;
    tot = (1 << n) - 1;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        for (int j = 0; j < 2; j++) {
            calc(j, i);
        }
    }
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            calcbetween(i, j);
        }
    }
    cout << fixed << setprecision(10) << solve(0, 0, 0) << endl;
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
