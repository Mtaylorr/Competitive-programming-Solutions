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
ll a[N];

void test_case() {
    cin >> n;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    ll ans = 0;
    ll mncontg = 0;
    ll mnskipped = 1e18;
    ll mxskipped = -1e18;
    ll curskipped = -1e18;
    ll mna = -1e17;
    ll mn2 = 1e17;  //  l-a[i];
    ll mn3 = 1e17;
    ll cur = 0;
    for (int i = 1; i <= n; i++) {
        ll tmp = cur - mncontg;
        ll tmp2 = mncontg;
        mna = max(mna, a[i]);
        cur += a[i];
        mn3 = min(mn3, mn2 + a[i]);
        mncontg = min(mncontg, cur);
        ans = max(ans, cur - mncontg);
        ans = max(ans, a[i] + mxskipped);
        ans = max(ans, cur - mn3);
        mnskipped = min(mnskipped, a[i] + tmp2);
        mxskipped = max(mxskipped, cur - mnskipped);
        mn2 = min(mn2, cur - mna);
        cout << ans << " ";
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
