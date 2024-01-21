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
ll x[N];
set<int> s;
vector<int> v;
ll l;
map<ll, bool> vis[N];
set<ll> ans;
void dfs(int i, ll s) {
    if (s > l) return;
    if (vis[i][s]) return;
    vis[i][s] = 1;
    if (i >= n) {
        if (s != 0)
            ans.insert(s);
        return;
    }
    dfs(i + 1, s);
    dfs(i, s + (1 + s) * v[i]);
}

void test_case() {
    cin >> n >> l;
    for (int i = 0; i < n; i++) {
        cin >> x[i];
        if (s.count(x[i]) == 0) {
            s.insert(x[i]);
            v.pb(x[i]);
        }
    }
    n = v.size();
    dfs(0, 0);
    cout << ans.size() << endl;
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
