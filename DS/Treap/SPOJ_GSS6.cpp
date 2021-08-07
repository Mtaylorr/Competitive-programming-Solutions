//https://www.spoj.com/problems/GSS6

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
    ll lsum,rsum, sum, ans;
    node * child[2];
    node (){
        v=0;
        p=INT_MIN;
        sz=0;
        lsum=rsum=sum=0;
        ans=-1e15;
        child[L]=child[R]=this;
    }
    node (ll val, node *l=emp, node*r =emp){
        p=rand();
        v=val;
        child[L]=l;
        child[R]=r;
        lsum=rsum=sum=ans=val;
        push_up();
    }
    void push_up(){
        sz = (child[L]->sz) + (child[R]->sz) + 1 ;
        sum = child[L]->sum + v + child[R]->sum;
        ans = max(v,max(child[L]->ans, child[R]->ans));
        ans = max(ans, child[L]->rsum  + v + child[R]->lsum );
        ans = max(ans, sum);
        lsum = max(child[L]->lsum, child[L]->sum+max(v, v+child[R]->lsum));
        rsum = max(child[R]->rsum, child[R]->sum+max(v, v+child[L]->rsum));
    }
};

node *emp = new node();

void split(node * rt, int lssz, node * & ls, node* & ge){
    if(rt==emp){
        ls=ge=emp;
        return ;
    }
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
    if(ls->p > ge->p){
        ls->child[R]=mrg(ls->child[R], ge);
        ls->push_up();
        return ls;
    }
    ge->child[L]=mrg(ls, ge->child[L]);
    ge->push_up();
    return ge;

}


void ins(node *&rt, int st,const ll &val){
    node * af, *bf;
    split(rt, st, bf, af);
    node * nd = new node(val);
    rt=mrg(bf,nd);
    rt=mrg(rt,af);
}

void erase(node *& rt, int st){
    node * af, *bf;
    split(rt, st+1, rt, af);
    split(rt, st, bf,rt);
    delete  rt;
    rt=mrg(bf,af);
}

ll query(node *&rt, int st ,int en){
    node * af, *bf;
    split(rt, en+1, rt, af);
    split(rt, st, bf,rt);
    ll ret = rt->ans;
    rt=mrg(bf,rt);
    rt=mrg(rt,af);
    return ret;
}

void replace(node *& rt,int st,const ll &val ){
    erase(rt, st);
    ins(rt, st, val);
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
                cout << query(rt, l,r) << endl;
                break;
        }
    }
    return 0;
}
