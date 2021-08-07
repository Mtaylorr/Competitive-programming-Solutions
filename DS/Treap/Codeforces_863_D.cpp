//https://codeforces.com/contest/863/problem/D
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


const int N = int(3e6) + 3;
const int MOD = int(1e9) + 7;


enum DIR{L,R};

struct node ;
extern node *emp;
struct node{
    long long v;
    int p,sz;
    bool reversed ;
    node * child[2];
    node  * par;
    node (){
        v=0;
        p=INT_MIN;
        sz=0;
        reversed=false;
        child[L]=child[R]=par=this;
    }
    node (ll val, node *l=emp, node*r =emp){
        p=rand();
        v=val;
        child[L]=l;
        child[R]=r;
        par = emp;
        reversed=false;
        push_up();
    }
    void push_up(){
        for(int i=0;i<2;i++){
            if(child[i]!=emp)
                child[i]->par=this;
        }
        sz = (child[L]->sz) + (child[R]->sz) + 1 ;
    }
    void push_down(){
        if(reversed){
            for(int i=0;i<2;i++){
                child[i]->reverse();
            }
            reversed=false;
        }
    }
    void reverse(){
        if(this==emp)return ;
        reversed^=1;
        swap(child[L],child[R]);
    }
};

node *emp = new node();

void split(node * rt, int lssz, node * & ls, node* & ge){
    if(rt==emp){
        ls=ge=emp;
        return ;
    }
    rt->push_down();
    int lfsz = rt->child[L]->sz;
    if(lssz<=lfsz){
        split(rt->child[L], lssz,ls,rt->child[L]);
        ge=rt;
    }else{
        split(rt->child[R], lssz - lfsz - 1, rt->child[R], ge);
        ls = rt;
    }
    rt->push_up();
    rt->par=emp;
}

node* mrg(node * ls, node * ge){
    if(ls==emp)return ge;
    if(ge==emp)return ls;
    ls->push_down();
    ge->push_down();
    if(ls->p > ge->p){
        ls->child[R]=mrg(ls->child[R], ge);
        ls->push_up();
        return ls;
    }
    ge->child[L]=mrg(ls, ge->child[L]);
    ge->push_up();
    return ge;

}

void print(node *rt,int depth=0){
    if(rt==emp){
        return ;
    }
    print(rt->child[L],depth+1);
    printf("%s%2lld,%2d\n",string(depth*5,' ').c_str(), rt->v, rt->p);
    print(rt->child[R],depth+1);
}



void unlazy(node * nd){
    if(nd==emp)return;
    unlazy(nd->par);
    nd->push_down();
}

DIR dir(node *par, node * child){
    return (DIR)(par->child[R]==child);
}

int getIndex(node * cur){
    unlazy(cur);
    int res = cur->child[L]->sz;
    while(cur->par != emp){
        DIR d = dir(cur->par, cur);
        cur=cur->par;
        if(d==R)
            res+=cur->child[L]->sz+1;

    }
    return res;
}

node * arr[int(1e5) + 5];

void doReverse(node *& rt,int st, int en){
    node * af, *bf;
    split(rt, en+1, rt, af);
    split(rt, st, bf,rt);
    rt->reverse();
    rt=mrg(bf,rt);
    rt=mrg(rt,af);
}

void doShift(node *& rt,int st, int en){
    if(en-st+1==1)
        return;
    int sz = en-st+1;
    node * af, *bf, *lef;
    split(rt, en+1, rt, af);
    split(rt, st, bf,rt);
    split(rt, sz-1,lef, rt );
    rt=mrg(rt, lef);
    rt=mrg(bf,rt);
    rt=mrg(rt,af);
}


int n,q,m;
int t,l,r;
node *rt = emp;
int a[N];
int b[N];
vector<int> v;

void calcans(node *rt){
    if(rt==emp)
        return ;
    rt->push_down();
    calcans(rt->child[L]);
    v.pb(rt->v);
    calcans(rt->child[R]);
}


int main() {
    FAST;
    cin >> n >> q>> m;
    for(int i=0;i<n;i++){
        cin >> a[i];
        rt=mrg(rt, new node(a[i]));
    }
    while(q--){
        cin >> t>> l >> r;
        l--;
        r--;
        if(t==1){
            doShift(rt, l,r);
        }else{
            doReverse(rt, l,r);
        }
    }
    calcans(rt);
    for(int i=0;i<m;i++){
        cin >> b[i];
        cout << v[b[i]-1] << " " ;
    }
    return 0;
}
