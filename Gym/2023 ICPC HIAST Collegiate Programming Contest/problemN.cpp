// Mtaylor
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(), (v).end()
#define rall(v) (v).rbegin(), (v).rend()
#define max(a, b) (a > b ? a : b)
#define min(a, b) (a < b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)

const int N = int(3e6) + 3;
const int MOD = int(1e9) + 7;

enum DIR { L, R };

struct node;
extern node *emp;
struct node {
    long long v;
    int p, sz;
    bool reversed;
    node *child[2];
    node() {
        v = 0;
        p = INT_MIN;
        sz = 0;
        reversed = false;
        child[L] = child[R] = this;
    }
    node(ll val, node *l = emp, node *r = emp) {
        p = rand();
        v = val;
        child[L] = l;
        child[R] = r;
        reversed = false;
        push_up();
    }
    void push_up() { sz = (child[L]->sz) + (child[R]->sz) + 1; }
    void push_down() {
        if (reversed) {
            for (int i = 0; i < 2; i++) {
                child[i]->reverse();
            }
            reversed = false;
        }
    }
    void reverse() {
        if (this == emp) return;
        reversed ^= 1;
        swap(child[L], child[R]);
    }
};

node *emp = new node();

void split(node *rt, int lssz, node *&ls, node *&ge) {
    if (rt == emp) {
        ls = ge = emp;
        return;
    }
    rt->push_down();
    int lfsz = rt->child[L]->sz;
    if (lssz <= lfsz) {
        split(rt->child[L], lssz, ls, rt->child[L]);
        ge = rt;
    } else {
        split(rt->child[R], lssz - lfsz - 1, rt->child[R], ge);
        ls = rt;
    }
    rt->push_up();
}

node *mrg(node *ls, node *ge) {
    if (ls == emp) return ge;
    if (ge == emp) return ls;
    ls->push_down();
    ge->push_down();
    if (ls->p > ge->p) {
        ls->child[R] = mrg(ls->child[R], ge);
        ls->push_up();
        return ls;
    }
    ge->child[L] = mrg(ls, ge->child[L]);
    ge->push_up();
    return ge;
}

void doReverse(node *&rt, int st, int en) {
    node *af, *bf;
    split(rt, en + 1, rt, af);
    split(rt, st, bf, rt);
    rt->reverse();
    rt = mrg(bf, rt);
    rt = mrg(rt, af);
}
void doInsert(node *&rt, int pos, int val) {
    node *af, *bf;
    split(rt, pos, bf, af);
    node *nd = new node(val);
    rt = mrg(bf, nd);
    rt = mrg(rt, af);
}

int getval(node *&rt, int pos) {
    node *af, *bf;
    split(rt, pos + 1, rt, af);
    split(rt, pos, bf, rt);
    int ans = rt->v;
    rt = mrg(bf, rt);
    rt = mrg(rt, af);
    return ans;
}

template <typename T>
class FenwickTree {
   public:
    vector<T> tree;
    int n;
    void init(int n) {
        tree.assign(n + 2, 0);
        this->n = n;
    }
    T mrg(T &x, T &y) { return x + y; }

    void upd(int x, T v) {
        for (; x <= n; x += (x) & (-x)) {
            tree[x] = mrg(tree[x], v);
        }
    }
    T getprefix(int x) {
        if (x <= 0) return 0;
        T rs = 0;
        for (; x; x -= (x) & (-x)) {
            rs = mrg(rs, tree[x]);
        }
        return rs;
    }
    T getrange(int l, int r) { return getprefix(r) - getprefix(l - 1); }
};
FenwickTree<int> ft;

int x, q;
int n;
int val[N];
int ty[N], l[N], r[N];
int p[N];
vector<int> adj[N];
int ord[N];
vector<int> vals;
int ti = 0;
void dfs(int u, int p = -1) {
    ord[u] = ti++;
    for (auto v : adj[u]) {
        if (v == p) continue;
        dfs(v, u);
    }
}

int main() {
    FAST;
    cin >> val[0] >> q;
    n = 1;
    for (int i = 0; i < q; i++) {
        cin >> ty[i];
        if (ty[i] == 1) {
            cin >> l[i] >> r[i];
            --l[i];
            adj[l[i]].pb(n);
            p[i] = n;
            val[n++] = r[i];
        } else if (ty[i] == 2) {
            cin >> l[i] >> r[i];
            --l[i], --r[i];
        } else {
            cin >> l[i];
            l[i]--;
        }
    }

    ft.init(n + 1);
    dfs(0);
    ft.upd(ord[0] + 1, 1);
    node *rt = emp;
    rt = mrg(rt, new node(val[0]));
    for (int i = 0; i < q; i++) {
        if (ty[i] == 1) {
            int x = ft.getprefix(ord[p[i]] + 1);
            doInsert(rt, x, r[i]);
            ft.upd(ord[p[i]] + 1, 1);
        } else if (ty[i] == 2) {
            doReverse(rt, l[i], r[i]);
        } else {
            int x = ft.getprefix(ord[l[i]]);
            cout << getval(rt, x) << endl;
        }
    }
    return 0;
}
