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

map<int, int> freq[2];
int n, x;
int g[2];
void test_case() {
    cin >> n;
    freq[0].clear();
    freq[1].clear();
    for (int k = 0; k < 2; k++) {
        for (int i = 0; i < n; i++) {
            cin >> x;
            if (i == 0) {
                g[k] = x;
            } else {
                g[k] = __gcd(g[k], x);
            }
        }
    }
    //dbg(g[0], g[1]);
    if (g[0] == g[1]) {
        cout << 0 << endl;
    } else if (__gcd(g[0], g[1]) == g[0]) {
        cout << 1 << endl;
    } else if (__gcd(g[0], g[1]) == g[1]) {
        cout << 1 << endl;
    } else {
        cout << 2 << endl;
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
