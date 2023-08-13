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

int d, r, t;

int pref(int p) { return (p * (p + 1)) / 2; }

int calc(int x) {
    int rs = pref(x) - pref(3);
    int oth = x - d;
    if (oth >= 3) {
        rs += pref(oth) - pref(2);
    }
    return rs;
}
void test_case() {
    cin >> d >> r >> t;
    int lf = 4;
    int rg = 100;
    while (lf < rg) {
        int md = (lf + rg + 1) / 2;
        int c = calc(md);
        if (c > (r + t)) {
            rg = md - 1;
        } else {
            lf = md;
        }
    }
    cout << r - (pref(lf) - pref(3)) << endl;
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
