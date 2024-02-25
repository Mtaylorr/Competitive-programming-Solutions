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

int lf[N], rg[N];
int n, a[N], l, r, k;

void test_case() {
    cin >> n >> k;
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    while (k--) {
        cin >> l >> r;
        lf[l - 1] = 0;
        if (l == r) {
            cout << l << endl;
            continue;
        }
        for (int i = l; i <= r; i++) {
            lf[i] = __gcd(lf[i - 1], a[i]);
        }
        rg[r + 1] = 0;
        for (int i = r; i >= l; i--) {
            rg[i] = __gcd(rg[i + 1], a[i]);
        }
        int mx = 0;
        int sghir = 0;
        int idx = -1;
        for (int i = l; i <= r; i++) {
            int d = __gcd(lf[i - 1], rg[i + 1]);
            if (d > mx) {
                mx = d;
                sghir = a[i];
                idx = i;
            }
            if (d == mx && a[i] < sghir) {
                sghir = a[i];
                idx = i;
            }
        }
        cout << idx << endl;
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
