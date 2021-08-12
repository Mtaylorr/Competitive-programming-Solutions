//https://www.spoj.com/problems/CERC07S/

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
    bool isReversed;
    node (){
        v=0;
        sz=0;
        child[L]=child[R]=p=this;
        isReversed=false;
    }
    node (ll val, node *l=emp, node*r =emp){
        v=val;
        child[L]=l;
        child[R]=r;
        p=emp;
        isReversed=false;
        push_up();
    }
    void push_up(){
        if(this==emp)return;
        sz = (child[L]->sz) + (child[R]->sz) + 1;
    }
    void push_down(){
        if(isReversed){
            for(int i=0;i<2;i++)
                child[i]->reverse();
            isReversed=false;
        }
    }
    void reverse(){
        if(this==emp)
            return ;
        isReversed^=1;
        swap(child[L], child[R]);
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


void unlazy(node *cur){
    if(cur==emp)
        return;
    unlazy(cur->p);
    cur->push_down();
}

int getIndex(node *cur , node *&rt){
    unlazy(cur);
    rt = splay(cur);
    return rt->child[L]->sz;
}

void doReverse(node *& rt, int st , int en){
    node * before, *after;
    split(rt, en+1, rt, after);
    split(rt, st, before, rt);
    rt->reverse();
    rt= mrg(mrg(before, rt), after);
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
            int j = getIndex(arr[i], rt);
            cout << j+1 << " ";
            doReverse(rt, i, j);
        }
        cout << endl;
    }
    return 0;
}
