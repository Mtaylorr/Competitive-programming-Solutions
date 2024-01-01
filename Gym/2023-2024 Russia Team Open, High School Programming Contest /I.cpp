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

set<pair<int, int> > st;
map<int, int> fc[2][2];
int f[2][2];
int n;
int x, y;

void upd(int x, int y, int v) {
    int mx = x % 2;
    int my = y % 2;
    f[0][x % 2] -= max(fc[0][0][x], fc[0][1][x]);
    fc[0][y % 2][x] += v;
    f[0][x % 2] += max(fc[0][0][x], fc[0][1][x]);
    f[1][y % 2] -= max(fc[1][0][y], fc[1][1][y]);
    fc[1][x % 2][y] += v;
    f[1][y % 2] += max(fc[1][0][y], fc[1][1][y]);
}

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> x >> y;
        if (st.count({x, y})) {
            upd(x, y, -1);
            st.erase({x, y});
        } else {
            st.insert({x, y});
            upd(x, y, +1);
        }
        int ans = 0;
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < 2; j++) {
                ans = max(ans, f[i][j]);
            }
        }
        cout << ans << endl;
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
