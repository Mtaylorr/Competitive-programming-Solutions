//https://codeforces.com/problemset/problem/558/E
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(2e6) + 3;
const int MOD = int(1e9) + 7;

struct node {
    int eq, inf, k, l, r;

    node() {
        eq = inf = k = l = r = 0;
    }

    node(int e, int i, int _k, int _l, int _r) {
        eq = e;
        inf = i;
        k = _k;
        l = _l;
        r = _r;
    }
};

pair<int, int> tree[N];
node lazy[N];
string ans, s;
int n, q;
vector<pair<pair<int, int>, int> > qu;

pair<int, int> mrg(pair<int, int> a, pair<int, int> b) {
    return {a.fi + b.fi, a.se + b.se};
}

node calcnode(node q, int lsz, int sz) {
    int i = 0;
    int e = 0;
    node nn;
    if (lsz <= q.inf) {
        nn =node(q.eq, q.inf - lsz, q.k, q.l, q.r);
    } else if (lsz <= q.inf + q.eq) {
        nn =node(q.eq - (lsz - q.inf), 0, q.k, q.l, q.r);
    } else {
        nn =node(0, 0, q.k, q.l, q.r);
    }
    if(nn.inf>=sz){
        nn.inf = sz;
        nn.eq=0;
    }else if(nn.inf+nn.eq>=sz){
        nn.eq = sz-nn.inf;
    }
    return nn;
}

node getnode(node q, int ns, int ne) {
    if (q.k == 1) {
        return calcnode(q, ns - q.l, ne-ns+1);
    } else {
        return calcnode(q, q.r - ne, ne-ns+1);
    }
}

void updlazy(int id, int ns, int ne) {
    if (lazy[id].eq == -1)
        return;
    node nn = getnode(lazy[id], ns, ne);
    tree[id] = {nn.eq, nn.inf};
    if (ns != ne) {
        int l = 2 * id + 1;
        int r = l + 1;
        lazy[l] = lazy[id];
        lazy[r] = lazy[id];

    }
    lazy[id].eq = -1;
}

void upd(int qs, int qe, node q, int id = 0, int ns = 0, int ne = n - 1) {
    updlazy(id, ns, ne);
    if (qs > ne || qe < ns) {
        return;
    }
    if (qs <= ns && qe >= ne) {
        lazy[id] = q;
        updlazy(id, ns, ne);
        return;
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    upd(qs, qe, q, l, ns, md);
    upd(qs, qe, q, r, md + 1, ne);
    tree[id] = mrg(tree[l], tree[r]);
}

pair<int, int> query(int qs, int qe, int id = 0, int ns = 0, int ne = n - 1) {
    updlazy(id, ns, ne);
    if (qs > ne || qe < ns) {
        return {0, 0};
    }
    if (qs <= ns && qe >= ne) {
        return tree[id];
    }
    int l = 2 * id + 1;
    int r = l + 1;
    int md = ns + (ne - ns) / 2;
    return mrg(query(qs, qe, l, ns, md), query(qs, qe, r, md + 1, ne));
}

void init() {
    for (int i = 0; i <= 4 * n; i++) {
        tree[i] = {0, 0};
        lazy[i] = {-1, -1, -1, -1, -1};
    }
}


int main() {
    FAST;
    cin >> n >> q;
    cin >> s;
    ans = s;
    for (int i = 0; i < n; i++) {
        ans[i] = '#';
    }
    int x, y, z;
    for (int i = 0; i < q; i++) {
        cin >> x >> y >> z;
        x--;
        y--;
        qu.pb({{x, y}, z});
    }
    for (int i = 0; i < 26; i++) {
        init();
        for (int j = 0; j < n; j++) {
            if ((s[j] - 'a') < i) {
                upd(j, j, node(0, 1, 0, j, j));
            } else if ((s[j] - 'a') == i) {
                upd(j, j, node(1, 0, 0, j, j));
            } else {
                upd(j, j, node(0, 0, 0, j, j));
            }
        }
        for (auto u:qu) {
            pair<int, int> o = query(u.fi.fi, u.fi.se);
            upd(u.fi.fi, u.fi.se, node(o.fi, o.se, u.se, u.fi.fi, u.fi.se));
        }
        for (int j = 0; j < n; j++) {
            pair<int, int> o = query(j, j);
            if (o.fi == 1) {
                ans[j] = char('a' + i);
            }
        }
    }
    cout << ans << endl;
    return 0;
}
