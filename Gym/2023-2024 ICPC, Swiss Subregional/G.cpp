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

ll d;
vector<pair<ll, ll> > v;

void calc(ll x) {
    ll y = d / x;
    if (y >= x && (y - 1 - x) >= 2 && (y - 1 - x) % 2 == 0) {
        ll n = (y - 1 - x) / 2;
        v.pb({n, n + x});
    }
}

void test_case() {
    cin >> d;
    d *= 2;
    for (ll i = 1; i * i <= d; i++) {
        if (d % i == 0) {
            calc(i);
            if (i * i != d) {
                calc(d / i);
            }
        }
    }
    cout << v.size() << endl;
    for (auto &u : v) {
        cout << u.fi << " " << u.se << endl;
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
