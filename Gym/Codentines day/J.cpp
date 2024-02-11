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

int n;
double c;
double a[N];

void test_case() {
    cin >> n >> c;
    double sm = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sm += a[i];
    }
    double ans = 0;
    sort(a, a + n);
    for (int i = n - 1; i >= 0; i--) {
        int take = min(c, 100.0);
        c -= take;
        ans += take * a[i];
    }
    ans /= sm;
    cout << fixed << setprecision(15) << ans << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
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
