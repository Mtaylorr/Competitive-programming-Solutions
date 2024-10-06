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
const int N = 5e5 + 5;

int n;
ll c, p, q;
string s;
int rnk[N];
ll sm[N];

ll f(int i) { return sm[i] * q - i * p; }

void test_case() {
    cin >> n >> c >> p >> q;
    cin >> s;
    ll mx = 1e18;
    for (int i = 1; i <= n; i++) {
        int a = s[i - 1] == 'Y';
        sm[i] = sm[i - 1] + a;
        rnk[i] = rnk[i - 1];
        ll g = f(i);
        if (i - c >= 0 && rnk[i - c] == rnk[i]) {
            mx = min(mx, f(i - c));
        }
        // dbg(i, rnk[i], mx, g, sm[i]);
        if (i - c >= 0 && rnk[i - c] == rnk[i] && g >= mx) {
            rnk[i]++;
            mx = 1e18;
        }
    }
    cout << rnk[n] << endl;
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
