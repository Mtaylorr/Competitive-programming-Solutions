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
int l[N], r[N];
int g[105][105];
vector<int> intervals[N];

int solve(int a, int b) {
    if (a > b) return 0;
    if (g[a][b] != -1) {
        return g[a][b];
    }
    int rs = 0;
    unordered_set<int> st;
    for (int i = a; i < b; i++) {
        for (auto &id : intervals[i]) {
            if (r[id] < b) {
                st.insert(solve(a, i) ^ solve(r[id] + 1, b));
            }
        }
    }
    while (st.count(rs)) rs++;
    return g[a][b] = rs;
}

void test_case() {
    cin >> n;
    memset(g, -1, sizeof(g));
    for (int i = 0; i <= 100; i++) {
        intervals[i].clear();
    }
    for (int i = 0; i < n; i++) {
        cin >> l[i] >> r[i];
        r[i]--;
        intervals[l[i]].pb(i);
    }
    int ans = solve(1, 101);

    if (ans) {
        cout << "Alice\n";
    } else {
        cout << "Bob\n";
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
