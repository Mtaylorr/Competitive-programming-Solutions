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

map<pair<ll, ll>, int> freq;

int s[N], v[N];
int n;

void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> s[i] >> v[i];
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (j == i) continue;
            int rs = 0;
            int always = 0;
            vector<pair<ll, ll> > tmp;
            for (int k = 0; k < n; k++) {
                if (k == i || k == j) continue;
                ll dy1 = j - i;
                ll dy2 = k - i;
                ll ds1 = s[j] - s[i];
                ll ds2 = s[k] - s[i];
                ll dv1 = v[j] - v[i];
                ll dv2 = v[k] - v[i];
                if (dy2 * ds1 == dy1 * ds2 && dy2 * dv1 == dy1 * dv2) {
                    always++;
                } else if (dy2 * dv1 == dy1 * dv2) {
                    continue;
                } else {
                    ll b = dy1 * ds2 - dy2 * ds1;
                    ll a = dy2 * dv1 - dy1 * dv2;
                    ll d = __gcd(abs(b), abs(a));
                    double da = a;
                    double db = b;
                    if (db / da < 0) continue;
                    b /= d;
                    a /= d;
                    tmp.pb({a, b});
                }
            }
            sort(all(tmp));
            int nb = 0;
            pair<ll, ll> p = {-1e18, -1e18};
            for (auto &u : tmp) {
                if (u == p) {
                    nb++;
                } else {
                    nb = 1;
                }
                p=u;
                rs=max(rs,nb);
            }
            ans = max(ans, rs + 2 + always);
        }
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
