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

double x[10], y[10];
double d;

void test_case() {
    cin >> x[0] >> y[0] >> d;
    double angle = 3 * pi / 5;
    double nangle = angle / 2;
    x[1] = x[0] - sin(nangle) * d;
    y[1] = y[0] - cos(nangle) * d;
    angle = 2 * pi - angle;
    for (int j = 2; j < 5; j++) {
        double dx = x[j - 2] - x[j - 1];
        double dy = y[j - 2] - y[j - 1];
        x[j] = x[j - 1] + dx * cos(angle) - dy * sin(angle);
        y[j] = y[j - 1] + dx * sin(angle) + dy * cos(angle);
    }

    cout << fixed << setprecision(10);
    for (int i = 1; i < 5; i++) {
        cout << x[i] << " " << y[i] << "\n";
    }
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
