// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
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

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }

int n;
int dx[] = {0, 0, 1, -1};
int dy[] = {1, -1, 0, 0};
void test_case() {
    cin >> n;
    ll mx = 0;
    int posx = 1;
    int posy = 1;

    for (int i = 1; i <= 2*n+100; i++) {
        ll x = myRand(n) + 1;
        ll y = myRand(n) + 1;
        cout << "? " << x << " " << y << endl;
        int v;
        cin >> v;
        if (v > mx) {
            mx = v;
            posx = x;
            posy = y;
        }
    }
    while (1) {
        int mxv = 0;
        int nx = 0;
        int ny = 0;
        for (int k = 0; k < 4; k++) {
            if (posx + dx[k] <= 0 || posx + dx[k] > n || posy + dy[k] <= 0 ||
                posy + dy[k] > n)
                continue;
            cout << "? " << posx + dx[k] << " " << posy + dy[k] << endl;
            int v;
            cin >> v;
            if (mxv < v) {
                mxv = v;
                nx = posx + dx[k];
                ny = posy + dy[k];
            }
        }
        if (mxv < mx) {
            cout << "! " << mx << endl;
            break;
        } else {
            mx = mxv;
            posx = nx;
            posy = ny;
        }
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
