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

int getval(char c) {
    if (c >= '0' && c <= '9') {
        return c - '0';
    }
    return 10 + int(c - 'a');
}

int toDecimal(string s) { return getval(s[0]) * 16 + getval(s[1]); }

string s;
vector<int> v;
int lb, ub;

bool isAscii() {
    int lb = toDecimal("20");
    int ub = toDecimal("7f");
    for (auto &u : v) {
        if (u == 0) {
            return true;
        }
        if (u > ub || u < lb) return false;
    }
    return false;
}

bool isPascal() {
    int l = v[0];
    int lb = toDecimal("20");
    int ub = toDecimal("7f");
    if (v.size() - 1 < l) return 0;
    for (int i = 1; i <= l; i++) {
        if (v[i] > ub || v[i] < lb) return 0;
    }

    return true;
}

void test_case() {
    while (cin >> s) {
        v.pb(toDecimal(s));
    }
    bool x = isAscii();
    bool y = isPascal();
    if (x & y) {
        cout << "Both";
    } else if (x) {
        cout << "C";
    } else if (y) {
        cout << "Pascal";
    } else {
        cout << "None";
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
