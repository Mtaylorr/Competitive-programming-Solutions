// Mtaylor
#include <bits/stdc++.h>
using namespace std;

#define pb push_back
#define fi first
#define se second
#define mp make_pair
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

int ask(ll x) {
    cout << "? " << x << endl;
    int r;
    cin >> r;
    return r;
}

void test_case() {
    cin >> n;
    ll l = 1;
    ll r = 1e14;
    while (l < r) {
        ll md = (l + r) / 2;
        int x = ask(md);
        if (x >= n + 1) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    ll x = l;
    l = 1;
    r = (ll)1e14;
    while (l < r) {
        ll md = (l + r) / 2;
        int y = ask(md + x);
        if (y >= n + 2) {
            r = md;
        } else {
            l = md + 1;
        }
    }
    int b = -1;
    for (int i = 2; i <= 2023; i++) {
        ll cur = i - 1;
        for (int j = 0; j < n; j++) {
            cur *= i;
            if (cur > l) break;
        }
        if (cur == l) {
            b = i;
            break;
        }
    }
    l /= (b - 1);
    cout << "! " << l - x << " " << b << endl;
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
