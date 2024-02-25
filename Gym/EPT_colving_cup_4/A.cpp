E// Mtaylor
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
const int N = 5e5 + 5;

int n, done[N];
int a[N], pos[N];
void test_case() {
    cin >> n;

    for (int i = 0; i < n; i++) {
        done[i] = 0;
        cin >> a[i];
        pos[a[i]] = i;
    }
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    done[n] = 0;
    int l = pos[0];
    int r = pos[0];
    int ans = 2;
    int mx = 1;
    done[0] = 1;
    for (int i = 1; i < n; i++) {
        int p = pos[i];
        while (l > p) {
            l--;
            done[a[l]] = 1;
        }
        while (r < p) {
            r++;
            done[a[r]] = 1;
        }
        while (done[mx]) mx++;
        if (ans == mx) ans++;
    }
    cout << ans << endl;
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
