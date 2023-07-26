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

int n;
string s;
int freq[26];

void test_case() {
    memset(freq, 0, sizeof(freq));
    cin >> n;
    cin >> s;
    int mn = 1e9;
    int mx = 0;
    int distincts = 0;
    for (int i = 0; i < n; i++) {
        int x = s[i] - 'a';
        distincts += !freq[x]++;
        mn = min(mn, x);
        mx = max(mx, x);
    }
    if (distincts <= 2 || mx - mn + 1 == distincts) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }
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
