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
ll k;

void test_case() {
    cin >> n >> k;
    set<int> used;
    while (k>0) {
        int l = 2;
        int r = n;
        while (l < r) {
            ll md = (l + r) / 2;
            if ((md * (md - 1)) / 2 >= k) {
                r = md;
            } else {
                l = md + 1;
            }
        }
        k-=(l-1);
        used.insert(-(n - l + 1));
    }
    for (int i = 1; i <= n; i++) {
        if (used.count(-i)) continue;
        cout << i << " ";
    }
    for (auto u : used) {
        cout << -u << " ";
    }
    cout << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
