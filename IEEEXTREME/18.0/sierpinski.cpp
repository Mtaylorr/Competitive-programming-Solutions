//https://csacademy.com/ieeextreme18/task/sierpinski/
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

ll x, y;

void test_case() {
    cin >> x >> y;
    int step = 0;
    ll a = 2;
    while (x + y > a) {
        a = 2 * a + 1;
        step++;
    }
    if (step == 0) {
        cout << 1 << endl;
        return;
    }
    while (true && step) {
        ll b = a / 2;
        // dbg(x, y, a);
        if (x - y <= b && x >= b + 1 && y <= b + 1) {
            cout << 0 << endl;
            return;
        }
        if (x > b + 1) {
            x -= (b + 1);
        }
        if (y > b + 1) {
            y -= (b + 1);
        }

        a = b;
        step--;
    }
    cout << 1 << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
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
