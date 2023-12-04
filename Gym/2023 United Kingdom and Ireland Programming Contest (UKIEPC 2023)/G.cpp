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
const int N = 1e6 + 5;

int n;
long double x[N];
long double y[N];
long double d[N];
long double dx[N], dy[N];
int pos[N];
long double s;
long double cur[N];

void test_case() {
    cin >> s >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    for (int i = 1; i < n; i++) {
        dx[i] = x[i] - x[i - 1];
        dy[i] = y[i] - y[i - 1];
        d[i] = (dx[i]) * (dx[i]) + (dy[i]) * (dy[i]);
        d[i] = sqrt(d[i]);
    }
    long double rem = s;
    pos[0] = 0;
    pos[1] = 0;
    while (rem > 1e-10) {
        if (rem - d[pos[0] + 1] > 1e-10) {
            rem -= d[pos[0] + 1];
            pos[0]++;
        } else {
            cur[0] = rem;
            break;
        }
    }
    long double ans = s;
    while (pos[0] <= n - 2) {
        long double rem = min(d[pos[0] + 1] - cur[0], d[pos[1] + 1] - cur[1]);
        long double l = 0;
        long double r = rem;
        for (int oo = 0; oo < 100; oo++) {
            long double m1 = l + (r - l) / 3;
            long double m2 = r - (r - l) / 3;
            long double _x[] = {0, 0};
            long double _y[] = {0, 0};
            for (int j = 0; j < 2; j++) {
                _x[j] = x[pos[j]] + dx[pos[j] + 1] / d[pos[j] + 1] * (cur[j] + m1);
                _y[j] = y[pos[j]] + dy[pos[j] + 1] / d[pos[j] + 1] * (cur[j] + m1);
            }
            long double v1 = (_x[0] - _x[1]) * (_x[0] - _x[1]) + (_y[0] - _y[1]) * (_y[0] - _y[1]);
            for (int j = 0; j < 2; j++) {
                _x[j] = x[pos[j]] + dx[pos[j] + 1] / d[pos[j] + 1] * (cur[j] + m2);
                _y[j] = y[pos[j]] + dy[pos[j] + 1] / d[pos[j] + 1] * (cur[j] + m2);
            }
            long double v2 = (_x[0] - _x[1]) * (_x[0] - _x[1]) + (_y[0] - _y[1]) * (_y[0] - _y[1]);
            if (v1 > v2) {
                l = m1;
            } else {
                r = m2;
            }
        }
        long double _x[] = {0, 0};
        long double _y[] = {0, 0};
        for (int j = 0; j < 2; j++) {
            _x[j] = x[pos[j]] + dx[pos[j] + 1] / d[pos[j] + 1] * (cur[j] + l);
            _y[j] = y[pos[j]] + dy[pos[j] + 1] / d[pos[j] + 1] * (cur[j] + l);
        }

        ans = min(ans, sqrt((_x[0] - _x[1]) * (_x[0] - _x[1]) + (_y[0] - _y[1]) * (_y[0] - _y[1])));
        // dbg(_x[0], _y[0], _x[1], _y[1], pos[0], pos[1], cur[0], cur[1],l,ans);
        if (abs(d[pos[0] + 1] - cur[0] - rem) < 1e-7) {
            cur[0] = 0;
            pos[0]++;
        } else {
            cur[0] += rem;
        }
        if (abs(d[pos[1] + 1] - cur[1] - rem) < 1e-7) {
            cur[1] = 0;
            pos[1]++;
        } else {
            cur[1] += rem;
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
