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
map<string, int> freq[3];
set<string> st;
string a, b;
int x;
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> a >> b >> x;
        int p = (b == "right") + 2 * (b == "any");
        freq[p][a] += x;
        st.insert(a);
    }
    int ans = 0;
    for (auto &u : st) {
        if (freq[0][u] == 0 && freq[1][u] == 0) {
            if (freq[2][u]) {
                ans += 1;
            }
        } else {
            ans += max(freq[1][u], freq[0][u]);
        }
    }
    int nb = 0;
    for (auto &u : st) {
        if (freq[0][u] == 0 && freq[2][u] == 0) {
            nb++;
        } else if (freq[1][u] == 0 && freq[2][u] == 0) {
            nb++;
        } else if (freq[0][u] == 0 && freq[1][u] == 0 && freq[2][u] <= 1) {
            nb++;
        }
    }
    if (nb == st.size()) {
        cout << "impossible\n";
        return;
    }
    cout << ans + 1 << endl;
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
