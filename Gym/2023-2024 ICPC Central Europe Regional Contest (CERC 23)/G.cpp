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
const double pi = 4 * atan(1);

int r;
int x[3], y[3];

int getSquaredDist(int i, int j) { return (x[i] - x[j]) * (x[i] - x[j]) + (y[i] - y[j]) * (y[i] - y[j]); }

double getDist(int i, int j) { return sqrt(getSquaredDist(i, j)); }
bool isInside(int i) { return getSquaredDist(i, 2) <= r * r; }

double dist(double x1, double y1, double x2, double y2) { return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2)); }

double getVal(double angle) {
    double xtarget = x[2] + r * cos(angle);
    double ytarget = y[2] + r * sin(angle);
    return dist(xtarget, ytarget, x[0], y[0]) + dist(xtarget, ytarget, x[1], y[1]);
}

void test_case() {
    cin >> x[0] >> y[0] >> x[1] >> y[1] >> x[2] >> y[2];
    cin >> r;
    if (isInside(0) || isInside(1)) {
        cout << fixed << setprecision(20) << getDist(0, 1) << endl;
        return;
    }
    double angle = 0;
    double ans = 1e18;
    for (int i = 0; i < 4; i++) {
        double lb = angle;
        double ub = angle + pi / 2;
        for (int i = 0; i < 100; i++) {
            double m1 = lb + (ub - lb) / 3;
            double m2 = ub - (ub - lb) / 3;
            double v1 = getVal(m1);
            double v2 = getVal(m2);
            if (v1 < v2) {
                ub = m2;
            } else {
                lb = m1;
            }
        }
        ans = min(ans, getVal(lb));
        angle += pi / 2;
    }
    cout << fixed << setprecision(20) << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
