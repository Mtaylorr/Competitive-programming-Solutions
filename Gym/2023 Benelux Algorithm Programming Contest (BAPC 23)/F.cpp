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

ll n, c;
ll a;
void test_case() {
    cin >> n >> c;
    ll s = 0;
    int mn = 1e9;
    int mnpos = -1;
    for (int i = 0; i < n; i++) {
        cin >> a;
        s += a;
        s -= c;
        if (s < 0) {
            cout << i << endl;
            return;
        }
        if (s + 1 <= (n - i - 1) * c) {
            ll x = (s + 1 + c - 1) / c;
            if (mn > x) {
                mn = x;
                mnpos = i;
            }
        }
    }
    if (mnpos != -1) {
        cout << mnpos;
    } else {
        cout << "impossible";
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
