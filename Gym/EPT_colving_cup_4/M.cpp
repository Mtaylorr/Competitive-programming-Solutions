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

int n, k;
void test_case() {
    cin >> n >> k;
    k = 1 - k;
    if (n == 1) {
        cout << 0 << endl;
        return;
    }
    if (n == 2) {
        cout << 1 << endl;
        return;
    }
    if (n == 4) {
        cout << 2 << endl;
        return;
    }
    if (k == 0) {
        cout << (n) / 2 + (n % 2 == 0) << endl;
    } else {
        cout << (n) / 2 + (n % 2) << endl;
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
