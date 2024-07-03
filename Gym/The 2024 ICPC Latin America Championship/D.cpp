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

ll n;

vector<pair<ll, ll> > v;

void test_case() {
    cin >> n;
    for (int i = 2; i * 1ll * i <= n; i++) {
        if (n % i == 0) {
            int nb = 0;
            while (n % i == 0) {
                nb++;
                n /= i;
            }
            v.pb({i, nb});
        }
    }
    if (n > 1) {
        v.pb({n, 1});
    }
    ll divs = 1;
    ll mx = 0;
    for (auto &u : v) {
        divs = (divs * 1ll * (u.se + 1));
        mx = max(mx, u.se + 1);
    }
    if (divs == 4 && v.size() == 2) {
        cout << "Y";
        return;
    }
    ll others = divs / (mx + 1) + 1;

    if (divs % 2 == 1 || others > 1) {
        cout << "N";
    } else {
        cout << "Y";
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
    while (T--) {
        test_case();
    }
    return 0;
}
