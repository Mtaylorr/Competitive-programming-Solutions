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
int n;
string s;
ll a[N];

bool ispal(int i, int j) {
    for (int k = 0; k < (j - i + 1); k++) {
        if (s[i + k] != s[j - k]) {
            return 0;
        }
    }
    return 1;
}
void test_case() {
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ll cs = 0;
        ll co = 0;
        for (int j = i; j < n; j++) {
            cs += a[j];
            co |= a[j];
            if (cs != co) break;
            if (ispal(i, j)) {
                ans = max(ans, j - i + 1);
            }
        }
    }
    cout << ans << endl;
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
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
