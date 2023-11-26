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

ll n, k, d;
vector<pair<int, int> > ans;

int id = 0;
int getid() { return id++; }
void test_case() {
    cin >> n >> k >> d;
    assert(n >= 2);
    assert(d <= n);
    assert((k / 2) + 3 * (d / 2) <= n);
    if (d == 1) {
        cout << "impossible\n";
        return;
    }
    if (d == 3) {
        if (k != ((n - 1) * (n - 2)) / 2) {
            cout << "impossible\n";
            return;
        }
        for (int i = 2; i <= n; i++) {
            cout << 1 << " " << i << endl;
        }
        return;
    }
    int st = getid();
    if (k % 2 == 0) {
        int p = (d - 1) / 2 - 1;
        int bef = st;
        for (int i = 0; i < p; i++) {
            int cur = getid();
            ans.pb({bef, cur});
            bef = cur;
        }
        for (int i = 0; i < k / 2; i++) {
            ans.pb({bef, getid()});
        }
        bef = st;
        for (int i = 0; i < p; i++) {
            int cur = getid();
            ans.pb({bef, cur});
            bef = cur;
        }
        for (int i = 0; i < 2; i++) {
            ans.pb({bef, getid()});
        }
    } else {
        int p = (d - 1) / 2 - 1;
        int bef = st;
        for (int i = 0; i < p; i++) {
            int cur = getid();
            ans.pb({bef, cur});
            bef = cur;
        }
        for (int i = 0; i < k / 2; i++) {
            ans.pb({bef, getid()});
        }
        bef = st;
        for (int i = 0; i < p; i++) {
            int cur = getid();
            ans.pb({bef, cur});
            bef = cur;
        }
        for (int i = 0; i < 1; i++) {
            ans.pb({bef, getid()});
        }
        bef = st;
        for (int i = 0; i < p; i++) {
            int cur = getid();
            ans.pb({bef, cur});
            bef = cur;
        }
        for (int i = 0; i < 1; i++) {
            ans.pb({bef, getid()});
        }
    }
    int cur;
    while ((cur = getid()) < n) {
        ans.pb({0, cur});
    }
    for (auto &x : ans) {
        cout << x.fi + 1 << " " << x.se + 1 << endl;
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
