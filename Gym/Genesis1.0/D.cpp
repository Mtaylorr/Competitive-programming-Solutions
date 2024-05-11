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
ll a[N];

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        ll x = a[i];
        a[i] = 0;
        while (x % 2 == 0) {
            a[i]++;
            x /= 2;
        }
    }
    int nbodd = 0;
    int nbeven = 0;
    for (int i = 0; i < n; i++) {
        nbodd += a[i] == 0;
    }
    sort(a, a + n);
    nbeven = n - nbodd;
    if (nbodd > nbeven) {
        cout << n / 2 - nbeven << endl;
        return;
    } else {
        int needed = n / 2 - nbodd;
        ll ans = 0;
        for (int i = 0; i < n; i++) {
            if (a[i] == 0) continue;
            if (needed == 0) continue;
            needed--;
            ans += a[i];
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
