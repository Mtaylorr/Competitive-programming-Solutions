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
int k;
int a[N];
ll sum[N];

void test_case() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        cin >> a[i];
        sum[i] = a[i];
        if (i) sum[i] += sum[i - 1];
    }
    sort(a, a + n);
    for (int i = 0; i < n; i++) {
        sum[i] = a[i];
        if (i) sum[i] += sum[i - 1];
    }
    sum[n] = sum[n - 1];
    cin >> k;
    while (k--) {
        ll l;
        cin >> l;
        int p = lower_bound(a, a + n, l) - a;
        ll ans = sum[n];
        if (p) ans -= sum[p - 1];
        cout << ans - (n - p) * l << endl;
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
