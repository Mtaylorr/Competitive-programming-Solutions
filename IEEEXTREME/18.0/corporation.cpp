//https://csacademy.com/ieeextreme18/task/corporation/
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

struct node {
    ll mn, mx, sal, hap;
    // define states here
    bool has_lazy;
    int lazytype;
    ll lazyhap = 0;
    ll lazy = 0;
    node() {
        mn = 0;
        mx = 0;
        sal = 0;
        hap = 0;
        // initialize states here
        has_lazy = false;
        lazy = 0;
        lazyhap = 0;
        lazytype = -1;
    }

    void apply(int ns, int ne, ll v, ll h, int ty) {
        // update value
        // dbg(ns, ne, v, h, ty);

        if (ty == 0) {
            sal = v * (ne - ns + 1);
            hap += h * (ne - ns + 1);
            mn = mx = v;
        } else {
            sal += v * (ne - ns + 1);
            hap += h * (ne - ns + 1);
            mn += v;
            mx += v;
        }

        // update lazy
        has_lazy = 1;
        if (ty == 0) {
            lazy = v;
            lazyhap += h;
        } else {
            lazy += v;
            lazyhap += h;
        }
        if (!(lazytype == 0 && ty == 1)) {
            lazytype = ty;
        }

        // dbg(ns, ne, mx, h, hap, lazyhap);
    }
    void clear_lazy() {
        has_lazy = 0;
        lazy = 0;
        lazyhap = 0;
        lazytype = -1;
    }
};

struct SegTree {
    vector<node> tree;
    int n;
    node mrg(const node &l, const node &r) {
        node res;
        // merge nodes
        res.mn = min(l.mn, r.mn);
        res.mx = max(l.mx, r.mx);
        res.hap = l.hap + r.hap;
        res.sal = l.sal + r.sal;
        return res;
    }
    void pull(int id, int ns, int ne) {
        int l = 2 * id + 1;
        int r = l + 1;
        tree[id] = mrg(tree[l], tree[r]);
    }

    void push(int id, int ns, int ne) {
        if (tree[id].has_lazy && ns != ne) {
            int l = 2 * id + 1;
            int r = l + 1;
            int md = ns + (ne - ns) / 2;
            tree[l].apply(ns, md, tree[id].lazy, tree[id].lazyhap, tree[id].lazytype);
            tree[r].apply(md + 1, ne, tree[id].lazy, tree[id].lazyhap, tree[id].lazytype);
            tree[id].clear_lazy();
        }
    }
    template <typename M>
    void build(int id, int ns, int ne, const vector<M> &v) {
        if (ns == ne) {
            tree[id].apply(ns, ne, v[ns], 0, 0);
            return;
        }
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        build(l, ns, md, v);
        build(r, md + 1, ne, v);
        pull(id, ns, ne);
    }
    node query(int qs, int qe, int id, int ns, int ne) {
        if (qs <= ns && qe >= ne) {
            return tree[id];
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        node res;
        if (qe <= md) {
            res = query(qs, qe, l, ns, md);
        } else {
            if (qs > md) {
                res = query(qs, qe, r, md + 1, ne);
            } else {
                node rl = query(qs, qe, l, ns, md);
                node rr = query(qs, qe, r, md + 1, ne);
                res = mrg(rl, rr);
            }
        }
        pull(id, ns, ne);
        return res;
    }

    int getFirstOnCondition(int qs, int qe, int dir, int id, int ns, int ne, int k) {
        if (qs > ne || qe < ns) return -1;
        if (qs <= ns && qe >= ne) {
            // check condition on interval
        }
        if (ns == ne) {
            return ns;
        }
        push(id, ns, ne);
        int p;
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        if (dir == 0)
            p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        else
            p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
        if (p == -1) {
            if (dir == 0)
                p = getFirstOnCondition(qs, qe, dir, r, md + 1, ne, k);
            else
                p = getFirstOnCondition(qs, qe, dir, l, ns, md, k);
        }
        pull(id, ns, ne);
        return p;
    }

    template <typename... M>
    void update(int qs, int qe, int id, int ns, int ne, const M &...v) {
        if (qs > ne || qe < ns) return;
        if (qs <= ns && qe >= ne) {
            tree[id].apply(ns, ne, v...);
            return;
        }
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        update(qs, qe, l, ns, md, v...);
        update(qs, qe, r, md + 1, ne, v...);
        pull(id, ns, ne);
    }

    void update2(int qs, int qe, int id, int ns, int ne, ll v) {
        // dbg(qs, qe, ns, ne, tree[id].mx);
        if (qs > ne || qe < ns) return;
        // dbg(ns, ne, qs, qe, tree[id].mn, tree[id].mx);
        if (qs <= ns && qe >= ne && tree[id].mx < v) {
            // dbg(ns, ne, 1, tree[id].mx, tree[id].sal);
            tree[id].apply(ns, ne, v, +1, 0);
            // dbg(ns, ne, 1, tree[id].mx, tree[id].sal);
            return;
        }
        if (qs <= ns && qe >= ne && tree[id].mn > v) {
            // dbg(ns, ne, -1, tree[id].mx);
            // dbg(ns, ne, v);
            tree[id].apply(ns, ne, v, -1, 0);
            return;
        }
        if (ns == ne) return;
        push(id, ns, ne);
        int l = 2 * id + 1;
        int r = l + 1;
        int md = ns + (ne - ns) / 2;
        update2(qs, qe, l, ns, md, v);
        update2(qs, qe, r, md + 1, ne, v);
        pull(id, ns, ne);
    }

    template <typename M>
    SegTree(const vector<M> &v) {
        n = v.size();
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }
    node get(int qs, int qe) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        return query(qs, qe, 0, 0, n - 1);
    }

