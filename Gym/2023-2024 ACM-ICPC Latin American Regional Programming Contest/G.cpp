// Mtaylor
#include <bits/stdc++.h>
#pragma GCC optimize("Ofast")
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

int treemn[4][4 * N];
int treemx[4][4 * N];

int X[N], Y[N], D[N];
int n;
int pos[N];

void build(int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        for (int j = 0; j < 4; j++) {
            treemn[j][id] = 1e9;
            treemx[j][id] = -1e9;
        }

        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = (ns) + (ne - ns) / 2;
    build(l, ns, md);
    build(r, md + 1, ne);
    for (int j = 0; j < 4; j++) {
        treemn[j][id] = min(treemn[j][l], treemn[j][r]);
        treemx[j][id] = max(treemx[j][l], treemx[j][r]);
    }
}

void upd(int p, int val, int b, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        treemn[b][id] = val;
        treemx[b][id] = val;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = (ns) + (ne - ns) / 2;
    if (p <= md) {
        upd(p, val, b, l, ns, md);
    } else {
        upd(p, val, b, r, md + 1, ne);
    }
    treemn[b][id] = min(treemn[b][l], treemn[b][r]);
    treemx[b][id] = max(treemx[b][l], treemx[b][r]);
}

void rem(int p, int b, int id = 0, int ns = 0, int ne = n - 1) {
    if (ns == ne) {
        treemn[b][id] = 1e9;
        treemx[b][id] = -1e9;
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = (ns) + (ne - ns) / 2;
    if (p <= md) {
        rem(p, b, l, ns, md);
    } else {
        rem(p, b, r, md + 1, ne);
    }
    treemn[b][id] = min(treemn[b][l], treemn[b][r]);
    treemx[b][id] = max(treemx[b][l], treemx[b][r]);
}

void query(int qs, int qe, int b, int &mn, int &mx, int id = 0, int ns = 0,
           int ne = n - 1) {
    if (qs > ne || qe < ns) return;
    if (qs <= ns && qe >= ne) {
        mn = min(mn, treemn[b][id]);
        mx = max(mx, treemx[b][id]);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = (ns) + (ne - ns) / 2;
    query(qs, qe, b, mn, mx, l, ns, md);
    query(qs, qe, b, mn, mx, r, md + 1, ne);
}

void add(int b, int idx) {
    int up = 2 * b;
    int lo = 2 * b + 1;
    int pup, plo;
    if (b == 0) {
        pup = X[idx] + Y[idx] - D[idx];
        plo = X[idx] - Y[idx] - D[idx];
    } else {
        pup = -X[idx] + Y[idx] - D[idx];
        plo = -X[idx] - Y[idx] - D[idx];
    }
    upd(pos[idx], pup, up, 0, 0, n - 1);
    upd(pos[idx], plo, lo, 0, 0, n - 1);
}

void remVal(int b, int idx) {
    int up = 2 * b;
    int lo = 2 * b + 1;
    rem(pos[idx], up, 0, 0, n - 1);
    rem(pos[idx], lo, 0, 0, n - 1);
}
vector<int> ys;

bool valid(int x, int y) {
    int y_idx = lower_bound(all(ys), y) - ys.begin();
    for (int i = 0; i < 4; i++) {
        int p = 0;
        if (i < 2) {
            p -= x;
        } else {
            p += x;
        }
        if (i % 2 == 0) {
            p -= y;
        } else {
            p += y;
        }
        int mn = 1e9;
        int mx = -1e9;
        if (i % 2 && y_idx >= 1) {
            query(0, y_idx - 1, i, mn, mx);
        }
        if (i % 2 == 0 && y_idx < n) {
            query(y_idx, n - 1, i, mn, mx);
        }

        if (mn > mx) continue;
        if (mn != mx) return 0;
        if (mn + p != 0) return 0;
    }
    return 1;
}

void test_case() {
    cin >> n;
    vector<int> tmp;
    for (int i = 0; i < n; i++) {
        scanf("%d%d%d", X + i, Y + i, D + i);
        tmp.pb(i);
    }
    sort(all(tmp), [](int &x, int &y) { return Y[x] < Y[y]; });

    for (auto &u : tmp) {
        ys.pb(Y[u]);
    }
    for (int i = 0; i < tmp.size(); i++) {
        pos[tmp[i]] = i;
    }
    vector<pair<int, int> > ans;
    sort(all(tmp), [](int &x, int &y) { return X[x] < X[y]; });
    build();
    for (int i = 0; i < n; i++) {
        add(0, i);
    }

    int j = 0;
    for (int x = -5e4; x <= 5e4; x++) {
        while (j < n && X[tmp[j]] < x) {
            remVal(0, tmp[j]);
            add(1, tmp[j]);
            j++;
        }
        int sm = D[0] - abs(X[0] - x);
        if (sm < 0) continue;
        int y = Y[0] - sm;
        if (valid(x, y) && y < Y[0]) {
            ans.pb({x, y});
        }
        y = sm + Y[0];
        if (valid(x, y) && y >= Y[0]) {
            ans.pb({x, y});
        }
    }
    for (auto &u : ans) {
        printf("%d %d\n", u.fi, u.se);
    }
}

int main() {
    // freopen("input.txt", "r", stdin);
    int T = 1;
    while (T--) {
        test_case();
    }
    return 0;
}
