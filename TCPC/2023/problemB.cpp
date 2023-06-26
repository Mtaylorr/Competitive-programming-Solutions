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

int val[N];
int dp[N];
int a[N];
int n, q, y;
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        val[a[i]] = a[i];
    }
    for (int i = 1; i <= 1e6; i++) {
        for (int j = 0; j < 20; j++) {
            if (i & (1 << j)) {
                val[i] = val[i] | val[i ^ (1 << j)];
            }
        }
        if (val[i] == i) {
            dp[i] = 1;
        }
    }
    for (int i = 0; i < 20; ++i)
        for (int mask = 0; mask <= 1e6; ++mask) {
            if (mask & (1 << i)) dp[mask] += dp[mask ^ (1 << i)];
        }
    cin >> q;
    while (q--) {
        cin >> y;
        cout << dp[y] << " ";
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
