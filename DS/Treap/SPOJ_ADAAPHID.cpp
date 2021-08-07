//https://www.spoj.com/problems/ADAAPHID/
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

enum DIR{L,R};

struct node ;
extern node *emp;
struct node{
    long long sm;
    long long v;
    long long vv;
    int p,sz, freq;
    node * child[2];
    node (){
        v=0;
        sm=0;
        p=INT_MIN;
        freq=sz=0;
        child[L]=child[R]=this;
    }
    node (ll val,ll s, node *l=emp, node*r =emp){
        p=rand();
        v=val;
        sm=s;
        vv = s;
        freq=1;
        child[L]=l;
        child[R]=r;
        push_up();
    }
    void push_up(){
        sz = (child[L]->sz) + (child[R]->sz) + freq;
        sm = freq*vv + (child[L]->sm) + (child[R]->sm);
    }
};

node *emp = new node();

void split(node * rt, const ll & val, node * & ls, node* & ge){
    if(rt==emp){
        ls=ge=emp;
        return ;
    }
    if(val<rt->v){
        split(rt->child[L], val,ls,rt->child[L]);
        ge=rt;
    }else{
        split(rt->child[R], val, rt->child[R], ge);
        ls = rt;
    }
    rt->push_up();
}

node* mrg(node * ls, node * ge){
    if(ls==emp)return ge;
    if(ge==emp)return ls;
    if(ls->p > ge->p){
        ls->child[R]=mrg(ls->child[R], ge);
        ls->push_up();
        return ls;
    }
    ge->child[L]=mrg(ls, ge->child[L]);
    ge->push_up();
    return ge;

}

void insert(node *&rt, node * nd){
    if(rt==emp){
        rt=nd;
        return ;
    }
    if(rt->p < nd->p){
        split(rt, nd->v, nd->child[L], nd->child[R]);
        rt=nd;
    }else if(nd->v < rt->v){
        insert(rt->child[L], nd);
    }else{
        insert(rt->child[R], nd);
    }
    rt->push_up();
}

bool incremented(node *rt, const ll & val){
    if(rt==emp)return 0;
    bool ret=false;
    if(rt->v==val){
        rt->freq++;
        ret =true;
    }
    else if(rt->v>val)
        ret =  incremented(rt->child[L],val);
    else
        ret = incremented(rt->child[R],val);
    if(ret)rt->push_up();
    return ret;
}

void insert(node *& rt, const ll & val, const ll & s){
    if(!incremented(rt, val))
        insert(rt, new node(val,s));

}

ll query(node *rt, ll val){
    if(rt==emp)
        return 0;
    if(rt->v>val){
        return query(rt->child[L], val);
    }else{
        return rt->vv * rt->freq + rt->child[L]->sm+ query(rt->child[R],val);
    }
}
int q;
ll a,v,l=0;

int main() {
    FAST;
    node *rt = emp;
    cin >> q;
    while(q--){
        cin >> a >> v;
        a = a^l;
        v = v^l;
        insert(rt, new node(a,v));
        ll ret = query(rt, a);
        cout  << a << " "<<ret << endl;
        l=ret;
    }
    return 0;
}
