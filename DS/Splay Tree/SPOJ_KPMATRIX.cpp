//https://www.spoj.com/problems/KPMATRIX/
#pragma GCC optimize("03")
#include <bits/stdc++.h>

using namespace std;

typedef int ll;

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


struct node ;
extern node *emp;
struct node{
    int sz;
    ll v;
    int freq;
    node * child[2];
    node * p;
    node (){
        v=0;
        sz=freq=0;
        child[L]=child[R]=p=this;
    }
    node (ll val, node *l=emp, node*r =emp){
        child[L]=l;
        child[R]=r;
        p=emp;
        v=val;
        freq=1;
        push_up();
    }
    void push_up(){
        if(this==emp)return;
        sz = (child[L]->sz) + (child[R]->sz) + freq;
    }
    void push_down(){
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

node*  splay(node * rt, ll v){
    rt->push_down();
    if( rt->v ==  v)
        rt = splay(rt);
    else if(rt->v > v) {
        if (rt->child[L] == emp) {
            rt = splay(rt);
        } else
            rt = splay(rt->child[L], v);
    }
    else {
        if (rt->child[R] == emp) {
            rt = splay(rt);
        } else
            rt = splay(rt->child[R], v);
    }
    return rt;
}
node * mrg(node *ls , node *ge){
    if(ls==emp)return ge;
    if(ge==emp)return ls;
    ge = splay(ge,-1e9);
    link(ge,ls,L);
    return ge;

}

void ins(node *&rt, ll val){
    if(rt==emp){
        rt= new node(val);
        return ;
    }
    rt = splay(rt, val);
    if(rt->v==val){
        rt->freq++;
        rt->sz++;
        return ;
    }else if(val< rt->v){
        link(rt, mrg(rt->child[L], new node(val)), L);
    }else{
        link(rt, mrg(new node(val), rt->child[R]), R);
    }
}

void print(node *rt,int depth){
    if(rt==emp){
        return ;
    }
    print(rt->child[L],depth+1);
    printf("%s%2lld,%2lld\n",string(depth*5,' ').c_str(), rt->v,rt->sz);
    print(rt->child[R],depth+1);
}

void print(node *rt){
    print(rt, 0);
    puts("--------");
    fflush(stdout);
}





void split(node *rt,ll v, node *&ls, node *& ge){

    rt=splay(rt, v);
	if(rt->v<v && rt->child[R]==emp){
		ls=rt;
		ge=emp;
		return;
	}
	if(rt->v <v){
	    rt=splay(rt, rt->child[R]->v);
	}

    ls = rt->child[L];
    link(emp, ls, L);
    link(rt,emp,L);
    ge=rt;

}
int countRange(node *& rt, ll qs, ll qe){
    node * before, *after;
    split(rt, qe +1 , rt, after);
    split(rt, qs, before, rt);
    int cnt = rt->sz;
    rt = mrg(mrg(before, rt), after);
    return cnt;
}

int n,m;
int a[255][255];


int main() {
    scanf("%d%d",&n,&m);
    for(int i=0;i<n;i++){
        for(int j=1;j<=m;j++){
            scanf("%d",&a[i][j]);
            a[i][j]+=a[i][j-1];
        }
    }
    ll qs, qe;
    scanf("%d%d",&qs, &qe);
    ll ret=0;
    for(int lf=0;lf<m;lf++){
        for(int rt=lf+1;rt<=m;rt++){
            node *root = emp;
            ins(root, 0);
            ll sum=0;
            for(int i=0;i<n;i++){
                ll diff =(a[i][rt]-a[i][lf]);
                sum+=diff;
                ret+=countRange(root, sum-qe, sum-qs);
                ins(root, sum);
            }
        }
    }
    printf("%lld\n",ret);
}
