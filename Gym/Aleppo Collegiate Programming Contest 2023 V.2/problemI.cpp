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
const int N = 1e6 + 5;

int n, a, b, m;
set<int> vals[N];
map<int, int> freq;

void add(int x, int &cur) {
    freq[x]++;
    while (freq[cur]) cur++;
}

void rem(int x, int &cur) {
    freq[x]--;
    if (freq[x] == 0) {
        cur = min(cur, x);
    }
    while (cur - 1 >= 0 && freq[cur - 1] == 0) cur--;
}
void test_case() {
    cin >> n >> m;
    freq.clear();
    for (int i = 0; i <= n + 1; i++) {
        vals[i].clear();
    }
    int cur = 0;
    for (int i = 0; i < m; i++) {
        cin >> a >> b;
        if (b < a) continue;
        vals[a].insert(b);
    }
    for (int i = 0; i <= n; i++) {
        for (auto &x : vals[i]) {
            add(x - i, cur);
        }
    }
    int ans = 1e9;
    for (int i = 0; i <= n; i++) {
        if (vals[i].count(i)) break;
        if (vals[i].size() && cur >= *vals[i].begin()) {
            for (auto &x : vals[i]) {
                rem(x - i, cur);
            }
            continue;
        }
        ans = min(ans, cur + n + 1);
        for (auto &x : vals[i]) {
            rem(x - i, cur);
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
    cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
