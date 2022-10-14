//https://codeforces.com/problemset/problem/522/D
#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long int ll;

using namespace std;

const int N = 5e5 + 100, M = 1000 + 5, E = 2e6 + 5;
const int MOD = 1e9 + 7;

int n, m;
map<int,int> pos;
int a[N];
int ans[N];
int l[N], r[N];
vector<int> qu[N];
int tree[4 * N];

void init(int id = 0, int ns = 0, int ne = n - 1) {
    tree[id] = 1e9;
    if (ns == ne) {
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    init(l, ns, md);
    init(r, md + 1, ne);
}

void upd(int p, int v, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns > p || ne < p)
        return;
    if (ns == ne) {
        tree[id] = v;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(p, v, l, ns, md);
    upd(p, v, r, md + 1, ne);
    tree[id] = min(tree[l], tree[r]);
}

int query(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns > qe || ne < qs)
        return 1e9;
    if (qs <= ns && qe >= ne) {
        return tree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return min(query(qs, qe, l, ns, md),
               query(qs, qe, r, md + 1, ne));
}

int main() {
    freopen("input.txt", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        pos[a[i]] = -1;
    }
    for (int i = 0; i < m; i++) {
        cin >> l[i] >> r[i];
        l[i]--, r[i]--;
        qu[r[i]].pb(i);
    }
    init();
    for (int i = 0; i < n; i++) {
        if (pos[a[i]] != -1) {
            upd(pos[a[i]], i - pos[a[i]]);
        }
        pos[a[i]] = i;
        for (auto u: qu[i]) {
            int rs = query(l[u], i);
            if (rs < 1e9) {
                ans[u] = rs;
            } else {
                ans[u] = -1;
            }
        }
    }
    for (int i = 0; i < m; i++) {
        cout << ans[i] << "\n";
    }
    return 0;

}
