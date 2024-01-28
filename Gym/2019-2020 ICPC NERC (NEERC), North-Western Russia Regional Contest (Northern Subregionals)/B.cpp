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
const double pi = 4 * atan(1);

vector<int> v[2];
int n;
void test_case() {
    cin >> n;
    int ans = 0;
    double mn = 1e9;
    int mni = 0;
    double cur = -5;
    for (int i = 0;; i += 710) {
        if (sin(i) < cur) break;
        cur = sin(i);
        ans++;
        v[0].pb(i);
    }
    cur = 0;
    for (int i = -710;; i -= 710) {
        if (sin(i) > cur) break;
        cur = sin(i);
        v[1].pb(i);
        ans++;
    }
    reverse(all(v[1]));
    for (auto &x : v[0]) {
        v[1].pb(x);
    }
    for (int i = 0; i < n; i++) {
        cout << v[1][i] << "\n";
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
