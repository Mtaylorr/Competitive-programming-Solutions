
mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }
typedef struct item *pitem;

int get_cnt(pitem &nd);
struct item {
    int prior, value, cnt;
    bool has_lazy;
    pitem l, r;
    item(int value, int prior)
        : value(value), prior(prior), cnt(1), has_lazy(0), l(NULL), r(NULL) {}
    void pull() { cnt = 1 + get_cnt(l) + get_cnt(r); }
    void apply() {}
    void apply(int val) {
        if (val) {
            swap(l, r);
        }
        has_lazy = 1;
        // update the lazy values to push
    }
    void push() {
        if (has_lazy) {
            // define here the values to push
            if (l) l->apply();
            if (r) r->apply();
            // clear here the values you pushed
            has_lazy = 0;
        }
    }
};

int get_cnt(pitem &nd) { return nd ? nd->cnt : 0; }

template <typename T>
class Treap {
   public:
    pitem root = NULL;
    void init() { clear(root); }

    void clear(pitem &p) {
        if (!p) return;
        clear(p->l);
        clear(p->r);
        delete p;
    }
    int size() { return get_cnt(root); }
    void push(pitem &p) {
        if (p) p->push();
    }

    void pull(pitem &p) {
        if (p) p->pull();
    }
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

    void erase(int idx) { erase(root, idx); }
    void erase(pitem &t, int idx) {
        pitem t1, t2, t3;
        split(root, idx, t1, t2);
        split(t2, 1, t2, t3);
        mrg(root, t1, t3);
    }

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

    void erase_range(T a, T b) {
        pitem t1, t2, t3;
        split(root, b + 1, t2, t3);
        split(t2, a, t1, t2);
        mrg(root, t1, t3);
    }

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
