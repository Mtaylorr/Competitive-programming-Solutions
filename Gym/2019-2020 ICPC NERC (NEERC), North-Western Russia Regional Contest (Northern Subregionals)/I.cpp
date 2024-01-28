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

int n;
ll x[N], y[N], h[N];

void test_case() {
    cin >> n;
    ll mnx = 1e18;
    ll mxx = -1e18;
    ll mny = 1e18;
    ll mxy = -1e18;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i] >> h[i];
        mnx = min(mnx, x[i] - h[i]);
        mxx = max(mxx, x[i] + h[i]);
        mny = min(mny, y[i] - h[i]);
        mxy = max(mxy, y[i] + h[i]);
    }
    if (abs(mnx % 2) != abs(mxx) % 2) {
        mnx--;
    }
    if (abs(mny) % 2 != abs(mxy) % 2) {
        mny--;
    }
    ll diffx = mxx - mnx;
    ll diffy = mxy - mny;
    if (diffx > diffy) {
        mny -= (diffx - diffy);
    } else {
        mnx -= (diffy - diffx);
    }
    if (abs(mnx) % 2 != abs(mxx) % 2) {
        mnx--;
        mny--;
    }
    cout << (mnx + mxx) / 2 << " " << (mny + mxy) / 2 << " " << (mxx - mnx) / 2 << endl;
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
