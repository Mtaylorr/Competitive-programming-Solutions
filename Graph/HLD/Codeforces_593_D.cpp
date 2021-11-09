//https://codeforces.com/problemset/problem/593/D

#include <bits/stdc++.h>

#define pb push_back
#define fi first
#define se second

typedef long long ll;

using namespace std;

const int N = 2e5  +5;
const int MOD = 1e9 + 7 ;

#define neig(u,v,e) for(int e=head[u],v;(e!=-1)&&(v=to[e], 1); e=nxt[e])

int nxt[2*N],to[2*N], head[N], edgcnt=0;
ll cst[2*N], val[N];
int  sz[N], par[N], chhead[N], heavyCh[N],dpth[N], ndcnt=0;
int n,m,u,v;
int edToNd[N] ,ndToId[N], idToNd[N];
ll x;
ll tree[4*N];


void addEdge(int u,int v, ll c){
    nxt[edgcnt]=head[u];
    head[u]=edgcnt;
    to[edgcnt]=v;
    cst[edgcnt]=c;
    edgcnt++;
}

void addbiEdge(int u, int v, ll c){
    addEdge(u,v,c);
    addEdge(v,u,c);
}

void dfs(int u=0, int p=-1, int d=0){
    dpth[u]=d;
    par[u]=p;
    heavyCh[u]=-1;
    sz[u]=1;
    int mx=-1;
    int mxv=-1;
    neig(u,v,e){
        if(v==par[u])
            continue;
        edToNd[e/2]=v;
        val[v]=cst[e];
        dfs(v,u,d+1);
        sz[u]+=sz[v];
        if(mx<sz[v]){
            mx=sz[v];
            mxv=v;
        }
    }
    if(2*mx>=sz[u]){
        heavyCh[u]=mxv;
    }
}

void HLD(int u=0, int c=0){
    if(u==-1)
        return ;
    chhead[u]=c;
    ndToId[u]=ndcnt;
    idToNd[ndcnt]=u;
    ndcnt++;
    HLD(heavyCh[u],c);
    neig(u,v,e){
        if(v==par[u] || v==heavyCh[u])
            continue;
        HLD(v,v);
    }
}

long double log18 = log(2e18);

ll mrg(ll x, ll y){
    if(x<0 || y<0)
        return -1;
    if(log(x)+log(y) >log18)
        return -1;
    return x*y;
}

void build(int id=0, int ns=0, int ne=n-1){
    if(ns==ne){
        tree[id]=val[idToNd[ns]];
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    build(l,ns, md);
    build(r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);
}
void upd(int p , ll v, int id=0, int ns=0 ,int ne=n-1){
    if(ns>p || ne<p)
        return ;
    if(ns==ne){
        tree[id]=v;
        return ;
    }
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    upd(p, v, l, ns, md);
    upd(p, v, r, md+1, ne);
    tree[id]=mrg(tree[l], tree[r]);
}

ll get(int qs, int qe, int id=0, int ns=0, int ne=n-1){
    if(qs>qe)
        return 1;
    if(ns>qe || ne<qs)
        return 1;
    if(qs<=ns && qe>=ne)
        return tree[id];
    int l = 2*id+1;
    int r = l+1;
    int md = ns+(ne-ns)/2;
    return mrg(get(qs, qe, l , ns, md), get(qs, qe, r, md+1, ne));
}

ll getans(int u, int v){
    ll res=1;

    while(chhead[u]!=chhead[v]){
        if(dpth[chhead[u]]<dpth[chhead[v]])
            swap(u,v);
        res=mrg(res, get(ndToId[chhead[u]], ndToId[u]));
        u=par[chhead[u]];
    }
    if(dpth[u]>dpth[v]){
        swap(u,v);
    }

    res=mrg(res, get(ndToId[u]+1, ndToId[v]));
    return res;
}

int ty;


int main(){
    freopen("input.txt", "r", stdin);
    memset(head,-1, sizeof(head));
    scanf("%d%d",&n,&m);
    for(int i=0;i<n-1;i++){
        scanf("%d%d%lld",&u,&v,&x);
        u--;v--;
        addbiEdge(u,v,x);
    }
    dfs();
    HLD();
    build();
    while(m--){
        scanf("%d",&ty);
        if(ty==1){
            scanf("%d%d%lld",&u,&v,&x);
            u--;v--;
            ll z = getans(u,v);
            if(z==-1){
                puts("0");
            }else{
                printf("%lld\n", x/z);
            }
        }else{
            scanf("%d%lld",&u,&x);
            u--;
            upd(ndToId[edToNd[u]],x);
        }
    }

    return 0;
}
