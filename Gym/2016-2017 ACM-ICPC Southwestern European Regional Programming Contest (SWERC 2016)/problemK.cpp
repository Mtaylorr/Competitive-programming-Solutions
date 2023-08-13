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

map<pair<int, pair<int, int> >, int> code3;
map<pair<int, int>, int> code2;
int nb = 0;
bool isfloor[N];

set<int> adj[N];

int getcode(int x, int y, int z = -1) {
    if (z == -1) {
        pair<int, int> p = {x, y};
        if (code2.count(p)) {
            return code2[p];
        }
        isfloor[nb] = 1;
        return code2[p] = nb++;
    } else {
        pair<int, pair<int, int> > p = {x, {y, z}};
        if (code3.count(p)) {
            return code3[p];
        }
        return code3[p] = nb++;
    }
}
void addEdge(int u, int v) {
    if(u==v)return ;
    adj[u].insert(v);
    adj[v].insert(u);
}

int vis[N];
bool cycle;
int k;

void dfs(int u, int p = -1) {
    vis[u] = 1;
    for (auto v : adj[u]) {
        if (v == p) continue;
        if (vis[v] == 1) {
            cycle = true;
            return;
        }
        if (vis[v]) continue;
        dfs(v,u);
    }
    vis[u] = 2;
}
void test_case() {
    cin >> k;
    for (int i = 0; i < k; i++) {
        int x, y, z;
        cin >> x >> y >> z;
        int u = getcode(x, y, z);
        int uu = getcode(x, y);
        cin >> x >> y >> z;
        int v = getcode(x, y, z);
        int vv = getcode(x, y);
        addEdge(u, v);
        addEdge(uu, vv);
        //dbg(u,v,uu,vv);
    }
    bool hasfloor = 0;
    bool hastrue = 0;
    for (int i = 0; i < nb; i++) {
        cycle = 0;
        if (!vis[i]) {
            dfs(i);
           // dbg(i, cycle, isfloor[i]);
            if (cycle) {
                if (isfloor[i]) {
                    hasfloor = 1;
                } else {
                    hastrue = 1;
                }
            }
        }
    }
    if (hastrue) {
        cout << "True closed chains\n";
    } else {
        cout << "No true closed chains\n";
    }
    if (hasfloor) {
        cout << "Floor closed chains\n";
    } else {
        cout << "No floor closed chains\n";
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
