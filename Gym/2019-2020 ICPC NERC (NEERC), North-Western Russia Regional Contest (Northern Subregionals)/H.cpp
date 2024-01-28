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
int a[N];
int q;
int t;
int dp[N];
int B = 1000;

void test_case() {
    cin >> n;
    int mx = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        mx = max(mx, a[i]);
    }
    for (int i = mx; i <= B; i++) {
        int r = 0;
        dp[i] = 1;
        for (int j = 0; j < n; j++) {
            if (r + a[j] > i) {
                dp[i]++;
                r = 0;
            }
            r += a[j];
        }
    }
    for (int i = 1; i < n; i++) {
        a[i] += a[i - 1];
    }
    cin >> q;
    for (int i = 0; i < q; i++) {
        cin >> t;
        if (t < mx) {
            cout << "Impossible\n";
            continue;
        }
        if (t <= B) {
            cout << dp[t] << endl;
        } else {
            int ans = 0;
            int cur = 0;
            int cursum = 0;
            while (cur < n) {
                int nxt = cursum + t;
                int p = upper_bound(a, a + n, nxt) - a;
                //dbg(t, cursum, cur, a[p - 1]);
                ans++;
                cur = p;
                cursum = a[cur - 1];
            }
            cout << ans << endl;
        }
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
