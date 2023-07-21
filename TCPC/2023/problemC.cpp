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

int freq[N];
int a[N], n;
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        freq[a[i]] = 1;
    }
    int ans = 0;
    for (int d = 1; d <= 2e6; d++) {
        for (int m = d; m <= 2e6; m += d) {
            if (m % 2) continue;
            int y = m / 2;
            int x = y + d;
            if (x <= 1e6 && y <= 1e6) ans += freq[x] * freq[y];
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
    while (T--) {
        test_case();
    }
    return 0;
}
