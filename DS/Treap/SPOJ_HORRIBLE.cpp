// https://www.spoj.com/problems/HORRIBLE/
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
    int p, sz;
    node *chld[2];
    long long lazy;
    long long sm;

    node() {
        v = 0;
        p = INT_MIN;
        sz =sm=lazy= 0;
        chld[L] = this;
        chld[R] = this;
    }

    node(long long val, node *l = emp, node *r = emp) {
        p = rand();
        sm = val;
        v=val;
        lazy = 0;
        chld[L] = l;
        chld[R] = r;
        push_up();
    }

    void push_up() {
        sz = (chld[L]->sz) + (chld[R]->sz) + 1;
        sm = (chld[L]->sm) + (chld[R]->sm) + v;
    }

    void push_down(){
        if(lazy){
            for(int i=0;i<2;i++){
                chld[i]->addLazy(lazy);
            }
            lazy=0;
        }
    }
    void addLazy(ll lz){
        if(this==emp)
            return ;
        sm+=(lz*sz);
        lazy+=lz;
        v+=lz;
    }

};


node *emp = new node();


void split(node *rt, int lssz, node *&ls, node *&ge) {
    if (rt == emp) {
        ls = ge = emp;
        return;
    }
    rt->push_down();
    int lsz = rt->chld[L]->sz;
    if (lssz <= lsz) {
        split(rt->chld[L], lssz, ls, rt->chld[L]);
        ge = rt;
    } else {
        split(rt->chld[R], lssz-lsz-1, rt->chld[R], ge);
        ls = rt;
    }
    rt->push_up();
}

node *mrg(node *ls, node *ge) {
    if (ls == emp)return ge;
    if (ge == emp)return ls;
    ls->push_down();
    ge->push_down();
    if (ls->p > ge->p) {
        ls->chld[R] = mrg(ls->chld[R], ge);
        ls->push_up();
        return ls;
    }
    ge->chld[L] = mrg(ls, ge->chld[L]);
    ge->push_up();
    return ge;

}

void addRange(node *& rt, int st , int en, ll val){
    node * before, *after;
    split(rt, en+1, rt, after);
    split(rt, st, before, rt);
    rt->addLazy(val);

    rt= mrg(mrg(before, rt), after);
}

ll getSum(node *& rt, int st , int en){
    node * before, *after;
    split(rt, en+1, rt, after);
    split(rt, st, before, rt);
    ll ret = rt->sm;
    rt= mrg(mrg(before, rt), after);
    return ret;
}


int t;
int n,c,p,q,v,ty;
int main() {
    FAST;
    cin >> t;
    while(t--){
        cin >> n >> c;
        node *rt = emp;
        while(n--){
            rt =mrg(rt, new node(0));
        }
        while(c--){
            cin >> ty >> p >> q;
            if(ty==0){
                cin >> v;
                addRange(rt, --p, --q, v);
            }else{
                cout << getSum(rt, --p, --q)<< endl;
            }
        }
    }
    return 0;
}
