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

ll n;
string s;

void test_case() {
    cin >> s;
    reverse(all(s));
    ll ans = 1e18;
    for (ll n = 1, i = 0; i <= 30; i++, n *= 2) {
        bool cond = true;
        ll x = n;
        for (auto &c : s) {
            if (c == 'E') {
                x *= 2;
            } else {
                if ((x - 1) % 3 == 0 && x - 1 >= 1) {
                    x = (x - 1) / 3;
                    if (x % 2 == 0) {
                        cond = false;
                        break;
                    }
                } else {
                    cond = false;
                    break;
                }
            }
            if (1ll << __lg(x) == x) {
                cond = false;
                break;
            }
        }
        if (cond) {
            cout << x << endl;
            return;
        }
    }

    if (ans < 1e18) {
        cout << ans << endl;
    } else {
        cout << "INVALID\n";
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
