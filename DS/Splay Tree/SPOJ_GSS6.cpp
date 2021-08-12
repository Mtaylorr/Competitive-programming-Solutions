//https://www.spoj.com/problems/GSS6/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

#define mp make_pair
#define pb push_back
#define fi first
#define se second
#define all(v) (v).begin(),(v).end()
#define rall(v) (v).rbegin(),(v).rend()
#define min(a, b) (a<b ? a : b)
#define FAST ios::sync_with_stdio(0), cin.tie(0),cout.tie(0)


const int N = int(2e6) + 3;
const int MOD = int(1e9) + 7;


enum DIR{L,R};

struct data{
    ll pre, suf, sum, best;
    data(){
        sum=0;
        pre=suf=best=-1e18;
    }
    data(ll v){
        sum=pre=suf=best=v;
    }
};

data combine(const data & lhs, const data & rhs){
    data ret ;
    ret.pre = max(lhs.pre, lhs.sum+rhs.pre);
    ret.suf = max(rhs.suf, rhs.sum+lhs.suf);
    ret.best = max({lhs.best, rhs.best, lhs.suf+rhs.pre});
    ret.sum = lhs.sum+rhs.sum;
    return ret;
}

struct node ;
extern node *emp;
struct node{
    int sz;
    ll v;
    node * child[2];
    node * p;
    data d;
    node (){
        v=0;
        sz=0;
        child[L]=child[R]=p=this;
    }
    node (ll val, node *l=emp, node*r =emp): d(val){
        child[L]=l;
        child[R]=r;
        p=emp;
        v=val;
        push_up();
    }
    void push_up(){
        if(this==emp)return;
        sz = (child[L]->sz) + (child[R]->sz) + 1;
        d = combine(combine(child[L]->d, data(v)), child[R]->d);
    }
    void push_down(){
        //
    }
    void addLazy(ll lz){
        //
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


void print(node *rt,int depth=0){
    if(rt==emp){
        return ;
    }
    print(rt->child[L],depth+1);
    printf("%s%2lld,%2lld\n",string(depth*5,' ').c_str(), rt->v,rt->p->v);
    print(rt->child[R],depth+1);
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
ll getSum(node *& rt, int st , int en){
    node * before, *after;
    split(rt, en+1, rt, after);
    split(rt, st, before, rt);
    ll ret = rt->d.best;
    rt= mrg(mrg(before, rt), after);
    return ret;
}

void replace(node *& rt, int qi , ll v){
    node * before, *after;
    split(rt, qi+1, rt, after);
    split(rt, qi, before, rt);
    rt->d = data(rt->v=v);
    rt= mrg(mrg(before, rt), after);
}
void erase(node *& rt, int qi){
    node * before, *after;
    split(rt, qi+1, rt, after);
    split(rt, qi, before, rt);
    delete rt;
    rt= mrg(before, after);
}

void ins(node *& rt, int qi , ll v){
    node * before, *after;
    split(rt, qi, before, after);
    rt = new node(v);
    rt= mrg(mrg(before, rt), after);
}
int n;
int a[N];
char c;
int l,r;
int q;


int main() {
    FAST;
    cin >> n;
    node *rt = emp;
    for(int i=0;i<n;i++){
        cin >> a[i];
        rt = mrg(rt, new node(a[i]));
    }
    cin >> q;
    while(q--){
        cin >> c >> l;
        l--;
        switch(c){
            case 'I':
                cin >> r;
                ins(rt, l, r);
                break;
            case 'D':
                erase(rt, l);
                break;
            case 'R':
                cin >> r;
                replace(rt, l,r);
                break;
            case 'Q':
                cin >> r;
                r--;
                cout << getSum(rt, l,r) << endl;
                break;
        }
    }
    return 0;
}
