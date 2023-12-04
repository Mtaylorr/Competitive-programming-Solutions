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

int n, w;
vector<pair<int, int> > ans;
void test_case() {
    cin >> n >> w;
    int p = n / 2;
    int q = 1e3;
    for (int i = 0; i < p; i++) {
        ans.pb({w, q});
        q--;
    }
    p = n - p;
    int l = 0;
    int r = 1e4;
    while (p) {
        if (abs(l - w) == abs(r - w)) {
            ans.pb({l, q});
            ans.pb({r, q});
            l++;
            r--;
            p-=2;
        } else if (abs(l - w) > abs(r - w)) {
            ans.pb({l, q});
            l++;
            p--;
        } else if (abs(r - w) > abs(l - w)) {
            ans.pb({r, q});
            r--;
            p--;
        }
        q--;
    }
    while (ans.size() > n) {
        ans.pop_back();
    }
    reverse(all(ans));
    for (auto &u : ans) {
        cout << u.fi << " " << u.se << endl;
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
