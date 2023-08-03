mt19937_64 rng(chrono::steady_clock::now().time_since_epoch().count());
ll myRand(ll B) { return (unsigned long long)rng() % B; }
typedef struct item *pitem;

int get_cnt(pitem &nd);
struct item {
    int prior, key, cnt, freq;
    pitem l, r;
    item(int key, int prior, int freq = 1)
        : key(key), prior(prior), freq(freq), cnt(freq), l(NULL), r(NULL) {}
    void pull() { cnt = freq + get_cnt(l) + get_cnt(r); }
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

    // split the treap into 2 treap where treap l have all valus <= key
    // and treap r have all values > key
    void split(pitem t, T key, pitem &l, pitem &r) {
        if (!t)
            l = r = NULL;
        else if (t->key <= key)
            split(t->r, key, t->r, r), l = t;
        else
            split(t->l, key, l, t->l), r = t;
        if (l) l->pull();
        if (r) r->pull();
    }

    // insert key and return the node of that key
    pitem insert_with_return(T key, int freq = 1) {
        int prior = myRand(1e9);
        pitem it = new item(key, prior, freq);
        insert(root, it);
        return it;
    }

    // insert key
    void insert(T key, int freq = 1) {
        int prior = myRand(1e9);
        pitem it = new item(key, prior, freq);
        insert(root, it);
    }

    void insert(pitem &t, pitem it) {
        if (!t)
            t = it;
        else if (it->prior > t->prior)
            split(t, it->key, it->l, it->r), t = it;
        else
            insert(t->key <= it->key ? t->r : t->l, it);
        if (t) t->pull();
    }

    // mrg 2 treaps such that all values in l < all values in r
    void mrg(pitem &t, pitem l, pitem r) {
        if (!l || !r)
            t = l ? l : r;
        else if (l->prior > r->prior)
            mrg(l->r, l->r, r), t = l;
        else
            mrg(r->l, l, r->l), t = r;
        if (t) t->pull();
    }

    // remove freq key items from the treap
    void erase(T key, int freq) { erase(root, key, freq); }
    void erase(pitem &t, T key, int freq) {
        if (!t) return;
        if (t->key == key) {
            pitem th = t;
            t->freq -= freq;
            t->cnt -= freq;
            if (t->freq > 0) return;
            mrg(t, t->l, t->r);
            delete th;
        } else
            erase(key < t->key ? t->l : t->r, key);
        if (t) t->pull();
    }
    // remove all frequencies of key in the treap
    void erase_all_freq(T key) { erase_all_freq(root, key); }
    void erase_all_freq(pitem &t, T key) { erase_range(key, key); }

    // remove range of values from the treap between a and b
    void erase_range(T a, T b) {
        if (a > b) swap(a, b);
        pitem t1, t2, t3;
        split(root, a - 1, t1, t2);
        split(t2, b, t2, t3);
        clear(t2);
        mrg(root, t1, t3);
    }

    // union of 2 treaps
    pitem unite(pitem l, pitem r) {
        if (!l || !r) return l ? l : r;
        if (l->prior < r->prior) swap(l, r);
        pitem lt, rt;
        split(r, l->key, lt, rt);
        l->l = unite(l->l, lt);
        l->r = unite(l->r, rt);
        l->pull();
        return l;
    }

    // check if an element exists or not
    bool has(T key) { return has(root, key); }
    bool has(pitem &t, T key) {
        if (!t) return 0;
        if (t->key == key) return 1;
        if (t->key < key) {
            return has(t->r, key);
        }
        return has(t->l, key);
    }

    // count the number of elements in the range [a,b]
    int count_range(T a, T b) {
        if (a > b) swap(a, b);
        pitem t1, t2, t3;
        split(root, a - 1, t1, t2);
        split(t2, b, t2, t3);
        int sz = t2->cnt;
        mrg(root, t1, t2);
        mrg(root, root, t3);
        return sz;
    }
    // count the frequency of key
    int count(T key) { return count_range(key, key); }

    // return the lowest element >= key
    T lower_bound(T key) { return lower_bound(root, key); }
    T lower_bound(pitem &t, T key) {
        if (!t) return numeric_limits<T>::max();
        if (t->key >= key) {
            return min(t->key, lower_bound(t->l, key));
        } else {
            return lower_bound(t->r, key);
        }
    }

    // return the highest element <= key
    T r_lower_bound(T key) { return r_lower_bound(root, key); }
    T r_lower_bound(pitem &t, T key) {
        if (!t) return numeric_limits<T>::min();
        if (t->key <= key) {
            return max(t->key, r_lower_bound(t->r, key));
        } else {
            return r_lower_bound(t->l, key);
        }
    }
    // return the first value after key != key
    T next_value(T key) { return lower_bound(key + 1); }
    // return the first value before key != key
    T prev_value(T key) { return r_lower_bound(root, key - 1); }

    // return the value at index idx
    T get_value_at_idx(int idx) { return get_value_at_idx(root, idx); }
    T get_value_at_idx(pitem &t, int idx) {
        if (!t) return numeric_limits<T>::max();
        int lsz = get_cnt(t->l);
        if (idx >= lsz && idx < lsz + t->freq) return t->key;
        if (idx < lsz) return get_value_at_idx(t->l, idx);
        return get_value_at_idx(t->r, idx - lsz - t->freq);
    }

    // return the number of items < key
    int count_less_than(T key) { return count_less_than(root, key); }
    int count_less_than(pitem &t, T key) {
        if (!t) return 0;
        if (t->key < key) {
            return get_cnt(t->l) + t->freq + count_less_than(t->r, key);
        }
        return count_less_than(t->l, key);
    }
};
Treap<int> treap;
