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

int n, x[N], y[N];

void test_case() {
    cin >> n;
    vector<int> ord;
    for (int i = 0; i < n; i++) {
        cin >> x[i] >> y[i];
        ord.pb(i);
    }
    sort(all(ord), [](int &a, int &b) { return mp(x[a], y[a]) < mp(x[b], y[b]); });

    for (int i = 0; i < n; i += 2) {
        cout << ord[i] + 1 << " " << ord[i + 1] + 1 << endl;
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
