//https://www.spoj.com/problems/TWIST/
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
    node (){
        v=0;
        p=INT_MIN;
        sz=0;
        reversed=false;
        child[L]=child[R]=this;
    }
    node (ll val, node *l=emp, node*r =emp){
        p=rand();
        v=val;
        child[L]=l;
        child[R]=r;
        reversed=false;
        push_up();
    }
    void push_up(){
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

void doReverse(node *& rt,int st, int en){
    node * af, *bf;
    split(rt, en+1, rt, af);
    split(rt, st, bf,rt);
    rt->reverse();
    rt=mrg(bf,rt);
    rt=mrg(rt,af);
}
void show(node *rt){
    if(rt==emp)
        return;
    rt->push_down();
    show(rt->child[L]);
    cout << rt->v << " ";
    show(rt->child[R]);
}

int n,m,p,q;
int main() {
    FAST;
    cin >> n >> m;
    node * rt=emp;
    for(int i=1;i<=n;i++){
        rt=mrg(rt, new node(i));
    }
    while(m--){
        cin >> p >> q;
        doReverse(rt, --p,--q);
    }
    show(rt);
    return 0;
}
