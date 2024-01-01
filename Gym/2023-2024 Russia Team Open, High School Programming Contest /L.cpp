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
const int N = 1e5 + 5;
#define left(x) (2 * (x) + 1)
#define right(x) (2 * (x) + 2)
#define mid(ns, ne) ((ns) + ((ne) - (ns)) / 2)

class segtree {
   public:
    struct node {
        // define the variables
        int add = 0;
        bool valid = 0;
        int statel = 0;
        int stater = 0;
        int l0;
        int r0;
        node() {
            // define initial values
        }
        void apply(int ns, int ne, int v) {
            // define apply operation
            statel = stater = 0;
            valid = true;
            l0 = r0 = v;
        }
    };
    // state 0 : ababababab
    // state 1 : aabababab
    // state 2 : bbabababa

    node unite(const node &a, const node &b) const {
        node res;
        // define the union operation
        res.l0 = a.l0;
        res.r0 = b.r0;
        res.valid = a.valid && b.valid;
        if (res.valid) {
            if (a.r0 == 0 && b.l0 == 0) {
                if (a.statel == 0) {
                    res.statel = 1;
                } else {
                    res.statel = a.statel;
                }
                if (b.stater == 0) {
                    res.stater = 1;
                } else {
                    res.stater = b.stater;
                }
            } else if (a.r0 == 1 && b.l0 == 1) {
                if (a.stater == 2 || b.statel == 2) {
                    res.valid = 0;
                }
                if (a.statel == 0) {
                    res.statel = 2;
                } else {
                    res.statel = a.statel;
                }
                if (b.stater == 0) {
                    res.stater = 2;
                } else {
                    res.stater = b.stater;
                }
            } else if (a.r0 == 1 && b.l0 == 0) {
                if (a.stater == 2 && b.statel == 2) {
                    res.valid = 0;
                }
                res.statel = a.statel == 0 ? b.statel : a.statel;
                res.stater = b.stater == 0 ? a.stater : b.stater;
            } else if (a.r0 == 0 && b.l0 == 1) {
                if (a.stater == 2 && b.statel == 2) {
                    res.valid = 0;
                }
                res.statel = a.statel == 0 ? b.statel : a.statel;
                res.stater = b.stater == 0 ? a.stater : b.stater;
            }
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

string s;
vector<int> a;
int n;
int q;
void test_case() {
    cin >> n;
    cin >> s;
    for (int i = 0; i < n; i++) {
        a.pb(s[i] - 'a');
    }
    segtree sg = segtree(a);
    cin >> q;
    while (q--) {
        int ty;
        int l, r;
        cin >> ty;
        if (ty == 1) {
            cin >> l;
            --l;
            a[l] ^= 1;
            sg.upd(l, l, a[l]);
        } else {
            cin >> l >> r;
            --l, --r;
            auto rs = sg.get(l, r);
            bool valid = rs.valid;
            if (rs.l0 == 1 && rs.statel == 2) {
                valid = false;
            }

            if (rs.r0 == 1 && rs.stater == 2) {
                valid = false;
            }
            if (rs.r0 == 1 && rs.l0 == 1 && rs.statel == 0) {
                valid = false;
            }
            if (valid) {
                cout << "YES\n";
            } else {
                cout << "NO\n";
            }
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
