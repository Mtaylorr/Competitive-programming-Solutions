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
ll sum[N];
int a[N];
int l[2], r[2];

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    cin >> l[0] >> r[0] >> l[1] >> r[1];
    for (int i = 1; i <= n; i++) {
        sum[i] = a[i] + sum[i - 1];
    }
    if (r[0] < l[1] || r[1] < l[0]) {
        int x = min(r[0], r[1]);
        int y = max(l[0], l[1]);
        int ty = l[0] > l[1];
        ll s0 = 0;
        ll s1 = 0;
        while (x <= y) {
            if (ty % 2 == 0) {
                s0 += a[x++];
            } else {
                s1 += a[y--];
            }
            ty = 1 - ty;
        }
        if (l[0] < l[1]) {
            for (int i = 1; i < r[0]; i++) {
                s0 += a[i];
            }
            cout << s0 << endl;
            return;
        } else {
            for (int i = l[0] + 1; i <= n; i++) {
                s1 += a[i];
            }
            cout << s1 << endl;
            return;
        }
    }

    ll ans = 0;
    for (int i = 1; i <= n; i++) {
        if (i >= l[0] && i <= r[0] && i >= l[1] && i <= r[1]) {
            ll x = (i + 1 >= l[1] && i + 1 <= r[1]) ? sum[n] - sum[i] : 0ll;
            ll y = (i - 1 >= l[1] && i - 1 <= r[1]) ? sum[i - 1] : 0ll;
            x = max(x, y);
            ans = max(ans, sum[n] - x);
        }
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
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
