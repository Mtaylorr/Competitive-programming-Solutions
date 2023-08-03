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
#define FAST ios::sync_with_stdio(0), cin.tie(0), cout.tie(0)
void dbg_out() { cerr << endl; }
template <typename Head, typename... Tail>
void dbg_out(Head H, Tail... T) {
    cerr << ' ' << H;
    dbg_out(T...);
}
#define dbg(...) cerr << "(" << #__VA_ARGS__ << "):", dbg_out(__VA_ARGS__)
const int N = int(3e6) + 3;

mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }
typedef struct item *pitem;

int get_cnt(pitem &nd);
struct item {
    int prior, value, cnt;
    int rev;
    bool has_lazy;
    pitem l, r;
    item(int value, int prior)
        : value(value), prior(prior), cnt(1), has_lazy(0), l(NULL), r(NULL) {
        rev = 0;
    }
    void pull() { cnt = 1 + get_cnt(l) + get_cnt(r); }
    void apply(int val) {
        if (val) {
            swap(l, r);
        }
        has_lazy = 1;
        rev ^= val;
    }
    void push() {
        if (has_lazy) {
            if (l) l->apply(rev);
            if (r) r->apply(rev);
            has_lazy = 0;
            rev=0;
        }
    }
};

int get_cnt(pitem &nd) { return nd ? nd->cnt : 0; }

template <typename T>
class Treap {
   public:
    pitem root = NULL;
    void init() { clear(root); }

    // Clear the whole treap : erase all items
    void clear(pitem &p) {
        if (!p) return;
        clear(p->l);
        clear(p->r);
        delete p;
    }
    // size of the treap
    int size() { return get_cnt(root); }
    void push(pitem &p) {
        if (p) p->push();
    }

    void pull(pitem &p) {
        if (p) p->pull();
    }

    // split the treap into 2 treap where treap l have all valus <= key
    // and treap r have all values > key
    void split(pitem t, T key, pitem &l, pitem &r, int add = 0) {
        if (!t) return void(l = r = NULL);
        push(t);
        int cur_key = add + get_cnt(t->l);
        if (cur_key < key) {
            split(t->r, key, t->r, r, add + 1 + get_cnt(t->l));
            l = t;
        } else
            split(t->l, key, l, t->l, add), r = t;
        pull(l);
        pull(r);
    }

    // insert key and return the node of that key
    pitem insert_with_return(int idx, T value) {
        int prior = myRand(1e9);
        pitem it = new item(value, prior);
        insert(root, it, idx);
        return it;
    }

    void push_back(int value) {
        int prior = myRand(1e9);
        pitem it = new item(value, prior);
        mrg(root, root, it);
    }
    // insert key
    void insert(int idx, T value) {
        int prior = myRand(1e9);
        pitem it = new item(value, prior);
        insert(root, it, idx);
    }

    void insert(pitem &t, pitem it, int idx) {
        pitem t1, t2;
        split(root, idx, t1, t2);
        mrg(t1, t1, it);
        mrg(root, t1, t2);
    }

    // remove freq key items from the treap
    void erase(int idx) { erase(root, idx); }
    void erase(pitem &t, int idx) {
        pitem t1, t2, t3;
        split(root, idx, t1, t2);
        split(t2, 1, t2, t3);
        mrg(root, t1, t3);
    }

    // mrg 2 treaps such that all values in l < all values in r
    void mrg(pitem &t, pitem l, pitem r) {
        push(l);
        push(r);
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            mrg(l->r, l->r, r), t = l;
        else
            mrg(r->l, l, r->l), t = r;
        pull(t);
    }

    // remove range of values from the treap between a and b
    void erase_range(T a, T b) {
        pitem t1, t2, t3;
        split(root, b + 1, t2, t3);
        split(t2, a, t1, t2);
        mrg(root, t1, t3);
    }

    // count the number of elements in the range [a,b]
    int query(T a, T b) {
        pitem t1, t2, t3;
        split(root, b + 1, t2, t3);
        split(t2, a, t1, t2);
        // define here the query operation
        mrg(root, t1, t2);
        mrg(root, root, t3);
        // return here the value of the query
        return 0;
    }

    // count the number of elements in the range [a,b]

    template <typename... M>
    void upd(T a, T b, const M &...v) {
        pitem t1, t2, t3;
        split(root, b + 1, t2, t3);
        split(t2, a, t1, t2);
        // define here the update operation
        t2->apply(v...);
        mrg(root, t1, t2);
        mrg(root, root, t3);
    }

    void show() { show(root); }
    void show(pitem &p) {
        push(p);
        if (!p) return;
        show(p->l);
        cout << p->value << " ";
        show(p->r);
    }
};
Treap<int> treap;
int n, m;
int a;
int main() {
    FAST;
    cin >> n >> m;
    for (int i = 0; i < n; i++) {
        treap.push_back(i + 1);
    }
    while (m--) {
        int l, r;
        cin >> l >> r;
        --l, --r;
        treap.upd(l, r, 1);
    }
    treap.show();
    return 0;
}
