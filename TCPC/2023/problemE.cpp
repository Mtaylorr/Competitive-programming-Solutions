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
const int MOD = 1e9 + 7;

string s;
int n;

int calc(int k) {
    int ans = 1;
    for (int i = 0; i < (n + 1) / 2; i++) {
        int l = (i + k) % n;
        int r = (n - i - 1 + k) % n;
        if (s[l] == s[r] && s[l] == '?') {
            ans = (ans * 1ll * 26) % MOD;
        } else if (s[l] != '?' && s[r] != '?') {
            ans = (ans * (s[l] == s[r]));
        }
    }
    return ans;
}

int allEqual() {
    int hasother = -1;
    for (auto &c : s) {
        if (c != '?') {
            if (hasother == -1) {
                hasother = c - 'a';
            } else if (hasother != (c - 'a')) {
                return 0;
            }
        }
    }
    if (hasother >= 0) {
        return 1;
    }
    return 26;
}

void test_case() {
    cin >> n;
    cin >> s;
    int ans = calc(0);
    ans = (ans + calc(1)) % MOD;
    ans = (ans + 0ll + MOD - allEqual()) % MOD;
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
