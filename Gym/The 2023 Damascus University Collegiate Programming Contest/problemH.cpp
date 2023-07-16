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

int n, a[N], c[N];
ll tot = 0;
ll sum[N];
vector<ll> vals[N];
int q;
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        vals[c[i]].pb(a[i]);
    }
    for (int i = 0; i <= 2e5; i++) {
        for (int j = 1; j < vals[i].size(); j++) {
            vals[i][j] += vals[i][j - 1];
        }
    }
    cin >> q;
    while (q--) {
        int t, c;
        ll x;
        cin >> t >> c >> x;
        if (t == 1) {
            tot += x;
            sum[c] += x;
        } else {
            int l = 0;
            int r = vals[c].size() - 1;
            while (l < r) {
                int md = (l + r + 1) / 2;
                if (vals[c][md] + (md + 1) * (tot - sum[c]) <= x) {
                    l = md;
                } else {
                    r = md - 1;
                }
            }
            if (vals[c][l] + (l + 1) * (tot - sum[c]) <= x) {
                cout << l + 1 << endl;
            } else {
                cout << 0 << endl;
            }
        }
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
