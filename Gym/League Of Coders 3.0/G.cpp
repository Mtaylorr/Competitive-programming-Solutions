// Mtaylor
// (W*H/N) * N should pass !!  fastest
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

int w, h;
int x[N], y[N], p[N];
int val[N];
int sum[N];
int n;
int tot[N];

void test_case() {
    cin >> h >> w >> n;
    int mxp = 0;
    int mxid = 0;
    for (int i = 0; i < n; i++) {
        cin >> p[i];
        if (p[i] > mxp) {
            mxp = p[i];
            mxid = i;
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
    }
    int ans = 0;
    for (int a = 1; a <= h; a++) {
        for (int b = 1; b <= w; b++) {
            bool cond = true;
            if ((abs(a - x[mxid]) + abs(b - y[mxid])) % p[mxid] == 0) {
                bool cond = true;
                for (int i = 0; i < n; i++) {
                    if ((abs(x[i] - a) + abs(y[i] - b)) % p[i] != 0) {
                        cond = false;
                        break;
                    }
                }
                if (cond) {
                    ans++;
                }
            }
        }
    }
    cout << ans << endl;
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
