//https://csacademy.com/ieeextreme18/task/another-sliding-window-problem/

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

int n, q;
ll a[N];
ll sum[N];
int val[N];

void test_case() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }

    for (int i = 1; i <= n; i++) {
        sum[i] = (sum[i - 1] + a[i]);
    }
    int x;
    for (int i = 0; i < q; i++) {
        cin >> x;
        int r = n;
        for (int j = 1; j <= n; j++) {
            val[j] = min(j, n - j);
        }
        for (int j = 1; j <= n; j++) {
            while (r > j && a[j] + a[r] > x) {
                r--;
            }
            // dbg(j, r);
            if (r > j) {
                int rg;
                if (r % 2 != j % 2) {
                    rg = r + 2;

                } else {
                    rg = r + 1;
                }
                if (rg <= n) {
                    int idx = j + (rg - j + 1) / 2 - 1;
                    val[idx] = min(val[idx], (rg - j + 1) / 2 - 1);
                }
            }
        }
        ll ans = 0;
        for (int j = 1; j <= n; j++) {
            if (a[j] > x) break;
            if (val[j] && j + 1 <= n && a[j] + a[j + 1] <= x) {
                ans += (sum[j + val[j]] - sum[j]);
                ans -= (sum[j] - sum[j - val[j]]);
                // dbg(j, j - val[j] + 1, j + val[j], ans);
                if (j + val[j] + 1 <= n && a[j + val[j] + 1] <= x) {
                    assert(j + val[j] + 1 - (j + 1) == j - (j - val[j]));
                    ans += sum[j + val[j] + 1] - sum[j + 1];
                    ans -= (sum[j] - sum[j - val[j]]);
                } else {
                    assert(j + val[j] - (j + 1) == j - (j - val[j] + 1));
                    // dbg(j+val[j] );
                    ans += sum[j + val[j]] - sum[j + 1];
                    ans -= (sum[j] - sum[j - val[j] + 1]);
                }
                // dbg(j, j - val[j] + 1, j + val[j], ans);
            }
        }
        cout << ans << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
