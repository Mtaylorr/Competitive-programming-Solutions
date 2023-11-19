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

int n, a[N], m, k;

void test_case() {
    ll sum = 0;
    ll tot = 0;
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    sort(a, a + n);
    reverse(a, a + n);
    int nb = min(n, k + m);
    ll ans=0;
    for (int i = 0; i < nb; i++) {
        ans += a[i];
    }
    double rs = (ans * 100.0) / (tot * 1.0);
    cout << fixed << setprecision(10) << rs << endl;
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
