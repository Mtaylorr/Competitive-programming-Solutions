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

ll gcd(ll a, ll b, ll &x, ll &y) {
    if (b == 0) {
        x = 1;
        y = 0;
        return a;
    }
    ll x1, y1;
    ll d = gcd(b, a % b, x1, y1);
    x = y1;
    y = x1 - y1 * (a / b);
    return d;
}

bool find_any_solution(ll a, ll b, ll c, ll &x0, ll &y0, ll &g) {
    g = gcd(abs(a), abs(b), x0, y0);
    if (c % g) {
        return false;
    }

    x0 *= c / g;
    y0 *= c / g;
    if (a < 0) x0 = -x0;
    if (b < 0) y0 = -y0;
    return true;
}

int w;
ll n, d;
ll x[N];

void test_case() {
    cin >> w >> n >> d;
    for (int i = 0; i < w; i++) {
        cin >> x[i];
    }
    ll ans = 0;
    for (int i = 0; i < w / 2; i++) {
        if (i == w - 1 - i) continue;
        ll x0, y0, g;
        ll c = abs(x[i] - x[w - 1 - i]);
        ll a = d;
        ll b = -n;
        bool cond = find_any_solution(a, b, c, x0, y0, g);
        if (!cond) {
            cout << "IMPOSSIBLE\n";
            return;
        }

        ll bg = b / g;
        ll abg = abs(bg);
       // dbg(x0, y0, x0 * a - y0 * b, c);
        if (x0 > 0) {
            x0 %= abg;
        } else {
            x0 = -abs(x0) % abg;
            while (x0 < 0) {
                x0 += abg;
            }
        }
        ll rs = 1e18;
        for (int i = -2; i <= 2; i++) {
            rs = min(rs, abs(x0 + i * abg));
        }
        ans += rs;
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
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
