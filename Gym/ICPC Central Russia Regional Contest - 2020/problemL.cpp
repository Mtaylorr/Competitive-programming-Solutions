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

void solve(int p, int n, int d) {
    if (n == 1) {
        cout << s[p];
        return;
    }
    if (d == 0) {
        solve(p + n - 1, n / 2, 1);
        solve(p + n / 2 - 1, n / 2, 1);
    } else {
        solve(p - n + 1, n / 2, 0);
        solve(p - n / 2 + 1, n / 2, 0);
    }
}

void test_case() {
    cin >> s;
    solve(0, s.size(), 0);
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
