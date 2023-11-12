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
string st[N];
vector<int> p[25];
map<pair<string, string>, int> freq[25][25];
void test_case() {
    cin >> n;
    for (int i = 0; i < n; i++) {
        cin >> st[i];
        p[st[i].size()].pb(i);
    }
    int ans = 0;
    vector<int> diff;
    for (int s = 3; s <= 20; s++) {
        int m = p[s].size();
        for (int j = 0; j < m; j++) {
            for (int k = j + 1; k < m; k++) {
                diff.clear();
                string &a = st[p[s][j]];
                string &b = st[p[s][k]];
                for (int o = 0; o < s; o++) {
                    if (a[o] != b[o]) {
                        diff.pb(o);
                    }
                }
                if (diff.size() != 2) continue;
                if (diff[0] != diff.back() - 1) continue;
                string t1 = "";

                t1 += a[diff[0]], t1 += a[diff.back()];
                string t2 = "";
                t2 += b[diff[0]], t2 += b[diff.back()];
                freq[s][diff[0]][{min(t1, t2), max(t1, t2)}]++;
            }
        }
        for (int j = 0; j < s; j++) {
            for (auto &u : freq[s][j]) {
                ans += (u.se == 1);
            }
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
