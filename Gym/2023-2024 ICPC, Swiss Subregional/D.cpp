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

int calc(string &s) {
    int ans = 0;
    for (int i = 0; i < s.size() - 1; i++) {
        ans += (s[i] == '4') && (s[i + 1] == '2');
    }
    return ans;
}

void test_case() {
    cin >> n;
    int ans = 0;
    for (int i = 2; i <= n; i++) {
        string x = to_string(i - 1);
        string y = to_string(i);
        ans += calc(y);
        ans += (x[x.size() - 1] == '4') && (y[0] == '2');
    }
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
