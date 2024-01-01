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

int x[3];
int a[3];

int getans(vector<int> v) {
    int s = 0;
    for (auto &u : v) {
        s += x[u];
    }
    int r = 0;
    if (s < 5) {
        r += a[0];
    } else if (s < 10) {
        r += a[1];
    } else {
        r += a[2];
    }
    return r;
}

void test_case() {
    for (int i = 0; i < 3; i++) {
        cin >> x[i];
    }
    for (int i = 0; i < 3; i++) {
        cin >> a[i];
    }
    int ans = getans({0, 1, 2});
    ans = min(ans, getans({0, 1}) + getans({2}));
    ans = min(ans, getans({0, 2}) + getans({1}));
    ans = min(ans, getans({2, 1}) + getans({0}));
    ans = min(ans, getans({2}) + getans({0}) + getans({1}));

    cout << ans << endl;
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
