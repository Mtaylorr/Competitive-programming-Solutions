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
const int N = 1 << 24;

int n;
ll a[N + 4];
ll sum[N + 4];
void test_case() {
    cin >> n;
    int m = (1 << n);
    for (int i = 0; i < m; i++) {
        cin >> a[i];
    }
    ll cur = m;
    ll d = 1;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < cur; j += 2) {
            sum[j * d] += a[j + 1];
            sum[(j + 1) * d] -= a[j + 1];
            sum[d * (j + 1)] += a[j];
            sum[d * (j + 2)] -= a[j];
            a[j / 2] = max(a[j], a[j + 1]);
        }
        cur /= 2;
        d *= 2;
    }
    for (int i = 0; i < m; i++) {
        if (i) sum[i] += sum[i - 1];
        cout << sum[i] << " ";
    }
    cout << endl;
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
