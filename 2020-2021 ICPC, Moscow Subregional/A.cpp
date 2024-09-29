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

int x[2], y[2];

int getCorner(int x, int y) {
    int ans = 0;
    if (x < 0) {
        ans++;
    }
    if (y < 0) ans += 2;
    return ans;
}

void test_case() {
    cin >> x[0] >> y[0] >> x[1] >> y[1];
    int a = getCorner(x[0], y[0]);
    int b = getCorner(x[1], y[1]);
    if (a == b) {
        cout << 0 << endl;
    } else {
        cout << 1 << endl;
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
    // cin >>T;
    while (T--) {
        test_case();
    }
    return 0;
}
