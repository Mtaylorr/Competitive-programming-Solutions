// https://codeforces.com/contest/707/problem/D
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


const int N = int(1e6) + 3;
const int MOD = int(1e9) + 7;

int n,m,q;
struct node;
extern node* emp;
struct node{
    int sum;
    node *l , *r;
    int inv;
    node(){
        sum = 0;
        inv=0;
        l=this;
        r=this;
    }
    node(int s  ,int in=0,  node *l = emp , node *r=emp){
        sum=s;
        inv=in;
        this->l=l;
        this->r=r;
    }
};
node* emp = new node;

void updlazy(node *rt, int ns, int ne){
    if(!rt->inv)
        return ;
    rt->sum = ne-ns+1-rt->sum;
    rt->inv=0;
    if(rt->l==emp){

        rt->l = new node(0, 1);
    }else{
        rt->l =  new node(rt->l->sum, rt->l->inv^1, rt->l->l, rt->l->r);
    }
    if(rt->r==emp){

        rt->r = new node(0, 1);
    }else{
        rt->r =  new node(rt->r->sum, rt->r->inv^1, rt->r->l, rt->r->r);
    }
}

node * ins(node *root,int pos, int val , int nst=1,int nen=m){
    updlazy(root, nst ,nen);
    if(pos>nen || pos<nst){
        return root;
    }

    if(nst==nen){

        return new node(min(1,max(root->sum +val, 0)));
    }
    int md = nst+(nen-nst)/2;
    node * ln = ins(root->l,pos,val, nst,md );
    node * rn = ins(root->r, pos,val, md+1, nen);
    return new node(ln->sum+rn->sum,0,ln, rn);
}

node * inv(node *rt){
    updlazy(rt, 1, m);
    return new node(rt->sum, rt->inv^1, rt->l, rt->r);
}
int getsum(node* rt){
    updlazy(rt, 1,m);
    return rt->sum;
}

vector<node*> roots;
int val[N];

int ty;
int a, b;

int pos[1002][int(1e5)+2];


ll sum[N];

int main() {
    scanf("%d%d%d",&n,&m,&q);
    roots.pb(emp);
    for(int i=1;i<=n;i++){
        pos[i][0]=0;
    }
    int ans = 0;
    for(int i=1;i<=q;i++){
        //cin >> ty;
        scanf("%d",&ty);
        if(ty==1){
            scanf("%d%d",&a,&b);
            int p = pos[a][i-1];
            roots.pb(ins(roots[p],b, 1));
            int x = getsum(roots[p]);
            int y = getsum(roots[roots.size()-1]);
            pos[a][i]=i;
            for(int j=1;j<=n;j++){
                if(j!=a){
                    pos[j][i]=pos[j][i-1];
                }
            }
            val[i]=y-x;
            ans+=val[i];
        }else if(ty==2){
            scanf("%d%d",&a,&b);
            int p = pos[a][i-1];
            roots.pb(ins(roots[p],b, -1 ));
            int x = getsum(roots[p]);
            int y = getsum(roots[roots.size()-1]);
            pos[a][i]=i;
            for(int j=1;j<=n;j++){
                if(j!=a){
                    pos[j][i]=pos[j][i-1];
                }
            }
            val[i]=y-x;
            ans+=val[i];
        }else if(ty==3){
            scanf("%d",&a);
            int p = pos[a][i-1];
            roots.pb(inv(roots[p]));
            int x = getsum(roots[p]);
            int y = getsum(roots[roots.size()-1]);
            pos[a][i]=i;
            for(int j=1;j<=n;j++){
                if(j!=a){
                    pos[j][i]=pos[j][i-1];
                }
            }
            val[i]=y-x;
            ans+=val[i];
        }else{
            scanf("%d",&a);
            ans=sum[a];
            roots.pb(emp);
            for(int j=1;j<=n;j++){
                pos[j][i]=pos[j][a];

            }
        }
        sum[i]=ans;
        printf("%d\n",ans);
    }
    return 0;
}
