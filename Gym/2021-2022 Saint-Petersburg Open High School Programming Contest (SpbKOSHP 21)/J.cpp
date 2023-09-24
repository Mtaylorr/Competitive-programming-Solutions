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

const int P = 1e5 + 5;
class NumberTheory {
   public:
    template <typename T>
    bool issquare(T w) {
        T sq = round(sqrt(w));
        return sq * sq == w;
    }

} nt;

bool isperfect(ll x) {
    if (x % 10 == 0) return 0;
    string s = to_string(x);
    reverse(all(s));
    return nt.issquare(stoll(s));
}

ll a, b;
void test_case() {
    cin >> a >> b;
    int ans = 0;
    for (ll i = 1;; i++) {
        if (i * i > b) break;
        if (i * i < a) continue;
        if (isperfect(i * i)) {
            ans++;
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
