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
const int N = 1e6 + 5;

int n;
ll A, B;
ll m[N];
void test_case() {
    cin >> n;
    int md = 0;
    vector<int> tmp;
    for (int i = 0; i < n; i++) {
        cin >> m[i];
        md += (m[i] % 2);
        if (m[i] % 2) {
            tmp.pb(i);
        }
    }
    cin >> A >> B;
    if (md % 2) {
        cout << "-1";
        return;
    }
    ll ans = 1e18;
    for (int i = 0; i < 2; i++) {
        ll rs = 0;
        for (int j = 0; j < tmp.size(); j += 2) {
            int l = tmp[(j + i) % tmp.size()];
            int r = tmp[(j + i + 1) % tmp.size()];
            if (r >= l) {
                rs += min(A, B) * (r - l);
            } else {
                rs += min(A, B) * (n - l + r);
            }
        }
        ans = min(ans, rs);
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
