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

ll a, b, n;
map<ll, int> freq;

void test_case() {
    cin >> n;
    for (ll i = 2; i * i <= n; i++) {
        if (n % i == 0) {
            while (n % i == 0) {
                freq[i]++;
                n /= i;
            }
        }
    }
    if (n > 1) {
        freq[n]++;
    }
    vector<pair<ll, int> > v;
    bool hasodd = 0;
    for (auto u : freq) {
        v.pb({u.fi, u.se});
        if (u.se % 2 == 1) {
            hasodd = 1;
        }
    }
    if (hasodd) {
        a = 1;
        b = 1;
        for (auto u : v) {
            a *= (u.se + 1);
            int x = u.se;
            while (x--) {
                b *= u.fi;
            }
        }
        a /= 2;
        cout << b << " " << a << endl;
    } else {
        a = 1;
        b = 1;
        for (auto u : v) {
            a *= (u.se + 1);
            int x = u.se/2;
            while (x--) {
                b *= u.fi;
            }
        }
        cout << b << " " << a << endl;
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
