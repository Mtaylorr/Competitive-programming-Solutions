//https://www.spoj.com/problems/HORRIBLE/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define max(a, b) (a>b ? a : b)
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(2e6) + 3;
const int MOD = int(1e9) + 7;


enum DIR{L,R};

struct node ;
extern node *emp;
struct node{
    long long v;
    int sz;
    node * child[2];
    node * p;
    long long lazy;
    long long sm;
    node (){
        v=0;
        sz=0;
        child[L]=child[R]=p=this;
        sz =sm=lazy= 0;
    }
    node (ll val, node *l=emp, node*r =emp){
        child[L]=l;
        child[R]=r;
        p=emp;
        sm = val;
        v=val;
        lazy = 0;
        push_up();
    }
    void push_up(){
        if(this==emp)return;
        sz = (child[L]->sz) + (child[R]->sz) + 1;
        sm = (child[L]->sm) + (child[R]->sm) + v;
    }
    void push_down(){
        if(lazy){
            for(int i=0;i<2;i++){
                child[i]->addLazy(lazy);
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

void link(node *p , node * ch , DIR d){
    if(ch!=emp)
        ch->p=p;
    if(p!=emp){
        p->child[d]=ch;
        p->push_up();
    }
}

DIR dir(node* par , node* child){
    return (DIR)(par->child[R]==child);
}

void rotate(node * rt, DIR d){
    node * par  = rt->p;
    DIR pd = dir(par,rt);
    node * ch = rt->child[!d];
    node * gch = ch->child[d];
    link(rt, gch,(DIR)!d);
    link(ch,rt,(DIR)d);
    link(par,ch,pd);
}


node * splay(node * cur){

    while(cur->p !=emp){
        node * p= cur->p;
        DIR pd = dir(p, cur);
        if(p->p ==emp){
            rotate(p,(DIR)!pd);
            continue;
        }
        node * gp = p->p;
        DIR gd = dir(gp,p);
        if(gd==pd){
            rotate(gp,(DIR)!gd);
            rotate(p,(DIR)!pd);
        }else{
            rotate(p,(DIR)!pd);
            rotate(gp,(DIR)!gd);
        }
    }
    return cur;
}

node*  splay(node * rt, int ind){
    rt->push_down();
    int lsz = rt->child[L]->sz;
    if( lsz ==  ind)
        rt = splay(rt);
    else if(lsz > ind)
        rt = splay(rt->child[L],ind);
    else
        rt = splay(rt->child[R],ind-lsz-1);
    return rt;
}


node * mrg(node *ls , node *ge){
    if(ls==emp)return ge;
    if(ge==emp)return ls;
    ge = splay(ge,0);
    link(ge,ls,L);
    return ge;

}

void split(node *rt,int lsz, node *&ls, node *& ge){
	if(lsz == rt->sz){
		ls=rt;
		ge=emp;
		return;
	}
    rt=splay(rt, lsz);
    ls = rt->child[L];
    link(emp, ls, L);
    link(rt,emp,L);
    ge=rt;

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
    return 0;
}
