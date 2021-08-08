//https://www.codechef.com/problems/PRESTIGE
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
    ll v[2];
    ll sum[2];
    int p,sz;
    bool reversed ;
    node * child[2];
    node (){
        v[0]=v[1]=0;
        sum[0]=sum[1]=0;
        p=INT_MIN;
        sz=0;
        reversed=false;
        child[L]=child[R]=this;
    }
    node (ll val1, ll val2, node *l=emp, node*r =emp){
        p=rand();
        v[0]=sum[0]=val1;
        v[1]=sum[1]=val2;
        child[L]=l;
        child[R]=r;
        reversed=false;
        push_up();
    }
    void push_up(){
        sz = (child[L]->sz) + (child[R]->sz) + 1 ;
        for(int i=0;i<2;i++)
            sum[i] = v[i] + (child[L]->sum[i]) + (child[R]->sum[i]);
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
        swap(sum[0],sum[1]);
        swap(v[0],v[1]);
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

node * arr[int(1e5) + 5];

void doReverse(node *& rt,int st, int en){
    node * af, *bf;
    split(rt, en+1, rt, af);
    split(rt, st, bf,rt);
    rt->reverse();
    rt=mrg(bf,rt);
    rt=mrg(rt,af);
}

ll query(node *&rt, int st , int en){
    node * af, *bf;
    split(rt, en+1, rt, af);
    split(rt, st, bf,rt);
    ll ret = rt->sum[0];
    rt=mrg(bf,rt);
    rt=mrg(rt,af);
    return ret;
}

int n,m,v[2][N],l,r,k,a,b,c,d;
int curk;
int t;
int main() {
    FAST;
    cin >> n >> m;
    node *rt =emp;
    for(int i=0;i<2;i++){
        for(int j=0;j<n;j++){
            cin >> v[i][j];
        }
    }
    for(int i=0;i<n;i++){
        rt = mrg(rt, new node(v[0][i], v[1][i]));
    }
    curk=0;
    while(m--){
        cin >> t;
        switch(t){
            case 1:
                cin >> l >> r;
                doReverse(rt, --l ,--r);
                break;
            case 2 :
                cin >> k;
                curk = k-curk;
                break;
            case 3 :
                cin >> a >> b >> c >> d;
                ll sum=0;
                int d1 = min(d,curk);
                if(d1>=c){
                    sum-=query(rt, a-1, a-1+(d1-c));
                    if(d1<d){
                        sum+=query(rt, a-1+(d1-c)+1,b-1);
                    }
                }else{
                    sum+=query(rt, a-1,b-1);
                }
                cout << sum << endl;
                break;
        }
    }
    return 0;
}
