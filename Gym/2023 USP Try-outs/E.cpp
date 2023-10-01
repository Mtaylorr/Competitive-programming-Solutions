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

ll x[3][N];
ll w[N];
ll ans[3];
int n;

ll calc(int i, ll c) {
    ll ans = 0;
    for (int j = 0; j < n; j++) {
        ans += (x[i][j] - c) * (x[i][j] - c) * w[j];
    }
    return ans;
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < 3; j++) {
            cin >> x[j][i];
        }
        cin >> w[i];
    }
    for (int i = 0; i < 3; i++) {
        ll l = 0;
        ll r = 2e5;
        while (r - l >= 3) {
            ll m1 = l + (r - l) / 3;
            ll m2 = r - (r - l) / 3;
            ll v1 = calc(i, m1);
            ll v2 = calc(i, m2);
            if (v1 > v2) {
                l = m1;
            } else {
                r = m2;
            }
        }
        pair<ll, ll> mn = {1e18, 0};
        for (int j = l; j <= r; j++) {
            mn = min(mn, {calc(i, j), j});
        }
        ans[i] = mn.se;
    }
    for (int i = 0; i < 3; i++) {
        cout << ans[i] << " ";
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
