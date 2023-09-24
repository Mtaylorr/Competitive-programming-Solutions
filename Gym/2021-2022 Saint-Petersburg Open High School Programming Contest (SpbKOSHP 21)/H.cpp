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
vector<int> t;
vector<ll> k;
ll a, b;

void test_case() {
    cin >> a >> b;
    while (a != 0 && b != 0) {
        int signa = (a > 0) - (a < 0);
        int signb = (b > 0) - (b < 0);
        if (abs(a) > abs(b)) {
            ll x = abs(a) / abs(b);
            if (signa == signb) {
                t.pb(1);
                k.pb(-x);
                a -= x * b;
                if (a != 0 && abs(a - b) <= 1e18 && abs(a - b) < abs(a)) {
                    k.back()--;
                    a -= b;
                }
            } else {
                t.pb(1);
                k.pb(x);
                a += x * b;
                if (a != 0 && abs(a + b) <= 1e18 && abs(a + b) < abs(a)) {
                    k.back()++;
                    a += b;
                }
            }
        } else {
            ll x = abs(b) / abs(a);
            if (signa == signb) {
                t.pb(2);
                k.pb(-x);
                b -= x * a;
                if (b != 0 && abs(b - a) <= 1e18 && abs(b - a) < abs(b)) {
                    k.back()--;
                    b -= a;
                }
            } else {
                t.pb(2);
                k.pb(x);
                b += x * a;
                if (b != 0 && abs(b + a) <= 1e18 && abs(b + a) < abs(b)) {
                    k.back()++;
                    b += a;
                }
            }
        }
    }
    cout << t.size() << endl;
    for (int i = 0; i < t.size(); i++) {
        cout << t[i] << " " << k[i] << "\n";
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
