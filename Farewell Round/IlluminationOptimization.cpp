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
ll r, m;
ll x[N];

void test_case() {
    cin >> m >> r >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
    }
    x[n] = 1e10;
    int ans = 0;
    ll cur = 0;
    while (cur < m) {
        ll nx = cur + r;
        int p = upper_bound(x, x + (n + 1), nx) - x;
        if (p == 0) {
            cout << "IMPOSSIBLE\n";
            return;
        }
        p--;
        if (abs(x[p] - cur) <= r && x[p] + r > cur) {
            ans++;
            cur = x[p] + r;
        } else {
            cout << "IMPOSSIBLE\n";
            return;
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
