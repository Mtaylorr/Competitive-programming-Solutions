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

int n, m, q;
vector<int> adj[N];
int t[N], a[N];
bool done[N];
vector<int> ans;
vector<int> res[N];
int col[N];
void add(int u) {
    int cnt = 0;
    int r = 0;
    for (auto v : adj[u]) {
        if (done[v] == 0) {
            continue;
        }
        r++;
        cnt += col[v] == 1;
    }
    if (2 * cnt >= r) {
        col[u] = 0;
    } else {
        col[u] = 1;
        ans.pb(u);
    }
    done[u] = 1;
}
void test_case() {
    cin >> n >> m >> q;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u;
        --v;
        adj[u].pb(v);
        adj[v].pb(u);
    }
    for (int i = 0; i < q; i++) {
        cin >> t[i];
        if (t[i] == 1) {
            cin >> a[i];
            --a[i];
            done[a[i]] = 1;
        }
    }
    vector<int> tmp;
    for (int i = 0; i < n; i++) {
        if (!done[i]) {
            tmp.pb(i);
        }
    }
    for (int i = 0; i < n; i++) {
        done[i] = 0;
    }
    for (auto &u : tmp) {
        add(u);
    }
    for (int i = q - 1; i >= 0; i--) {
        if (t[i] == 1) {
            add(a[i]);
        } else {
            res[i] = ans;
        }
    }
    for (int i = 0; i < q; i++) {
        if (t[i] != 1) {
            cout << res[i].size() << endl;
            for (auto &u : res[i]) {
                cout << u + 1 << " ";
            }
            cout << endl;
        }
    }
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
