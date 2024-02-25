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

ll n, k;

void test_case() {
    cin >> n >> k;
    ll delta = n * n - (4 * (k - 1));
    if (delta < 0) {
        cout << "Yes\n";
        return;
    }
    double x1 = (n * 1.0 - sqrt(delta)) / 2.0;
    double x2 = (n * 1.0 + sqrt(delta)) / 2.0;
    if (abs(x1 - x2) <= 1e-7) {
        cout << "Yes\n";
        return;
    }

    ll x11 = ceil(x1);
    if (abs(x1 - x11) <= 1e-7) {
        x11++;
    }
    ll x22 = floor(x2);
    if (abs(x2 - x22) <= 1e-7) {
        x22--;
    }
    if ((x11 > x22) || ((x22 < 1) || (x11 > n))) {
        cout << "Yes\n";
    } else {
        cout << "No\n";
    }
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
