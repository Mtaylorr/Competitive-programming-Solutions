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

const int E = 1e6 + 5;

vector<int> tmp;
bool incycle[N];
bool isleaf[N];
int d[N], c[N];
int vis[N];
ll ans = 0;
int n;
ll val[N];
ll sum[N];
int indeg[N];

void dfs(int u) {
    tmp.pb(u);
    vis[u] = 1;
    if (vis[d[u]] == 0) {
        dfs(d[u]);
    } else if (vis[d[u]] == 1) {
        while (tmp.back() != d[u]) {
            int x = tmp.back();
            tmp.pop_back();
            incycle[x] = 1;
        }
        incycle[d[u]] = 1;
        tmp.pop_back();
    }

    vis[u] = 2;
}

void solve(int u) {
    if (incycle[u]) return;
    ans += max(0ll, c[u] - val[u]);
    val[d[u]] += c[u];
    solve(d[u]);
}

void test_case() {
    cin >> n;
    ans = 0;
    for (int i = 0; i < n; i++) {
        isleaf[i] = 1;
        sum[i] = val[i] = 0;
        indeg[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        cin >> d[i];
        d[i]--;
        vis[i] = 0;
        incycle[i] = 0;
        isleaf[d[i]] = 0;
        indeg[d[i]]++;
    }
    for (int i = 0; i < n; i++) {
        cin >> c[i];
        sum[d[i]] += c[i];
    }
    for (int i = 0; i < n; i++) {
        if (vis[i]) continue;
        dfs(i);
    }
    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (isleaf[i]) {
            q.push(i);
            indeg[i]--;
        }
    }
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        ans += max(0ll, c[u] - val[u]);
        val[d[u]] += c[u];
        indeg[d[u]]--;
        if (incycle[d[u]]) continue;
        if (indeg[d[u]] == 0) {
            { q.push(d[u]); }
        }
    }
    for (int i = 0; i < n; i++) {
        vis[i] = 0;
    }
    for (int i = 0; i < n; i++) {
        tmp.clear();
        if (vis[i]) continue;
        if (!incycle[i]) continue;
        int x = i;
        do {
            tmp.pb(x);
            x = d[x];
            vis[x] = 1;
        } while (x != i);
        ll mn = 1e18;
        for (int i = 0; i < tmp.size(); i++) {
            int p = (i + 1) % tmp.size();
            ll x = max(0ll, c[tmp[p]] - c[tmp[i]] - val[tmp[p]]);
            mn = min(mn, max(0ll, c[tmp[p]] - val[tmp[p]]) - x);
            ans += x;
        }
        ans += mn;
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
    int tst = 0;
    while (T--) {
        cout << "Case #" << ++tst << ": ";
        test_case();
    }
    return 0;
}
