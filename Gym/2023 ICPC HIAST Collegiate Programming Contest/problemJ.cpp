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

ll a[N];
int n;

void test_case() {
    cin >> n;
    ll sm = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sm += (a[i]);
    }
    sort(a, a + n);
    a[n] = 1e18;
    int posmedian = ((n) / 2);
    ll ans = 1e18;
    ll bef = -1e18;
    for (int i = 0; i <= n; i++) {
        if (i + 1 <= posmedian) {
            ll median = a[posmedian - 1];
            ll value = (n + 1) * median - sm;
            if (value <= a[i] && value >= bef) ans = min(ans, value);
        } else if (i == posmedian) {
            if (abs(sm) % n == 0) {
                ll value = sm / n;
                if (value <= a[i + 1] && value >= bef) ans = min(ans, value);
            }
        } else {
            ll median = a[posmedian];
            ll value = (n + 1) * median - sm;
            if (value <= a[i] && value >= bef) ans = min(ans, value);
        }
        bef = a[i];
    }

    cout << ans << endl;
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
