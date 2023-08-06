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

ll x[N], y[N];
int n;
map<pair<pair<ll, ll>, pair<ll, ll> >, int> freq;

void add(int a, int b, int c) {
    ll d = 2 *
           (x[a] * (y[b] - y[c]) + x[b] * (y[c] - y[a]) + x[c] * (y[a] - y[b]));
    if (d == 0) return;
    ll cx = ((x[a] * x[a] + y[a] * y[a]) * (y[b] - y[c]) +
             (x[b] * x[b] + y[b] * y[b]) * (y[c] - y[a]) +
             (x[c] * x[c] + y[c] * y[c]) * (y[a] - y[b]));
    ll cy = ((x[a] * x[a] + y[a] * y[a]) * (x[c] - x[b]) +
             (x[b] * x[b] + y[b] * y[b]) * (x[a] - x[c]) +
             (x[c] * x[c] + y[c] * y[c]) * (x[b] - x[a]));
    ll dx = __gcd(abs(cx), abs(d));
    cx /= dx;
    ll ddx = d / dx;
    ll dy = __gcd(abs(cy), abs(d));

    ll ddy = d / dy;

    cy /= dy;
    freq[{{cx, ddx}, {cy, ddy}}]++;
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    int ans = 2;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            freq.clear();
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                add(i, j, k);
            }
            for (auto &u : freq) {
                ans = max(ans, 2 + u.se);
            }
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
    while (T--) {
        test_case();
    }
    return 0;
}
