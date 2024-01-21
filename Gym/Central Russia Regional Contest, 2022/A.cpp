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

map<char, int> d;
string a, b, c;
char decode[N];
int tot = 0;

bool valid(int B) {
    int mx = max(sz(a), sz(b));
    string tmp = "";
    int cur = 0;
    for (int i = 0; i < mx; i++) {
        if (i < sz(a)) {
            cur += d[a[i]];
        }
        if (i < sz(b)) {
            cur += d[b[i]];
        }
        if (cur % B >= tot) {
            return 0;
        }
        tmp += decode[cur % B];
        cur /= B;
    }
    if (cur && (cur % B) >= tot) return 0;
    if (cur)
        tmp += decode[cur % B];
    return tmp == c;
}

void test_case() {
    cin >> a >> b >> c;
    reverse(all(a));
    reverse(all(b));
    reverse(all(c));
    int cur = 0;

    for (char c = '0'; c <= '9'; c++) {
        decode[cur] = c;
        d[c] = cur++;
    }
    for (char c = 'A'; c <= 'Z'; c++) {
        decode[cur] = c;
        d[c] = cur++;
    }
    tot = cur;
    int mx = 0;
    for (auto &c : a) {
        mx = max(mx, d[c] + 1);
    }
    for (auto &c : b) {
        mx = max(mx, d[c] + 1);
    }
    for (auto &c : c) {
        mx = max(mx, d[c] + 1);
    }
    int nb = 0;
    int v = -1;
    for (int i = mx; i <= 100; i++) {
        if (valid(i)) {
            nb++;
            v = i;
        }
    }
    if (nb == 1) {
        cout << v << endl;
    } else {
        cout << 0 << endl;
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
