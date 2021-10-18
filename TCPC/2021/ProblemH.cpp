#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;


const int N = 2e6+5;

struct node;
extern node* emp;
struct node{
    int freq;
    node *l , *r;
    node(){
        freq=0;
        l=this;
        r=this;
    }
    node(int f  , node *l = emp , node *r=emp){
        freq=f;
        this->l=l;
        this->r=r;
    }
};
node* emp = new node;

node * ins(node *root,int val , int nst=0,int nen=1e9){

    if(val>nen || val<nst){
        return root;
    }
    if(nst ==  nen){
        return new node(root->freq+1);
    }
    int md = nst+(nen-nst)/2;
    node * ln = ins(root->l, val, nst,md );
    node * rn = ins(root->r, val , md+1, nen);
    return new node(ln->freq+rn->freq, ln, rn);
}

int query(node * rtst, node * rten, int k, int nst = 0, int nen=1e9){

    if(nst==nen){
        return nst;
    }

    int lsz = rten->l->freq - rtst->l->freq;

    int md = nst+(nen-nst)/2;
    if(k<=lsz){
        return query(rtst->l, rten->l, k, nst,md);
    }else{
        return query(rtst->r, rten->r, k-lsz, md+1, nen);
    }
}

int n,q;
ll a[N], b[N], c[N];
vector<int> adj[N];
int t;
int u,v;
int ti;
node* roots[N];
int ts[N];
ll ans[N];
int sz[N];
vector<int> o;

void init(){
    for(int i=0;i<n;i++){
        adj[i].clear();
    }
    roots[0]=emp;
    ti=1;
    o.clear();
}

void dfs(int u=0, int p=-1){
    ts[u]=ti;
    sz[u]=1;
    for(auto v:adj[u]){
        if(v==p)
            continue;
        dfs(v,u);
        sz[u]+=sz[v];
    }
    int k = ((sz[u]-1)*b[u] +99)/100;
    if(sz[u]==1){
        ans[u]=a[u];
        roots[ti]=ins(roots[ti-1],ans[u]);
    }else{
        ans[u] = query(roots[ts[u]-1],roots[ti-1],k);
        ans[u] = min(ans[u]+c[u],a[u]);
        roots[ti]=ins(roots[ti-1],ans[u]);
    }

    ti++;
}




int main(){
    //freopen("input.txt", "r", stdin);
    freopen("time.in", "r", stdin);
    scanf("%d",&t);
    while(t--){
        scanf("%d",&n);
        init();
        for(int i=0;i<n;i++){
            scanf("%lld",&a[i]);
        }

        for(int i=0;i<n;i++){
            scanf("%lld",&b[i]);
        }
        for(int i=0;i<n;i++){
            scanf("%lld",&c[i]);
        }

        for(int i=0;i<n-1;i++){
            scanf("%d%d",&u,&v);
            --u;--v;
            adj[u].pb(v);
            adj[v].pb(u);
        }
        dfs();
        for(int i=0;i<n;i++){
            o.pb(ans[i]);
        }
        sort(o.begin(),o.end());
        scanf("%d",&q);
        while(q--){
            scanf("%d",&u);
            int res = upper_bound(o.begin(), o.end(),u)-o.begin();
            printf("%d\n", res);
        }

    }
    return 0;
}
