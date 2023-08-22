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
/*
2
1 6 -64 96
1 -2 9 -36

2
1 1 2 -12
6 425 2539 -5440

4
1 0 0 0
1 -1 1 -1
1 1 1 1
2 2 -23 443

1
21 222 -32 124

*/

ll a, b, c, d;

bool solve(ll x) { return a * x * x * x + b * x * x + c * x + d == 0; }

void test_case() {
    cin >> a >> b >> c >> d;
    if (d == 0) {
        cout << "Yes\n";
        cout << 0 << endl;
        return;
    }
    ll p = abs(d);
    for (int i = 1; i * i <= p; i++) {
        ll x = i;
        if (solve(x)) {
            cout << "Yes\n";
            cout << x << endl;
            return;
        }
        if (solve(-x)) {
            cout << "Yes\n";
            cout << -x << endl;
            return;
        }
        x = p / i;
        if (solve(x)) {
            cout << "Yes\n";
            cout << x << endl;
            return;
        }
        if (solve(-x)) {
            cout << "Yes\n";
            cout << -x << endl;
            return;
        }
    }
    cout << "No\n";
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
