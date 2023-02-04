const int MAXND = N * 40;

template <typename T>
class DynSegTree {
   public:
    T vals[MAXND];
    int lch[MAXND], rch[MAXND], ndcnt = 0;
    T defautl_value = 0;

    void init() { ndcnt = 0; }

    int addnode() {
        vals[ndcnt] = defautl_value;
        lch[ndcnt] = rch[ndcnt] = -1;
        return ndcnt++;
    }
    int left(int u) { return u == -1 ? -1 : lch[u]; }
    int right(int u) { return u == -1 ? -1 : rch[u]; };

    T mrg(T u, T v) { return u + v; }

    T getval(int nd) {
        if (nd != -1) {
            return vals[nd];
        }
        return defautl_value;
    }

    void pull_up(int& nd) {
        vals[nd] = mrg(getval(left(nd)), getval(right(nd)));
    }

    void apply(int old_idx, int new_idx, T v) {
        vals[new_idx] = mrg(v, vals[old_idx]);
    }
    template <typename... M>
    int modify(int cur, int p, int l, int r, bool inplace, const M&... v) {
        if (l == r) {
            int idx = cur;
            if (cur == -1 || !inplace) {
                idx = addnode();
            }
            apply(cur, idx, v...);
            return idx;
        }
        int idx = cur;
        if (cur == -1 || !inplace) {
            idx = addnode();
        }
        int md = l + (r - l) / 2;
        if (p <= md) {
            lch[idx] = modify(left(cur), p, l, md, inplace, v...);
            rch[idx] = right(cur);
        } else {
            lch[idx] = left(cur);
            rch[idx] = modify(right(cur), p, md + 1, r, inplace, v...);
        }
        pull_up(idx);
        return idx;
    }

    T get(int cur, int qs, int qe, int l, int r) {
        if (cur == -1) {
            return defautl_value;
        }
        if (qs <= l && qe >= r) {
            return getval(cur);
        }
        int md = l + (r - l) / 2;
        if (qe <= md) {
            return get(left(cur), qs, qe, l, md);
        } else if (qs > md) {
            return get(right(cur), qs, qe, md + 1, r);
        } else {
            return mrg(get(left(cur), qs, qe, l, md),
                       get(right(cur), qs, qe, md + 1, r));
        }
    }

    T getkth(int lnd, int rnd, int k, int l, int r) {
        if (l == r) {
            return l;
        }
        int lsum = getval(left(rnd)) - getval(left(lnd));
        int md = l + (r - l) / 2;
        if (lsum >= k) {
            return getkth(left(lnd), left(rnd), k, l, md);
        }
        return getkth(right(lnd), right(rnd), k - lsum, md + 1, r);
    }

    T getkthInPathTree(int ndu, int ndv, int ndlc, int vallc, int k, int l,
                       int r) {
        if (l == r) {
            return l;
        }
        int md = l + (r - l) / 2;
        int lsum = getval(left(ndu)) + getval(left(ndv)) -
                   2 * getval(left(ndlc)) + (vallc <= md);

        if (lsum >= k) {
            return getkth(left(ndu), left(ndv), left(ndlc), vallc, k, l, md);
        }
        return getkth(left(ndu), left(ndv), left(ndlc), vallc, k - lsum, md + 1,
                      r);
    }
    T getMex(int lnd, int rnd, int l, int r) {
        if (l == r) {
            return l;
        }
        int lsum = getval(left(rnd)) - getval(left(lnd));
        int md = l + (r - l) / 2;
        if (lsum != (md - l + 1)) {
            return getkth(left(lnd), left(rnd), l, md);
        }
        return getkth(right(lnd), right(rnd), md + 1, r);
    }
    T getMexInverse(int lnd, int rnd, int l, int r) {
        if (l == r) {
            return l;
        }
        int rsum = getval(right(rnd)) - getval(right(lnd));
        int md = l + (r - l) / 2;
        if (rsum == (r - md)) {
            return getkth(left(lnd), left(rnd), l, md);
        }
        return getkth(right(lnd), right(rnd), md + 1, r);
    }
};
DynSegTree<int> sg;
