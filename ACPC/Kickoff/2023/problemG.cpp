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
const int MOD = 1e9 + 7;

int n, m, k;
int a[N];

void test_case() {
    cin >> n >> m >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        a[i] = abs(a[i]);
    }
    sort(a, a + n);
    reverse(a, a + n);
    int rs = 1;
    for (int i = 0; i < m; i++) {
        rs = (rs * 1ll * a[i]) % MOD;
    }
    cout << rs << endl;
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
