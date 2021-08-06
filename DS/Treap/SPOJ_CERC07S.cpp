//https://www.spoj.com/problems/CERC07S/
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
    node * par;
    node *chld[2];
    bool isReversed;

    node() {
        v = 0;
        p = INT_MIN;
        sz = 0;
        chld[L] = this;
        chld[R] = this;
        par = this;
        isReversed=false;
    }

    node(long long val, node *l = emp, node *r = emp) {
        p = rand();
        v = val;
        chld[L] = l;
        chld[R] = r;
        par=emp;
        isReversed=false;
        push_up();
    }

    void push_up() {
        for(int i=0;i<2;i++)
            if(chld[i]!=emp)
                chld[i]->par = this;
        sz = (chld[L]->sz) + (chld[R]->sz) + 1;
    }

    void push_down(){
        if(isReversed){
            for(int i=0;i<2;i++)
                chld[i]->reverse();
            isReversed=false;
        }
    }
    void reverse(){
        if(this==emp)
            return ;
        isReversed^=1;
        swap(chld[L], chld[R]);
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
    rt->par = emp;
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

void unlazy(node *nd){
    if(nd==emp)
        return ;
    unlazy(nd->par);
    nd->push_down();
}

const long long &getByIndex(node *rt, int ind) {
    rt->push_down();
    if (ind < rt->chld[L]->sz) {
        return getByIndex(rt->chld[L], ind);
    }
    int sm = rt->chld[L]->sz + 1;
    if (ind >= sm) {
        return getByIndex(rt->chld[R], ind - sm);
    }
    return rt->v;
}
DIR dir(node * par , node *chld){
    return (DIR)(par->chld[R]==chld);
}

int getIndex(node *cur){
    unlazy(cur);
    int res = cur->chld[L]->sz;
    while(cur->par!=emp){
        DIR d = dir(cur->par, cur);
        cur = cur->par;
        if(d==R){
            res+=(cur->chld[L]->sz+1);
        }
    }
    return res;
}

void doReverse(node *& rt, int st , int en){
    node * before, *after;
    split(rt, en+1, rt, after);
    split(rt, st, before, rt);
    rt->reverse();
    rt= mrg(mrg(before, rt), after);
}


void print(node *rt, int dpth = 0) {
    if (rt == emp)
        return;
    print(rt->chld[L], dpth + 1);
    printf("%s%2d,%2d\n", string(dpth * 5, ' ').c_str(), rt->v, rt->p);
    print(rt->chld[R], dpth + 1);
}

node * arr[int(1e5)+5];
int main() {
    FAST;
    int n,x;
    while(1){
        node *rt = emp;
        cin >> n;
        if(n==0)
            break;
        for(int i=0;i<n;i++){
            cin >> x;
            arr[i] = new node(x);
            rt = mrg(rt, arr[i]);
        }

        stable_sort(arr, arr+n, [](node *a , node *b){return a->v<b->v;});

        for(int i=0;i<n;i++){
            int j = getIndex(arr[i]);
            cout << j+1 << " ";
            doReverse(rt, i, j);
        }
        cout << endl;
    }
    return 0;
}
