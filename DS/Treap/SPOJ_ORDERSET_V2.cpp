//https://www.spoj.com/problems/ORDERSET/
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef unsigned long long ull;
typedef vector<ll> vl;
typedef pair<ll, ll> pl;
typedef long double ld;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(3e6) + 3;
const int MOD = int(1e9) + 7;

struct node;
extern node *emp;

enum DIR {
    L, R
};


struct node {
    long long v;
    int p, sz, freq;
    node *chld[2];

    node() {
        v = 0;
        p = INT_MIN;
        freq = 0;
        sz = 0;
        chld[L] = emp;
        chld[R] = emp;
    }

    node(long long val, node *l = emp, node *r = emp) {
        p = rand();
        v = val;
        freq = 1;
        chld[L] = l;
        chld[R] = r;
        push_up();
    }

    void push_up() {
        sz = (chld[L]->sz) + (chld[R]->sz) + freq;
    }

};


node *emp = new node();


void split(node *rt, const ll &val, node *&ls, node *&ge) {
    if (rt == emp) {
        ls = ge = emp;
        return;
    }
    if (val < rt->v) {
        split(rt->chld[L], val, ls, rt->chld[L]);
        ge = rt;
    } else {
        split(rt->chld[R], val, rt->chld[R], ge);
        ls = rt;
    }
    rt->push_up();
}

node *mrg(node *ls, node *ge) {
    if (ls == emp)return ge;
    if (ge == emp)return ls;
    if (ls->p > ge->p) {
        ls->chld[R] = mrg(ls->chld[R], ge);
        ls->push_up();
        return ls;
    }
    ge->chld[L] = mrg(ls, ge->chld[L]);
    ge->push_up();
    return ge;

}

void insert(node *&rt, node *nd) {
    if (rt == emp) {
        rt = nd;
        return;
    }
    if (rt->p < nd->p) {
        split(rt, nd->v, nd->chld[L], nd->chld[R]);
        rt = nd;
    } else if (nd->v < rt->v) {
        insert(rt->chld[L], nd);
    } else {
        insert(rt->chld[R], nd);
    }
    rt->push_up();
}


bool incremented(node *rt, const long long &val) {
    if (rt == emp)return 0;
    bool ret = false;
    if (rt->v == val) {
        rt->freq++;
        ret = true;
    } else if (rt->v > val)
        ret = incremented(rt->chld[L], val);
    else
        ret = incremented(rt->chld[R], val);
    if (ret)rt->push_up();
    return ret;
}


void insert(node *&rt, const ll &val) {
    if (!incremented(rt, val))
        insert(rt, new node(val));

}

void erase(node *&rt, const ll &val) {
    if (rt == emp)return;
    if (val < rt->v) {
        erase(rt->chld[L], val);
    } else if (val > rt->v) {
        erase(rt->chld[R], val);
    } else {
        if (rt->freq > 1) {
            rt->freq--;
        } else {

            node *tmp = mrg(rt->chld[L], rt->chld[R]);
            delete rt;

            rt = tmp;
        }
    }
    rt->push_up();
}

int getCount(node *&rt, const long long &val) {
    if (rt == emp) {
        return 0;
    }
    if (rt->v == val) {
        return rt->freq;
    } else if (rt->v < val) {
        return getCount(rt->chld[R], val);
    }
    return getCount(rt->chld[L], val);
}

const long long &getByIndex(node *rt, int ind) {
    if (ind < rt->chld[L]->sz) {
        return getByIndex(rt->chld[L], ind);
    }
    int sm = rt->chld[L]->sz + rt->freq;
    if (ind >= sm) {
        return getByIndex(rt->chld[R], ind - sm);
    }
    return rt->v;
}

int lower_bound(node *rt, const long long &val) {
    if (rt == emp)
        return 0;
    if (rt->v == val)
        return rt->chld[L]->sz;
    if (rt->v > val) {
        return lower_bound(rt->chld[L], val);
    }
    return lower_bound(rt->chld[R], val) + rt->freq + rt->chld[L]->sz;
}

void print(node *rt, int dpth = 0) {
    if (rt == emp)
        return;
    print(rt->chld[L], dpth + 1);
    printf("%s%2d,%2d\n", string(dpth * 5, ' ').c_str(), rt->v, rt->p);
    print(rt->chld[R], dpth + 1);
}

int n, val;
char c;

int main() {
    FAST;
    emp->chld[L]=emp->chld[R]=emp;
    node *rt = emp;

    cin >> n;
    while (n--) {
        cin >> c >> val;

        switch (c) {
            case 'I':
                if (getCount(rt, val) == 0) {
                    insert(rt, val);
                }

                break;
            case 'D':
                erase(rt, val);
                break;
            case 'K':
                if (val > rt->sz) {
                    puts("invalid");
                } else {
                    cout << getByIndex(rt, val - 1) << endl;
                }
                break;
            case 'C':
                cout << lower_bound(rt, val) << endl;
                break;
        }


    }
    return 0;
}
