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

int a[N];
vector<int> v;
vector<pair<int, int> > ans;

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    reverse(a, a + n);
    int cur = n;
    for (int i = 0; i < n; i++) {
        if (a[i] == cur) {
            ans.pb({1, 3});
            cur--;
        } else {
            vector<int> tmp;
            ans.pb({1, 3});
            while (v.size() && v.back() < a[i]) {
                tmp.pb(v.back());
                v.pop_back();
                ans.pb({2, 1});
            }
            v.pb(a[i]);
            ans.pb({3, 2});
            while (tmp.size()) {
                v.pb(tmp.back());
                tmp.pop_back();
                ans.pb({1, 2});
            }
        }
        if (v.size() && v[0] == cur) {
            vector<int> tmp;
            while (v.size()) {
                ans.pb({2, 1});
                tmp.pb(v.back());
                v.pop_back();
            }
            while (tmp.size() && tmp.back() == cur) {
                cur--;
                tmp.pop_back();
                ans.pb({1, 3});
            }
            while (tmp.size()) {
                v.pb(tmp.back());
                tmp.pop_back();
                ans.pb({1, 2});
            }
        }
    }
    cout << ans.size() << endl;
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
