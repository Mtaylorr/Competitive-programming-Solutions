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

double x, t;

void test_case() {
    cin >> x >> t;
    double ans = 0;
    double l = 0;
    double r = t / 6;
    double t6 = t / 6;
    double t3 = t / 3;
    for (int i = 0; i < 200; i++) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double v1 = (x * m1 / t6) * (t - m1);
        double v2 = (x * m2 / t6) * (t - m2);
        if (v1 > v2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    ans = max(ans, (x * l / t6) * (t - l));
    l = t / 6;
    r = t / 3;
    double tot = t / 3 - t / 6;
    for (int i = 0; i < 200; i++) {
        double m1 = l + (r - l) / 3;
        double m2 = r - (r - l) / 3;
        double v1 = (x + (100 - x) * (m1 - t6) / tot) * (t - m1);
        double v2 = (x + (100 - x) * (m2 - t6) / tot) * (t - m2);
        if (v1 > v2) {
            r = m2;
        } else {
            l = m1;
        }
    }
    ans = max(ans, (x + (100 - x) * (l - t6) / tot) * (t - l));
    ans = max(ans, 100 * (t - t / 3));
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
