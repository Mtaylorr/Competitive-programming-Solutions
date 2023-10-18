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

int n, a[1005][1005];
vector<pair<int,int> > steps;

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> a[i][j];
        }
    }
    ll ans = 0;
    for (int i = n - 1; i > 0; i--) {
        int mx = -1;
        int pmx = -1;
        for (int j = i - 1; j >= 0; j--) {
            if (mx < a[i][j]) {
                mx = a[i][j];
                pmx = j;
            }
        }
        ans += mx;
        steps.pb({i+1, pmx+1});
        for (int j = i - 1; j >= 0; j--) {
            a[j][pmx] = max(a[j][pmx], a[i][j]);
            a[pmx][j] = max(a[pmx][j], a[i][j]);
        }
    }
    cout << ans << endl;
    for(auto &u:steps){
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
