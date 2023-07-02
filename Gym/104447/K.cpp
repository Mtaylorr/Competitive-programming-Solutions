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
bool done[N];
vector<int> ans;
vector<int> adj[N];
bool vis[N];

void dfs(int u) {
    if (vis[u]) return;
    vis[u] = 1;
    sort(all(adj[u]));
    for (auto v : adj[u]) {
        dfs(v);
    }
    if (u != n - 1) ans.pb(u);
}
void test_case() {
    cin >> n;
    if (n % 3 == 0) {
        cout << "NO\n";
        return;
    }
    set<int> cur;
    done[n - 1] = 0;
    for (int i = 0; i < n; i++) {
        done[i] = 0;
    }
    ans.clear();
    int nb = 1;
    done[0] = 1;
    ans.pb(0);
    cur.insert(3);
    cur.insert(n - 3);
    while (cur.size()) {

        int x = *cur.begin();
        cur.erase(cur.begin());
        int l = (x + n - 3) % n;
        int r = (x + 3) % n;

        if (done[l] && done[r]) {
            continue;
        }
        if (!done[l] && !done[r]) {
            continue;
        }nb++;
        // dbg(x, l, r, done[l], done[r]);
        done[x] = 1;
        ans.pb(x);
        if (!done[l]) {
            cur.insert(l);
        }
        if (!done[r]) {
            cur.insert(r);
        }
    }
    if (nb != n - 1) {
        cout << "NO\n";
    } else {
        cout << "YES\n";
        for (auto u : ans) {
            cout << u + 1 << " ";
        }
        cout << endl;
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
