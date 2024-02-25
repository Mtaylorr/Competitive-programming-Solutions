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

int n, a[N];
map<int, int> f;

void test_case() {
    cin >> n;
    f.clear();
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        f[a[i]]++;
    }
    int hastwo = 0;
    int ans = 0;
    int bef = 0;
    ll tot = 1;
    for (auto &u : f) {
        while (bef < u.fi && tot < 1e9) {
            bef++;
            tot *= 2;
        }
        if (u.se > tot) {
            cout << "NO\n";
            return;
        }

        tot -= u.se;
    }
    cout << "YES\n";
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
