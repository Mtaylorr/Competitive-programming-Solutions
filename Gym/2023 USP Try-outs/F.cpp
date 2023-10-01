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

#define left(x) (2 * (x) + 1)
#define right(x) (2 * (x) + 2)
#define mid(ns, ne) ((ns) + ((ne) - (ns)) / 2)

class segtree {
   public:
    struct node {
        // define the variables
        int add = 0;
        vector<int> vals;
        node() {
            // define initial values
        }
        void apply(int ns, int ne, int v) {
            // define apply operation
            vals.clear();
            vals.pb(v);
        }
    };

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        int i = 0;
        int j = 0;
        while (i < a.vals.size() && j < b.vals.size() && res.vals.size() < 3) {
            if (a.vals[i] < b.vals[j]) {
                res.vals.pb(a.vals[i]);
                i++;
            } else {
                res.vals.pb(b.vals[j]);
                j++;
            }
        }
        while (res.vals.size() < 3 && i < a.vals.size()) {
            res.vals.pb(a.vals[i]);
            i++;
        }
        while (res.vals.size() < 3 && j < b.vals.size()) {
            res.vals.pb(b.vals[j]);
            j++;
        }
        return res;
    }

    inline void push(int id, int ns, int ne) {
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        if (tree[id].add != 0) {
            tree[l].apply(ns, md, tree[id].add);
            tree[r].apply(md + 1, ne, tree[id].add);
            tree[id].add = 0;
        }
    }

    inline void pull(int id, int l, int r) {
        tree[id] = unite(tree[l], tree[r]);
    }
    int n;
    vector<node> tree;

    void build(int id, int ns, int ne) {
        if (ns == ne) {
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        build(l, ns, md);
        build(r, md + 1, ne);
        pull(id, l, r);
    }
    template <typename M>
    void build(int id, int ns, int ne, const vector<M> &v) {
        if (ns == ne) {
            tree[id].apply(ns, ne, v[ns]);
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        build(l, ns, md, v);
        build(r, md + 1, ne, v);
        pull(id, l, r);
    }
    node get(int qs, int qe, int id, int ns, int ne) {
        if (qs <= ns && qe >= ne) {
            return tree[id];
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        push(id, ns, ne);
        node res{};
        if (qe <= md) {
            res = get(qs, qe, l, ns, md);
        } else {
            if (qs > md) {
                res = get(qs, qe, r, md + 1, ne);
            } else {
                res = unite(get(qs, qe, l, ns, md), get(qs, qe, r, md + 1, ne));
            }
        }
        pull(id, l, r);
        return res;
    }

    template <typename... M>
    void modify(int qs, int qe, int id, int ns, int ne, const M &...v) {
        if (qs <= ns && qe >= ne) {
            tree[id].apply(ns, ne, v...);
            return;
        }
        int l = left(id);
        int r = right(id);
        int md = mid(ns, ne);
        push(id, ns, ne);
        if (qs <= md) {
            modify(qs, qe, l, ns, md, v...);
        }
        if (qe > md) {
            modify(qs, qe, r, md + 1, ne, v...);
        }
        pull(id, l, r);
    }

    segtree(int _n) : n(_n) {
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1);
    }

    template <typename M>
    segtree(const vector<M> &v) {
        n = v.size();
        assert(n > 0);
        tree.resize(4 * n);
        build(0, 0, n - 1, v);
    }

    node get(int qs, int qe) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        return get(qs, qe, 0, 0, n - 1);
    }
    node get(int p) {
        assert(0 <= p && p <= n - 1);
        return get(p, p, 0, 0, n - 1);
    }

    template <typename... M>
    void upd(int qs, int qe, const M &...v) {
        assert(0 <= qs && qs <= qe && qe <= n - 1);
        modify(qs, qe, 0, 0, n - 1, v...);
    }
};

int n, q;
int a[N];
map<int, set<int> > pos;
vector<int> tmp;

int getprior(int p) {
    int v = a[p];
    set<int>::iterator it = pos[v].find(p);
    if (it == pos[v].begin()) {
        return -1;
    }
    --it;
    return *it;
}

int getnext(int p) {
    int v = a[p];
    set<int>::iterator it = pos[v].find(p);
    it++;
    if (it == pos[v].end()) return n;
    return *it;
}

void add(int p, int x) {
    pos[a[p]].erase(p);
    a[p] = x;
    pos[a[p]].insert(p);
}

void test_case() {
    cin >> n >> q;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    for (int i = n - 1; i >= 0; i--) {
        if (pos[a[i]].size() == 0) {
            tmp.pb(n);
        } else {
            tmp.pb(*pos[a[i]].begin());
        }
        pos[a[i]].insert(i);
    }
    reverse(all(tmp));
    // for (auto &u : tmp) {
    //     cout << u << " ";
    // }
    // cout << endl;
    segtree sg = segtree(tmp);

    while (q--) {
        int t;
        cin >> t;
        if (t == 1) {
            int l, r;
            cin >> l >> r;
            --l, --r;
            auto ans = sg.get(l, r);
            vector<int> vals = ans.vals;

            while (vals.size() && vals.back() > r) {
                vals.pop_back();
            }
            if (vals.size() <= 1) {
                cout << -1 << endl;
                continue;
            }
            if (vals.size() == 2) {
                int l = vals[0];
                int r = vals[1];
                if (a[l] == a[r]) {
                    cout << -1 << endl;
                } else {
                    int pl = getprior(l);
                    int pr = getprior(r);
                    cout << pl + 1 << " " << l + 1 << " " << pr + 1 << " "
                         << r + 1 << endl;
                }
            }
            if (vals.size() == 3) {
                int l = vals[0];
                int r = vals[1];
                if (a[l] == a[r]) {
                    r = vals[2];
                }
                int pl = getprior(l);
                int pr = getprior(r);
                cout << pl + 1 << " " << l + 1 << " " << pr + 1 << " " << r + 1
                     << endl;
            }
        } else {
            int p, x;
            cin >> p >> x;
            p--;
            int pp = getprior(p);
            int ap = getnext(p);
            if (pp != -1) sg.upd(pp, pp, ap);
            add(p, x);
            pp = getprior(p);
            ap = getnext(p);
            if (pp != -1) sg.upd(pp, pp, p);
            sg.upd(p, p, ap);
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
