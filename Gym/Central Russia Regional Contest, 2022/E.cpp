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
const double PI = 4 * atan(1);
long double circleIntersectionArea(long double r1, long double r2,
                                   long double d) {
    // d is the distance between the 2 centers
    if (r1 < r2) swap(r1, r2);
    if (d >= r1 + r2) return 0;
    if (d <= r1 - r2) return PI * r2 * r2;
    long double alpha = acos((r2 * r2 + d * d - r1 * r1) / (2 * r2 * d));
    long double s = alpha * r2 * r2;
    long double t = r2 * r2 * sin(alpha) * cos(alpha);
    long double x = s - t;
    alpha = acos((r1 * r1 + d * d - r2 * r2) / (2 * r1 * d));
    s = alpha * r1 * r1;
    t = r1 * r1 * sin(alpha) * cos(alpha);
    long double y = s - t;
    return x + y;
}

long double r[N], x[N];
int n;
void test_case() {
    cin >> n;
    vector<int> ord;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> r[i];
        ord.pb(i);
    }
    sort(all(ord), [](int &a, int &b) { return x[a] < x[b]; });
    long double ans = 0;
    for (int i = 0; i < n; i++) {
        ans += PI * r[ord[i]] * r[ord[i]];

        if (i + 1 < n) {
            ans -= circleIntersectionArea(r[ord[i]], r[ord[i + 1]], x[ord[i + 1]] - x[ord[i]]);
        }
    }
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
