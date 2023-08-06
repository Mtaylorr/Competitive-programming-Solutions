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
int n, q;
ll a[N];
ll dpl[N], dpr[N];
ll s;

void test_case() {
    cin >> n >> q;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    dpl[0] = 0;
    for (int i = 1; i <= n; i++) {
        dpl[i] = dpl[i - 1] + a[i];
    }
    reverse(a + 1, a + (n + 1));
    dpr[0] = 0;
    for (int i = 1; i <= n; i++) {
        dpr[i] = dpr[i - 1] + a[i];
    }
    while (q--) {
        cin >> s;
        int p = upper_bound(dpl, dpl + (n + 1), s) - dpl;
        if (p == n + 1) {
            cout << 0 << endl;
            continue;
        }
        int r = upper_bound(dpr, dpr + (n + 1), s) - dpr;
        //dbg(p,r,s);
        r = n + 1 - r;
        if (p <= r) {
            cout << r - p + 1 << endl;
        } else {
            cout << 0 << endl;
        }
    }
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
