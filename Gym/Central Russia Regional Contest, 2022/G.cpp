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
const int N = 1e6 + 5;

int getVal() {
    char c1, c2;
    cin >> c1 >> c2;
    return (c1 - '0') * 10 + (c2 - '0');
}

int getTime() {
    int h = getVal();
    char c;
    cin >> c;
    int m = getVal();
    cin >> c;
    int s = getVal();
    return h * 3600 + m * 60 + s;
}
int n;

int sum[N];
void test_case() {
    ll ans = 0;
    cin >> n;
    while (n--) {
        int l = getTime();
        int r = getTime() - 1;
        if (l > r) {
            sum[l]++;
            sum[24 * 3600]--;
            sum[0]++;
            sum[r + 1]--;
        } else {
            sum[l]++;
            sum[r + 1]--;
        }
    }
    for (int i = 0; i < 1e6; i++) {
        if (i)
            sum[i] += sum[i - 1];
        if (sum[i]) {
            ans++;
        }
    }
    cout << 24 * 3600 - ans << endl;
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