    node get(int p) {
        assert(p >= 0 && p <= n - 1);
        return query(p, p, 0, 0, n - 1);
    }
    template <typename... M>
    int getFirstOnCondition(int qs, int qe, int dir, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1 && dir >= 0 && dir <= 1);
        return getFirstOnCondition(qs, qe, dir, 0, 0, n - 1, v...);
    }
    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        update(qs, qe, 0, 0, n - 1, v...);
    }

    void upd2(int qs, int qe, ll v) {
        assert(qs >= 0 && qs <= qe && qe <= n - 1);
        update2(qs, qe, 0, 0, n - 1, v);
    }
};

int n, q;

vector<ll> salary;
vector<ll> sal, hap;
int t, l, r, c;

void test_case() {
    cin >> n >> q;
    salary.resize(n);
    sal.resize(n);
    hap.resize(n);
    for (int i = 0; i < n; i++) {
        cin >> salary[i];
        hap[i] = 0;
        sal[i] = salary[i];
    }
    SegTree sg = SegTree(salary);
    while (q--) {
        cin >> t >> l >> r;
        --l, --r;
        if (t == 0) {
            cin >> c;
            sg.upd2(l, r, c);
        } else if (t == 1) {
            cin >> c;

            if (c == 0) {
                sg.upd(l, r, c, 0, 1);
            } else if (c > 0) {
                sg.upd(l, r, c, 1, 1);
            } else {
                sg.upd(l, r, c, -1, 1);
            }
        } else if (t == 2) {
            ll ans = sg.get(l, r).sal;
            ll x = ans;
            ll y = (r - l + 1);
            ll g = __gcd(abs(x), abs(y));
            x /= g;
            y /= g;
            cout << x << "/" << y << endl;
        } else {
            ll ans = sg.get(l, r).hap;
            ll x = ans;
            ll y = (r - l + 1);
            ll g = __gcd(abs(x), abs(y));
            x /= g;
            y /= g;
            cout << x << "/" << y << endl;
        }
    }
}

int main() {
#ifndef ONLINE_JUDGE
    freopen("in.txt", "r", stdin);
#endif
    ios::sync_with_stdio(0);
    cin.tie(0);
    cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--) {
        test_case();
    }
    return 0;
}
