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
int a[N];
bool done[N];

void test_case() {
    cin >> n >> k;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        done[i] = 0;
    }
    ll ans = 0;
    for (int j = k - 1; j >= 0; j--) {
        bool canadd = 1;
        int cur = (1 << j);
        for (int i = 0; i < n; i++) {
            if (a[i] & cur) continue;
            if (done[i]) {
                canadd = 0;
            }
        }
        if (canadd) {
            for (int i = 0; i < n; i++) {
                if (a[i] & cur) continue;
                if (!done[i]) {
                    done[i] = 1;
                }
            }
            ans += cur;
        }
    }
    bool hasleft = 0;
    for (int i = 0; i < n; i++) {
        hasleft += !done[i];
    }
    if (hasleft && (ans == ((1 << k) - 1))) {
        ans--;
    }
    cout << ans << endl;
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
