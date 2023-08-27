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
/*
4 4
1 4 2 3

6 10
15 4 12 10 6 20

3 10
3 3 3

*/

int n, k;
int a[N];
void test_case() {
    cin >> n >> k;
    ll tot = 0;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        tot += a[i];
    }
    if (tot < k) {
        cout << n << endl;
        return;
    }
    int ans = 0;
    set<pair<int, int> > s;
    int sm = 0;
    int j = 0;
    for (int i = 0; i < n; i++) {
        sm += a[i];
        s.insert({-a[i], i});

        while (sm - a[j] >= k) {
            if (s.count({-a[j], j})) {
                s.erase({-a[j], j});
            }
            sm -= a[j];
            j++;
        }
        while (s.size() && sm > k && (*s.begin()).fi < k - sm) {
            s.erase(s.begin());
            ans++;
        }
    }
    cout << n-ans << endl;
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
